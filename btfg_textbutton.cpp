#include "btfg_textbutton.h"

BTFGTextButton::BTFGTextButton(int x, int y, int w, int h, const char *label)
: Fl_Widget(x,y,w,h,label) {
	labelcolor(fl_rgb_color(26,13,13));
}

int BTFGTextButton::handle(int event) {
	switch (event) {
		case FL_ENTER:
			labelcolor(fl_rgb_color(177,100,2));
			redraw();
			return 1;
		case FL_LEAVE:
			labelcolor(fl_rgb_color(26,13,13));
			redraw();
			return 1;
		case FL_PUSH:
			do_callback();
			return 1;
	}
	return 0;
}

void BTFGTextButton::draw() {
	//parent()->damage(FL_DAMAGE_ALL,x(),y(),w(),h());
	draw_label();
}