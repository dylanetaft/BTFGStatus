#include "btfg_controller.h"
#include "config_window_factory.h"
void BTFGController::init() {
	
	ConfigWindowFactory configfactory;
	configWindow = configfactory.make_window();
	
	ConfigWindowFactory configWindowFactory;
	configWindowFactory.addObserver(shared_from_this());
	StatusWindow window(100,64);
	window.layout();
	window.show();
	std::cout << "Init\n";
	Fl::run();
}

void BTFGController::onConfigUpdate(std::map<std::string,std::string> newconfig) {
	
}

void BTFGController::showConfigWindow() {
	configWindow->show();
}