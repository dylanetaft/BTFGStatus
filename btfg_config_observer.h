#pragma once
#include <map>
#include <string>

class BTFGConfigObserver {
	public:
		virtual void onConfigUpdate(std::map<std::string,std::string> newconfig) = 0;
};