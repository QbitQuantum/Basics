//---------------------------------------------------------------------------
void __fastcall TExtOptDialog::GetExtErrOpt(void)
{
    TEdit *editc[][6]= {
        {CodeErr00,CodeErr01,CodeErr02,CodeErr03,CodeErr04,CodeErr05},
        {CodeErr10,CodeErr11,CodeErr12,CodeErr13,CodeErr14,CodeErr15},
        {CodeErr20,CodeErr21,CodeErr22,CodeErr23,CodeErr24,CodeErr25}
    };
    TEdit *editp[][6]= {
        {PhaseErr00,PhaseErr01,PhaseErr02,PhaseErr03,PhaseErr04,PhaseErr05},
        {PhaseErr10,PhaseErr11,PhaseErr12,PhaseErr13,PhaseErr14,PhaseErr15},
        {PhaseErr20,PhaseErr21,PhaseErr22,PhaseErr23,PhaseErr24,PhaseErr25}
    };
    AnsiString s;

    ExtEna0->Checked=OptDialog->ExtErr.ena[0];
    ExtEna1->Checked=OptDialog->ExtErr.ena[1];
    ExtEna2->Checked=OptDialog->ExtErr.ena[2];
    ExtEna3->Checked=OptDialog->ExtErr.ena[3];

    for (int i=0; i<3; i++) for (int j=0; j<6; j++) {
            editc[i][j]->Text=s.sprintf("%.3f",OptDialog->ExtErr.cerr[i][j]);
            editp[i][j]->Text=s.sprintf("%.3f",OptDialog->ExtErr.perr[i][j]);
        }
    GpsGloB0->Text=s.sprintf("%.3f",OptDialog->ExtErr.gpsglob[0]);
    GpsGloB1->Text=s.sprintf("%.3f",OptDialog->ExtErr.gpsglob[1]);
    GloICB0->Text=s.sprintf("%.3f",OptDialog->ExtErr.gloicb[0]);
    GloICB1->Text=s.sprintf("%.3f",OptDialog->ExtErr.gloicb[1]);
}