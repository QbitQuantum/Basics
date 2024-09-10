Fl_Double_Window* SUBnoteUI::make_window() {
  { SUBparameters = new Fl_Double_Window(735, 390, "SUBsynth Parameters");
    SUBparameters->user_data((void*)(this));
    { Fl_Scroll* o = new Fl_Scroll(5, 140, 435, 245);
      o->type(1);
      o->box(FL_THIN_UP_BOX);
      { Fl_Pack* o = harmonics = new Fl_Pack(10, 145, 425, 235);
        harmonics->type(1);
        for (int i=0;i<MAX_SUB_HARMONICS;i++){h[i]=new SUBnoteharmonic(0,0,15,o->h(),"");h[i]->init(pars,i);}
        harmonics->end();
      } // Fl_Pack* harmonics
      o->end();
    } // Fl_Scroll* o
    { Fl_Button* o = new Fl_Button(625, 365, 105, 20, "Close");
      o->box(FL_THIN_UP_BOX);
      o->labelfont(1);
      o->labelsize(11);
      o->callback((Fl_Callback*)cb_Close);
    } // Fl_Button* o
    { Fl_Group* o = new Fl_Group(5, 5, 215, 135, "AMPLITUDE");
      o->box(FL_THIN_UP_FRAME);
      o->labeltype(FL_EMBOSSED_LABEL);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
      { Fl_Value_Slider* o = vol = new Fl_Value_Slider(10, 25, 140, 15, "Vol");
        vol->tooltip("Volume");
        vol->type(5);
        vol->box(FL_FLAT_BOX);
        vol->labelsize(11);
        vol->maximum(127);
        vol->step(1);
        vol->callback((Fl_Callback*)cb_vol);
        vol->align(FL_ALIGN_RIGHT);
        o->value(pars->PVolume);
      } // Fl_Value_Slider* vol
      { Fl_Value_Slider* o = vsns = new Fl_Value_Slider(10, 45, 140, 15, "V.Sns");
        vsns->tooltip("Velocity Sensing Function (rightmost to disable)");
        vsns->type(5);
        vsns->box(FL_FLAT_BOX);
        vsns->labelsize(11);
        vsns->maximum(127);
        vsns->step(1);
        vsns->callback((Fl_Callback*)cb_vsns);
        vsns->align(FL_ALIGN_RIGHT);
        o->value(pars->PAmpVelocityScaleFunction);
      } // Fl_Value_Slider* vsns
      { WidgetPDial* o = pan = new WidgetPDial(185, 20, 30, 30, "Pan");
        pan->tooltip("Panning (leftmost is Random)");
        pan->box(FL_ROUND_UP_BOX);
        pan->color(FL_BACKGROUND_COLOR);
        pan->selection_color(FL_INACTIVE_COLOR);
        pan->labeltype(FL_NORMAL_LABEL);
        pan->labelfont(0);
        pan->labelsize(10);
        pan->labelcolor(FL_FOREGROUND_COLOR);
        pan->maximum(127);
        pan->step(1);
        pan->callback((Fl_Callback*)cb_pan);
        pan->align(FL_ALIGN_BOTTOM);
        pan->when(FL_WHEN_CHANGED);
        o->value(pars->PPanning);
      } // WidgetPDial* pan
      { EnvelopeUI* o = ampenv = new EnvelopeUI(10, 65, 205, 70, "SUBsynth - Amplitude Envelope");
        ampenv->box(FL_FLAT_BOX);
        ampenv->color((Fl_Color)51);
        ampenv->selection_color(FL_BACKGROUND_COLOR);
        ampenv->labeltype(FL_NORMAL_LABEL);
        ampenv->labelfont(0);
        ampenv->labelsize(14);
        ampenv->labelcolor(FL_FOREGROUND_COLOR);
        ampenv->align(FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
        ampenv->when(FL_WHEN_RELEASE);
        o->init(pars->AmpEnvelope,master);
        ampenv->end();
      } // EnvelopeUI* ampenv
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(495, 325, 235, 35);
      o->box(FL_THIN_UP_FRAME);
      { Fl_Counter* o = filterstages = new Fl_Counter(515, 340, 45, 15, "Filter Stages");
        filterstages->tooltip("How many times the noise is filtered");
        filterstages->type(1);
        filterstages->labelfont(1);
        filterstages->labelsize(10);
        filterstages->minimum(1);
        filterstages->maximum(5);
        filterstages->step(1);
        filterstages->textsize(10);
        filterstages->callback((Fl_Callback*)cb_filterstages);
        filterstages->align(FL_ALIGN_TOP);
        o->value(pars->Pnumstages);
      } // Fl_Counter* filterstages
      { Fl_Choice* o = magtype = new Fl_Choice(585, 340, 65, 15, "Mag.Type");
        magtype->down_box(FL_BORDER_BOX);
        magtype->labelfont(1);
        magtype->labelsize(10);
        magtype->textsize(11);
        magtype->callback((Fl_Callback*)cb_magtype);
        magtype->align(FL_ALIGN_TOP);
        magtype->menu(menu_magtype);
        o->value(pars->Phmagtype);
      } // Fl_Choice* magtype
      { Fl_Choice* o = start = new Fl_Choice(670, 340, 50, 15, "Start");
        start->down_box(FL_BORDER_BOX);
        start->labelfont(1);
        start->labelsize(10);
        start->textsize(11);
        start->callback((Fl_Callback*)cb_start);
        start->align(FL_ALIGN_TOP);
        start->menu(menu_start);
        o->value(pars->Pstart);
      } // Fl_Choice* start
      o->end();
    } // Fl_Group* o
    { freqsettingsui = new Fl_Group(440, 5, 290, 135, "FREQUENCY");
      freqsettingsui->box(FL_THIN_UP_FRAME);
      freqsettingsui->labeltype(FL_EMBOSSED_LABEL);
      freqsettingsui->labelfont(1);
      freqsettingsui->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
      { EnvelopeUI* o = freqenvelopegroup = new EnvelopeUI(445, 65, 205, 70, "SUBsynth - Frequency Envelope");
        freqenvelopegroup->box(FL_FLAT_BOX);
        freqenvelopegroup->color((Fl_Color)51);
        freqenvelopegroup->selection_color(FL_BACKGROUND_COLOR);
        freqenvelopegroup->labeltype(FL_NORMAL_LABEL);
        freqenvelopegroup->labelfont(0);
        freqenvelopegroup->labelsize(14);
        freqenvelopegroup->labelcolor(FL_FOREGROUND_COLOR);
        freqenvelopegroup->align(FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
        freqenvelopegroup->when(FL_WHEN_RELEASE);
        o->init(pars->FreqEnvelope,master);
        if (pars->PFreqEnvelopeEnabled==0) o->deactivate();
        freqenvelopegroup->end();
      } // EnvelopeUI* freqenvelopegroup
      { Fl_Check_Button* o = freqee = new Fl_Check_Button(445, 68, 55, 15, "Enabled");
        freqee->down_box(FL_DOWN_BOX);
        freqee->labelfont(1);
        freqee->labelsize(10);
        freqee->callback((Fl_Callback*)cb_freqee);
        o->value(pars->PFreqEnvelopeEnabled);
      } // Fl_Check_Button* freqee
      { Fl_Counter* o = octave = new Fl_Counter(670, 50, 45, 15, "Octave");
        octave->tooltip("Octave");
        octave->type(1);
        octave->labelsize(10);
        octave->minimum(-8);
        octave->maximum(7);
        octave->step(1);
        octave->textfont(1);
        octave->textsize(11);
        octave->callback((Fl_Callback*)cb_octave);
        octave->align(FL_ALIGN_TOP);
        int k=pars->PCoarseDetune/1024;if (k>=8) k-=16;
        o->value(k);
      } // Fl_Counter* octave
      { Fl_Counter* o = coarsedet = new Fl_Counter(655, 115, 60, 20, "Coarse Det.");
        coarsedet->tooltip("Coarse Detune");
        coarsedet->labelsize(10);
        coarsedet->minimum(-64);
        coarsedet->maximum(63);
        coarsedet->step(1);
        coarsedet->textfont(1);
        coarsedet->textsize(11);
        coarsedet->callback((Fl_Callback*)cb_coarsedet);
        coarsedet->align(FL_ALIGN_TOP);
        int k=pars->PCoarseDetune%1024;if (k>=512) k-=1024;
        o->value(k);
        o->lstep(10);
      } // Fl_Counter* coarsedet
      { Fl_Slider* o = detune = new Fl_Slider(495, 25, 230, 15);
        detune->tooltip("Fine Detune (cents)");
        detune->type(5);
        detune->box(FL_FLAT_BOX);
        detune->minimum(-8192);
        detune->maximum(8191);
        detune->step(1);
        detune->callback((Fl_Callback*)cb_detune);
        o->value(pars->PDetune-8192);
      } // Fl_Slider* detune
      { Fl_Value_Output* o = detunevalueoutput = new Fl_Value_Output(448, 25, 45, 15, "Detune");
        detunevalueoutput->labelsize(10);
        detunevalueoutput->minimum(-5000);
        detunevalueoutput->maximum(5000);
        detunevalueoutput->step(0.01);
        detunevalueoutput->textfont(1);
        detunevalueoutput->textsize(10);
        detunevalueoutput->callback((Fl_Callback*)cb_detunevalueoutput);
        detunevalueoutput->align(FL_ALIGN_TOP_LEFT);
        o->value(getdetune(pars->PDetuneType,0,pars->PDetune));
      } // Fl_Value_Output* detunevalueoutput
      { Fl_Check_Button* o = hz440 = new Fl_Check_Button(555, 45, 50, 15, "440Hz");
        hz440->tooltip("set the base frequency to 440Hz");
        hz440->down_box(FL_DOWN_BOX);
        hz440->labelfont(1);
        hz440->labelsize(10);
        hz440->callback((Fl_Callback*)cb_hz440);
        o->value(pars->Pfixedfreq);
      } // Fl_Check_Button* hz440
      { WidgetPDial* o = fixedfreqetdial = new WidgetPDial(610, 45, 15, 15, "Eq.T.");
        fixedfreqetdial->tooltip("How the frequency varies acording to the keyboard (leftmost for fixed frequen\
cy)");
        fixedfreqetdial->box(FL_ROUND_UP_BOX);
        fixedfreqetdial->color(FL_BACKGROUND_COLOR);
        fixedfreqetdial->selection_color(FL_INACTIVE_COLOR);
        fixedfreqetdial->labeltype(FL_NORMAL_LABEL);
        fixedfreqetdial->labelfont(0);
        fixedfreqetdial->labelsize(10);
        fixedfreqetdial->labelcolor(FL_FOREGROUND_COLOR);
        fixedfreqetdial->maximum(127);
        fixedfreqetdial->step(1);
        fixedfreqetdial->callback((Fl_Callback*)cb_fixedfreqetdial);
        fixedfreqetdial->align(FL_ALIGN_RIGHT);
        fixedfreqetdial->when(FL_WHEN_CHANGED);
        o->value(pars->PfixedfreqET);
        if (pars->Pfixedfreq==0) o->deactivate();
      } // WidgetPDial* fixedfreqetdial
      { Fl_Choice* o = detunetype = new Fl_Choice(655, 85, 70, 15, "Detune Type");
        detunetype->down_box(FL_BORDER_BOX);
        detunetype->labelsize(10);
        detunetype->textfont(1);
        detunetype->textsize(10);
        detunetype->callback((Fl_Callback*)cb_detunetype);
        detunetype->align(FL_ALIGN_TOP_LEFT);
        o->add("L35cents");o->add("L10cents");o->add("E100cents");o->add("E1200cents");
        o->value(pars->PDetuneType-1);
      } // Fl_Choice* detunetype
      freqsettingsui->end();
    } // Fl_Group* freqsettingsui
    { Fl_Check_Button* o = stereo = new Fl_Check_Button(440, 325, 55, 35, "Stereo");
      stereo->box(FL_THIN_UP_BOX);
      stereo->down_box(FL_DOWN_BOX);
      stereo->labelfont(1);
      stereo->labelsize(10);
      stereo->callback((Fl_Callback*)cb_stereo);
      o->value(pars->Pstereo);
    } // Fl_Check_Button* stereo
    { Fl_Button* o = new Fl_Button(445, 365, 70, 20, "Clear");
      o->tooltip("Clear the harmonics");
      o->box(FL_THIN_UP_BOX);
      o->labelfont(1);
      o->labelsize(11);
      o->callback((Fl_Callback*)cb_Clear);
    } // Fl_Button* o
    { bandwidthsettingsui = new Fl_Group(220, 5, 220, 135, "BANDWIDTH");
      bandwidthsettingsui->box(FL_THIN_UP_FRAME);
      bandwidthsettingsui->labeltype(FL_EMBOSSED_LABEL);
      bandwidthsettingsui->labelfont(1);
      bandwidthsettingsui->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
      { EnvelopeUI* o = bandwidthenvelopegroup = new EnvelopeUI(225, 65, 205, 70, "SUBsynth - BandWidth Envelope");
        bandwidthenvelopegroup->box(FL_FLAT_BOX);
        bandwidthenvelopegroup->color((Fl_Color)51);
        bandwidthenvelopegroup->selection_color(FL_BACKGROUND_COLOR);
        bandwidthenvelopegroup->labeltype(FL_NORMAL_LABEL);
        bandwidthenvelopegroup->labelfont(0);
        bandwidthenvelopegroup->labelsize(14);
        bandwidthenvelopegroup->labelcolor(FL_FOREGROUND_COLOR);
        bandwidthenvelopegroup->align(FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
        bandwidthenvelopegroup->when(FL_WHEN_RELEASE);
        o->init(pars->BandWidthEnvelope,master);
        if (pars->PBandWidthEnvelopeEnabled==0) o->deactivate();
        bandwidthenvelopegroup->end();
      } // EnvelopeUI* bandwidthenvelopegroup
      { Fl_Check_Button* o = bwee = new Fl_Check_Button(225, 67, 55, 15, "Enabled");
        bwee->down_box(FL_DOWN_BOX);
        bwee->labelfont(1);
        bwee->labelsize(10);
        bwee->callback((Fl_Callback*)cb_bwee);
        o->value(pars->PBandWidthEnvelopeEnabled);
      } // Fl_Check_Button* bwee
      { Fl_Value_Slider* o = bandwidth = new Fl_Value_Slider(225, 40, 115, 15, "Band Width");
        bandwidth->type(5);
        bandwidth->box(FL_FLAT_BOX);
        bandwidth->labelsize(10);
        bandwidth->maximum(127);
        bandwidth->step(1);
        bandwidth->callback((Fl_Callback*)cb_bandwidth);
        bandwidth->align(FL_ALIGN_TOP);
        o->value(pars->Pbandwidth);
      } // Fl_Value_Slider* bandwidth
      { Fl_Value_Slider* o = bwidthscale = new Fl_Value_Slider(345, 40, 90, 15, "B.Width Scale");
        bwidthscale->tooltip("How much I increase the BandWidth according to lower/higher harmonics");
        bwidthscale->type(5);
        bwidthscale->box(FL_FLAT_BOX);
        bwidthscale->labelsize(10);
        bwidthscale->minimum(-64);
        bwidthscale->maximum(63);
        bwidthscale->step(1);
        bwidthscale->callback((Fl_Callback*)cb_bwidthscale);
        bwidthscale->align(FL_ALIGN_TOP);
        o->value(pars->Pbwscale-64);
      } // Fl_Value_Slider* bwidthscale
      bandwidthsettingsui->end();
    } // Fl_Group* bandwidthsettingsui
    { Fl_Group* o = globalfiltergroup = new Fl_Group(440, 140, 290, 185, "FILTER");
      globalfiltergroup->box(FL_THIN_UP_FRAME);
      globalfiltergroup->labeltype(FL_EMBOSSED_LABEL);
      globalfiltergroup->labelfont(1);
      globalfiltergroup->labelsize(13);
      globalfiltergroup->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
      { EnvelopeUI* o = filterenv = new EnvelopeUI(445, 250, 275, 70, "SUBsynth - Filter Envelope");
        filterenv->box(FL_FLAT_BOX);
        filterenv->color((Fl_Color)51);
        filterenv->selection_color(FL_BACKGROUND_COLOR);
        filterenv->labeltype(FL_NORMAL_LABEL);
        filterenv->labelfont(0);
        filterenv->labelsize(14);
        filterenv->labelcolor(FL_FOREGROUND_COLOR);
        filterenv->align(FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
        filterenv->when(FL_WHEN_RELEASE);
        o->init(pars->GlobalFilterEnvelope,master);
        filterenv->end();
      } // EnvelopeUI* filterenv
      { FilterUI* o = filterui = new FilterUI(445, 170, 275, 75, "SUBsynthl - Filter");
        filterui->box(FL_FLAT_BOX);
        filterui->color(FL_LIGHT1);
        filterui->selection_color(FL_BACKGROUND_COLOR);
        filterui->labeltype(FL_NORMAL_LABEL);
        filterui->labelfont(0);
        filterui->labelsize(14);
        filterui->labelcolor(FL_FOREGROUND_COLOR);
        filterui->align(FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
        filterui->when(FL_WHEN_RELEASE);
        o->init(pars->GlobalFilter,&pars->PGlobalFilterVelocityScale,&pars->PGlobalFilterVelocityScaleFunction,master);
        filterui->end();
      } // FilterUI* filterui
      if (pars->PGlobalFilterEnabled==0) o->deactivate();
      globalfiltergroup->end();
    } // Fl_Group* globalfiltergroup
    { Fl_Check_Button* o = filtere = new Fl_Check_Button(445, 145, 85, 20, "Enabled");
      filtere->down_box(FL_DOWN_BOX);
      filtere->labelfont(1);
      filtere->labelsize(11);
      filtere->callback((Fl_Callback*)cb_filtere);
      o->value(pars->PGlobalFilterEnabled);
    } // Fl_Check_Button* filtere
    { Fl_Button* o = new Fl_Button(540, 370, 25, 15, "C");
      o->box(FL_THIN_UP_BOX);
      o->color((Fl_Color)179);
      o->labelfont(1);
      o->labelsize(11);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_C);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(570, 370, 25, 15, "P");
      o->box(FL_THIN_UP_BOX);
      o->color((Fl_Color)179);
      o->labelfont(1);
      o->labelsize(11);
      o->labelcolor(FL_BACKGROUND2_COLOR);
      o->callback((Fl_Callback*)cb_P);
    } // Fl_Button* o
    SUBparameters->end();
  } // Fl_Double_Window* SUBparameters
  return SUBparameters;
}