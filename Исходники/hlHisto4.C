void hlHisto4()
{
   TCanvas *c1 = new TCanvas("c1", "", 0, 0, 600, 400);
   TF1 *f1 = new TF1("f1", "x*gaus(0) + [3]*abs(sin(x)/x)", -50.0, 50.0);
   f1->SetParameters(20.0, 4.0, 1.0, 20.0);
   TH1F *h1 = new TH1F("h1", "Test random numbers", 200, -50.0, 50.0);
   h1->FillRandom("f1", 100000);
   h1->Draw();
   h1->Fit(f1, "Q");
   gStyle->SetGridColor(kGray);
   c1->SetGrid();

   TText *info = new TText(0.0, h1->GetMaximum()*0.7, "please move the mouse over the frame");
   info->SetTextSize(0.04);
   info->SetTextAlign(22);
   info->SetTextColor(kRed-1);
   info->SetBit(kCannotPick);
   info->Draw();
   c1->Update();

   h1->SetHighlight();
   c1->HighlightConnect("HighlightZoom(TVirtualPad*,TObject*,Int_t,Int_t)");
}