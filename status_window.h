#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/x.H>
#include <FL/Fl_Button.H>
#include "btfg_status_label.h"


class StatusWindow:public Fl_Window {
	public:
		StatusWindow(int w, int h);
		int handle(int event) override;
		void layout();
		void refresh(BTFGUIStatusState uiState);
	private:
			static void buttonCallback(Fl_Button*, void*);
			void draw() override;
			int _mouseGrabXOffset = 0;
			int _mouseGrabYOffset = 0;
			bool _mouseGrabbing = 0;
		  int _SWIDTH ;
		  int _SHEIGHT;
			BTFGStatusLabel *pendingPaymentLabel_;
			BTFGStatusLabel *statusLabel_;
			


};

