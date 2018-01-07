#pragma once
#include <map>
#include <string>

class ConfigObserver {
		virtual void onConfigUpdate(std::map<std::string,std::string> newconfig) = 0;
};