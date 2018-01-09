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


class BTFGController:public BTFGConfigObserver,
 public std::enable_shared_from_this<BTFGController> {
	public:
		static BTFGController &getInstance() {
			static BTFGController *rptr = new BTFGController();
			static std::shared_ptr<BTFGController> instance(rptr);
			return *rptr;
		}
		void init();
		void onConfigUpdate(std::map<std::string,std::string> newconfig) override;
		void showConfigWindow();
		
	private:
		Fl_Window *configWindow;
		BTFGController(){};
};

