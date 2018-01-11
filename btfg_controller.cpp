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
	StatusWindow window(100,64);
	Fl::lock();
	window.layout();
	window.show();
	std::cout << "Init\n";
	loadConfig();
	_netThreadState = UPDATE;
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
//void setConfigProps for multiple TODO
void BTFGController::setConfigProp(std::string prop, std::string val) {
	_netMutex.lock();
	_currentConfig[prop] = val;
	_netThreadState = UPDATE;
	saveConfig();
	_netMutex.unlock();
}
std::string BTFGController::getConfigProp(std::string prop) {
	_netMutex.lock();
	return _currentConfig[prop];
	_netMutex.unlock();
}

void BTFGController::netThreadCall() {
	for (;;) {
		_netMutex.lock();
		if (_netThreadState == UPDATE) { //update from net
			_netMutex.unlock();
			auto jsondata = _proto.getRestJSONData();
			_netMutex.lock();
			double pendingVal = _proto.getPendingPayment(jsondata, _currentConfig["account_id"]);
			std::cout << pendingVal << "\n";
			_netThreadState = SLEEP;
			_netMutex.unlock();
		}
		else if (_netThreadState == DIE) {
			_netMutex.unlock();
			break; //exit for loop
		}
		_netMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}


void BTFGController::showConfigWindow() {
	configWindow->show();
}