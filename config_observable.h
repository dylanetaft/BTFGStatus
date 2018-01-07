#pragma once
#include "config_observer.h"
#include <vector>
#include <memory>

class ConfigObservable {
	public:
		virtual ~ConfigObservable(){};
		virtual void addObserver(const std::shared_ptr<ConfigObserver> observer);
	private:
		std::vector<std::shared_ptr<ConfigObserver>> _observers;
};