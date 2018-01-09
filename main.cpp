#include <iostream>
#include <string>
#include <exception>
#include <curl/curl.h>
#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <cjson/cJSON.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/x.H>

#include "btfg_controller.h"


#include <map>
#include <memory>
#include <chrono>
#include <thread>

std::vector<char> getRestJSONData() {
	std::vector<char> http_data;
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL,"http://burst.btfg.space/pool-payments.json");
		
		
		auto cb_lambda = [](void *buffer, size_t size, size_t nmemb, void *stream) {
			auto *http_data = (std::vector<char> *) stream;
			
			int len = size * nmemb;
			char *tbuf = (char *)buffer;
			std::vector<char> t_data;
			t_data.assign(tbuf , tbuf + len);
			http_data->insert(http_data->end(),t_data.begin(), t_data.end());
			return len;				
		};
		int (*fptr)(void *, size_t, size_t, void*);
		fptr = cb_lambda;

		
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &http_data);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fptr);
		res = curl_easy_perform(curl);
		if (res == CURLE_OK) {
		}
		else {
			std::cout << res << " " << curl_easy_strerror(res) << "\n";
			
		}
		curl_easy_cleanup(curl);
	}	
	return http_data;
}

double getPendingPayment(std::vector<char> json_data, const std::string &account_id) {
	json_data.push_back('\0');
	double val = 0;
	if (json_data.size() > 0) {
		cJSON *json = cJSON_Parse(&json_data[0]);
		cJSON *pending_list_obj = cJSON_GetObjectItem(json, "pendingPaymentList");
		if (cJSON_IsObject(pending_list_obj)) {
				cJSON *item = cJSON_GetObjectItem(pending_list_obj,account_id.c_str());
				if (item != NULL) {
					val = item->valuedouble;
				}
		}
		cJSON_Delete(json);	
	}
	return val; //actually throw an error
}

int main() {
		//std::shared_ptr<BTFGController> controller = std::make_shared<BTFGController>();
		auto data = getRestJSONData();
	  std::cout << "Pending payout:" << getPendingPayment(data, "4058609956838583597");
		BTFGController::getInstance().init();

		
		
		//MWM_DECOR_MENU
		//XChangeProperty
		//PropModeReplace

	
	
	
		//_NET_WM_STATE_ABOVE

		
}