void effAndSmallSF_DATA_MC_Cracks_pT2()
{
//=========Macro generated from canvas: Canvas/Canvas
//=========  (Mon Feb  8 17:29:37 2016) by ROOT version6.02/05
   TCanvas *Canvas = new TCanvas("Canvas", "Canvas",0,0,725,725);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   Canvas->SetHighLightColor(2);
   Canvas->Range(0,0,1,1);
   Canvas->SetFillColor(0);
   Canvas->SetBorderMode(0);
   Canvas->SetBorderSize(2);
   Canvas->SetTickx(1);
   Canvas->SetTicky(1);
   Canvas->SetLeftMargin(0.15);
   Canvas->SetRightMargin(0.05);
   Canvas->SetTopMargin(0.07);
   Canvas->SetBottomMargin(0.17);
   Canvas->SetFrameFillStyle(0);
   Canvas->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "pad1",0.01,0.3,0.99,0.99);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-15.32432,-0.03620689,94.13513,1.17069);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetGridx();
   pad1->SetGridy();
   pad1->SetTickx(1);
   pad1->SetTicky(1);
   pad1->SetLeftMargin(0.14);
   pad1->SetRightMargin(0.12);
   pad1->SetBottomMargin(0.03);
   pad1->SetFrameFillStyle(0);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameFillStyle(0);
   pad1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx3001[3] = {
   13.5,
   25,
   55};
   Double_t Graph0_fy3001[3] = {
   0.9387,
   0.9652,
   0.9863};
   Double_t Graph0_felx3001[3] = {
   6.5,
   5,
   25};
   Double_t Graph0_fely3001[3] = {
   0.0034,
   0.0013,
   0.0003};
   Double_t Graph0_fehx3001[3] = {
   6.5,
   5,
   25};
   Double_t Graph0_fehy3001[3] = {
   0.0034,
   0.0013,
   0.0003};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(3,Graph0_fx3001,Graph0_fy3001,Graph0_felx3001,Graph0_fehx3001,Graph0_fely3001,Graph0_fehy3001);
   grae->SetName("Graph0");
   grae->SetTitle("TGraphAsymmErrors for MC efficiencies");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#99ccff");
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#3399ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#3399ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(22);
   grae->SetMarkerSize(0.7);
   
   TH1F *Graph_TH1F3001 = new TH1F("Graph_TH1F3001","TH1F histogram",100,0,81);
   Graph_TH1F3001->SetMinimum(0);
   Graph_TH1F3001->SetMaximum(1.05);
   Graph_TH1F3001->SetFillStyle(0);
   Graph_TH1F3001->SetLineStyle(0);
   Graph_TH1F3001->SetMarkerStyle(20);
   Graph_TH1F3001->GetXaxis()->SetLabelFont(42);
   Graph_TH1F3001->GetXaxis()->SetLabelOffset(0.007);
   Graph_TH1F3001->GetXaxis()->SetLabelSize(0);
   Graph_TH1F3001->GetXaxis()->SetTitleSize(0.06);
   Graph_TH1F3001->GetXaxis()->SetTitleFont(42);
   Graph_TH1F3001->GetYaxis()->SetTitle("ID efficiency");
   Graph_TH1F3001->GetYaxis()->SetLabelFont(42);
   Graph_TH1F3001->GetYaxis()->SetLabelOffset(0.007);
   Graph_TH1F3001->GetYaxis()->SetLabelSize(0.05);
   Graph_TH1F3001->GetYaxis()->SetTitleSize(0.06);
   Graph_TH1F3001->GetYaxis()->SetTitleOffset(0.85);
   Graph_TH1F3001->GetYaxis()->SetTitleFont(42);
   Graph_TH1F3001->GetZaxis()->SetLabelFont(42);
   Graph_TH1F3001->GetZaxis()->SetLabelOffset(0.007);
   Graph_TH1F3001->GetZaxis()->SetLabelSize(0.05);
   Graph_TH1F3001->GetZaxis()->SetTitleSize(0.06);
   Graph_TH1F3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_TH1F3001);
   
   grae->Draw("a2");
   
   Double_t Graph0_fx3002[3] = {
   13.5,
   25,
   55};
   Double_t Graph0_fy3002[3] = {
   0.9387,
   0.9652,
   0.9863};
   Double_t Graph0_felx3002[3] = {
   6.5,
   5,
   25};
   Double_t Graph0_fely3002[3] = {
   0.0034,
   0.0013,
   0.0003};
   Double_t Graph0_fehx3002[3] = {
   6.5,
   5,
   25};
   Double_t Graph0_fehy3002[3] = {
   0.0034,
   0.0013,
   0.0003};
   grae = new TGraphAsymmErrors(3,Graph0_fx3002,Graph0_fy3002,Graph0_felx3002,Graph0_fehx3002,Graph0_fely3002,Graph0_fehy3002);
   grae->SetName("Graph0");
   grae->SetTitle("TGraphAsymmErrors for MC efficiencies");

   ci = TColor::GetColor("#99ccff");
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#3399ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#3399ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(22);
   grae->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph_TH1F30013002 = new TH1F("Graph_Graph_TH1F30013002","TH1F histogram",100,0,81);
   Graph_Graph_TH1F30013002->SetMinimum(0);
   Graph_Graph_TH1F30013002->SetMaximum(1.05);
   Graph_Graph_TH1F30013002->SetFillStyle(0);
   Graph_Graph_TH1F30013002->SetLineStyle(0);
   Graph_Graph_TH1F30013002->SetMarkerStyle(20);
   Graph_Graph_TH1F30013002->GetXaxis()->SetLabelFont(42);
   Graph_Graph_TH1F30013002->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_TH1F30013002->GetXaxis()->SetLabelSize(0);
   Graph_Graph_TH1F30013002->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_TH1F30013002->GetXaxis()->SetTitleFont(42);
   Graph_Graph_TH1F30013002->GetYaxis()->SetTitle("ID efficiency");
   Graph_Graph_TH1F30013002->GetYaxis()->SetLabelFont(42);
   Graph_Graph_TH1F30013002->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_TH1F30013002->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_TH1F30013002->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_TH1F30013002->GetYaxis()->SetTitleOffset(0.85);
   Graph_Graph_TH1F30013002->GetYaxis()->SetTitleFont(42);
   Graph_Graph_TH1F30013002->GetZaxis()->SetLabelFont(42);
   Graph_Graph_TH1F30013002->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph_TH1F30013002->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph_TH1F30013002->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph_TH1F30013002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_TH1F30013002);
   
   grae->Draw("p");
   
   Double_t Graph1_fx3003[3] = {
   13.5,
   25,
   55};
   Double_t Graph1_fy3003[3] = {
   0.973,
   0.9563,
   0.9835};
   Double_t Graph1_felx3003[3] = {
   6.5,
   5,
   25};
   Double_t Graph1_fely3003[3] = {
   0.004,
   0.0015,
   0.0009};
   Double_t Graph1_fehx3003[3] = {
   6.5,
   5,
   25};
   Double_t Graph1_fehy3003[3] = {
   0.004,
   0.0015,
   0.0009};
   grae = new TGraphAsymmErrors(3,Graph1_fx3003,Graph1_fy3003,Graph1_felx3003,Graph1_fehx3003,Graph1_fely3003,Graph1_fehy3003);
   grae->SetName("Graph1");
   grae->SetTitle("TGraphAsymmErrors for Data efficiencies");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(9);
   grae->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph3003 = new TH1F("Graph_Graph3003","TGraphAsymmErrors for Data efficiencies",100,0,87.3);
   Graph_Graph3003->SetMinimum(0.95184);
   Graph_Graph3003->SetMaximum(0.98736);
   Graph_Graph3003->SetDirectory(0);
   Graph_Graph3003->SetStats(0);
   Graph_Graph3003->SetFillStyle(0);
   Graph_Graph3003->SetLineStyle(0);
   Graph_Graph3003->SetMarkerStyle(20);
   Graph_Graph3003->GetXaxis()->SetLabelFont(42);
   Graph_Graph3003->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph3003->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph3003->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph3003->GetXaxis()->SetTitleFont(42);
   Graph_Graph3003->GetYaxis()->SetLabelFont(42);
   Graph_Graph3003->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph3003->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph3003->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph3003->GetYaxis()->SetTitleOffset(0.85);
   Graph_Graph3003->GetYaxis()->SetTitleFont(42);
   Graph_Graph3003->GetZaxis()->SetLabelFont(42);
   Graph_Graph3003->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph3003->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph3003->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3003);
   
   grae->Draw("p");
   
   TLegend *leg = new TLegend(0.63,0.2,0.87,0.33,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.03);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph1","Data","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(9);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph0","Simulation","fp");

   ci = TColor::GetColor("#99ccff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#3399ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#3399ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(62);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.14,0.94,0.89,0.99,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.03);
   TText *AText = pt->AddText(0.01,0.3,"CMS Preliminary");
   AText = pt->AddText(0.7,0.3,"#sqrt{s} = 13 TeV, L = 2.26 fb^{-1}");
   pt->Draw();
      tex = new TLatex(0.67,0.4,"Z #rightarrow e^{+} e^{-}");
tex->SetNDC();
   tex->SetTextSize(0.03);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.63,0.35," Crack probes");
tex->SetNDC();
   tex->SetTextSize(0.03);
   tex->SetLineWidth(2);
   tex->Draw();
   pad1->Modified();
   Canvas->cd();
  
// ------------>Primitives in pad: pad2
   TPad *pad2 = new TPad("pad2", "pad2",0.01,0.01,0.99,0.3);
   pad2->Draw();
   pad2->cd();
   pad2->Range(-15.32432,0.4915493,94.13513,1.125352);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetGridx();
   pad2->SetGridy();
   pad2->SetTickx(1);
   pad2->SetTicky(1);
   pad2->SetLeftMargin(0.14);
   pad2->SetRightMargin(0.12);
   pad2->SetTopMargin(0.04);
   pad2->SetBottomMargin(0.25);
   pad2->SetFrameFillStyle(0);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameFillStyle(0);
   pad2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx3004[3] = {
   13.5,
   25,
   55};
   Double_t Graph0_fy3004[3] = {
   1.0365,
   0.9908,
   0.9971};
   Double_t Graph0_felx3004[3] = {
   6.5,
   5,
   25};
   Double_t Graph0_fely3004[3] = {
   0.009,
   0.0082,
   0.0016};
   Double_t Graph0_fehx3004[3] = {
   6.5,
   5,
   25};
   Double_t Graph0_fehy3004[3] = {
   0.009,
   0.0082,
   0.0016};
   grae = new TGraphAsymmErrors(3,Graph0_fx3004,Graph0_fy3004,Graph0_felx3004,Graph0_fehx3004,Graph0_fely3004,Graph0_fehy3004);
   grae->SetName("Graph0");
   grae->SetTitle("TGraphAsymmErrors for scale factors");

   ci = TColor::GetColor("#99ccff");
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#3399ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#3399ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerSize(0.7);
   
   TH1F *Graph_Small TH1F3004 = new TH1F("Graph_Small TH1F3004","Small TH1F histogram",100,0,81);
   Graph_Small TH1F3004->SetMinimum(0.65);
   Graph_Small TH1F3004->SetMaximum(1.1);
   Graph_Small TH1F3004->SetFillStyle(0);
   Graph_Small TH1F3004->SetLineStyle(0);
   Graph_Small TH1F3004->SetMarkerStyle(20);
   Graph_Small TH1F3004->GetXaxis()->SetTitle("p_{T} [GeV]");
   Graph_Small TH1F3004->GetXaxis()->SetLabelFont(42);
   Graph_Small TH1F3004->GetXaxis()->SetLabelOffset(0.007);
   Graph_Small TH1F3004->GetXaxis()->SetLabelSize(0.08);
   Graph_Small TH1F3004->GetXaxis()->SetTitleSize(0.08);
   Graph_Small TH1F3004->GetXaxis()->SetTitleFont(42);
   Graph_Small TH1F3004->GetYaxis()->SetLabelFont(42);
   Graph_Small TH1F3004->GetYaxis()->SetLabelOffset(0.007);
   Graph_Small TH1F3004->GetYaxis()->SetLabelSize(0.08);
   Graph_Small TH1F3004->GetYaxis()->SetTitleSize(0.08);
   Graph_Small TH1F3004->GetYaxis()->SetTitleOffset(0.75);
   Graph_Small TH1F3004->GetYaxis()->SetTitleFont(42);
   Graph_Small TH1F3004->GetZaxis()->SetLabelFont(42);
   Graph_Small TH1F3004->GetZaxis()->SetLabelOffset(0.007);
   Graph_Small TH1F3004->GetZaxis()->SetLabelSize(0.05);
   Graph_Small TH1F3004->GetZaxis()->SetTitleSize(0.06);
   Graph_Small TH1F3004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Small TH1F3004);
   
   grae->Draw("a2");
   
   Double_t Graph0_fx3005[3] = {
   13.5,
   25,
   55};
   Double_t Graph0_fy3005[3] = {
   1.0365,
   0.9908,
   0.9971};
   Double_t Graph0_felx3005[3] = {
   6.5,
   5,
   25};
   Double_t Graph0_fely3005[3] = {
   0.009,
   0.0082,
   0.0016};
   Double_t Graph0_fehx3005[3] = {
   6.5,
   5,
   25};
   Double_t Graph0_fehy3005[3] = {
   0.009,
   0.0082,
   0.0016};
   grae = new TGraphAsymmErrors(3,Graph0_fx3005,Graph0_fy3005,Graph0_felx3005,Graph0_fehx3005,Graph0_fely3005,Graph0_fehy3005);
   grae->SetName("Graph0");
   grae->SetTitle("TGraphAsymmErrors for scale factors");

   ci = TColor::GetColor("#99ccff");
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#3399ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#3399ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerSize(0.7);
   
   TH1F *Graph_Graph_Small TH1F30043005 = new TH1F("Graph_Graph_Small TH1F30043005","Small TH1F histogram",100,0,81);
   Graph_Graph_Small TH1F30043005->SetMinimum(0.65);
   Graph_Graph_Small TH1F30043005->SetMaximum(1.1);
   Graph_Graph_Small TH1F30043005->SetFillStyle(0);
   Graph_Graph_Small TH1F30043005->SetLineStyle(0);
   Graph_Graph_Small TH1F30043005->SetMarkerStyle(20);
   Graph_Graph_Small TH1F30043005->GetXaxis()->SetTitle("p_{T} [GeV]");
   Graph_Graph_Small TH1F30043005->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Small TH1F30043005->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph_Small TH1F30043005->GetXaxis()->SetLabelSize(0.08);
   Graph_Graph_Small TH1F30043005->GetXaxis()->SetTitleSize(0.08);
   Graph_Graph_Small TH1F30043005->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Small TH1F30043005->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Small TH1F30043005->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph_Small TH1F30043005->GetYaxis()->SetLabelSize(0.08);
   Graph_Graph_Small TH1F30043005->GetYaxis()->SetTitleSize(0.08);
   Graph_Graph_Small TH1F30043005->GetYaxis()->SetTitleOffset(0.75);
   Graph_Graph_Small TH1F30043005->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Small TH1F30043005->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Small TH1F30043005->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph_Small TH1F30043005->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph_Small TH1F30043005->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph_Small TH1F30043005->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_Small TH1F30043005);
   
   grae->Draw("p");
   pad2->Modified();
   Canvas->cd();
   Canvas->Modified();
   Canvas->cd();
   Canvas->SetSelected(Canvas);
}