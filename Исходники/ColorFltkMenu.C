void ColorFltkMenu::make_window() {
  size(400, 305);
  { 
    { Fl_Hold_Browser* o = categorybrowser = new Fl_Hold_Browser(10, 55, 125, 100, "Categories");
      o->align(FL_ALIGN_TOP);
      o->color(VMDMENU_BROWSER_BG, VMDMENU_BROWSER_SEL);
      o->callback(category_cb, this);
      VMDFLTKTOOLTIP(o, "Select color category then name to set active color")
    }
    { Fl_Hold_Browser* o = itembrowser = new Fl_Hold_Browser(140, 55, 120, 100, "Names");
      o->align(FL_ALIGN_TOP);
      o->color(VMDMENU_BROWSER_BG, VMDMENU_BROWSER_SEL);
      o->callback(item_cb, this);
      VMDFLTKTOOLTIP(o, "Select color category then name to set active color")
    }
    { Fl_Hold_Browser* o = colorbrowser = new Fl_Hold_Browser(265, 55, 125, 100, "Colors");
      o->align(FL_ALIGN_TOP);
      o->color(VMDMENU_BROWSER_BG, VMDMENU_BROWSER_SEL);
      o->callback(color_cb, this);
      VMDFLTKTOOLTIP(o, "Select color category then name to set active color")
    }
    new Fl_Box(10, 10, 190, 25, "Assign colors to categories:");
    { Fl_Tabs* o = new Fl_Tabs(0, 165, 400, 150);
#if defined(VMDMENU_WINDOW)
      o->color(VMDMENU_WINDOW, FL_GRAY);
      o->selection_color(VMDMENU_WINDOW);
#endif

      { Fl_Group* o = new Fl_Group(0, 185, 400, 125, "Color Definitions");
#if defined(VMDMENU_WINDOW)
        o->color(VMDMENU_WINDOW, FL_GRAY);
        o->selection_color(VMDMENU_WINDOW);
#endif
        { Fl_Hold_Browser* o = colordefbrowser = new Fl_Hold_Browser(15, 195, 135, 100);
          o->labeltype(FL_NO_LABEL);
          o->color(VMDMENU_BROWSER_BG, VMDMENU_BROWSER_SEL);
          o->callback(colordef_cb, this);
          VMDFLTKTOOLTIP(o, "Select color name to adjust RGB color definition")
        }
        { Fl_Value_Slider* o = redscale = new Fl_Value_Slider(160, 195, 225, 20);
          o->type(FL_HORIZONTAL);
          o->color(VMDMENU_COLOR_RSLIDER);
          o->callback(rgb_cb, this);
          VMDFLTKTOOLTIP(o, "Adjust slider to change RGB color definition")
        }
        { Fl_Value_Slider* o = greenscale = new Fl_Value_Slider(160, 215, 225, 20);
          o->type(FL_HORIZONTAL);
          o->color(VMDMENU_COLOR_GSLIDER);
          o->callback(rgb_cb, this);
          VMDFLTKTOOLTIP(o, "Adjust slider to change RGB color definition")
        }
        { Fl_Value_Slider* o = bluescale = new Fl_Value_Slider(160, 235, 225, 20);
          o->type(FL_HORIZONTAL);
          o->color(VMDMENU_COLOR_BSLIDER);
          o->callback(rgb_cb, this);
          VMDFLTKTOOLTIP(o, "Adjust slider to change RGB color definition")
        }
        { Fl_Button* o = grayscalebutton = new Fl_Button(165, 265, 85, 25, "Grayscale");
          o->type(FL_TOGGLE_BUTTON);
#if defined(VMDMENU_WINDOW)
          o->color(VMDMENU_WINDOW, FL_GRAY);
#endif
          VMDFLTKTOOLTIP(o, "Lock sliders for grayscale color")
        }
        defaultbutton = new Fl_Button(290, 265, 85, 25, "Default");
#if defined(VMDMENU_WINDOW)
        defaultbutton->color(VMDMENU_WINDOW, FL_GRAY);
#endif
        defaultbutton->callback(default_cb, this);
        VMDFLTKTOOLTIP(defaultbutton, "Reset to original RGB color")
        o->end();
      }
      { Fl_Group* o = new Fl_Group(0, 185, 400, 125, "Color Scale");
#if defined(VMDMENU_WINDOW)
        o->color(VMDMENU_WINDOW, FL_GRAY);
        o->selection_color(VMDMENU_WINDOW);
#endif
        o->hide();
        { Fl_Choice* o = scalemethod = new Fl_Choice(15, 220, 80, 25, "Method");
          o->color(VMDMENU_CHOOSER_BG, VMDMENU_CHOOSER_SEL);
          o->down_box(FL_BORDER_BOX);
          o->align(FL_ALIGN_TOP);
          o->callback(scalemethod_cb, this);
        }
        offsetvalue = new Fl_Value_Slider(160, 205, 180, 20, "Offset");
        offsetvalue->type(FL_HORIZONTAL);
        offsetvalue->color(VMDMENU_SLIDER_BG, VMDMENU_SLIDER_FG);
        offsetvalue->align(FL_ALIGN_LEFT);
        offsetvalue->range(-1.0, 1.0);
        offsetvalue->callback(scalesettings_cb, this);
        { Fl_Value_Slider* o = midpointvalue = new Fl_Value_Slider(160, 235, 180, 20, "Midpoint");
          o->type(FL_HORIZONTAL);
          midpointvalue->align(FL_ALIGN_LEFT);
          midpointvalue->color(VMDMENU_SLIDER_BG, VMDMENU_SLIDER_FG);
          o->range(0.0, 1.0);
          o->callback(scalesettings_cb, this);
        }
        image = new ColorscaleImage(10, 265, 380, 25, app);
        o->end();
      }
      o->end();
    }
    end();
  }
}