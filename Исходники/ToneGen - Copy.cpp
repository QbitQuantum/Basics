void EffectToneGen::PopulateOrExchange(ShuttleGui & S)
{
   wxTextCtrl *t;

   S.StartMultiColumn(2, wxCENTER);
   {
      wxChoice *c = S.AddChoice(_("Waveform:"), wxT(""), &mWaveforms);
      c->SetValidator(wxGenericValidator(&mWaveform));

      if (mChirp)
      {
         S.AddFixedText(wxT(""));
         S.StartHorizontalLay(wxEXPAND);
         {
            S.StartHorizontalLay(wxLEFT, 50);
            {
               S.AddTitle(_("Start"));
            }
            S.EndHorizontalLay();

            S.StartHorizontalLay(wxLEFT, 50);
            {
               S.AddTitle(_("End"));
            }
            S.EndHorizontalLay();
         }
         S.EndHorizontalLay();

         S.AddPrompt(_("Frequency (Hz):"));
         S.StartHorizontalLay(wxEXPAND);
         {
            S.StartHorizontalLay(wxLEFT, 50);
            {
               FloatingPointValidator<double> vldStartFreq(6, &mFrequency[0], NUM_VAL_NO_TRAILING_ZEROES);
               vldStartFreq.SetRange(MIN_StartFreq, GetActiveProject()->GetRate() / 2.0);
               t = S.AddTextBox(wxT(""), wxT(""), 12);
               t->SetName(_("Frequency Hertz Start"));
               t->SetValidator(vldStartFreq);
            }
            S.EndHorizontalLay();

            S.StartHorizontalLay(wxLEFT, 50);
            {
               FloatingPointValidator<double> vldEndFreq(6, &mFrequency[1], NUM_VAL_NO_TRAILING_ZEROES);
               vldEndFreq.SetRange(MIN_EndFreq, GetActiveProject()->GetRate() / 2.0);
               t = S.AddTextBox(wxT(""), wxT(""), 12);
               t->SetName(_("Frequency Hertz End"));
               t->SetValidator(vldEndFreq);
            }
            S.EndHorizontalLay();
         }
         S.EndHorizontalLay();

         S.AddPrompt(_("Amplitude (Hz):"));
         S.StartHorizontalLay(wxEXPAND);
         {
            S.StartHorizontalLay(wxLEFT, 50);
            {
               FloatingPointValidator<double> vldStartAmp(6, &mAmplitude[0], NUM_VAL_NO_TRAILING_ZEROES);
               vldStartAmp.SetRange(MIN_StartAmp, MAX_StartAmp);
               t = S.AddTextBox(wxT(""), wxT(""), 12);
               t->SetName(_("Amplitude Start"));
               t->SetValidator(vldStartAmp);
            }
            S.EndHorizontalLay();

            S.StartHorizontalLay(wxLEFT, 50);
            {
               FloatingPointValidator<double> vldEndAmp(6, &mAmplitude[1], NUM_VAL_NO_TRAILING_ZEROES);
               vldEndAmp.SetRange(MIN_EndAmp, MAX_EndAmp);
               t = S.AddTextBox(wxT(""), wxT(""), 12);
               t->SetName(_("Amplitude End"));
               t->SetValidator(vldEndAmp);
            }
            S.EndHorizontalLay();
         }
         S.EndHorizontalLay();

         c = S.AddChoice(_("Interpolation:"), wxT(""), &mInterpolations);
         c->SetValidator(wxGenericValidator(&mInterpolation));
      }
      else
      {
         FloatingPointValidator<double> vldFrequency(6, &mFrequency[0], NUM_VAL_NO_TRAILING_ZEROES);
         vldFrequency.SetRange(MIN_Frequency, GetActiveProject()->GetRate() / 2.0);
         t = S.AddTextBox(_("Frequency (Hz):"), wxT(""), 12);
         t->SetValidator(vldFrequency);

         FloatingPointValidator<double> vldAmplitude(6, &mAmplitude[0], NUM_VAL_NO_TRAILING_ZEROES);
         vldAmplitude.SetRange(MIN_Amplitude, MAX_Amplitude);
         t = S.AddTextBox(_("Amplitude (0-1):"), wxT(""), 12);
         t->SetValidator(vldAmplitude);
      }

      bool isSelection;
      double duration = GetDuration(&isSelection);

      S.AddPrompt(_("Duration:"));
      mToneDurationT = new
         NumericTextCtrl(NumericConverter::TIME,
                        S.GetParent(),
                        wxID_ANY,
                        isSelection ? _("hh:mm:ss + samples") : _("hh:mm:ss + milliseconds"),
                        duration,
                        mProjectRate,
                        wxDefaultPosition,
                        wxDefaultSize,
                        true);
      mToneDurationT->SetName(_("Duration"));
      mToneDurationT->EnableMenu();
      S.AddWindow(mToneDurationT, wxALIGN_LEFT | wxALL);
   }
   S.EndMultiColumn();

   return;
}