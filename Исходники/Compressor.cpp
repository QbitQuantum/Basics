void EffectCompressor::PopulateOrExchange(ShuttleGui & S)
{
   S.SetBorder(5);

   S.StartHorizontalLay(wxEXPAND, true);
   {
      S.SetBorder(10);
      mPanel = safenew EffectCompressorPanel(S.GetParent(),
                                         mThresholdDB,
                                         mNoiseFloorDB,
                                         mRatio);
      mPanel->SetMinSize(wxSize(400, 200));
      S.Prop(true).AddWindow(mPanel, wxEXPAND | wxALL);
      S.SetBorder(5);
   }
   S.EndHorizontalLay();

   S.StartStatic(wxT(""));
   {
      S.StartMultiColumn(3, wxEXPAND);
      {
         S.SetStretchyCol(1);
         mThresholdLabel = S.AddVariableText(_("Threshold:"), true,
                                             wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
         S.SetStyle(wxSL_HORIZONTAL);
         mThresholdSlider = S.Id(ID_Threshold).AddSlider(wxT(""),
                                                         DEF_Threshold * SCL_Threshold,
                                                         MAX_Threshold * SCL_Threshold,
                                                         MIN_Threshold * SCL_Threshold);
         mThresholdSlider->SetName(_("Threshold"));
         mThresholdText = S.AddVariableText(wxT("XXX dB"), true,
                                            wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

         mNoiseFloorLabel = S.AddVariableText(_("Noise Floor:"), true,
                                             wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
         S.SetStyle(wxSL_HORIZONTAL);
         mNoiseFloorSlider = S.Id(ID_NoiseFloor).AddSlider(wxT(""),
                                                           DEF_NoiseFloor / SCL_NoiseFloor,
                                                           MAX_NoiseFloor / SCL_NoiseFloor,
                                                           MIN_NoiseFloor / SCL_NoiseFloor);
         mNoiseFloorSlider->SetName(_("Noise Floor"));
         mNoiseFloorText = S.AddVariableText(wxT("XXX dB"), true,
                                            wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

         mRatioLabel = S.AddVariableText(_("Ratio:"), true,
                                         wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
         S.SetStyle(wxSL_HORIZONTAL);
         mRatioSlider = S.Id(ID_Ratio).AddSlider(wxT(""),
                                                 DEF_Ratio * SCL_Ratio,
                                                 MAX_Ratio * SCL_Ratio,
                                                 MIN_Ratio * SCL_Ratio);
         mRatioSlider->SetName(_("Ratio"));
         mRatioSlider->SetPageSize(5);
         mRatioText = S.AddVariableText(wxT("XXXX:1"), true,
                                             wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

         /* i18n-hint: Particularly in percussion, sounds can be regarded as having
          * an 'attack' phase where the sound builds up and a 'decay' where the
          * sound dies away.  So this means 'onset duration'.  */
         mAttackLabel = S.AddVariableText(_("Attack Time:"), true,
                                         wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
         S.SetStyle(wxSL_HORIZONTAL);
         mAttackSlider = S.Id(ID_Attack).AddSlider(wxT(""),
                                                   DEF_AttackTime * SCL_AttackTime,
                                                   MAX_AttackTime * SCL_AttackTime,
                                                   MIN_AttackTime * SCL_AttackTime);
         mAttackSlider->SetName(_("Attack Time"));
         mAttackText = S.AddVariableText(wxT("XXXX secs"), true,
                                         wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

         mDecayLabel = S.AddVariableText(_("Release Time:"), true,
                                         wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
         S.SetStyle(wxSL_HORIZONTAL);
         mDecaySlider = S.Id(ID_Decay).AddSlider(wxT(""),
                                                 DEF_ReleaseTime * SCL_ReleaseTime,
                                                 MAX_ReleaseTime * SCL_ReleaseTime,
                                                 MIN_ReleaseTime * SCL_ReleaseTime);
         mDecaySlider->SetName(_("Release Time"));
         mDecayText = S.AddVariableText(wxT("XXXX secs"), true,
                                        wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
      }
      S.EndMultiColumn();
   }
   S.EndStatic();

   S.StartHorizontalLay(wxCENTER, false);
   {
      /* i18n-hint: Make-up, i.e. correct for any reduction, rather than fabricate it.*/
      mGainCheckBox = S.AddCheckBox(_("Make-up gain for 0 dB after compressing"),
                                    DEF_Normalize ? wxT("true") : wxT("false"));
      mPeakCheckBox = S.AddCheckBox(_("Compress based on Peaks"),
                                    DEF_UsePeak ? wxT("true") : wxT("false"));
   }
   S.EndHorizontalLay();
}