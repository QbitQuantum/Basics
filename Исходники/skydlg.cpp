//---------------------------------------------------------------------------
void __fastcall TSkyImgDialog::UpdateField(void)
{
    AnsiString s;
    Caption=Plot->SkyImageFile;
    SkySize1->Text=s.sprintf("%d",Plot->SkySize[0]);
    SkySize2->Text=s.sprintf("%d",Plot->SkySize[1]);
    SkyCent1->Text=s.sprintf("%.2f",Plot->SkyCent[0]);
    SkyCent2->Text=s.sprintf("%.2f",Plot->SkyCent[1]);
    SkyScale->Text=s.sprintf("%.2f",Plot->SkyScale);
    SkyFov1 ->Text=s.sprintf("%.2f",Plot->SkyFov[0]);
    SkyFov2 ->Text=s.sprintf("%.2f",Plot->SkyFov[1]);
    SkyFov3 ->Text=s.sprintf("%.2f",Plot->SkyFov[2]);
    SkyDest1->Text=s.sprintf("%.1f",Plot->SkyDest[1]);
    SkyDest2->Text=s.sprintf("%.1f",Plot->SkyDest[2]);
    SkyDest3->Text=s.sprintf("%.1f",Plot->SkyDest[3]);
    SkyDest4->Text=s.sprintf("%.1f",Plot->SkyDest[4]);
    SkyDest5->Text=s.sprintf("%.1f",Plot->SkyDest[5]);
    SkyDest6->Text=s.sprintf("%.1f",Plot->SkyDest[6]);
    SkyDest7->Text=s.sprintf("%.1f",Plot->SkyDest[7]);
    SkyDest8->Text=s.sprintf("%.1f",Plot->SkyDest[8]);
    SkyDest9->Text=s.sprintf("%.1f",Plot->SkyDest[9]);
    SkyElMask->Checked=Plot->SkyElMask;
    SkyDestCorr->Checked=Plot->SkyDestCorr;
    SkyRes->ItemIndex=Plot->SkyRes;
    SkyFlip->Checked=Plot->SkyFlip;
}