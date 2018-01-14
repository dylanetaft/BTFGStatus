#include "btfg_controller.h"
#include "config_window_factory.h"
#include <chrono>
#include <cjson/cJSON.h>
#include <fstream>
#include <iostream>


void BTFGController::init() {
	ConfigWindowFactory configfactory;
	configWindow = configfactory.make_window();
	
	ConfigWindowFactory configWindowFactory;
	_statusWindow = new StatusWindow(128,128);
	Fl::lock();
	_statusWindow->layout();
	_statusWindow->show();
	std::cout << "Init\n";
	loadConfig();
	setThreadState(UPDATE);
	_netThread = std::thread(&BTFGController::netThreadCall, this);
	Fl::run();
}

void BTFGController::loadConfig() {
	
	char *data;
	std::ifstream configfile;
	configfile.open("config.cfg", std::ios::in | std::ios::binary | std::ios::ate);	
	if (configfile.is_open()) {
		std::streampos size;
		size = configfile.tellg();
		data = new char[size];
		configfile.seekg(0,std::ios::beg);
		configfile.read (data, size);
		configfile.close();
		cJSON *json = cJSON_Parse(data);
		
		if (cJSON_IsObject(json)) {
			cJSON *jsonstr = json -> child;
			while (jsonstr != NULL) {
				if (cJSON_IsString(jsonstr)) {
					std::string name = jsonstr->string;
					std::string val = jsonstr->valuestring;
					std::cout << name << ":" << val << "\n";
					//set config properties, no need to call setConfigProp
					_currentConfig[name] = val; //will make a copy of strings, no need to string::copy
					jsonstr = jsonstr->next;
				}
			}
		}
		
		cJSON_Delete(json);
		delete(data);
		//std::cout << "ACCT ID:" << _currentConfig["account_id"] << "\n";
		
	}
	else {
		//no config file exists, not really an error
	}
	
}
void BTFGController::saveConfig() {
	cJSON *json = cJSON_CreateObject();
	for (auto &prop:_currentConfig) {
		cJSON_AddStringToObject(json, prop.first.c_str(), prop.second.c_str());
	}
	std::ofstream configfile;
	configfile.open("config.cfg", std::ios::out | std::ios::binary);
	if (configfile.is_open()) {
		char *jdat = cJSON_Print(json);
		configfile << cJSON_Print(json);
		delete(jdat);
		configfile.close();
	}
	else {
		throw std::runtime_error("Error saving config file");
	}
	
	cJSON_Delete(json);
	
}
void BTFGController::refreshMinerData() {
	_netMutex.lock();
	setThreadState(UPDATE);
	_netMutex.unlock();
}

void BTFGController::refreshMinerStatusWindow(BTFGUIStatusState uiState) {
		Fl::lock();
			std::cout << "made it here 2\n";
			_statusWindow->refresh(uiState);
		Fl::unlock();
	
}
void BTFGController::setConfigProp(std::string prop, std::string val) {
	_netMutex.lock();
	_currentConfig[prop] = val;
	saveConfig();
	_netMutex.unlock();
}

void BTFGController::setStatusProp(std::string prop, std::string val) {
	std::cout << "setting status prop\n";
	_netMutex.lock();
	_currentStatus[prop] = val;
	_netMutex.unlock();
	std::cout << "setting status prop 2\n";
}

std::string BTFGController::getConfigProp(std::string prop) {
	_netMutex.lock();
	return _currentConfig[prop];
	_netMutex.unlock();
}

std::string BTFGController::getStatusProp(std::string prop) {
	_netMutex.lock();
	return _currentStatus[prop];
	_netMutex.unlock();
}

void BTFGController::setThreadState(ThreadState state) {
	_netMutex.lock();
	_netThreadState = state;
	_netMutex.unlock();
}
void BTFGController::netThreadCall() {
	for (;;) {
		_netMutex.lock();
		ThreadState mystate = _netThreadState;
		_netMutex.unlock();
		if (mystate == UPDATE) { //update from net
			std::cout << "Made it here\n";
			auto jsondata = _proto.getRestJSONData();
			std::cout << "made it here 3\n";
			double pendingVal = _proto.getPendingPayment(jsondata, _currentConfig["account_id"]);
			BTFGController &c = BTFGController::getInstance();
			c.setStatusProp("pending_payout", std::to_string(pendingVal));
			refreshMinerStatusWindow(BTFGUIStatusState::OK);
			setThreadState(SLEEP);
		}
		else if (mystate == DIE) {
			break; //exit for loop
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}


void BTFGController::showConfigWindow() {
	configWindow->show();
}