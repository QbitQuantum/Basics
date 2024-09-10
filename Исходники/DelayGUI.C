void DelayGUI::CreateGUI(int xoff, int yoff, char *name)
{
	 Fl_Group* o = GUIDelayGroup = new Fl_Group(xoff, yoff, 300, 60, name);
      o->type(1);
	  o->color(GUIBG2_COLOUR);
	  o->box(FL_UP_BOX);
      o->labeltype(FL_ENGRAVED_LABEL);
      o->align(FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE);
	  o->user_data((void*)(this));
       	  
	  DelayA = new Fl_Knob(xoff+50, yoff+5, 40, 40, "Delay");
	  DelayA->color(GUI_COLOUR);
      DelayA->labelsize(10);
	  DelayA->maximum(1);
      DelayA->step(0.01);
      DelayA->value(0.5);
      DelayA->callback((Fl_Callback*)cb_Delay);
	  
	  Feedback = new Fl_Knob(xoff+100, yoff+5, 40, 40, "Feedback");
	  Feedback->color(GUI_COLOUR);
      Feedback->labelsize(10);
	  Feedback->maximum(1.0);
      Feedback->step(0.01);
      Feedback->value(0.5);
      Feedback->callback((Fl_Callback*)cb_Feedback);
	  
	  Bypass = new Fl_Button(xoff+5, yoff+25, 40, 20, "Bypass");
	  Bypass->color(GUIBG2_COLOUR);
	  Bypass->labelsize(10);
	  Bypass->type(1);
	  Bypass->value(1);
	  Bypass->callback((Fl_Callback*)cb_Bypass);
	  
      o->end();
    
}