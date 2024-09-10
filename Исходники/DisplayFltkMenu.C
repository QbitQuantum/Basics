void DisplayFltkMenu::make_window() {
  size(235, 445);
  { 
    { Fl_Counter* o = nearclip = new Fl_Counter(105, 25, 110, 25, "Near Clip");
      o->align(FL_ALIGN_LEFT);
      o->range(0.01, 1000.0);
      o->step(0.05);
      o->lstep(0.5);
      o->precision(2);
      o->callback(nearclip_cb, app);
      VMDFLTKTOOLTIP(o, "Set near clipping plane (OpenGL display only)")
    }
    { Fl_Counter* o = farclip = new Fl_Counter(105, 50, 110, 25, "Far Clip");
      o->align(FL_ALIGN_LEFT);
      o->range(0.01, 1000.0);
      o->step(0.05);
      o->lstep(0.5);
      o->precision(2);
      o->callback(farclip_cb, app);
      VMDFLTKTOOLTIP(o, "Set far clipping plane (OpenGL display only)")
    }
    { Fl_Counter* o = eyesep = new Fl_Counter(105, 75, 110, 25, "Eye Sep");
      o->align(FL_ALIGN_LEFT);
      o->range(0.0, 100.0);
      o->step(0.01);
      o->lstep(0.1);
      o->precision(2);
      o->callback(eyesep_cb, app);
      VMDFLTKTOOLTIP(o, "Set stereo eye separation")
    }
    { Fl_Counter* o = focal = new Fl_Counter(105, 100, 110, 25, "Focal Length");
      o->align(FL_ALIGN_LEFT);
      o->range(0.01, 1000.0);
      o->step(0.05);
      o->lstep(0.5);
      o->precision(2);
      o->callback(focal_cb, app);
      VMDFLTKTOOLTIP(o, "Set stereo focal point")
    }
    { Fl_Counter* o = screenh = new Fl_Counter(105, 135, 110, 25, "Screen Hgt");
      o->align(FL_ALIGN_LEFT);
      o->range(0.0, 100000.0);
      o->step(0.1);
      o->lstep(1.0);
      o->precision(1);
      o->callback(screenh_cb, app);
      VMDFLTKTOOLTIP(o, "Set viewing frustum height")
    }
    { Fl_Counter* o = screend = new Fl_Counter(105, 160, 110, 25, "Screen Dist");
      o->align(FL_ALIGN_LEFT);
      o->range(-100000.0, 100000.0);
      o->step(0.1);
      o->lstep(1.0);
      o->precision(1);
      o->callback(screend_cb, app);
      VMDFLTKTOOLTIP(o, "Set viewing frustum distance")
    }

    { Fl_Choice* o = cuemode = new Fl_Choice(105, 195, 110, 25, "Cue Mode");
      o->color(VMDMENU_CHOOSER_BG);
      o->selection_color(VMDMENU_CHOOSER_SEL);
      o->box(FL_THIN_UP_BOX);
      o->align(FL_ALIGN_LEFT);
      o->callback(cuemode_cb, app);
      VMDFLTKTOOLTIP(o, "Set depth cueing mode")
      for (int m=0; m<app->display->num_cue_modes(); m++)
        cuemode->add(app->display->cue_mode_name(m));
    }
    { Fl_Counter* o = cuestart = new Fl_Counter(105, 220, 110, 25, "Cue Start");
      o->align(FL_ALIGN_LEFT);
      o->range(0.001, 1000.0);
      o->step(0.05);
      o->lstep(0.25);
      o->precision(2);
      o->callback(cuestart_cb, app);
      VMDFLTKTOOLTIP(o, "Set linear depth cueing starting distance")
    }
    { Fl_Counter* o = cueend = new Fl_Counter(105, 245, 110, 25, "Cue End");
      o->align(FL_ALIGN_LEFT);
      o->range(0.001, 1000.0);
      o->step(0.05);
      o->lstep(0.25);
      o->precision(2);
      o->callback(cueend_cb, app);
      VMDFLTKTOOLTIP(o, "Set linear depth cueing end distance")
    }
    { Fl_Counter* o = cuedensity = new Fl_Counter(105, 270, 110, 25, "Cue Density");
      o->align(FL_ALIGN_LEFT);
      o->range(0.001, 1000.0);
      o->step(0.05);
      o->lstep(0.1);
      o->precision(2);
      o->callback(cuedensity_cb, app);
      VMDFLTKTOOLTIP(o, "Set exponential depth cueing density")
    }

    new Fl_Box(35, 305, 170, 25, "External Renderer Options");
    { Fl_Choice* o = shadowmode = new Fl_Choice(105, 330, 110, 25, "Shadows");
      o->color(VMDMENU_CHOOSER_BG);
      o->selection_color(VMDMENU_CHOOSER_SEL);
      o->box(FL_THIN_UP_BOX);
      o->align(FL_ALIGN_LEFT);
      o->callback(shadowmode_cb, app);
      VMDFLTKTOOLTIP(o, "Enable shadows in external renderers")
      shadowmode->add("Off");
      shadowmode->add("On");
    }
    { Fl_Choice* o = aomode = new Fl_Choice(105, 355, 110, 25, "Amb. Occl.");
      o->color(VMDMENU_CHOOSER_BG);
      o->selection_color(VMDMENU_CHOOSER_SEL);
      o->box(FL_THIN_UP_BOX);
      o->align(FL_ALIGN_LEFT);
      o->callback(aomode_cb, app);
      VMDFLTKTOOLTIP(o, "Enable ambient occlusion lighting in external renderers")
      aomode->add("Off");
      aomode->add("On");
    }
    { Fl_Counter* o = aoambient = new Fl_Counter(105, 380, 110, 25, "AO Ambient");
      o->align(FL_ALIGN_LEFT);
      o->range(0.0, 1.0);
      o->step(0.01);
      o->lstep(0.10);
      o->precision(2);
      o->callback(aoambient_cb, app);
      VMDFLTKTOOLTIP(o, "Ambient occlusion lighting coefficient")
    }
    { Fl_Counter* o = aodirect = new Fl_Counter(105, 405, 110, 25, "AO Direct");
      o->align(FL_ALIGN_LEFT);
      o->range(0.0, 1.0);
      o->step(0.01);
      o->lstep(0.10);
      o->precision(2);
      o->callback(aodirect_cb, app);
      VMDFLTKTOOLTIP(o, "Direct lighting rescaling coefficient")
    }

    Fl_Box *box1 = new Fl_Box(10, 10, 215, 120);
    box1->box(FL_ENGRAVED_FRAME);
    Fl_Box *box2 = new Fl_Box(10, 130, 215, 65);
    box2->box(FL_ENGRAVED_FRAME);
    Fl_Box *box3 = new Fl_Box(10, 190, 215, 110);
    box3->box(FL_ENGRAVED_FRAME);
    Fl_Box *box4 = new Fl_Box(10, 300, 215, 135);
    box4->box(FL_ENGRAVED_FRAME);
    end();
    end();
  }
}