Fl_Scopes_Manager::Fl_Scopes_Manager(int x, int y, int width, int height, Fl_MDI_Viewport *s, const char *name)
{
	Fl::lock();

	s->begin();
	Fl_MDI_Window *w = SWin = new Fl_MDI_Window(0, 0, width, height, name);
	w->user_data((void *)this);
	w->resizable(w->view());

	w->titlebar()->close_button()->hide();

	w->view()->begin();

	Scopes_Tabs = new Fl_Tabs*[Num_Scopes];
	Scope_Show = new Fl_Check_Button*[Num_Scopes];
	Scope_Pause = new Fl_Button*[Num_Scopes];
	Scope_OneShot = new Fl_Check_Button*[Num_Scopes];
	Scope_Options = new Fl_Menu_Button*[Num_Scopes];
	Grid_Color = new Fl_Button*[Num_Scopes];
	Bg_Color = new Fl_Button*[Num_Scopes];
	Sec_Div = new Fl_Input_Browser*[Num_Scopes];
	Save_Type = new Fl_Check_Button*[Num_Scopes];
	Save_Points = new Fl_Int_Input*[Num_Scopes];
	Save_Time = new Fl_Float_Input*[Num_Scopes];
	Save_File = new Fl_Input*[Num_Scopes];
	Save = new Fl_Light_Button*[Num_Scopes];
	Save_Flag = new int[Num_Scopes];
	Save_File_Pointer = new FILE*[Num_Scopes];

	Trace_Page = new Fl_Group**[Num_Scopes];
	Trace_Show = new Fl_Check_Button**[Num_Scopes];
	Units_Div = new Fl_Input_Browser**[Num_Scopes];
	Trace_Color = new Fl_Button**[Num_Scopes];
	Trace_Pos = new Fl_Dial**[Num_Scopes];
	Trace_Width = new Fl_Dial**[Num_Scopes];
 	Trigger_Mode = new Fl_Choice*[Num_Scopes];

        Trace_Options = new Fl_Menu_Button**[Num_Scopes];

	Scope_Windows = new Fl_Scope_Window*[Num_Scopes];

	for (int i = 0; i < Num_Scopes; i++) {
		Save_Flag[i] = false;
		{ Fl_Tabs *o = Scopes_Tabs[i] = new Fl_Tabs(160, 5, width-165, height-40);
		  o->new_page("General");
		  { Fl_Check_Button *o = Scope_Show[i] = new Fl_Check_Button(10, 25, 100, 20, "Show/Hide");
		    o->callback((Fl_Callback *)show_scope, (void *)i);
		  }
		  { Fl_Button *o = Scope_Pause[i] = new Fl_Button(10, 75, 90, 25, "Trigger");
		    o->value(0);
		    o->deactivate();
		    o->when(FL_WHEN_CHANGED);
		    o->callback((Fl_Callback *)pause_scope, (void *)i);
		  }
		  { Fl_Check_Button *o = Scope_OneShot[i] = new Fl_Check_Button(10, 50, 100, 20, "OneShot/Run");
		    o->deactivate();
		    o->callback((Fl_Callback *)oneshot_scope, (void *)i);
		  }
		  { Fl_Menu_Button *o = Scope_Options[i] = new Fl_Menu_Button(10, 105, 90, 25, "Options");
			o->menu(Scope_Opts);
			o->when(FL_WHEN_ENTER_KEY);
			o->child(0)->set_value();
		    	o->callback((Fl_Callback *)enter_options, (void *)i);
		  }
		  { Fl_Button *o = Grid_Color[i] = new Fl_Button(10, 135, 90, 25, "Grid Color");
		    o->callback((Fl_Callback *)select_grid_color, (void *)i);
		  }
		  { Fl_Button *o = Bg_Color[i] = new Fl_Button(10, 165, 90, 25, "Bg Color");
		    o->callback((Fl_Callback *)select_bg_color, (void *)i);
		  }
		  { Fl_Input_Browser *o = Sec_Div[i] = new Fl_Input_Browser(200, 25, 60, 20, "Sec/Div:  ");
		    o->add("0.001|0.005|0.01|0.05|0.1|0.5|1");
		    o->align(FL_ALIGN_LEFT);
		    o->value("0.1");
		    o->when(FL_WHEN_ENTER_KEY);
		    o->callback((Fl_Callback *)enter_secdiv, (void *)i);
		  }
		  { Fl_Check_Button *o = Save_Type[i] = new Fl_Check_Button(140, 50, 100, 20, "Points/Time");
		    o->value(1);
		    o->callback((Fl_Callback *)select_save, (void *)i);
		  }
		  { Fl_Int_Input *o = Save_Points[i] = new Fl_Int_Input(200, 75, 60, 20, "N Points: ");
		    o->align(FL_ALIGN_LEFT);
		    o->value("1000");
		  }
		  { Fl_Float_Input *o = Save_Time[i] = new Fl_Float_Input(200, 105, 60, 20, "Time [s]:  ");
		    o->align(FL_ALIGN_LEFT);
		    o->value("1.0");
		    o->deactivate();
		  }
		  { Fl_Input *o = Save_File[i] = new Fl_Input(200, 135, 100, 20, "Filename:");
		    char buf[100];
		    o->align(FL_ALIGN_LEFT);
		    sprintf(buf, "%s", Scopes[i].name);
		    o->value(buf);
		  }
		  { Fl_Light_Button *o = Save[i] = new Fl_Light_Button(140, 165, 90, 25, "Save");
		    o->selection_color(FL_BLACK);
		    o->callback((Fl_Callback *)enable_saving, (void *)i);
		  }
   		  {  Fl_Choice *o = Trigger_Mode[i] = new Fl_Choice(60, 200, 170, 25, "Trigger:");
                    o->add("Continuous Roling|Continuous Overwrite|Rising (-to+) CH1|Falling (+to-) CH1|Hold");
                    o->align(FL_ALIGN_LEFT);
                    o->value(0);
                    o->when(FL_WHEN_ENTER_KEY);
                    o->callback((Fl_Callback *)enter_trigger_mode, (void *)i);
                  }


		  Trace_Page[i] = new Fl_Group*[Scopes[i].ntraces];
		  Trace_Show[i] = new Fl_Check_Button*[Scopes[i].ntraces];
		  Units_Div[i] = new Fl_Input_Browser*[Scopes[i].ntraces];
		  Trace_Color[i] = new Fl_Button*[Scopes[i].ntraces];
		  Trace_Pos[i] = new Fl_Dial*[Scopes[i].ntraces];
  		  Trace_Width[i] = new Fl_Dial*[Scopes[i].ntraces];
		  Trace_Options[i] = new Fl_Menu_Button*[Scopes[i].ntraces];
		  

		  for (int j = 0; j < Scopes[i].ntraces; j++) {
			s_idx_T *idx = new s_idx_T;
			idx->scope_idx = i;
			idx->trace_idx = j;
		  	Trace_Page[i][j] = o->new_page(Scopes[i].traceName[j]);
			Trace_Page[i][j]->label_color(FL_WHITE);
			{ Fl_Check_Button *o = Trace_Show[i][j] = new Fl_Check_Button(10, 25, 100, 20, "Show/Hide");
			  o->value(1);
		    	  o->callback((Fl_Callback *)show_trace, (void *)idx);
		  	}
		  	{ Fl_Input_Browser *o = Units_Div[i][j] = new Fl_Input_Browser(77, 55, 60, 20, "Units/Div:  ");
		    	  o->align(FL_ALIGN_LEFT);
		    	  o->value("2.5");
			  o->add("0.001|0.002|0.005|0.01|0.02|0.05|0.1|0.2|0.5|1|2|5|10|50|100|1000");
		    	  o->when(FL_WHEN_ENTER_KEY);
		    	  o->callback((Fl_Callback *)enter_unitsdiv, (void *)idx);
		  	}
		  	{ Fl_Button *o = Trace_Color[i][j] = new Fl_Button(10, 90, 90, 25, "Trace Color");
		    	  o->callback((Fl_Callback *)select_trace_color, (void *)idx);
		  	}
			{ Fl_Dial *o = Trace_Pos[i][j] = new Fl_Dial(170, 40, 50, 50, "Trace Offset");
			  o->type(Fl_Dial::LINE);
			  o->minimum(0.0);
			  o->maximum(2.0);
			  o->value(1);
		    	  o->callback((Fl_Callback *)change_trace_pos, (void *)idx);
			}
			{ Fl_Dial *o = Trace_Width[i][j] = new Fl_Dial(250, 40, 50, 50, "Trace Width");
			  o->type(Fl_Dial::LINE);
			  o->minimum(0.1);
			  o->maximum(40.0);
			  o->value(0.1);
		    	  o->callback((Fl_Callback *)change_trace_width, (void *)idx);
			}
			{ Fl_Menu_Button *o = Trace_Options[i][j] = new Fl_Menu_Button(10, 130, 90, 25, "Options ");
			  int i;
			  o->menu(Trace_Opts);
			  o->when(FL_WHEN_ENTER_KEY);
		    	  o->callback((Fl_Callback *)enter_options, (void *)idx);
			 // for(i=0;i<o->children();i++) { // loop through all menu items, and add checked items to the value
	  		 //   o->child(i)->set_value(); 
			 // } 
		  	}
		  }
		  o->end();
		  Fl_Group::current()->resizable(w);
		}
	}
	for (int i = 1; i < Num_Scopes; i++) {
		Scopes_Tabs[i]->hide();
	}
	Scopes_Tabs[0]->show();
	Help = new Fl_Button(width-150, height-30, 70, 25, "Help");
	Close = new Fl_Button(width-75, height-30, 70, 25, "Close");
	Close->callback((Fl_Callback *)close);
	Fl_Browser *o = Scopes_Tree = new Fl_Browser(5, 5, 150, height-10);
	o->indented(1);
	o->callback((Fl_Callback *)select_scope);
	for (int i = 0; i < Num_Scopes; i++) {
		add_paper(Scopes_Tree, Scopes[i].name, Fl_Image::read_xpm(0, scope_icon));
	}

	w->view()->end();

	s->end();

	w->titlebar()->h(15);
	w->titlebar()->color(FL_BLACK);

	w->position(x, y);

	Fl::unlock();
}