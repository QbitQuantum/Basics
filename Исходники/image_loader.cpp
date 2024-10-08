Fl_Double_Window* make_window() {
  Fl_Double_Window* w;
   {Fl_Double_Window* o = new Fl_Double_Window(560, 489);
    w = o;
    o->type(241);
     {Fl_Box* o = imbox = new Fl_Box(5, 30, 385, 455);
      o->box(FL_ENGRAVED_BOX);
      o->align(FL_ALIGN_CLIP);
      Fl_Group::current()->resizable(o);
    }
     {Fl_Box* o = filename_box = new Fl_Box(5, 5, 385, 20, "No file loaded...");
      o->box(FL_THIN_DOWN_BOX);
      o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    }
     {Fl_Group* o = new Fl_Group(395, 5, 160, 480);
      o->box(FL_THIN_DOWN_BOX);
       {Fl_Button* o = new Fl_Button(10, 10, 140, 25, "Load File");
        o->box(FL_THIN_UP_BOX);
        o->callback((Fl_Callback*)cb_Load);
      }
       {Fl_Button* o = new Fl_Button(10, 40, 140, 25, "Exit");
        o->box(FL_THIN_UP_BOX);
        o->callback((Fl_Callback*)cb_Exit);
      }
      new Fl_Divider(10, 75, 140, 15, "label");
       {Fl_Button* o = new Fl_Button(10, 100, 140, 25, "Fit To Box");
        o->type(Fl_Button::TOGGLE);
        o->box(FL_THIN_UP_BOX);
        o->callback((Fl_Callback*)cb_Fit);
      }
       {Fl_Button* o = new Fl_Button(10, 130, 140, 25, "Tile");
        o->type(Fl_Button::TOGGLE);
        o->box(FL_THIN_UP_BOX);
        o->callback((Fl_Callback*)cb_Tile);
      }
       {Fl_Choice* o = filter_choice = new Fl_Choice(10, 335, 140, 25, "Filter:"); o->begin();
        o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
        o->tooltip("Choose filter");
         {Fl_Item* o = new Fl_Item("None");
          o->user_data((void*)(0));
        }
         {Fl_Item* o = new Fl_Item("Brightness");
          o->user_data((void*)(FILTER_BRIGHTNESS));
        }
         {Fl_Item* o = new Fl_Item("Contrast");
          o->user_data((void*)(FILTER_CONTRAST));
        }
         {Fl_Item* o = new Fl_Item("Grayscale");
          o->user_data((void*)(FILTER_GRAYSCALE));
        }
         {Fl_Item* o = new Fl_Item("Gamma");
          o->user_data((void*)(FILTER_GAMMA));
        }
         {Fl_Item* o = new Fl_Item("Fore Blend");
          o->user_data((void*)(FILTER_FOREBLEND));
        }
         {Fl_Item* o = new Fl_Item("Back Blend");
          o->user_data((void*)(FILTER_BACKBLEND));
        }
        o->end();
      }
       {Fl_Box* o = new Fl_Box(10, 160, 140, 160);
        o->parent()->resizable(o);
      }
       {Fl_Value_Slider* o = Rslider = new Fl_Value_Slider(25, 380, 125, 15, "R");
        o->type(Fl_Value_Slider::HORIZONTAL);
        o->label_size(10);
        o->text_size(10);
        o->minimum(-3);
        o->maximum(3);
        o->value(1);
        o->slider_size(5);
        o->align(FL_ALIGN_LEFT);
        o->tooltip("Red value for filter");
      }
       {Fl_Value_Slider* o = Gslider = new Fl_Value_Slider(25, 400, 125, 15, "G");
        o->type(Fl_Value_Slider::HORIZONTAL);
        o->label_size(10);
        o->text_size(10);
        o->minimum(-3);
        o->maximum(3);
        o->value(1);
        o->slider_size(5);
        o->align(FL_ALIGN_LEFT);
        o->tooltip("Green value for filter");
      }
       {Fl_Value_Slider* o = Bslider = new Fl_Value_Slider(25, 420, 125, 15, "B");
        o->type(Fl_Value_Slider::HORIZONTAL);
        o->label_size(10);
        o->text_size(10);
        o->minimum(-3);
        o->maximum(3);
        o->value(1);
        o->slider_size(5);
        o->align(FL_ALIGN_LEFT);
        o->tooltip("Blue value for filter");
      }
       {Fl_Button* o = new Fl_Button(10, 445, 140, 25, "Apply");
        o->box(FL_THIN_UP_BOX);
        o->callback((Fl_Callback*)cb_Apply);
        o->tooltip("Apply current selected filter");
      }
       {Fl_Check_Button* o = lock = new Fl_Check_Button(10, 365, 140, 15, "Lock sliders");
        o->label_size(10);
        o->callback((Fl_Callback*)cb_lock);
        o->tooltip("Lock slider, RGB values taken from R slider ");
      }
      o->end();
    }
    o->end();
  }
  return  w;
}