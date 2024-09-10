ImageWindow::ImageWindow() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(930, 580, "Total Counts");
    w = o;
    o->user_data((void*)(this));
    { new Fl_Button(30, 190, 285, 30, "Save Image");
    } // Fl_Button* o
    { new Fl_Button(30, 240, 285, 30, "Reset Image");
    } // Fl_Button* o
    { new Fl_Light_Button(85, 492, 175, 40, "Analyze Pointing");
    } // Fl_Light_Button* o
    { new Fl_Value_Output(127, 384, 115, 25, "RA");
    } // Fl_Value_Output* o
    { new Fl_Value_Output(127, 419, 115, 25, "Dec");
    } // Fl_Value_Output* o
    { new Fl_Value_Output(127, 455, 115, 25, "Roll");
    } // Fl_Value_Output* o
    { Fl_Box* o = new Fl_Box(25, 359, 300, 214, "Current Pointing");
      o->box(FL_THIN_UP_FRAME);
      o->labelfont(1);
      o->align(Fl_Align(FL_ALIGN_TOP));
    } // Fl_Box* o
    { Fl_Choice* o = new Fl_Choice(456, 535, 155, 25, "Image Scaling");
      o->down_box(FL_BORDER_BOX);
    } // Fl_Choice* o
    { new Fl_Value_Output(199, 55, 115, 25, "Total Counts");
    } // Fl_Value_Output* o
    { Fl_Value_Output* o = new Fl_Value_Output(199, 97, 115, 25, "Average Count Rate");
      o->align(Fl_Align(132));
    } // Fl_Value_Output* o
    { Fl_Value_Output* o = new Fl_Value_Output(199, 140, 115, 25, "Bright Pixel Count Rate");
      o->align(Fl_Align(132));
    } // Fl_Value_Output* o
    { Fl_Box* o = new Fl_Box(23, 37, 300, 258, "Image Statistics");
      o->box(FL_THIN_UP_FRAME);
      o->labelfont(1);
      o->align(Fl_Align(FL_ALIGN_TOP));
    } // Fl_Box* o
    { new Fl_Progress(30, 540, 290, 30);
    } // Fl_Progress* o
    { Fl_Box* o = new Fl_Box(365, 40, 530, 475, "Detector Image");
      o->box(FL_THIN_UP_FRAME);
      o->labelfont(1);
      o->align(Fl_Align(FL_ALIGN_TOP));
    } // Fl_Box* o
    { Fl_Choice* o = new Fl_Choice(760, 535, 155, 25, "Pixel Arrangement");
      o->down_box(FL_BORDER_BOX);
    } // Fl_Choice* o
	plot = new plotWindow (100,100,500,500);
    o->end();
    w->show();
  } // Fl_Double_Window* o
}