int main (int argc, char **argv) {

  Fl_Window* w;
  fl_init_locale_support("ewmconf", PREFIX"/share/locale");
  readConfiguration();
   {Fl_Window* o = new Fl_Window(320, 370, _("Window manager settings"));
    w = o;
     {Fl_Tabs* o = new Fl_Tabs(2, 5, 318, 325);
      o->color((Fl_Color)16);
       {Fl_Group* o = new Fl_Group(1, 29, 316, 295, _("&Titlebar"));
        o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
         {Fl_Choice* o = new Fl_Choice(83, 13, 105, 22, _("Text align:")); o->begin();
          o->callback((Fl_Callback*)cb_Text);
          new Fl_Item(_("Left"));
          new Fl_Item(_("Right"));
          new Fl_Item(_("Center"));
          o->value(title_align);
          o->end();
        }
         {Fl_Value_Input* o = new Fl_Value_Input(243, 13, 60, 22, _("Height:"));
          o->minimum(10);
          o->maximum(50);
          o->step(1);
          o->value(20);
          o->callback((Fl_Callback*)cb_Height);
          o->value(title_height);
        }
         {Fl_Button* o = titlebarLabelColorButton = new Fl_Button(85, 55, 60, 20, _("Titlebar label color: "));
          o->box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_titlebarLabelColorButton);
          o->align(132);
          o->color((Fl_Color)title_normal_color_text);
        }
         {Fl_Button* o = titlebarColorButton = new Fl_Button(85, 120, 60, 20, _("Titlebar color: "));
          o->box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_titlebarColorButton);
          o->align(132);
          o->color((Fl_Color) title_normal_color);
        }
         {Fl_Group* o = new Fl_Group(153, 45, 160, 110);
           {Fl_Button* o = titlebarActiveLabelColorButton = new Fl_Button(90, 10, 60, 20, _("Titlebar active label color: "));
            o->box(FL_DOWN_BOX);
            o->callback((Fl_Callback*)cb_titlebarActiveLabelColorButton);
            o->align(132);
            o->color((Fl_Color) title_active_color_text);
          }
           {Fl_Button* o = titlebarActiveColorButton = new Fl_Button(90, 75, 60, 20, _("Titlebar active color: "));
            o->box(FL_DOWN_BOX);
            o->callback((Fl_Callback*)cb_titlebarActiveColorButton);
            o->align(132);
            o->color((Fl_Color)title_active_color);
          }
          o->end();
        }
         {Fl_Choice* o = titlebarDrawGrad = new Fl_Choice(85, 157, 163, 23, _("Box type:")); o->begin();
          o->callback((Fl_Callback*)cb_titlebarDrawGrad);
          o->align(132);
          new Fl_Item(_("Flat"));
          new Fl_Item(_("Horizontal shade"));
          new Fl_Item(_("Thin down"));
          new Fl_Item(_("Up box"));
          new Fl_Item(_("Down box"));
          new Fl_Item(_("Plastic"));
          o->value(title_draw_grad);
          o->end();
        }
         {Fl_Check_Button* o = useThemeButton = new Fl_Check_Button(8, 220, 300, 20, _("&Use theme"));
          o->callback((Fl_Callback*)cb_useThemeButton);
          o->value(use_theme);
        }
         {Fl_Input* o = themePathInput = new Fl_Input(65, 247, 210, 23, _("Path:"));
          o->callback((Fl_Callback*)cb_themePathInput);
          o->deactivate();
          themePathInput->value(theme_path);
        }
         {Fl_Button* o = browse_btn = new Fl_Button(280, 247, 25, 23, _("..."));
          o->callback((Fl_Callback*)cb_browse_btn);
          o->deactivate();
        }
         {Fl_Divider* o = new Fl_Divider(8, 190, 300, 25, _("label"));
          o->color((Fl_Color)16);
        }
         {Fl_Divider* o = new Fl_Divider(8, 85, 297, 25, _("label"));
          o->color((Fl_Color)16);
        }
        o->end();
      }
       {Fl_Group* o = new Fl_Group(3, 20, 310, 305, _("&Resizing"));
        o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
        o->hide();
         {Fl_Check_Button* o = animateButton = new Fl_Check_Button(10, 10, 300, 20, _("Animate size changes"));
          o->value(1);
          o->callback((Fl_Callback*)cb_animateButton);
          o->value(animate);
        }
         {Fl_Value_Slider* o = animateSlider = new Fl_Value_Slider(70, 35, 235, 20, _("Speed:"));
          o->type(Fl_Value_Slider::HORIZONTAL|Fl_Slider::TICK_ABOVE);
          o->box(FL_DOWN_BOX);
          o->text_size(10);
          o->minimum(5);
          o->maximum(20);
          o->step(2);
          o->value(14);
          o->slider_size(8);
          o->callback((Fl_Callback*)cb_animateSlider);
          o->align(FL_ALIGN_LEFT);
          o->value(animate_speed);
          if(animate) o->activate(); else o->deactivate();
        }
        new Fl_Divider(0, 60, 300, 25, _("label"));
         {Fl_Check_Button* o = opaqueResize = new Fl_Check_Button(10, 85, 290, 20, _("Show window content while resizing"));
          o->callback((Fl_Callback*)cb_opaqueResize);
          o->value(opaque_resize);
        }
        o->end();
      }
      o->end();
    }
     {Fl_Button* o = new Fl_Button(67, 337, 80, 25, _("&OK"));
      o->shortcut(0xff0d);
      o->callback((Fl_Callback*)cb_OK);
    }
     {Fl_Button* o = new Fl_Button(152, 337, 80, 25, _("&Apply"));
      o->callback((Fl_Callback*)cb_Apply);
    }
     {Fl_Button* o = new Fl_Button(237, 337, 80, 25, _("&Cancel"));
      o->shortcut(0xff1b);
      o->callback((Fl_Callback*)cb_Cancel);
    }
    o->end();
  }
  useThemeButton->do_callback();
  w->show(argc, argv);
  return  Fl::run();
}