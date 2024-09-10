void DarkSusy_mH_125_mGammaD_2000_cT_1000_LHE_dimuon_m1_vs_m2()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May 24 15:19:04 2015) by ROOT version6.02/05
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-10.36674,-7.877387,51.86701,54.35636);
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
   
   TH2F *h_m1_vs_m2113 = new TH2F("h_m1_vs_m2113","h_m1_vs_m2",500,0.213,50,100,0.213,50);
   h_m1_vs_m2113->SetBinContent(20279,79998);
   h_m1_vs_m2113->SetBinContent(20280,1);
   h_m1_vs_m2113->SetEntries(79999);
   h_m1_vs_m2113->SetLineStyle(0);
   h_m1_vs_m2113->SetMarkerStyle(20);
   h_m1_vs_m2113->GetXaxis()->SetTitle("m_{2#mu#mu} [GeV]");
   h_m1_vs_m2113->GetXaxis()->SetLabelFont(42);
   h_m1_vs_m2113->GetXaxis()->SetLabelOffset(0.007);
   h_m1_vs_m2113->GetXaxis()->SetTitleSize(0.06);
   h_m1_vs_m2113->GetXaxis()->SetTitleOffset(0.95);
   h_m1_vs_m2113->GetXaxis()->SetTitleFont(42);
   h_m1_vs_m2113->GetYaxis()->SetTitle("m_{1#mu#mu} [GeV]");
   h_m1_vs_m2113->GetYaxis()->SetLabelFont(42);
   h_m1_vs_m2113->GetYaxis()->SetLabelOffset(0.007);
   h_m1_vs_m2113->GetYaxis()->SetTitleSize(0.06);
   h_m1_vs_m2113->GetYaxis()->SetTitleOffset(1.3);
   h_m1_vs_m2113->GetYaxis()->SetTitleFont(42);
   h_m1_vs_m2113->GetZaxis()->SetLabelFont(42);
   h_m1_vs_m2113->GetZaxis()->SetLabelOffset(0.007);
   h_m1_vs_m2113->GetZaxis()->SetTitleSize(0.06);
   h_m1_vs_m2113->GetZaxis()->SetTitleFont(42);
   h_m1_vs_m2113->Draw("");
   
   TLegend *leg = new TLegend(0.4566667,0.82,0.7822222,0.9066667,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.02777778);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","#splitline{pp #rightarrow h #rightarrow 2n_{1} #rightarrow 2n_{D} + 2 #gamma_{D} #rightarrow 2n_{D} + 4#mu}{#splitline{m_{h} = 125 GeV, m_{n_{1}} = 50 GeV, m_{n_{D}} = 1 GeV}{m_{#gamma_{D}} = 20 GeV, c#tau_{#gamma_{D}} = 1000 mm}}","h");
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