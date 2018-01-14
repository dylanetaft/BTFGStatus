#pragma once
#include <map>
#include <string>
#include <memory>
#include "config_window_factory.h"
#include "status_window.h"
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "btfg_proto.h"
#include <thread>
#include <mutex>
#include "btfg_enums.h"

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
		void setStatusProp(std::string prop, std::string val);
		std::string getStatusProp(std::string prop);
		void refreshMinerData();
		void refreshMinerStatusWindow(BTFGUIStatusState uiState);
	private:
		std::map<std::string,std::string> _currentConfig;
		std::map<std::string,std::string> _currentStatus;
		Fl_Window *configWindow;
		StatusWindow *_statusWindow;
		BTFGProto _proto;
		BTFGController(){};
		enum ThreadState {SLEEP, UPDATE, DIE} _netThreadState;
		void netThreadCall();
		void setThreadState(ThreadState state);
		
		std::thread _netThread;
		std::mutex _netMutex;
		void saveConfig();
		void loadConfig();
};

