#include "status_window.h"
#include <FL/Enumerations.H> 
#include <FL/fl_draw.H>

#include <FL/Fl_Box.H>
#include <iostream>
#include "btfg_controller.h"
#include "btfg_textbutton.h"

StatusWindow::StatusWindow(int w, int h)
:
_SWIDTH(w)
,_SHEIGHT(h)
,Fl_Window(w,h,"Hello") {
}


void StatusWindow::buttonCallback(Fl_Button *obj, void *data) {
	StatusWindow *ptr = (StatusWindow *)obj->parent()->user_data();
	std::string name = (char *)data;
	if (name == "config_button") {
			BTFGController::getInstance().showConfigWindow();
	}
		
	
}

void StatusWindow::layout() {
	begin();
	Fl_Box *window_handle_box = new Fl_Box(FL_BORDER_BOX,0,0,_SWIDTH,16,"BTFG Status");
	clear_border();
	skip_taskbar(0);
	window_handle_box->labelcolor(fl_rgb_color(177,100,2));
	window_handle_box->color(fl_rgb_color(26,13,13));
	user_data((void*)(this));
	BTFGTextButton *button = new BTFGTextButton(4, _SHEIGHT-24, 64, 16, "Config");
	button->callback((Fl_Callback *)buttonCallback,(void *)"config_button");
	//button->box(FL_FLAT_BOX);
	std::cout << "layout\n";
	end();
	
}
void StatusWindow::draw() {
	fl_rectf(0, 0, w(), h(), FL_DARK3);
	draw_children();
}
int StatusWindow::handle(int event) {
	if (Fl_Group::handle(event)) return 1;
	switch (event) {
	case FL_DRAG:
		position(Fl::event_x_root() - _mouseGrabXOffset,Fl::event_y_root() - _mouseGrabYOffset);
		return 1;
	case FL_PUSH:
		if (!_mouseGrabbing) {
			_mouseGrabbing = 1;
			_mouseGrabXOffset = Fl::event_x();
			_mouseGrabYOffset = Fl::event_y();
		}
		return 1;
	case FL_RELEASE:
		_mouseGrabbing = 0;
		return 1;
	}
	return 0;
}


