void SetupTowerDisplay(TH2F *hist)
{
  hist->SetStats(kFALSE);
  hist->SetXTitle("ieta");
  hist->SetYTitle("iphi");
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();
  hist->GetXaxis()->SetNdivisions(65);
  hist->GetXaxis()->SetLabelColor(0);
  hist->GetXaxis()->SetTickLength(.78);
  hist->GetXaxis()->SetTitleOffset(0.95);
  hist->GetYaxis()->SetNdivisions(72);
  hist->GetYaxis()->SetLabelColor(0);
  hist->GetYaxis()->SetTitleOffset(0.85);
  TText *yLabel = new TText();
  TLine *pLine = new TLine();
  pLine->SetLineStyle(1);
  pLine->SetLineColor(1);
  pLine->SetLineWidth(1);
  yLabel->SetTextAlign(22);
  yLabel->SetTextSize(0.015);
  char phi_num[3];
  char eta_num[3];
  TText *xLabel = new TText();
  xLabel->SetTextSize(0.015);
  xLabel->SetTextAlign(22);
  for (Int_t i=1; i<73; ++i)
    {
      sprintf(phi_num,"%d",i);
      if(TMath::Abs(i%2)==1) {yLabel->DrawText(-33,0.5+i,phi_num);}
      else {yLabel->DrawText(-34.5,0.5+i,phi_num);}
      pLine->DrawLine(-32,i,33,i);
    }
  for (Int_t i=-32; i<33;++i)
    {
      sprintf(eta_num,"%d",i);
      if(TMath::Abs(i%2)==0) {xLabel->DrawText(0.5+i,-0.5,eta_num);}
      else {xLabel->DrawText(0.5+i,-2,eta_num);}
      pLine->DrawLine(i,1,i,72);
    }
}