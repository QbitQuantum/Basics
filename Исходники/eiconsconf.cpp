int main (int argc, char **argv) {

  Fl_Window* w;
  fl_init_locale_support("eiconsconf", PREFIX"/share/locale");
  readIconsConfiguration();
   {Fl_Window* o = iconsConfWindow = new Fl_Window(265, 314, _("Icons settings"));
    w = o;
    o->shortcut(0xff1b);
     {Fl_Button* o = new Fl_Button(25, 280, 75, 25, _("&OK"));
      o->callback((Fl_Callback*)cb_OK);
    }
     {Fl_Button* o = new Fl_Button(185, 280, 75, 25, _("&Cancel"));
      o->callback((Fl_Callback*)cb_Cancel);
    }
     {Fl_Button* o = new Fl_Button(105, 280, 75, 25, _("&Apply"));
      o->callback((Fl_Callback*)cb_Apply);
    }
     {Fl_Tabs* o = new Fl_Tabs(3, 5, 257, 265);
      o->color((Fl_Color)0xfffffffe);
       {Fl_Group* o = new Fl_Group(1, 23, 255, 241, _("Look&&feel"));
        o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
         {Fl_Button* o = colorButton = new Fl_Button(165, 17, 60, 18, _("Background color: "));
          o->box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_colorButton);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_WRAP);
          o->color((Fl_Color) label_background);
          if(label_trans) o->deactivate();
        }
         {Fl_Button* o = colorButton1 = new Fl_Button(165, 47, 60, 18, _("Label color: "));
          o->box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_colorButton1);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_WRAP);
          o->color((Fl_Color) label_foreground);
        }
         {Fl_Value_Slider* o = maxWidthSlider = new Fl_Value_Slider(115, 95, 125, 20, _("Maximum width: "));
          o->type(Fl_Value_Slider::HORIZONTAL);
          o->minimum(48);
          o->maximum(200);
          o->step(1);
          o->value(50);
          o->slider_size(10);
          o->callback((Fl_Callback*)cb_maxWidthSlider);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_WRAP);
          o->value(label_maxwidth);
        }
         {Fl_Value_Slider* o = fontsizeSlider = new Fl_Value_Slider(115, 125, 125, 20, _("Font height: "));
          o->type(Fl_Value_Slider::HORIZONTAL|Fl_Slider::TICK_ABOVE);
          o->minimum(8);
          o->maximum(48);
          o->step(1);
          o->value(10);
          o->slider_size(10);
          o->callback((Fl_Callback*)cb_fontsizeSlider);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_WRAP);
          o->value(label_fontsize);
        }
         {Fl_Value_Slider* o = gridspaceSlider = new Fl_Value_Slider(115, 155, 125, 20, _("Grid spacing: "));
          o->type(Fl_Value_Slider::HORIZONTAL|Fl_Slider::TICK_ABOVE);
          o->minimum(1);
          o->maximum(50);
          o->step(1);
          o->value(10);
          o->slider_size(10);
          o->callback((Fl_Callback*)cb_gridspaceSlider);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_WRAP);
          o->value(label_gridspacing);
        }
         {Fl_Check_Button* o = autoArrButton = new Fl_Check_Button(25, 215, 222, 20, _("Auto arrange icons"));
          o->callback((Fl_Callback*)cb_autoArrButton);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_CLIP);
          o->value(auto_arr);
        }
         {Fl_Check_Button* o = engageButton = new Fl_Check_Button(25, 190, 222, 20, _("Engage with just one click"));
          o->callback((Fl_Callback*)cb_engageButton);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_CLIP);
          o->value(label_engage_1click);
        }
         {Fl_Check_Button* o = bg_color_check = new Fl_Check_Button(227, 17, 20, 18);
          o->callback((Fl_Callback*)cb_bg_color_check);
          o->tooltip(_("Clear this, to get transparent background."));
          if(!label_trans) o->set_value();
        }
        o->end();
      }
      o->end();
    }
    o->end();
    o->resizable(o);
  }
  w->show(argc, argv);
  return  Fl::run();
}