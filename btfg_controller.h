#pragma once
#include <map>
#include <string>
#include <memory>
#include "btfg_config_observer.h"
#include "config_window_factory.h"
#include "status_window.h"
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "btfg_proto.h"
#include <thread>
#include <mutex>


class BTFGController:
 public std::enable_shared_from_this<BTFGController> {
	public:
		static BTFGController &getInstance() {
			static BTFGController *rptr = new BTFGController();
			static std::shared_ptr<BTFGController> instance(rptr);
			return *rptr;
		}
		void init();
		void showConfigWindow();
		void setConfigProp(std::string prop, std::string val);
		std::string getConfigProp(std::string prop);
	private:
		std::map<std::string,std::string> _currentConfig;
		Fl_Window *configWindow;
		BTFGProto _proto;
		BTFGController(){};
		void netThreadCall();
		std::thread _netThread;
		std::mutex _netMutex;
		enum ThreadState {SLEEP, UPDATE, DIE} _netThreadState;
		void saveConfig();
		void loadConfig();
};

