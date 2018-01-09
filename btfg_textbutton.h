#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
class BTFGTextButton:public Fl_Widget {
	public:
		BTFGTextButton(int x, int y, int w, int h, const char *label);
		int handle(int event) override;
	protected:
		void draw();
};