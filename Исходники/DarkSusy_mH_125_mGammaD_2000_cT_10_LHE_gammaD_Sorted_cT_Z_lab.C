void DarkSusy_mH_125_mGammaD_2000_cT_10_LHE_gammaD_Sorted_cT_Z_lab()
{
//=========Macro generated from canvas: cnv/cnv
//=========  (Sun May 24 15:17:53 2015) by ROOT version6.02/05
   TCanvas *cnv = new TCanvas("cnv", "cnv",1,1,904,904);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cnv->SetHighLightColor(2);
   cnv->Range(-10.625,-0.01342717,51.875,0.08985876);
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
   
   TH1F *h_gammaD_1_cT_Z_lab_dummy68 = new TH1F("h_gammaD_1_cT_Z_lab_dummy68","h_gammaD_1_cT_Z_lab_dummy",5,0,50);
   h_gammaD_1_cT_Z_lab_dummy68->SetMaximum(0.08262875);
   h_gammaD_1_cT_Z_lab_dummy68->SetLineStyle(0);
   h_gammaD_1_cT_Z_lab_dummy68->SetMarkerStyle(20);
   h_gammaD_1_cT_Z_lab_dummy68->GetXaxis()->SetTitle("L_{Z} of #gamma_{D} [mm]");
   h_gammaD_1_cT_Z_lab_dummy68->GetXaxis()->SetLabelFont(42);
   h_gammaD_1_cT_Z_lab_dummy68->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_Z_lab_dummy68->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_Z_lab_dummy68->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_1_cT_Z_lab_dummy68->GetXaxis()->SetTitleFont(42);
   h_gammaD_1_cT_Z_lab_dummy68->GetYaxis()->SetTitle("Normalized Fraction of events / 10.0 mm");
   h_gammaD_1_cT_Z_lab_dummy68->GetYaxis()->SetLabelFont(42);
   h_gammaD_1_cT_Z_lab_dummy68->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_Z_lab_dummy68->GetYaxis()->SetTitleSize(0.05);
   h_gammaD_1_cT_Z_lab_dummy68->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_1_cT_Z_lab_dummy68->GetYaxis()->SetTitleFont(42);
   h_gammaD_1_cT_Z_lab_dummy68->GetZaxis()->SetLabelFont(42);
   h_gammaD_1_cT_Z_lab_dummy68->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_Z_lab_dummy68->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_Z_lab_dummy68->GetZaxis()->SetTitleFont(42);
   h_gammaD_1_cT_Z_lab_dummy68->Draw("");
   
   TH1F *h_gammaD_1_cT_Z_lab69 = new TH1F("h_gammaD_1_cT_Z_lab69","h_gammaD_1_cT_Z_lab",5,0,50);
   h_gammaD_1_cT_Z_lab69->SetBinContent(1,0.04371162);
   h_gammaD_1_cT_Z_lab69->SetBinContent(2,0.02445529);
   h_gammaD_1_cT_Z_lab69->SetBinContent(3,0.01502482);
   h_gammaD_1_cT_Z_lab69->SetBinContent(4,0.01002103);
   h_gammaD_1_cT_Z_lab69->SetBinContent(5,0.006787247);
   h_gammaD_1_cT_Z_lab69->SetBinContent(6,0.03459914);
   h_gammaD_1_cT_Z_lab69->SetEntries(79999);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h_gammaD_1_cT_Z_lab69->SetLineColor(ci);
   h_gammaD_1_cT_Z_lab69->SetLineWidth(2);
   h_gammaD_1_cT_Z_lab69->SetMarkerStyle(20);
   h_gammaD_1_cT_Z_lab69->GetXaxis()->SetLabelFont(42);
   h_gammaD_1_cT_Z_lab69->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_Z_lab69->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_Z_lab69->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_1_cT_Z_lab69->GetXaxis()->SetTitleFont(42);
   h_gammaD_1_cT_Z_lab69->GetYaxis()->SetLabelFont(42);
   h_gammaD_1_cT_Z_lab69->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_Z_lab69->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_Z_lab69->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_1_cT_Z_lab69->GetYaxis()->SetTitleFont(42);
   h_gammaD_1_cT_Z_lab69->GetZaxis()->SetLabelFont(42);
   h_gammaD_1_cT_Z_lab69->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_1_cT_Z_lab69->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_1_cT_Z_lab69->GetZaxis()->SetTitleFont(42);
   h_gammaD_1_cT_Z_lab69->Draw("same");
   
   TH1F *h_gammaD_2_cT_Z_lab70 = new TH1F("h_gammaD_2_cT_Z_lab70","h_gammaD_2_cT_Z_lab",5,0,50);
   h_gammaD_2_cT_Z_lab70->SetBinContent(1,0.04590486);
   h_gammaD_2_cT_Z_lab70->SetBinContent(2,0.02475454);
   h_gammaD_2_cT_Z_lab70->SetBinContent(3,0.01457528);
   h_gammaD_2_cT_Z_lab70->SetBinContent(4,0.008818965);
   h_gammaD_2_cT_Z_lab70->SetBinContent(5,0.005946348);
   h_gammaD_2_cT_Z_lab70->SetBinContent(6,0.02668493);
   h_gammaD_2_cT_Z_lab70->SetEntries(79999);

   ci = TColor::GetColor("#ff0000");
   h_gammaD_2_cT_Z_lab70->SetLineColor(ci);
   h_gammaD_2_cT_Z_lab70->SetLineWidth(2);
   h_gammaD_2_cT_Z_lab70->SetMarkerStyle(20);
   h_gammaD_2_cT_Z_lab70->GetXaxis()->SetLabelFont(42);
   h_gammaD_2_cT_Z_lab70->GetXaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_Z_lab70->GetXaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_Z_lab70->GetXaxis()->SetTitleOffset(0.95);
   h_gammaD_2_cT_Z_lab70->GetXaxis()->SetTitleFont(42);
   h_gammaD_2_cT_Z_lab70->GetYaxis()->SetLabelFont(42);
   h_gammaD_2_cT_Z_lab70->GetYaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_Z_lab70->GetYaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_Z_lab70->GetYaxis()->SetTitleOffset(1.3);
   h_gammaD_2_cT_Z_lab70->GetYaxis()->SetTitleFont(42);
   h_gammaD_2_cT_Z_lab70->GetZaxis()->SetLabelFont(42);
   h_gammaD_2_cT_Z_lab70->GetZaxis()->SetLabelOffset(0.007);
   h_gammaD_2_cT_Z_lab70->GetZaxis()->SetTitleSize(0.06);
   h_gammaD_2_cT_Z_lab70->GetZaxis()->SetTitleFont(42);
   h_gammaD_2_cT_Z_lab70->Draw("same");
   
   TLegend *leg = new TLegend(0.46,0.6744444,0.6955556,0.7644444,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.02777778);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("h_gammaD_1_cT_Z_lab","1st dark photon (leading p_{T})","L");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h_gammaD_2_cT_Z_lab","2nd dark photon","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.4566667,0.82,0.7822222,0.9066667,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.02777778);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","#splitline{pp #rightarrow h #rightarrow 2n_{1} #rightarrow 2n_{D} + 2 #gamma_{D} #rightarrow 2n_{D} + 4#mu}{#splitline{m_{h} = 125 GeV, m_{n_{1}} = 50 GeV, m_{n_{D}} = 1 GeV}{m_{#gamma_{D}} = 20 GeV, c#tau_{#gamma_{D}} = 10 mm}}","h");
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