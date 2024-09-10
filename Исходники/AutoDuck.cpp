void EffectAutoDuck::PopulateOrExchange(ShuttleGui & S)
{
   S.SetBorder(5);
   S.StartVerticalLay(true);
   {
      S.AddSpace(0, 5);

      mPanel = safenew EffectAutoDuckPanel(S.GetParent(), this);
      S.AddWindow(mPanel);

      S.AddSpace(0, 5);

      S.StartMultiColumn(6, wxCENTER);
      {
         FloatingPointValidator<double> vldDuckAmountDb(1, &mDuckAmountDb, NUM_VAL_NO_TRAILING_ZEROES);
         vldDuckAmountDb.SetRange(MIN_DuckAmountDb, MAX_DuckAmountDb);
         mDuckAmountDbBox = S.AddTextBox(_("Duck amount:"), wxT(""), 10);
         mDuckAmountDbBox->SetValidator(vldDuckAmountDb);
         S.AddUnits(_("dB"));

         FloatingPointValidator<double> vldMaximumPause(2, &mMaximumPause, NUM_VAL_NO_TRAILING_ZEROES);
         vldMaximumPause.SetRange(MIN_MaximumPause, MAX_MaximumPause);
         mMaximumPauseBox = S.AddTextBox(_("Maximum pause:"), wxT(""), 10);
         mMaximumPauseBox->SetValidator(vldMaximumPause);
         S.AddUnits(_("seconds"));

         FloatingPointValidator<double> vldOuterFadeDownLen(2, &mOuterFadeDownLen, NUM_VAL_NO_TRAILING_ZEROES);
         vldOuterFadeDownLen.SetRange(MIN_OuterFadeDownLen, MAX_OuterFadeDownLen);
         mOuterFadeDownLenBox = S.AddTextBox(_("Outer fade down length:"), wxT(""), 10);
         mOuterFadeDownLenBox->SetValidator(vldOuterFadeDownLen);
         S.AddUnits(_("seconds"));

         FloatingPointValidator<double> vldOuterFadeUpLen(2, &mOuterFadeUpLen, NUM_VAL_NO_TRAILING_ZEROES);
         vldOuterFadeUpLen.SetRange(MIN_OuterFadeUpLen, MAX_OuterFadeUpLen);
         mOuterFadeUpLenBox = S.AddTextBox(_("Outer fade up length:"), wxT(""), 10);
         mOuterFadeUpLenBox->SetValidator(vldOuterFadeUpLen);
         S.AddUnits(_("seconds"));

         FloatingPointValidator<double> vldInnerFadeDownLen(2, &mInnerFadeDownLen, NUM_VAL_NO_TRAILING_ZEROES);
         vldInnerFadeDownLen.SetRange(MIN_InnerFadeDownLen, MAX_InnerFadeDownLen);
         mInnerFadeDownLenBox = S.AddTextBox(_("Inner fade down length:"), wxT(""), 10);
         mInnerFadeDownLenBox->SetValidator(vldInnerFadeDownLen);
         S.AddUnits(_("seconds"));

         FloatingPointValidator<double> vldInnerFadeUpLen(2, &mInnerFadeUpLen, NUM_VAL_NO_TRAILING_ZEROES);
         vldInnerFadeUpLen.SetRange(MIN_InnerFadeUpLen, MAX_InnerFadeUpLen);
         mInnerFadeUpLenBox = S.AddTextBox(_("Inner fade up length:"), wxT(""), 10);
         mInnerFadeUpLenBox->SetValidator(vldInnerFadeUpLen);
         S.AddUnits(_("seconds"));
      }
      S.EndMultiColumn();

      S.StartMultiColumn(3, wxCENTER);
      {
         FloatingPointValidator<double> vldThresholdDb(2, &mThresholdDb, NUM_VAL_NO_TRAILING_ZEROES);
         vldThresholdDb.SetRange(MIN_ThresholdDb, MAX_ThresholdDb);
         mThresholdDbBox = S.AddTextBox(_("Threshold:"), wxT(""), 10);
         mThresholdDbBox->SetValidator(vldThresholdDb);
         S.AddUnits(_("dB"));
      }
      S.EndMultiColumn();

   }
   S.EndVerticalLay();

   return;
}