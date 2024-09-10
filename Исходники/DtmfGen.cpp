void EffectDtmf::PopulateOrExchange(ShuttleGui & S)
{
   // dialog will be passed values from effect
   // Effect retrieves values from saved config
   // Dialog will take care of using them to initialize controls
   // If there is a selection, use that duration, otherwise use
   // value from saved config: this is useful is user wants to
   // replace selection with dtmf sequence

   S.AddSpace(0, 5);
   S.StartMultiColumn(2, wxCENTER);
   {
      wxTextValidator vldDtmf(wxFILTER_INCLUDE_CHAR_LIST, &dtmfSequence);
      vldDtmf.SetIncludes(wxArrayString(WXSIZEOF(kSymbols), kSymbols));
      mDtmfSequenceT = S.Id(ID_Sequence).AddTextBox(_("DTMF sequence:"), wxT(""), 10);
      mDtmfSequenceT->SetValidator(vldDtmf);

      FloatingPointValidator<double> vldAmp(3, &dtmfAmplitude, NUM_VAL_NO_TRAILING_ZEROES);
      vldAmp.SetRange(MIN_Amplitude, MAX_Amplitude);
      S.Id(ID_Amplitude).AddTextBox(_("Amplitude (0-1):"), wxT(""), 10)->SetValidator(vldAmp);

      S.AddPrompt(_("Duration:"));
      mDtmfDurationT = safenew
         NumericTextCtrl(NumericConverter::TIME,
                         S.GetParent(),
                         ID_Duration,
                         GetDurationFormat(),
                         GetDuration(),
                         mProjectRate,
                         wxDefaultPosition,
                         wxDefaultSize,
                         true);
      mDtmfDurationT->SetName(_("Duration"));
      mDtmfDurationT->EnableMenu();
      S.AddWindow(mDtmfDurationT);

      S.AddFixedText(_("Tone/silence ratio:"), false);
      S.SetStyle(wxSL_HORIZONTAL | wxEXPAND);
      mDtmfDutyCycleS = S.Id(ID_DutyCycle).AddSlider( {},
                                                     dtmfDutyCycle * SCL_DutyCycle,
                                                     MAX_DutyCycle * SCL_DutyCycle, 
                                                     MIN_DutyCycle * SCL_DutyCycle);
      S.SetSizeHints(-1,-1);
   }
   S.EndMultiColumn();

   S.StartMultiColumn(2, wxCENTER);
   {
      S.AddFixedText(_("Duty cycle:"), false);
      mDtmfDutyT = S.AddVariableText(wxString::Format(wxT("%.1f %%"), dtmfDutyCycle), false);
      
      S.AddFixedText(_("Tone duration:"), false);
      mDtmfSilenceT = S.AddVariableText(wxString::Format(wxString(wxT("%.0f ")) + _("ms"), dtmfTone * 1000.0), false);

      S.AddFixedText(_("Silence duration:"), false);
      mDtmfToneT = S.AddVariableText(wxString::Format(wxString(wxT("%0.f ")) + _("ms"), dtmfSilence * 1000.0), false);
   }
   S.EndMultiColumn();
}