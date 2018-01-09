#pragma once
#include "btfg_config_observer.h"
#include <vector>
#include <memory>
#include <map>
#include <string>

class BTFGConfigObservable {
	public:
		virtual ~BTFGConfigObservable(){};
		virtual void addObserver(const std::shared_ptr<BTFGConfigObserver> observer);
		virtual void notifyObservers(std::map<std::string,std::string> newconfig);
	private:
		std::vector<std::shared_ptr<BTFGConfigObserver>> _observers;
	
};