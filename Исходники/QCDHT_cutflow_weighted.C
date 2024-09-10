void QCDHT_cutflow_weighted()
{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Feb 24 17:48:49 2016) by ROOT version6.02/05
   TCanvas *c1 = new TCanvas("c1", "c1",65,52,700,500);
   c1->Range(-1.25,-2351156,16.25,2.11604e+07);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *cutflow1 = new TH1D("cutflow1","cut flow",14,0.5,14.5);
   cutflow1->SetBinContent(1,1.791357e+07);
   cutflow1->SetBinContent(2,1.791357e+07);
   cutflow1->SetBinContent(3,1.482016e+07);
   cutflow1->SetBinContent(4,1.397007e+07);
   cutflow1->SetBinContent(5,8159947);
   cutflow1->SetBinContent(6,1368453);
   cutflow1->SetBinContent(7,12035.83);
   cutflow1->SetBinContent(8,10653.79);
   cutflow1->SetBinContent(9,4100.401);
   cutflow1->SetBinContent(10,4323.004);
   cutflow1->SetBinContent(11,1820.803);
   cutflow1->SetBinContent(12,374.2397);
   cutflow1->SetBinContent(13,35.33991);
   cutflow1->SetBinContent(14,214.6597);
   cutflow1->SetEntries(1.137194e+08);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("cutflow");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries =   1.137194e+08");
   AText = ptstats->AddText("Mean  =      0");
   AText = ptstats->AddText("RMS   =      0");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   cutflow1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(cutflow1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   cutflow1->SetLineColor(ci);
   cutflow1->GetXaxis()->SetBinLabel(1,"All");
   cutflow1->GetXaxis()->SetBinLabel(2,"Trigger");
   cutflow1->GetXaxis()->SetBinLabel(3,"p_{T}");
   cutflow1->GetXaxis()->SetBinLabel(4,"|#eta|");
   cutflow1->GetXaxis()->SetBinLabel(5,"|#Delta#eta|");
   cutflow1->GetXaxis()->SetBinLabel(6,"M(jet_{0},jet(1))");
   cutflow1->GetXaxis()->SetBinLabel(7,"M(jets)");
   cutflow1->GetXaxis()->SetBinLabel(8,"#tau_{21}");
   cutflow1->GetXaxis()->SetBinLabel(9,"0b");
   cutflow1->GetXaxis()->SetBinLabel(10,"1b");
   cutflow1->GetXaxis()->SetBinLabel(11,"2b");
   cutflow1->GetXaxis()->SetBinLabel(12,"3b");
   cutflow1->GetXaxis()->SetBinLabel(13,"4b");
   cutflow1->GetXaxis()->SetBinLabel(14,"3b+HPHP");
   cutflow1->GetXaxis()->SetLabelFont(42);
   cutflow1->GetXaxis()->SetLabelSize(0.035);
   cutflow1->GetXaxis()->SetTitleSize(0.035);
   cutflow1->GetXaxis()->SetTitleFont(42);
   cutflow1->GetYaxis()->SetLabelFont(42);
   cutflow1->GetYaxis()->SetLabelSize(0.035);
   cutflow1->GetYaxis()->SetTitleSize(0.035);
   cutflow1->GetYaxis()->SetTitleFont(42);
   cutflow1->GetZaxis()->SetLabelFont(42);
   cutflow1->GetZaxis()->SetLabelSize(0.035);
   cutflow1->GetZaxis()->SetTitleSize(0.035);
   cutflow1->GetZaxis()->SetTitleFont(42);
   cutflow1->Draw("");
   
   TPaveText *pt = new TPaveText(0.4246264,0.94,0.5753736,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("cut flow");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}