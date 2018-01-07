#include "status_window.h"
#include <FL/Enumerations.H> 
#include <FL/fl_draw.H>


StatusWindow::StatusWindow(int w, int h)
:
_SWIDTH(w)
,_SHEIGHT(h)
,_windowHandleBox(FL_BORDER_BOX,0,0,w,16,"BTFG Status")
,Fl_Window(w,h,"Hello") {
	layout();
}

void StatusWindow::layout() {
	clear_border();
	clear_flag(Fl_Widget::SKIP_TASKBAR);	
	color(FL_DARK3);
	_windowHandleBox.labelcolor(fl_rgb_color(177,100,2));
	_windowHandleBox.color(fl_rgb_color(26,13,13));
	
}
int StatusWindow::handle(int event) {
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
	}
	return 0;
}