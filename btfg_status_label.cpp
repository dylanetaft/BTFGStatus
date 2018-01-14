#include "btfg_status_label.h"
#include <iostream>

BTFGStatusLabel::BTFGStatusLabel(int x, int y, int w, int h)
: Fl_Box(x,y,w,h) {
	align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
}

void BTFGStatusLabel::updateMessage(BTFGUIStatusState state, std::string message) {
	_state = state;
	_message = message;
	if (_state == BTFGUIStatusState::LOADING) { //yellow
		labelcolor(fl_rgb_color(255,255,0));
		label(_message.c_str());
	}
	
	if (_state == BTFGUIStatusState::OK) { //green
		labelcolor(fl_rgb_color(0,255,0));
		label(_message.c_str());
	}	
}