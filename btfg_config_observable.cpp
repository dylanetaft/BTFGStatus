#include "btfg_config_observable.h"

void BTFGConfigObservable::addObserver(const std::shared_ptr<BTFGConfigObserver> observer) {
	_observers.push_back(observer);
}

void BTFGConfigObservable::notifyObservers(std::map<std::string,std::string> newconfig) {
	for (auto &o:_observers) {
		o->onConfigUpdate(newconfig);
	}
}
