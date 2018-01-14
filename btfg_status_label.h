#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <string>
#include "btfg_enums.h"


class BTFGStatusLabel:public Fl_Box {
	public:
		BTFGStatusLabel(int x, int y, int w, int h);
		BTFGUIStatusState _state;
		void updateMessage(BTFGUIStatusState state, std::string message);
		
	private:
		std::string _message;
	
};