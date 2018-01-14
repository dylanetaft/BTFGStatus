// generated by Fast Light User Interface Designer (fluid) version 1.0400

#include "config_window_factory.h"
#include "btfg_controller.h"

void ConfigWindowFactory::cb_Apply_i(Fl_Button*, void*) {
  BTFGController::getInstance().setConfigProp("account_id",AccountIdInput->value());
BTFGController::getInstance().refreshMinerData();
ConfigWindow->hide();
}
void ConfigWindowFactory::cb_Apply(Fl_Button* o, void* v) {
  ((ConfigWindowFactory*)(o->parent()->user_data()))->cb_Apply_i(o,v);
}

Fl_Window* ConfigWindowFactory::make_window() {
  { ConfigWindow = new Fl_Window(305, 155);
    ConfigWindow->user_data((void*)(this));
    { Fl_Button* o = new Fl_Button(5, 120, 115, 30, "Apply");
      o->callback((Fl_Callback*)cb_Apply);
    } // Fl_Button* o
    { new Fl_Button(190, 120, 110, 30, "Cancel");
    } // Fl_Button* o
    { AccountIdInput = new Fl_Input(94, 15, 206, 24, "Wallet ID #");
    } // Fl_Input* AccountIdInput
    ConfigWindow->set_modal();
    ConfigWindow->end();
  } // Fl_Window* ConfigWindow
  return ConfigWindow;
}
