void DarkSusy_mH_125_mGammaD_2000_cT_10_LHE_gammaD_L_Z()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May 24 15:17:52 2015) by ROOT version6.02/05
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-10.625,-0.01311612,51.875,0.08777715);
   cnv->SetFillColor(0);
   cnv->SetBorderMode(0);
   cnv->SetBorderSize(2);
   cnv->SetTickx(1);
   cnv->SetTicky(1);
   cnv->SetLeftMargin(0.17);
   cnv->SetRightMargin(0.03);
   cnv->SetTopMargin(0.07);
   cnv->SetBottomMargin(0.13);
   cnv->SetFrameFillStyle(0);
   cnv->SetFrameBorderMode(0);
   cnv->SetFrameFillStyle(0);
   cnv->SetFrameBorderMode(0);
   
   TH1F *h_gammaD_cT_Z_lab_dummy57 = new TH1F("h_gammaD_cT_Z_lab_dummy57","h_gammaD_cT_Z_lab_dummy",5,0,50);
   h_gammaD_cT_Z_lab_dummy57->SetMaximum(0.08071462);
   h_gammaD_cT_Z_lab_dummy57->SetLineStyle(0);
   h_gammaD_cT_Z_lab_dummy57->SetMarkerStyle(20);
   h_gammaD_cT_Z_lab_dummy57->GetXaxis()->SetTitle("L_{Z} of #gamma_{D} [mm]");
   h_gammaD_cT_Z_lab_dummy57->GetXaxis()->SetLabelFont(42);
   h_gammaD_cT_Z_lab_dummy57->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_Z_lab_dummy57->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_cT_Z_lab_dummy57->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_cT_Z_lab_dummy57->GetXaxis()->SetTitleFont(42);
   h_gammaD_cT_Z_lab_dummy57->GetYaxis()->SetTitle("Normalized Fraction of events / 10.0 mm");
   h_gammaD_cT_Z_lab_dummy57->GetYaxis()->SetLabelFont(42);
   h_gammaD_cT_Z_lab_dummy57->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_Z_lab_dummy57->GetYaxis()->SetTitleSize(0.05);
   h_gammaD_cT_Z_lab_dummy57->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_cT_Z_lab_dummy57->GetYaxis()->SetTitleFont(42);
   h_gammaD_cT_Z_lab_dummy57->GetZaxis()->SetLabelFont(42);
   h_gammaD_cT_Z_lab_dummy57->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_Z_lab_dummy57->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_cT_Z_lab_dummy57->GetZaxis()->SetTitleFont(42);
   h_gammaD_cT_Z_lab_dummy57->Draw("");
   
   TH1F *h_gammaD_cT_Z_lab58 = new TH1F("h_gammaD_cT_Z_lab58","h_gammaD_cT_Z_lab",5,0,50);
   h_gammaD_cT_Z_lab58->SetBinContent(1,0.04484145);
   h_gammaD_cT_Z_lab58->SetBinContent(2,0.02460945);
   h_gammaD_cT_Z_lab58->SetBinContent(3,0.01479324);
   h_gammaD_cT_Z_lab58->SetBinContent(4,0.009401793);
   h_gammaD_cT_Z_lab58->SetBinContent(5,0.006354062);
   h_gammaD_cT_Z_lab58->SetBinContent(6,0.03052218);
   h_gammaD_cT_Z_lab58->SetEntries(159998);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_gammaD_cT_Z_lab58->SetLineColor(ci);
   h_gammaD_cT_Z_lab58->SetLineWidth(2);
   h_gammaD_cT_Z_lab58->SetMarkerStyle(20);
   h_gammaD_cT_Z_lab58->GetXaxis()->SetTitle("L_{z} of #gamma_{D} [mm]");
   h_gammaD_cT_Z_lab58->GetXaxis()->SetLabelFont(42);
   h_gammaD_cT_Z_lab58->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_Z_lab58->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_cT_Z_lab58->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_cT_Z_lab58->GetXaxis()->SetTitleFont(42);
   h_gammaD_cT_Z_lab58->GetYaxis()->SetTitle("Events");
   h_gammaD_cT_Z_lab58->GetYaxis()->SetLabelFont(42);
   h_gammaD_cT_Z_lab58->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_Z_lab58->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_cT_Z_lab58->GetYaxis()->SetTitleOffset(1.5);
   h_gammaD_cT_Z_lab58->GetYaxis()->SetTitleFont(42);
   h_gammaD_cT_Z_lab58->GetZaxis()->SetLabelFont(42);
   h_gammaD_cT_Z_lab58->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_cT_Z_lab58->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_cT_Z_lab58->GetZaxis()->SetTitleFont(42);
   h_gammaD_cT_Z_lab58->Draw("same");
   
   TLegend *leg = new TLegend(0.4566667,0.82,0.7822222,0.9066667,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.02777778);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","#splitline{pp #rightarrow h #rightarrow 2n_{1} #rightarrow 2n_{D} + 2 #gamma_{D} #rightarrow 2n_{D} + 4#mu}{#splitline{m_{h} = 125 GeV, m_{n_{1}} = 50 GeV, m_{n_{D}} = 1 GeV}{m_{#gamma_{D}} = 20 GeV, c#tau_{#gamma_{D}} = 10 mm}}","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.17,0.935,0.97,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextAlign(22);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","CMS Simulation (LHE) 14 TeV","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   cnv->Modified();
   cnv->cd();
   cnv->SetSelected(cnv);
}