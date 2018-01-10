#include "btfg_controller.h"
#include "config_window_factory.h"
#include <chrono>

void BTFGController::init() {
	
	ConfigWindowFactory configfactory;
	configWindow = configfactory.make_window();
	
	ConfigWindowFactory configWindowFactory;
	StatusWindow window(100,64);
	Fl::lock();
	window.layout();
	window.show();
	std::cout << "Init\n";
	_netThreadState = UPDATE;
	_netThread = std::thread(&BTFGController::netThreadCall, this);
	Fl::run();
}

void BTFGController::setConfigProp(std::string prop, std::string val) {
	_netMutex.lock();
	_currentConfig[prop] = val;
	_netThreadState = UPDATE;
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
			auto jsondata = _proto.getRestJSONData();
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