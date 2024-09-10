void EffectSilence::PopulateOrExchange(ShuttleGui & S)
{
   S.StartVerticalLay();
   {
      S.StartHorizontalLay();
      {
         S.AddPrompt(_("Duration:"));
         mDurationT = new
            NumericTextCtrl(NumericConverter::TIME,
                              S.GetParent(),
                              wxID_ANY,
                              GetDurationFormat(),
                              GetDuration(),
                              mProjectRate,
                              wxDefaultPosition,
                              wxDefaultSize,
                              true);
         mDurationT->SetName(_("Duration"));
         mDurationT->EnableMenu();
         S.AddWindow(mDurationT, wxALIGN_CENTER | wxALL);
      }
      S.EndHorizontalLay();
   }
   S.EndVerticalLay();

   return;
}