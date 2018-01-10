#pragma once
#include <vector>
#include <cjson/cJSON.h>
#include <string>


class BTFGProto {
	public:
		std::vector<char> getRestJSONData();
		double getPendingPayment(std::vector<char> json_data, const std::string &account_id);
		
		enum ERRORCODES {
			NONE = 0,
			SERVER_CONNECTION_ERROR = 1,
		  JSON_MISSING_VALUE = 2
		};
		int getLastError();
	private:
		int _errorcode = 0;
		std::string _errorstr = "";
		
};