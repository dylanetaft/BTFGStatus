#include "config_observable.h"

void ConfigObservable::addObserver(const std::shared_ptr<ConfigObserver> observer) {
	_observers.push_back(observer);
}
