void EffectChangeSpeed::PopulateOrExchange(ShuttleGui & S)
{
   GetPrivateConfig(GetCurrentSettingsGroup(), wxT("TimeFormat"), mFormat, mFormat);
   GetPrivateConfig(GetCurrentSettingsGroup(), wxT("VinylChoice"), mFromVinyl, mFromVinyl);

   S.SetBorder(5);

   S.StartVerticalLay(0);
   {
      S.AddSpace(0, 5);
      S.AddTitle(_("Change Speed, affecting both Tempo and Pitch"));
      S.AddSpace(0, 10);

      // Speed multiplier and percent change controls.
      S.StartMultiColumn(4, wxCENTER);
      {
         FloatingPointValidator<double> vldMultiplier(3, &mMultiplier, NUM_VAL_THREE_TRAILING_ZEROES);
         vldMultiplier.SetRange(MIN_Percentage / 100.0, ((MAX_Percentage / 100.0) + 1));
         mpTextCtrl_Multiplier =
            S.Id(ID_Multiplier).AddTextBox(_("Speed Multiplier:"), wxT(""), 12);
         mpTextCtrl_Multiplier->SetValidator(vldMultiplier);

         FloatingPointValidator<double> vldPercentage(3, &m_PercentChange, NUM_VAL_THREE_TRAILING_ZEROES);
         vldPercentage.SetRange(MIN_Percentage, MAX_Percentage);
         mpTextCtrl_PercentChange =
            S.Id(ID_PercentChange).AddTextBox(_("Percent Change:"), wxT(""), 12);
         mpTextCtrl_PercentChange->SetValidator(vldPercentage);
      }
      S.EndMultiColumn();

      // Percent change slider.
      S.StartHorizontalLay(wxEXPAND);
      {
         S.SetStyle(wxSL_HORIZONTAL);
         mpSlider_PercentChange =
            S.Id(ID_PercentChange).AddSlider(wxT(""), 0, (int)kSliderMax, (int)MIN_Percentage);
         mpSlider_PercentChange->SetName(_("Percent Change"));
      }
      S.EndHorizontalLay();

      // Vinyl rpm controls.
      S.StartMultiColumn(5, wxCENTER);
      {
         /* i18n-hint: "rpm" is an English abbreviation meaning "revolutions per minute". */
         S.AddUnits(_("Standard Vinyl rpm:"));

         wxASSERT(kNumVinyl == WXSIZEOF(kVinylStrings));

         wxArrayString vinylChoices;
         for (int i = 0; i < kNumVinyl; i++)
         {
            if (i == kVinyl_NA)
            {
               vinylChoices.Add(wxGetTranslation(kVinylStrings[i]));
            }
            else
            {
               vinylChoices.Add(kVinylStrings[i]);
            }
         }

         mpChoice_FromVinyl =
            S.Id(ID_FromVinyl).AddChoice(_("from"), wxT(""), &vinylChoices);
         mpChoice_FromVinyl->SetName(_("From rpm"));
         mpChoice_FromVinyl->SetSizeHints(100, -1);

         mpChoice_ToVinyl =
            S.Id(ID_ToVinyl).AddChoice(_("to"), wxT(""), &vinylChoices);
         mpChoice_ToVinyl->SetName(_("To rpm"));
         mpChoice_ToVinyl->SetSizeHints(100, -1);
      }
      S.EndMultiColumn();

      // From/To time controls.
      S.StartStatic(_("Selection Length"), 0);
      {
         S.StartMultiColumn(2, wxALIGN_LEFT);
         {
            S.AddPrompt(_("Current Length:"));

            mpFromLengthCtrl = safenew
                  NumericTextCtrl(NumericConverter::TIME,
                                 S.GetParent(),
                                 wxID_ANY,
                                 mFormat,
                                 mFromLength,
                                 mProjectRate);

            mpFromLengthCtrl->SetName(_("from"));
            mpFromLengthCtrl->SetToolTip(_("Current length of selection."));
            mpFromLengthCtrl->SetReadOnly(true);
            mpFromLengthCtrl->EnableMenu(false);
            S.AddWindow(mpFromLengthCtrl, wxALIGN_LEFT);

            S.AddPrompt(_("New Length:"));

            mpToLengthCtrl = safenew
                  NumericTextCtrl(NumericConverter::TIME,
                                 S.GetParent(),
                                 ID_ToLength,
                                 mFormat,
                                 mToLength,
                                 mProjectRate);

            mpToLengthCtrl->SetName(_("to"));
            mpToLengthCtrl->EnableMenu();
            S.AddWindow(mpToLengthCtrl, wxALIGN_LEFT);
         }
         S.EndMultiColumn();
      }
      S.EndStatic();
   }
   S.EndVerticalLay();
}