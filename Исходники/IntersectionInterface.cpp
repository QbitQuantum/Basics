Fl_Double_Window* IntersectionInterface::make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = m_intersectionWindow = new Fl_Double_Window(420, 265, "Intersection UI");
    w = o;
    o->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(5, 25, 145, 30);
      o->end();
    }
    { Fl_Choice* o = m_iShapeType = new Fl_Choice(5, 25, 145, 30, "Object type");
      o->down_box(FL_BORDER_BOX);
      o->align(FL_ALIGN_TOP_LEFT);
      o->menu(menu_m_iShapeType);
    }
    { Fl_Value_Slider* o = m_dXAt = new Fl_Value_Slider(5, 75, 200, 25, "At x pos");
      o->type(5);
      o->minimum(-1.5);
      o->maximum(1.5);
      o->callback((Fl_Callback*)cb_m_dXAt);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Value_Slider* o = m_dYAt = new Fl_Value_Slider(5, 115, 200, 25, "At y pos");
      o->type(5);
      o->minimum(-1.5);
      o->maximum(1.5);
      o->callback((Fl_Callback*)cb_m_dYAt);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Value_Slider* o = m_dZAt = new Fl_Value_Slider(5, 155, 200, 25, "At z pos");
      o->type(5);
      o->minimum(-1.5);
      o->maximum(1.5);
      o->callback((Fl_Callback*)cb_m_dZAt);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Value_Slider* o = m_dTheta = new Fl_Value_Slider(5, 195, 200, 25, "Vec theta");
      o->type(5);
      o->maximum(360);
      o->step(1);
      o->callback((Fl_Callback*)cb_m_dTheta);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Value_Slider* o = m_dPhi = new Fl_Value_Slider(5, 235, 200, 25, "Vec phi");
      o->type(5);
      o->minimum(-90);
      o->maximum(90);
      o->step(1);
      o->value(45);
      o->callback((Fl_Callback*)cb_m_dPhi);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Button* o = new Fl_Button(330, 25, 85, 25, "Write test");
      o->callback((Fl_Callback*)cb_Write);
    }
    { Fl_Value_Slider* o = m_dXRot = new Fl_Value_Slider(215, 75, 200, 25, "View rotation");
      o->type(5);
      o->maximum(360);
      o->step(1);
      o->callback((Fl_Callback*)cb_m_dXRot);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Value_Slider* o = m_dYRot = new Fl_Value_Slider(215, 115, 200, 25, "View height");
      o->type(5);
      o->minimum(-90);
      o->maximum(90);
      o->step(1);
      o->callback((Fl_Callback*)cb_m_dYRot);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Check_Button* o = m_bGrid = new Fl_Check_Button(215, 155, 25, 25, "Show grid");
      o->down_box(FL_DOWN_BOX);
      o->value(1);
      o->callback((Fl_Callback*)cb_m_bGrid);
    }
    { Fl_Check_Button* o = m_bRay = new Fl_Check_Button(215, 195, 25, 25, "Show ray");
      o->down_box(FL_DOWN_BOX);
      o->value(1);
      o->callback((Fl_Callback*)cb_m_bRay);
    }
    { Fl_Check_Button* o = m_bRayShadow = new Fl_Check_Button(215, 235, 25, 25, "Show ray shadow");
      o->down_box(FL_DOWN_BOX);
      o->value(1);
      o->callback((Fl_Callback*)cb_m_bRayShadow);
    }
    m_iSeed = new Fl_Value_Input(240, 30, 85, 20, "Seed");
    o->end();
    o->resizable(o);
  }
  return w;
}