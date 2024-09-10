HelpPageUI::HelpPageUI() {
  Fl_Window* w;
  { Fl_Window* o = mainWindow = new Fl_Window(390, 366, "About my image filter :)");
    w = o;
    o->user_data((void*)(this));
    { Fl_Output* o = helpText = new Fl_Output(0, 25, 390, 305, "     How to ...");
      o->type(4);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Button* o = new Fl_Button(130, 335, 135, 25, "OK");
      o->callback((Fl_Callback*)cb_OK);
    }
    o->end();
  }
}