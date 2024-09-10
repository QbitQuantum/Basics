void EffectScienFilter::PopulateOrExchange(ShuttleGui & S)
{
   wxWindow *parent = S.GetParent();

   S.AddSpace(5);
   S.SetSizerProportion(1);
   S.StartMultiColumn(3, wxEXPAND);
   {
      S.SetStretchyCol(1);
      S.SetStretchyRow(0);

      // -------------------------------------------------------------------
      // ROW 1: Freq response panel and sliders for vertical scale
      // -------------------------------------------------------------------

      S.StartVerticalLay();
      {
         mdBRuler = new RulerPanel(parent, wxID_ANY);
         mdBRuler->ruler.SetBounds(0, 0, 100, 100); // Ruler can't handle small sizes
         mdBRuler->ruler.SetOrientation(wxVERTICAL);
         mdBRuler->ruler.SetRange(30.0, -120.0);
         mdBRuler->ruler.SetFormat(Ruler::LinearDBFormat);
         mdBRuler->ruler.SetUnits(_("dB"));
         mdBRuler->ruler.SetLabelEdges(true);
         int w;
         mdBRuler->ruler.GetMaxSize(&w, NULL);
         mdBRuler->SetSize(wxSize(w, 150));  // height needed for wxGTK

         S.SetBorder(1);
         S.AddSpace(1, 1);
         S.Prop(1);
         S.AddWindow(mdBRuler, wxALIGN_RIGHT | wxTOP);
         S.AddSpace(1, 1);
      }
      S.EndVerticalLay();

      mPanel = new EffectScienFilterPanel(this, parent);
      mPanel->SetFreqRange(mLoFreq, mNyquist);

      S.SetBorder(5);
      S.Prop(1);
      S.AddWindow(mPanel, wxEXPAND | wxRIGHT);
      S.SetSizeHints(-1, -1);

      S.StartVerticalLay();
      {
         S.AddVariableText(_("+ dB"), false, wxCENTER);
         S.SetStyle(wxSL_VERTICAL | wxSL_INVERSE);
         mdBMaxSlider = S.Id(ID_dBMax).AddSlider(wxT(""), 10, 20, 0);
#if wxUSE_ACCESSIBILITY
         mdBMaxSlider->SetName(_("Max dB"));
         mdBMaxSlider->SetAccessible(new SliderAx(mdBMaxSlider, wxString(wxT("%d ")) + _("dB")));
#endif

         S.SetStyle(wxSL_VERTICAL | wxSL_INVERSE);
         mdBMinSlider = S.Id(ID_dBMin).AddSlider(wxT(""), -10, -10, -120);
         S.AddVariableText(_("- dB"), false, wxCENTER);
#if wxUSE_ACCESSIBILITY
         mdBMinSlider->SetName(_("Min dB"));
         mdBMinSlider->SetAccessible(new SliderAx(mdBMinSlider, wxString(wxT("%d ")) + _("dB")));
#endif
      }
      S.EndVerticalLay();

      // -------------------------------------------------------------------
      // ROW 2: Frequency ruler
      // -------------------------------------------------------------------

      S.AddSpace(1, 1);

      mfreqRuler  = new RulerPanel(parent, wxID_ANY);
      mfreqRuler->ruler.SetBounds(0, 0, 100, 100); // Ruler can't handle small sizes
      mfreqRuler->ruler.SetOrientation(wxHORIZONTAL);
      mfreqRuler->ruler.SetLog(true);
      mfreqRuler->ruler.SetRange(mLoFreq, mNyquist);
      mfreqRuler->ruler.SetFormat(Ruler::IntFormat);
      mfreqRuler->ruler.SetUnits(wxT(""));
      mfreqRuler->ruler.SetFlip(true);
      mfreqRuler->ruler.SetLabelEdges(true);
      int h;
      mfreqRuler->ruler.GetMaxSize(NULL, &h);
      mfreqRuler->SetMinSize(wxSize(-1, h));

      S.Prop(1);
      S.AddWindow(mfreqRuler, wxEXPAND | wxALIGN_LEFT | wxRIGHT);

      S.AddSpace(1, 1);

      // -------------------------------------------------------------------
      // ROW 3 and 4: Type, Order, Ripple, Subtype, Cutoff
      // -------------------------------------------------------------------

      S.AddSpace(1, 1);
      S.SetSizerProportion(0);
      S.StartMultiColumn(8, wxALIGN_CENTER);
      {
         wxASSERT(kNumTypes == WXSIZEOF(kTypeStrings));

         wxArrayString typeChoices;
         for (int i = 0; i < kNumTypes; i++)
         {
            typeChoices.Add(wxGetTranslation(kTypeStrings[i]));
         }

         mFilterTypeCtl = S.Id(ID_Type).AddChoice(_("&Filter Type:"), wxT(""), &typeChoices);
         mFilterTypeCtl->SetValidator(wxGenericValidator(&mFilterType));
         S.SetSizeHints(-1, -1);

         wxArrayString orders;
         for (int i = 1; i <= 10; i++)
         {
            orders.Add(wxString::Format(wxT("%d"), i));
         }
         /*i18n-hint: 'Order' means the complexity of the filter, and is a number between 1 and 10.*/
         mFilterOrderCtl = S.Id(ID_Order).AddChoice(_("O&rder:"), wxT(""), &orders);
         mFilterOrderCtl->SetValidator(wxGenericValidator(&mOrderIndex));
         S.SetSizeHints(-1, -1);
         S.AddSpace(1, 1);

         FloatingPointValidator<float> vldRipple(1, &mRipple);
         vldRipple.SetRange(MIN_Passband, MAX_Passband);
         
         mRippleCtlP = S.AddVariableText(_("&Passband Ripple:"), false, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
         mRippleCtl = S.Id(ID_Ripple).AddTextBox(wxT(""), wxT(""), 10);
         mRippleCtl->SetName(_("Passband Ripple (dB)"));
         mRippleCtl->SetValidator(vldRipple);
         mRippleCtlU = S.AddVariableText(_("dB"), false, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

         wxASSERT(kNumSubTypes == WXSIZEOF(kSubTypeStrings));

         wxArrayString subTypeChoices;
         for (int i = 0; i < kNumSubTypes; i++)
         {
            subTypeChoices.Add(wxGetTranslation(kSubTypeStrings[i]));
         }

         mFilterSubTypeCtl = S.Id(ID_SubType).AddChoice(_("&Subtype:"), wxT(""), &subTypeChoices);
         mFilterSubTypeCtl->SetValidator(wxGenericValidator(&mFilterSubtype));
         S.SetSizeHints(-1, -1);
      
         FloatingPointValidator<float> vldCutoff(1, &mCutoff);
         vldCutoff.SetRange(MIN_Cutoff, mNyquist - 1);
         
         mCutoffCtl = S.Id(ID_Cutoff).AddTextBox(_("C&utoff:"), wxT(""), 10);
         mCutoffCtl->SetName(_("Cutoff (Hz)"));
         mCutoffCtl->SetValidator(vldCutoff);
         S.AddUnits(_("Hz"));

         FloatingPointValidator<float> vldStopbandRipple(1, &mStopbandRipple);
         vldStopbandRipple.SetRange(MIN_Stopband, MAX_Stopband);
         
         mStopbandRippleCtlP = S.AddVariableText(_("Minimum S&topband Attenuation:"), false, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
         mStopbandRippleCtl = S.Id(ID_StopbandRipple).AddTextBox(wxT(""), wxT(""), 10);
         mStopbandRippleCtl->SetName(_("Minimum S&topband Attenuation (dB)"));
         mStopbandRippleCtl->SetValidator(vldStopbandRipple);
         mStopbandRippleCtlU = S.AddVariableText(_("dB"), false, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
      }
      S.EndMultiColumn();
      S.AddSpace(1, 1);
   }
   S.EndMultiColumn();

   mFilterTypeCtl->SetFocus();

   return;
}