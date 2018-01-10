#include "btfg_config_observable.h"
#include <iostream>

void BTFGConfigObservable::addObserver(const std::shared_ptr<BTFGConfigObserver> observer) {
	_observers.push_back(observer);
	std::cout << "adding an observer\n";
}

void BTFGConfigObservable::notifyObservers(std::map<std::string,std::string> newconfig) {
	std::cout << "Notify stuff1\n";
	for (auto &o:_observers) {
		std::cout << "Notify stuff\n";
		o->onConfigUpdate(newconfig);
	}
}
