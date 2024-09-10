BrushConfigUI::BrushConfigUI() {
  Fl_Window* w;
  { Fl_Window* o = mainWindow = new Fl_Window(234, 116, "Brush Property");
    w = o;
    o->user_data((void*)(this));
    /*{ Fl_Group* o = new Fl_Group(5, 25, 120, 55, "Brush Type:");
      o->box(FL_ENGRAVED_FRAME);
      { Fl_Round_Button* o = round = new Fl_Round_Button(9, 30, 111, 25, "Round Brush");
        o->type(102);
        o->down_box(FL_ROUND_DOWN_BOX);
        o->callback((Fl_Callback*)cb_round);
      }
      { Fl_Check_Button* o = square = new Fl_Check_Button(6, 50, 111, 28, "Square Brush");
        o->type(102);
        o->down_box(FL_DIAMOND_DOWN_BOX);
        o->callback((Fl_Callback*)cb_square);
      }
      o->end();
    }*/
    { Fl_Value_Slider* o = brushSize = new Fl_Value_Slider(70, 25, 90, 20, "Brush Size:");
      o->type(1);
      o->maximum(20);
      o->step(1);
      o->value(10);
      o->callback((Fl_Callback*)cb_brushSize);
      o->align(FL_ALIGN_TOP);
      o->when(FL_WHEN_RELEASE);
    }
    { Fl_Value_Slider* o = brushOpacity = new Fl_Value_Slider(70, 60, 90, 19, "Brush Opacity:");
      o->type(1);
      o->value(1);
      o->callback((Fl_Callback*)cb_brushOpacity);
      o->align(FL_ALIGN_TOP);
      o->when(FL_WHEN_RELEASE);
    }
    { Fl_Button* o = new Fl_Button(5, 90, 107, 25, "Clean All");
      o->callback((Fl_Callback*)cb_Clean);
    }
    { Fl_Button* o = new Fl_Button(128, 90, 102, 25, "Close");
      o->callback((Fl_Callback*)cb_Close);
    }
    o->end();
  }
}