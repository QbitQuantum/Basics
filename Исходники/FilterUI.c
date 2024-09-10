Fl_Double_Window* FilterUI::make_formant_window() {
  { formantparswindow = new Fl_Double_Window(700, 205, "Formant Filter Parameters");
    formantparswindow->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(485, 47, 105, 113);
      o->box(FL_THIN_UP_BOX);
      { Fl_Counter* o = new Fl_Counter(545, 80, 40, 15, "Formant ");
        o->type(1);
        o->labelfont(1);
        o->labelsize(10);
        o->minimum(0);
        o->maximum(127);
        o->step(1);
        o->textsize(10);
        o->callback((Fl_Callback*)cb_Formant);
        o->align(FL_ALIGN_LEFT);
        o->bounds(0,FF_MAX_FORMANTS-1);
        o->value(nformant);
      } // Fl_Counter* o
      { Fl_Counter* o = new Fl_Counter(545, 55, 40, 20, "Vowel no.");
        o->type(1);
        o->labelfont(1);
        o->labelsize(10);
        o->minimum(0);
        o->maximum(127);
        o->step(1);
        o->textfont(1);
        o->textsize(11);
        o->callback((Fl_Callback*)cb_Vowel);
        o->align(FL_ALIGN_LEFT);
        o->bounds(0,FF_MAX_VOWELS-1);
        o->value(nvowel);
      } // Fl_Counter* o
      { formantparsgroup = new Fl_Group(490, 105, 95, 50);
        formantparsgroup->box(FL_ENGRAVED_FRAME);
        { formant_freq_dial = new WidgetPDial(495, 115, 25, 25, "freq");
          formant_freq_dial->tooltip("Formant frequency");
          formant_freq_dial->box(FL_ROUND_UP_BOX);
          formant_freq_dial->color(FL_BACKGROUND_COLOR);
          formant_freq_dial->selection_color(FL_INACTIVE_COLOR);
          formant_freq_dial->labeltype(FL_NORMAL_LABEL);
          formant_freq_dial->labelfont(0);
          formant_freq_dial->labelsize(10);
          formant_freq_dial->labelcolor(FL_FOREGROUND_COLOR);
          formant_freq_dial->maximum(127);
          formant_freq_dial->step(1);
          formant_freq_dial->callback((Fl_Callback*)cb_formant_freq_dial);
          formant_freq_dial->align(FL_ALIGN_BOTTOM);
          formant_freq_dial->when(FL_WHEN_CHANGED);
        } // WidgetPDial* formant_freq_dial
        { formant_q_dial = new WidgetPDial(525, 115, 24, 25, "Q");
          formant_q_dial->tooltip("Formant\'s Q");
          formant_q_dial->box(FL_ROUND_UP_BOX);
          formant_q_dial->color(FL_BACKGROUND_COLOR);
          formant_q_dial->selection_color(FL_INACTIVE_COLOR);
          formant_q_dial->labeltype(FL_NORMAL_LABEL);
          formant_q_dial->labelfont(0);
          formant_q_dial->labelsize(10);
          formant_q_dial->labelcolor(FL_FOREGROUND_COLOR);
          formant_q_dial->maximum(127);
          formant_q_dial->step(1);
          formant_q_dial->callback((Fl_Callback*)cb_formant_q_dial);
          formant_q_dial->align(FL_ALIGN_BOTTOM);
          formant_q_dial->when(FL_WHEN_CHANGED);
        } // WidgetPDial* formant_q_dial
        { formant_amp_dial = new WidgetPDial(555, 115, 24, 25, "amp");
          formant_amp_dial->tooltip("Formant amplitude");
          formant_amp_dial->box(FL_ROUND_UP_BOX);
          formant_amp_dial->color(FL_BACKGROUND_COLOR);
          formant_amp_dial->selection_color(FL_INACTIVE_COLOR);
          formant_amp_dial->labeltype(FL_NORMAL_LABEL);
          formant_amp_dial->labelfont(0);
          formant_amp_dial->labelsize(10);
          formant_amp_dial->labelcolor(FL_FOREGROUND_COLOR);
          formant_amp_dial->maximum(127);
          formant_amp_dial->step(1);
          formant_amp_dial->callback((Fl_Callback*)cb_formant_amp_dial);
          formant_amp_dial->align(FL_ALIGN_BOTTOM);
          formant_amp_dial->when(FL_WHEN_CHANGED);
        } // WidgetPDial* formant_amp_dial
        formantparsgroup->end();
      } // Fl_Group* formantparsgroup
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(590, 47, 100, 113);
      o->box(FL_THIN_UP_BOX);
      { Fl_Counter* o = new Fl_Counter(595, 62, 55, 20, "Seq.Size");
        o->type(1);
        o->labelfont(1);
        o->labelsize(10);
        o->minimum(0);
        o->maximum(127);
        o->step(1);
        o->textfont(1);
        o->textsize(11);
        o->callback((Fl_Callback*)cb_Seq);
        o->align(FL_ALIGN_TOP_LEFT);
        o->bounds(1,FF_MAX_SEQUENCE-1);
        o->value(pars->Psequencesize);
      } // Fl_Counter* o
      { Fl_Counter* o = new Fl_Counter(595, 97, 40, 15, "S.Pos.");
        o->tooltip("Current position from the sequence");
        o->type(1);
        o->labelfont(1);
        o->labelsize(10);
        o->minimum(0);
        o->maximum(127);
        o->step(1);
        o->textsize(10);
        o->callback((Fl_Callback*)cb_S);
        o->align(FL_ALIGN_TOP_RIGHT);
        o->bounds(0,FF_MAX_SEQUENCE-2);
        o->value(nseqpos);
      } // Fl_Counter* o
      { Fl_Counter* o = vowel_counter = new Fl_Counter(640, 97, 40, 15, "Vowel");
        vowel_counter->type(1);
        vowel_counter->labelsize(10);
        vowel_counter->minimum(0);
        vowel_counter->maximum(127);
        vowel_counter->step(1);
        vowel_counter->textsize(10);
        vowel_counter->callback((Fl_Callback*)cb_vowel_counter);
        vowel_counter->align(FL_ALIGN_TOP);
        o->bounds(0,FF_MAX_VOWELS-1);
      } // Fl_Counter* vowel_counter
      { Fl_Check_Button* o = new Fl_Check_Button(625, 132, 60, 20, "Neg.Input");
        o->tooltip("Negate the input from LFO/envelopes/etc.");
        o->down_box(FL_DOWN_BOX);
        o->labelsize(10);
        o->callback((Fl_Callback*)cb_Neg);
        o->value(pars->Psequencereversed);
      } // Fl_Check_Button* o
      { WidgetPDial* o = strchdial = new WidgetPDial(595, 130, 25, 25, "Strch");
        strchdial->tooltip("Sequence Stretch");
        strchdial->box(FL_ROUND_UP_BOX);
        strchdial->color(FL_BACKGROUND_COLOR);
        strchdial->selection_color(FL_INACTIVE_COLOR);
        strchdial->labeltype(FL_NORMAL_LABEL);
        strchdial->labelfont(0);
        strchdial->labelsize(10);
        strchdial->labelcolor(FL_FOREGROUND_COLOR);
        strchdial->maximum(127);
        strchdial->step(1);
        strchdial->callback((Fl_Callback*)cb_strchdial);
        strchdial->align(FL_ALIGN_TOP);
        strchdial->when(FL_WHEN_CHANGED);
        o->value(pars->Psequencestretch);
      } // WidgetPDial* strchdial
      o->end();
    } // Fl_Group* o
    { Fl_Counter* o = new Fl_Counter(485, 15, 65, 20, "Num.Formants");
      o->type(1);
      o->labelfont(1);
      o->labelsize(10);
      o->minimum(0);
      o->maximum(127);
      o->step(1);
      o->callback((Fl_Callback*)cb_Num);
      o->align(FL_ALIGN_TOP_LEFT);
      o->bounds(1,FF_MAX_FORMANTS);
      o->value(pars->Pnumformants);
    } // Fl_Counter* o
    { WidgetPDial* o = frsldial = new WidgetPDial(565, 15, 25, 25, "Fr.Sl.");
      frsldial->tooltip("Formant\'s Slowness (Morphing)");
      frsldial->box(FL_ROUND_UP_BOX);
      frsldial->color(FL_BACKGROUND_COLOR);
      frsldial->selection_color(FL_INACTIVE_COLOR);
      frsldial->labeltype(FL_NORMAL_LABEL);
      frsldial->labelfont(1);
      frsldial->labelsize(10);
      frsldial->labelcolor(FL_FOREGROUND_COLOR);
      frsldial->maximum(127);
      frsldial->step(1);
      frsldial->callback((Fl_Callback*)cb_frsldial);
      frsldial->align(FL_ALIGN_TOP);
      frsldial->when(FL_WHEN_CHANGED);
      o->value(pars->Pformantslowness);
    } // WidgetPDial* frsldial
    { Fl_Value_Output* o = centerfreqvo = new Fl_Value_Output(515, 164, 33, 18, "C.f.");
      centerfreqvo->tooltip("Center Frequency (kHz)");
      centerfreqvo->minimum(1);
      centerfreqvo->maximum(10);
      centerfreqvo->step(0.01);
      centerfreqvo->value(1);
      centerfreqvo->textfont(1);
      centerfreqvo->callback((Fl_Callback*)cb_centerfreqvo);
      centerfreqvo->when(3);
      o->value(pars->getcenterfreq()/1000.0);
    } // Fl_Value_Output* centerfreqvo
    { Fl_Value_Output* o = octavesfreqvo = new Fl_Value_Output(515, 182, 33, 18, "Oct.");
      octavesfreqvo->tooltip("No. of octaves");
      octavesfreqvo->minimum(1);
      octavesfreqvo->maximum(127);
      octavesfreqvo->step(1);
      octavesfreqvo->value(5);
      octavesfreqvo->textfont(1);
      octavesfreqvo->callback((Fl_Callback*)cb_octavesfreqvo);
      octavesfreqvo->when(3);
      o->value(pars->getoctavesfreq());
    } // Fl_Value_Output* octavesfreqvo
    { Fl_Slider* o = cfknob = new Fl_Slider(551, 167, 84, 15);
      cfknob->type(5);
      cfknob->box(FL_FLAT_BOX);
      cfknob->maximum(127);
      cfknob->callback((Fl_Callback*)cb_cfknob);
      o->value(pars->Pcenterfreq);
    } // Fl_Slider* cfknob
    { Fl_Slider* o = octknob = new Fl_Slider(551, 185, 84, 15);
      octknob->type(5);
      octknob->box(FL_FLAT_BOX);
      octknob->maximum(127);
      octknob->callback((Fl_Callback*)cb_octknob);
      o->value(pars->Poctavesfreq);
    } // Fl_Slider* octknob
    { FormantFilterGraph* o = formantfiltergraph = new FormantFilterGraph(5, 5, 475, 195);
      formantfiltergraph->box(FL_BORDER_BOX);
      formantfiltergraph->color(FL_BACKGROUND_COLOR);
      formantfiltergraph->selection_color(FL_BACKGROUND_COLOR);
      formantfiltergraph->labeltype(FL_NORMAL_LABEL);
      formantfiltergraph->labelfont(0);
      formantfiltergraph->labelsize(14);
      formantfiltergraph->labelcolor(FL_FOREGROUND_COLOR);
      formantfiltergraph->align(FL_ALIGN_CENTER);
      formantfiltergraph->when(FL_WHEN_RELEASE);
      o->init(pars,&nvowel,&nformant);
    } // FormantFilterGraph* formantfiltergraph
    { WidgetPDial* o = wvknob = new WidgetPDial(600, 15, 25, 25, "Vw.Cl.");
      wvknob->tooltip("Vowel \"clearness\" (how the mixed vowels are avoided)");
      wvknob->box(FL_ROUND_UP_BOX);
      wvknob->color(FL_BACKGROUND_COLOR);
      wvknob->selection_color(FL_INACTIVE_COLOR);
      wvknob->labeltype(FL_NORMAL_LABEL);
      wvknob->labelfont(1);
      wvknob->labelsize(10);
      wvknob->labelcolor(FL_FOREGROUND_COLOR);
      wvknob->maximum(127);
      wvknob->step(1);
      wvknob->callback((Fl_Callback*)cb_wvknob);
      wvknob->align(FL_ALIGN_TOP);
      wvknob->when(FL_WHEN_CHANGED);
      o->value(pars->Pvowelclearness);
    } // WidgetPDial* wvknob
    { Fl_Button* o = new Fl_Button(645, 180, 50, 25, "Close");
      o->box(FL_THIN_UP_BOX);
      o->callback((Fl_Callback*)cb_Close);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(635, 25, 25, 15, "C");
      o->box(FL_THIN_UP_BOX);
      o->color((Fl_Color)179);
      o->labelfont(1);
      o->labelsize(11);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_C1);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(665, 25, 25, 15, "P");
      o->box(FL_THIN_UP_BOX);
      o->color((Fl_Color)179);
      o->labelfont(1);
      o->labelsize(11);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_P1);
    } // Fl_Button* o
    { new Fl_Box(635, 10, 55, 15, "Vowel");
    } // Fl_Box* o
    formantparswindow->end();
  } // Fl_Double_Window* formantparswindow
  return formantparswindow;
}