ct_image_window::ct_image_window( ) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = image_window = new Fl_Double_Window(421, 528);
    w = o;
    o->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(5, 30, 410, 410);
      o->box(FL_PLASTIC_DOWN_FRAME);
      { ct_draw_area* o = ct_image = new ct_draw_area(10, 35, 400, 400, "label");
        o->box(FL_FLAT_BOX);
        o->color(FL_DARK3);
        o->selection_color(FL_BACKGROUND_COLOR);
        o->labeltype(FL_NORMAL_LABEL);
        o->labelfont(0);
        o->labelsize(14);
        o->labelcolor(FL_BLACK);
        o->align(FL_ALIGN_CENTER);
        o->when(FL_WHEN_RELEASE);
      }
      o->end();
    }
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 100, 25);
      o->box(FL_FLAT_BOX);
      o->menu(menu_);
    }
    { Fl_Value_Slider* o = WL = new Fl_Value_Slider(40, 470, 375, 20, "WL");
      o->type(1);
      o->box(FL_PLASTIC_THIN_DOWN_BOX);
      o->minimum(-2000);
      o->maximum(7000);
      o->step(1);
      o->value(40);
      o->callback((Fl_Callback*)cb_WL);
      o->align(FL_ALIGN_LEFT);
    }
    { Fl_Value_Slider* o = WW = new Fl_Value_Slider(40, 495, 375, 20, "WW");
      o->type(1);
      o->box(FL_PLASTIC_THIN_DOWN_BOX);
      o->minimum(1);
      o->maximum(4000);
      o->step(1);
      o->value(300);
      o->callback((Fl_Callback*)cb_WW);
      o->align(FL_ALIGN_LEFT);
    }
    { Fl_Value_Slider* o = Indx = new Fl_Value_Slider(40, 445, 375, 20, "Indx");
      o->type(1);
      o->box(FL_PLASTIC_THIN_DOWN_BOX);
      o->step(1);
      o->callback((Fl_Callback*)cb_Indx);
      o->align(FL_ALIGN_LEFT);
    }
    { Fl_Progress* o = progress_bar = new Fl_Progress(115, 5, 300, 20);
      o->box(FL_PLASTIC_THIN_UP_BOX);
      o->selection_color((Fl_Color)1);
      o->hide();
    }
    o->end();
  }
}