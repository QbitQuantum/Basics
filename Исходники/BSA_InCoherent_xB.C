void BSA_InCoherent_xB()
{
//=========Macro generated from canvas: c16/Incoherent channe
//=========  (Tue Aug 21 12:00:25 2018) by ROOT version6.09/01
   TCanvas *c16 = new TCanvas("c16", "Incoherent channe",0,0,1200,400);
   gStyle->SetOptFit(1);
   c16->Range(0,0,1,1);
   c16->SetFillColor(0);
   c16->SetBorderMode(0);
   c16->SetBorderSize(2);
   c16->SetLeftMargin(0.025);
   c16->SetRightMargin(0.02325581);
   c16->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c16_1
   TPad *c16_1 = new TPad("c16_1", "Incoherent channe_1",0,0,0.262936,0.9);
   c16_1->Draw();
   c16_1->cd();
   c16_1->Range(-29.34641,-0.4888889,350.2581,0.4);
   c16_1->SetFillColor(0);
   c16_1->SetBorderMode(0);
   c16_1->SetBorderSize(2);
   c16_1->SetGridx();
   c16_1->SetGridy();
   c16_1->SetRightMargin(0);
   c16_1->SetTopMargin(0);
   c16_1->SetFrameBorderMode(0);
   c16_1->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("0.12<x_{B}<0.21 ");
   
   Double_t Graph_fx1134[9] = {
   24.14331,
   62.70082,
   96.14623,
   141.7289,
   180.8857,
   220.5862,
   258.7856,
   303.3336,
   334.7288};
   Double_t Graph_fy1134[9] = {
   0.1330996,
   -0.03883743,
   0.1388413,
   0.2120595,
   0.03749243,
   -0.09129921,
   -0.1273289,
   -0.1643618,
   0.03103783};
   Double_t Graph_fex1134[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1134[9] = {
   0.07077824,
   0.06445297,
   0.05939535,
   0.06833722,
   0.08559024,
   0.08401363,
   0.06136237,
   0.05845869,
   0.08718727};
   TGraphErrors *gre = new TGraphErrors(9,Graph_fx1134,Graph_fy1134,Graph_fex1134,Graph_fey1134);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1134 = new TH1F("Graph_Graph1134","Graph",100,0,365.7873);
   Graph_Graph1134->SetMinimum(-0.2731422);
   Graph_Graph1134->SetMaximum(0.3307184);
   Graph_Graph1134->SetDirectory(0);
   Graph_Graph1134->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1134->SetLineColor(ci);
   Graph_Graph1134->GetXaxis()->SetLabelFont(42);
   Graph_Graph1134->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1134->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1134->GetXaxis()->SetTitleFont(42);
   Graph_Graph1134->GetYaxis()->SetLabelFont(42);
   Graph_Graph1134->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1134->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1134->GetYaxis()->SetTitleFont(42);
   Graph_Graph1134->GetZaxis()->SetLabelFont(42);
   Graph_Graph1134->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1134->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1134->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1134);
   
   
   TF1 *myfit1135 = new TF1("myfit","[0]*sin(x*3.1416/180.0)/(1 + [1]*cos(x*3.1416/180.0))",0,365.7873);
   myfit1135->SetFillColor(19);
   myfit1135->SetFillStyle(0);
   myfit1135->SetLineColor(2);
   myfit1135->SetLineWidth(2);
   myfit1135->SetChisquare(10.13595);
   myfit1135->SetNDF(7);
   myfit1135->GetXaxis()->SetLabelFont(42);
   myfit1135->GetXaxis()->SetLabelSize(0.035);
   myfit1135->GetXaxis()->SetTitleSize(0.035);
   myfit1135->GetXaxis()->SetTitleFont(42);
   myfit1135->GetYaxis()->SetLabelFont(42);
   myfit1135->GetYaxis()->SetLabelSize(0.035);
   myfit1135->GetYaxis()->SetTitleSize(0.035);
   myfit1135->GetYaxis()->SetTitleFont(42);
   myfit1135->SetParameter(0,0.1205343);
   myfit1135->SetParError(0,0.03387604);
   myfit1135->SetParLimits(0,0,0);
   myfit1135->SetParameter(1,0.6858633);
   myfit1135->SetParError(1,0.2646153);
   myfit1135->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(myfit1135);
   
   TPaveStats *ptstats = new TPaveStats(0.27,0.74,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("#chi^{2} / ndf = 10.14 / 7");
   AText = ptstats->AddText("p0       = 0.1205 #pm 0.03388 ");
   AText = ptstats->AddText("p1       = 0.6859 #pm 0.2646 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   multigraph->Add(gre,"");
   multigraph->Draw("AP");
   multigraph->GetXaxis()->SetTitle("#phi [deg.]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleSize(0.035);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("A_{LU}");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleSize(0.035);
   multigraph->GetYaxis()->SetTitleFont(42);
     gPad->Modified();  
   multigraph->GetYaxis()->SetRangeUser(-0.35, 0.35);  




   c16_1->Modified();
   c16->cd();
  
// ------------>Primitives in pad: c16_2
   TPad *c16_2 = new TPad("c16_2", "Incoherent channe_2",0.262936,0,0.5008721,0.9);
   c16_2->Draw();
   c16_2->cd();
   c16_2->Range(5.85529,-0.4888889,352.0975,0.4);
   c16_2->SetFillColor(0);
   c16_2->SetBorderMode(0);
   c16_2->SetBorderSize(2);
   c16_2->SetGridx();
   c16_2->SetGridy();
   c16_2->SetLeftMargin(0);
   c16_2->SetRightMargin(0);
   c16_2->SetTopMargin(0);
   c16_2->SetFrameBorderMode(0);
   c16_2->SetFrameBorderMode(0);
   
   multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("0.21<x_{B}<0.31 ");
   
   Double_t Graph_fx1137[9] = {
   21.59357,
   60.08662,
   95.00395,
   140.4897,
   181.0443,
   224.9978,
   260.1264,
   302.891,
   336.3592};
   Double_t Graph_fy1137[9] = {
   0.0984356,
   0.1891659,
   0.2419886,
   0.08897874,
   0.2077051,
   -0.3071227,
   -0.1933684,
   -0.2875592,
   -0.08265727};
   Double_t Graph_fex1137[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1137[9] = {
   0.04446748,
   0.058618,
   0.06898028,
   0.1082398,
   0.135301,
   0.1152745,
   0.0716065,
   0.04680018,
   0.05547391};
   gre = new TGraphErrors(9,Graph_fx1137,Graph_fy1137,Graph_fex1137,Graph_fey1137);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1137 = new TH1F("Graph_Graph1137","Graph",100,0,367.8358);
   Graph_Graph1137->SetMinimum(-0.4989376);
   Graph_Graph1137->SetMaximum(0.4195464);
   Graph_Graph1137->SetDirectory(0);
   Graph_Graph1137->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1137->SetLineColor(ci);
   Graph_Graph1137->GetXaxis()->SetLabelFont(42);
   Graph_Graph1137->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1137->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1137->GetXaxis()->SetTitleFont(42);
   Graph_Graph1137->GetYaxis()->SetLabelFont(42);
   Graph_Graph1137->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1137->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1137->GetYaxis()->SetTitleFont(42);
   Graph_Graph1137->GetZaxis()->SetLabelFont(42);
   Graph_Graph1137->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1137->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1137->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1137);
   
   
   TF1 *myfit1138 = new TF1("myfit","[0]*sin(x*3.1416/180.0)/(1 + [1]*cos(x*3.1416/180.0))",0,367.8358);
   myfit1138->SetFillColor(19);
   myfit1138->SetFillStyle(0);
   myfit1138->SetLineColor(2);
   myfit1138->SetLineWidth(2);
   myfit1138->SetChisquare(7.336971);
   myfit1138->SetNDF(7);
   myfit1138->GetXaxis()->SetLabelFont(42);
   myfit1138->GetXaxis()->SetLabelSize(0.035);
   myfit1138->GetXaxis()->SetTitleSize(0.035);
   myfit1138->GetXaxis()->SetTitleFont(42);
   myfit1138->GetYaxis()->SetLabelFont(42);
   myfit1138->GetYaxis()->SetLabelSize(0.035);
   myfit1138->GetYaxis()->SetTitleSize(0.035);
   myfit1138->GetYaxis()->SetTitleFont(42);
   myfit1138->SetParameter(0,0.2508538);
   myfit1138->SetParError(0,0.03583101);
   myfit1138->SetParLimits(0,0,0);
   myfit1138->SetParameter(1,-0.1422748);
   myfit1138->SetParError(1,0.2426713);
   myfit1138->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(myfit1138);
   
   ptstats = new TPaveStats(0.27,0.74,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   AText = ptstats->AddText("#chi^{2} / ndf = 7.337 / 7");
   AText = ptstats->AddText("p0       = 0.2509 #pm 0.03583 ");
   AText = ptstats->AddText("p1       = -0.1423 #pm 0.2427 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   multigraph->Add(gre,"");
   multigraph->Draw("AP");
   multigraph->GetXaxis()->SetTitle("#phi [deg.]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleSize(0.035);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleSize(0.035);
   multigraph->GetYaxis()->SetTitleFont(42);
     gPad->Modified();  
   multigraph->GetYaxis()->SetRangeUser(-0.35, 0.35);  



   c16_2->Modified();
   c16->cd();
  
// ------------>Primitives in pad: c16_3
   TPad *c16_3 = new TPad("c16_3", "Incoherent channe_3",0.5008721,0,0.7388081,0.9);
   c16_3->Draw();
   c16_3->cd();
   c16_3->Range(4.159976,-0.4888889,357.6921,0.4);
   c16_3->SetFillColor(0);
   c16_3->SetBorderMode(0);
   c16_3->SetBorderSize(2);
   c16_3->SetGridx();
   c16_3->SetGridy();
   c16_3->SetLeftMargin(0);
   c16_3->SetRightMargin(0);
   c16_3->SetTopMargin(0);
   c16_3->SetFrameBorderMode(0);
   c16_3->SetFrameBorderMode(0);
   
   multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("0.31<x_{B}<0.39 ");
   
   Double_t Graph_fx1140[9] = {
   20.22962,
   57.37981,
   95.86069,
   135.3486,
   182.9227,
   229.5531,
   263.4275,
   301.2495,
   341.6225};
   Double_t Graph_fy1140[9] = {
   0.09662004,
   0.06965272,
   0.269744,
   -0.170935,
   -0.1509905,
   0.6309487,
   0.06270791,
   -0.2582676,
   -0.152689};
   Double_t Graph_fex1140[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1140[9] = {
   0.05297617,
   0.09107484,
   0.121636,
   0.2287053,
   0.3066164,
   0.3879093,
   0.1400804,
   0.07623737,
   0.06739512};
   gre = new TGraphErrors(9,Graph_fx1140,Graph_fy1140,Graph_fex1140,Graph_fey1140);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1140 = new TH1F("Graph_Graph1140","Graph",100,0,373.7618);
   Graph_Graph1140->SetMinimum(-0.6052533);
   Graph_Graph1140->SetMaximum(1.166504);
   Graph_Graph1140->SetDirectory(0);
   Graph_Graph1140->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1140->SetLineColor(ci);
   Graph_Graph1140->GetXaxis()->SetLabelFont(42);
   Graph_Graph1140->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1140->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1140->GetXaxis()->SetTitleFont(42);
   Graph_Graph1140->GetYaxis()->SetLabelFont(42);
   Graph_Graph1140->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1140->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1140->GetYaxis()->SetTitleFont(42);
   Graph_Graph1140->GetZaxis()->SetLabelFont(42);
   Graph_Graph1140->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1140->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1140->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1140);
   
   
   TF1 *myfit1141 = new TF1("myfit","[0]*sin(x*3.1416/180.0)/(1 + [1]*cos(x*3.1416/180.0))",0,373.7618);
   myfit1141->SetFillColor(19);
   myfit1141->SetFillStyle(0);
   myfit1141->SetLineColor(2);
   myfit1141->SetLineWidth(2);
   myfit1141->SetChisquare(10.84482);
   myfit1141->SetNDF(7);
   myfit1141->GetXaxis()->SetLabelFont(42);
   myfit1141->GetXaxis()->SetLabelSize(0.035);
   myfit1141->GetXaxis()->SetTitleSize(0.035);
   myfit1141->GetXaxis()->SetTitleFont(42);
   myfit1141->GetYaxis()->SetLabelFont(42);
   myfit1141->GetYaxis()->SetLabelSize(0.035);
   myfit1141->GetYaxis()->SetTitleSize(0.035);
   myfit1141->GetYaxis()->SetTitleFont(42);
   myfit1141->SetParameter(0,0.124049);
   myfit1141->SetParError(0,0.05069177);
   myfit1141->SetParLimits(0,0,0);
   myfit1141->SetParameter(1,-0.6977989);
   myfit1141->SetParError(1,0.2049165);
   myfit1141->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(myfit1141);
   
   ptstats = new TPaveStats(0.27,0.74,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   AText = ptstats->AddText("#chi^{2} / ndf = 10.84 / 7");
   AText = ptstats->AddText("p0       = 0.124 #pm 0.05069 ");
   AText = ptstats->AddText("p1       = -0.6978 #pm 0.2049 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   multigraph->Add(gre,"");
   multigraph->Draw("AP");
   multigraph->GetXaxis()->SetTitle("#phi [deg.]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleSize(0.035);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleSize(0.035);
   multigraph->GetYaxis()->SetTitleFont(42);
     gPad->Modified();  
   multigraph->GetYaxis()->SetRangeUser(-0.35, 0.35);  




   c16_3->Modified();
   c16->cd();
  
// ------------>Primitives in pad: c16_4
   TPad *c16_4 = new TPad("c16_4", "Incoherent channe_4",0.7388081,0,0.9767442,0.9);
   c16_4->Draw();
   c16_4->cd();
   c16_4->Range(-17.15326,-0.4888889,360.2184,0.4);
   c16_4->SetFillColor(0);
   c16_4->SetBorderMode(0);
   c16_4->SetBorderSize(2);
   c16_4->SetGridx();
   c16_4->SetGridy();
   c16_4->SetLeftMargin(0);
   c16_4->SetRightMargin(0);
   c16_4->SetTopMargin(0);
   c16_4->SetFrameBorderMode(0);
   c16_4->SetFrameBorderMode(0);
   
   multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("0.39<x_{B}<0.60 ");
   
   Double_t Graph_fx1143[9] = {
   19.13311,
   55.36321,
   90.36243,
   127.5684,
   0,
   232.109,
   268.7816,
   302.6639,
   343.0651};
   Double_t Graph_fy1143[9] = {
   0.1307559,
   0.1996612,
   0.006608881,
   -2.830736,
   0,
   -2.034047,
   0.1276631,
   -0.2950426,
   -0.003784223};
   Double_t Graph_fex1143[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1143[9] = {
   0.05218982,
   0.09871893,
   0.1820512,
   4.457049,
   0,
   1.502801,
   0.207584,
   0.0825667,
   0.06276702};
   gre = new TGraphErrors(9,Graph_fx1143,Graph_fy1143,Graph_fex1143,Graph_fey1143);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1143 = new TH1F("Graph_Graph1143","Graph",100,0,377.3716);
   Graph_Graph1143->SetMinimum(-8.179195);
   Graph_Graph1143->SetMaximum(2.517722);
   Graph_Graph1143->SetDirectory(0);
   Graph_Graph1143->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1143->SetLineColor(ci);
   Graph_Graph1143->GetXaxis()->SetLabelFont(42);
   Graph_Graph1143->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1143->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1143->GetXaxis()->SetTitleFont(42);
   Graph_Graph1143->GetYaxis()->SetLabelFont(42);
   Graph_Graph1143->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1143->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1143->GetYaxis()->SetTitleFont(42);
   Graph_Graph1143->GetZaxis()->SetLabelFont(42);
   Graph_Graph1143->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1143->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1143->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1143);
   
   
   TF1 *myfit1144 = new TF1("myfit","[0]*sin(x*3.1416/180.0)/(1 + [1]*cos(x*3.1416/180.0))",0,377.3716);
   myfit1144->SetFillColor(19);
   myfit1144->SetFillStyle(0);
   myfit1144->SetLineColor(2);
   myfit1144->SetLineWidth(2);
   myfit1144->SetChisquare(8.6938);
   myfit1144->SetNDF(7);
   myfit1144->GetXaxis()->SetLabelFont(42);
   myfit1144->GetXaxis()->SetLabelSize(0.035);
   myfit1144->GetXaxis()->SetTitleSize(0.035);
   myfit1144->GetXaxis()->SetTitleFont(42);
   myfit1144->GetYaxis()->SetLabelFont(42);
   myfit1144->GetYaxis()->SetLabelSize(0.035);
   myfit1144->GetYaxis()->SetTitleSize(0.035);
   myfit1144->GetYaxis()->SetTitleFont(42);
   myfit1144->SetParameter(0,0.1663497);
   myfit1144->SetParError(0,0.06722025);
   myfit1144->SetParLimits(0,0,0);
   myfit1144->SetParameter(1,-0.5093054);
   myfit1144->SetParError(1,0.2952021);
   myfit1144->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(myfit1144);
   
   ptstats = new TPaveStats(0.27,0.74,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   AText = ptstats->AddText("#chi^{2} / ndf = 8.694 / 7");
   AText = ptstats->AddText("p0       = 0.1663 #pm 0.06722 ");
   AText = ptstats->AddText("p1       = -0.5093 #pm 0.2952 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   multigraph->Add(gre,"");
   multigraph->Draw("AP");
   multigraph->GetXaxis()->SetTitle("#phi [deg.]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleSize(0.035);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleSize(0.035);
   multigraph->GetYaxis()->SetTitleFont(42);
    gPad->Modified();  
   multigraph->GetYaxis()->SetRangeUser(-0.35, 0.35);  

 


   c16_4->Modified();
   c16->cd();
   c16->Modified();
   c16->cd();
   c16->SetSelected(c16);
}