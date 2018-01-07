#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/x.H>



class StatusWindow:public Fl_Window {
	public:
		StatusWindow(int w, int h);
		int handle(int event) override;
		void layout();
	private:
			int _mouseGrabXOffset = 0;
			int _mouseGrabYOffset = 0;
			bool _mouseGrabbing = 0;
			
		  int _SWIDTH ;
		  int _SHEIGHT;
			
			Fl_Box _windowHandleBox;
};

