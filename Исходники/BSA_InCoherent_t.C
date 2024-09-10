void BSA_InCoherent_t()
{
//=========Macro generated from canvas: c17/Incoherent channe
//=========  (Tue Aug 21 12:00:26 2018) by ROOT version6.09/01
   TCanvas *c17 = new TCanvas("c17", "Incoherent channe",0,0,1200,400);
   gStyle->SetOptFit(1);
   c17->Range(0,0,1,1);
   c17->SetFillColor(0);
   c17->SetBorderMode(0);
   c17->SetBorderSize(2);
   c17->SetLeftMargin(0.025);
   c17->SetRightMargin(0.02325581);
   c17->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c17_1
   TPad *c17_1 = new TPad("c17_1", "Incoherent channe_1",0,0,0.262936,0.9);
   c17_1->Draw();
   c17_1->cd();
   c17_1->Range(-32.86883,-0.4888889,353.6809,0.4);
   c17_1->SetFillColor(0);
   c17_1->SetBorderMode(0);
   c17_1->SetBorderSize(2);
   c17_1->SetGridx();
   c17_1->SetGridy();
   c17_1->SetRightMargin(0);
   c17_1->SetTopMargin(0);
   c17_1->SetFrameBorderMode(0);
   c17_1->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("0.05<-t<0.21 [GeV^{2}/c^{2}]");
   
   Double_t Graph_fx1154[9] = {
   21.59954,
   59.03178,
   96.06391,
   141.7703,
   179.2242,
   222.8541,
   259.5793,
   303.38,
   337.8675};
   Double_t Graph_fy1154[9] = {
   0.1020231,
   0.03114899,
   0.2309077,
   0.1341245,
   0.01684177,
   -0.1267998,
   -0.2824572,
   -0.2260703,
   -0.0186068};
   Double_t Graph_fex1154[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1154[9] = {
   0.04242532,
   0.05165487,
   0.05483741,
   0.07646672,
   0.1006626,
   0.09089962,
   0.05905575,
   0.04462244,
   0.05521722};
   TGraphErrors *gre = new TGraphErrors(9,Graph_fx1154,Graph_fy1154,Graph_fex1154,Graph_fey1154);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1154 = new TH1F("Graph_Graph1154","Graph",100,0,369.4943);
   Graph_Graph1154->SetMinimum(-0.4042387);
   Graph_Graph1154->SetMaximum(0.3484709);
   Graph_Graph1154->SetDirectory(0);
   Graph_Graph1154->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1154->SetLineColor(ci);
   Graph_Graph1154->GetXaxis()->SetLabelFont(42);
   Graph_Graph1154->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1154->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1154->GetXaxis()->SetTitleFont(42);
   Graph_Graph1154->GetYaxis()->SetLabelFont(42);
   Graph_Graph1154->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1154->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1154->GetYaxis()->SetTitleFont(42);
   Graph_Graph1154->GetZaxis()->SetLabelFont(42);
   Graph_Graph1154->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1154->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1154->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1154);
   
   
   TF1 *myfit1155 = new TF1("myfit","[0]*sin(x*3.1416/180.0)/(1 + [1]*cos(x*3.1416/180.0))",0,369.4943);
   myfit1155->SetFillColor(19);
   myfit1155->SetFillStyle(0);
   myfit1155->SetLineColor(2);
   myfit1155->SetLineWidth(2);
   myfit1155->SetChisquare(12.03234);
   myfit1155->SetNDF(7);
   myfit1155->GetXaxis()->SetLabelFont(42);
   myfit1155->GetXaxis()->SetLabelSize(0.035);
   myfit1155->GetXaxis()->SetTitleSize(0.035);
   myfit1155->GetXaxis()->SetTitleFont(42);
   myfit1155->GetYaxis()->SetLabelFont(42);
   myfit1155->GetYaxis()->SetLabelSize(0.035);
   myfit1155->GetYaxis()->SetTitleSize(0.035);
   myfit1155->GetYaxis()->SetTitleFont(42);
   myfit1155->SetParameter(0,0.2160608);
   myfit1155->SetParError(0,0.02670852);
   myfit1155->SetParLimits(0,0,0);
   myfit1155->SetParameter(1,0.2378828);
   myfit1155->SetParError(1,0.2292802);
   myfit1155->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(myfit1155);
   
   TPaveStats *ptstats = new TPaveStats(0.27,0.74,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("#chi^{2} / ndf = 12.03 / 7");
   AText = ptstats->AddText("p0       = 0.2161 #pm 0.02671 ");
   AText = ptstats->AddText("p1       = 0.2379 #pm 0.2293 ");
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




   TPaveText *pt = new TPaveText(0.2292451,0.9268996,0.7707549,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("0.05<-t<0.21 [GeV^{2}/c^{2}]");
   pt->Draw();
   c17_1->Modified();
   c17->cd();
  
// ------------>Primitives in pad: c17_2
   TPad *c17_2 = new TPad("c17_2", "Incoherent channe_2",0.262936,0,0.5008721,0.9);
   c17_2->Draw();
   c17_2->cd();
   c17_2->Range(5.895345,-0.4888889,352.6198,0.4);
   c17_2->SetFillColor(0);
   c17_2->SetBorderMode(0);
   c17_2->SetBorderSize(2);
   c17_2->SetGridx();
   c17_2->SetGridy();
   c17_2->SetLeftMargin(0);
   c17_2->SetRightMargin(0);
   c17_2->SetTopMargin(0);
   c17_2->SetFrameBorderMode(0);
   c17_2->SetFrameBorderMode(0);
   
   multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("0.21<-t<0.36 [GeV^{2}/c^{2}]");
   
   Double_t Graph_fx1157[9] = {
   21.65555,
   61.41754,
   96.1904,
   139.625,
   182.9173,
   222.6445,
   259.1526,
   302.149,
   336.8596};
   Double_t Graph_fy1157[9] = {
   0.04372413,
   0.1019325,
   0.1737435,
   0.1708402,
   0.2316287,
   -0.1435087,
   -0.1227365,
   -0.1969296,
   -0.07714485};
   Double_t Graph_fex1157[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1157[9] = {
   0.0517677,
   0.05885852,
   0.0646232,
   0.09789667,
   0.1185262,
   0.09557657,
   0.06953456,
   0.04921871,
   0.06282415};
   gre = new TGraphErrors(9,Graph_fx1157,Graph_fy1157,Graph_fex1157,Graph_fey1157);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1157 = new TH1F("Graph_Graph1157","Graph",100,0,368.38);
   Graph_Graph1157->SetMinimum(-0.3057786);
   Graph_Graph1157->SetMaximum(0.4097851);
   Graph_Graph1157->SetDirectory(0);
   Graph_Graph1157->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1157->SetLineColor(ci);
   Graph_Graph1157->GetXaxis()->SetLabelFont(42);
   Graph_Graph1157->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1157->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1157->GetXaxis()->SetTitleFont(42);
   Graph_Graph1157->GetYaxis()->SetLabelFont(42);
   Graph_Graph1157->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1157->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1157->GetYaxis()->SetTitleFont(42);
   Graph_Graph1157->GetZaxis()->SetLabelFont(42);
   Graph_Graph1157->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1157->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1157->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1157);
   
   
   TF1 *myfit1158 = new TF1("myfit","[0]*sin(x*3.1416/180.0)/(1 + [1]*cos(x*3.1416/180.0))",0,368.38);
   myfit1158->SetFillColor(19);
   myfit1158->SetFillStyle(0);
   myfit1158->SetLineColor(2);
   myfit1158->SetLineWidth(2);
   myfit1158->SetChisquare(6.955655);
   myfit1158->SetNDF(7);
   myfit1158->GetXaxis()->SetLabelFont(42);
   myfit1158->GetXaxis()->SetLabelSize(0.035);
   myfit1158->GetXaxis()->SetTitleSize(0.035);
   myfit1158->GetXaxis()->SetTitleFont(42);
   myfit1158->GetYaxis()->SetLabelFont(42);
   myfit1158->GetYaxis()->SetLabelSize(0.035);
   myfit1158->GetYaxis()->SetTitleSize(0.035);
   myfit1158->GetYaxis()->SetTitleFont(42);
   myfit1158->SetParameter(0,0.1721707);
   myfit1158->SetParError(0,0.0324291);
   myfit1158->SetParLimits(0,0,0);
   myfit1158->SetParameter(1,0.001708824);
   myfit1158->SetParError(1,0.4101565);
   myfit1158->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(myfit1158);
   
   ptstats = new TPaveStats(0.27,0.74,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   AText = ptstats->AddText("#chi^{2} / ndf = 6.956 / 7");
   AText = ptstats->AddText("p0       = 0.1722 #pm 0.03243 ");
   AText = ptstats->AddText("p1       = 0.001709 #pm 0.4102 ");
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



   pt = new TPaveText(0.2194177,0.9304839,0.7805823,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("0.21<-t<0.36 [GeV^{2}/c^{2}]");
   pt->Draw();
   c17_2->Modified();
   c17->cd();
  
// ------------>Primitives in pad: c17_3
   TPad *c17_3 = new TPad("c17_3", "Incoherent channe_3",0.5008721,0,0.7388081,0.9);
   c17_3->Draw();
   c17_3->cd();
   c17_3->Range(7.121854,-0.4888889,349.9594,0.4);
   c17_3->SetFillColor(0);
   c17_3->SetBorderMode(0);
   c17_3->SetBorderSize(2);
   c17_3->SetGridx();
   c17_3->SetGridy();
   c17_3->SetLeftMargin(0);
   c17_3->SetRightMargin(0);
   c17_3->SetTopMargin(0);
   c17_3->SetFrameBorderMode(0);
   c17_3->SetFrameBorderMode(0);
   
   multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("0.36<-t<0.67 [GeV^{2}/c^{2}]");
   
   Double_t Graph_fx1160[9] = {
   22.70538,
   60.97743,
   94.23011,
   138.1892,
   183.0975,
   222.79,
   259.8951,
   302.6808,
   334.3759};
   Double_t Graph_fy1160[9] = {
   0.1761498,
   0.1945204,
   0.1034809,
   -0.09380414,
   0.2967375,
   -0.1094475,
   -0.1583282,
   -0.1819771,
   -0.09543453};
   Double_t Graph_fex1160[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1160[9] = {
   0.06358895,
   0.0584754,
   0.07622601,
   0.115077,
   0.1268505,
   0.1278475,
   0.07389284,
   0.04701977,
   0.07415904};
   gre = new TGraphErrors(9,Graph_fx1160,Graph_fy1160,Graph_fex1160,Graph_fey1160);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1160 = new TH1F("Graph_Graph1160","Graph",100,0,365.5429);
   Graph_Graph1160->SetMinimum(-0.3033832);
   Graph_Graph1160->SetMaximum(0.4896763);
   Graph_Graph1160->SetDirectory(0);
   Graph_Graph1160->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1160->SetLineColor(ci);
   Graph_Graph1160->GetXaxis()->SetLabelFont(42);
   Graph_Graph1160->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1160->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1160->GetXaxis()->SetTitleFont(42);
   Graph_Graph1160->GetYaxis()->SetLabelFont(42);
   Graph_Graph1160->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1160->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1160->GetYaxis()->SetTitleFont(42);
   Graph_Graph1160->GetZaxis()->SetLabelFont(42);
   Graph_Graph1160->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1160->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1160->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1160);
   
   
   TF1 *myfit1161 = new TF1("myfit","[0]*sin(x*3.1416/180.0)/(1 + [1]*cos(x*3.1416/180.0))",0,365.5429);
   myfit1161->SetFillColor(19);
   myfit1161->SetFillStyle(0);
   myfit1161->SetLineColor(2);
   myfit1161->SetLineWidth(2);
   myfit1161->SetChisquare(8.926216);
   myfit1161->SetNDF(7);
   myfit1161->GetXaxis()->SetLabelFont(42);
   myfit1161->GetXaxis()->SetLabelSize(0.035);
   myfit1161->GetXaxis()->SetTitleSize(0.035);
   myfit1161->GetXaxis()->SetTitleFont(42);
   myfit1161->GetYaxis()->SetLabelFont(42);
   myfit1161->GetYaxis()->SetLabelSize(0.035);
   myfit1161->GetYaxis()->SetTitleSize(0.035);
   myfit1161->GetYaxis()->SetTitleFont(42);
   myfit1161->SetParameter(0,0.1371093);
   myfit1161->SetParError(0,0.03383483);
   myfit1161->SetParLimits(0,0,0);
   myfit1161->SetParameter(1,-0.6800102);
   myfit1161->SetParError(1,0.1832383);
   myfit1161->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(myfit1161);
   
   ptstats = new TPaveStats(0.27,0.74,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   AText = ptstats->AddText("#chi^{2} / ndf = 8.926 / 7");
   AText = ptstats->AddText("p0       = 0.1371 #pm 0.03383 ");
   AText = ptstats->AddText("p1       = -0.68 #pm 0.1832 ");
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




   pt = new TPaveText(0.2194177,0.9304839,0.7805823,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("0.36<-t<0.67 [GeV^{2}/c^{2}]");
   pt->Draw();
   c17_3->Modified();
   c17->cd();
  
// ------------>Primitives in pad: c17_4
   TPad *c17_4 = new TPad("c17_4", "Incoherent channe_4",0.7388081,0,0.9767442,0.9);
   c17_4->Draw();
   c17_4->cd();
   c17_4->Range(7.951117,-0.4888889,350.3641,0.4);
   c17_4->SetFillColor(0);
   c17_4->SetBorderMode(0);
   c17_4->SetBorderSize(2);
   c17_4->SetGridx();
   c17_4->SetGridy();
   c17_4->SetLeftMargin(0);
   c17_4->SetRightMargin(0);
   c17_4->SetTopMargin(0);
   c17_4->SetFrameBorderMode(0);
   c17_4->SetFrameBorderMode(0);
   
   multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("0.67<-t<0.90 [GeV^{2}/c^{2}]");
   
   Double_t Graph_fx1163[9] = {
   23.51534,
   59.3759,
   90.55341,
   131.0631,
   176.9476,
   229.0094,
   260.8643,
   304.7922,
   334.7999};
   Double_t Graph_fy1163[9] = {
   0.0123906,
   0.195403,
   0.18963,
   -0.1677207,
   -0.8232306,
   -0.7760588,
   -0.2579708,
   -0.2579435,
   -0.08614626};
   Double_t Graph_fex1163[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1163[9] = {
   0.09527872,
   0.1168373,
   0.1651642,
   0.3137499,
   0.3909388,
   0.4596559,
   0.1665094,
   0.09339681,
   0.09961735};
   gre = new TGraphErrors(9,Graph_fx1163,Graph_fy1163,Graph_fex1163,Graph_fey1163);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00ff00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1163 = new TH1F("Graph_Graph1163","Graph",100,0,365.9283);
   Graph_Graph1163->SetMinimum(-1.394766);
   Graph_Graph1163->SetMaximum(0.5138451);
   Graph_Graph1163->SetDirectory(0);
   Graph_Graph1163->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1163->SetLineColor(ci);
   Graph_Graph1163->GetXaxis()->SetLabelFont(42);
   Graph_Graph1163->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1163->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1163->GetXaxis()->SetTitleFont(42);
   Graph_Graph1163->GetYaxis()->SetLabelFont(42);
   Graph_Graph1163->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1163->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1163->GetYaxis()->SetTitleFont(42);
   Graph_Graph1163->GetZaxis()->SetLabelFont(42);
   Graph_Graph1163->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1163->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1163->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1163);
   
   
   TF1 *myfit1164 = new TF1("myfit","[0]*sin(x*3.1416/180.0)/(1 + [1]*cos(x*3.1416/180.0))",0,365.9283);
   myfit1164->SetFillColor(19);
   myfit1164->SetFillStyle(0);
   myfit1164->SetLineColor(2);
   myfit1164->SetLineWidth(2);
   myfit1164->SetChisquare(8.810638);
   myfit1164->SetNDF(7);
   myfit1164->GetXaxis()->SetLabelFont(42);
   myfit1164->GetXaxis()->SetLabelSize(0.035);
   myfit1164->GetXaxis()->SetTitleSize(0.035);
   myfit1164->GetXaxis()->SetTitleFont(42);
   myfit1164->GetYaxis()->SetLabelFont(42);
   myfit1164->GetYaxis()->SetLabelSize(0.035);
   myfit1164->GetYaxis()->SetTitleSize(0.035);
   myfit1164->GetYaxis()->SetTitleFont(42);
   myfit1164->SetParameter(0,0.2352442);
   myfit1164->SetParError(0,0.0807391);
   myfit1164->SetParLimits(0,0,0);
   myfit1164->SetParameter(1,0.003684647);
   myfit1164->SetParError(1,0.5673774);
   myfit1164->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(myfit1164);
   
   ptstats = new TPaveStats(0.27,0.74,0.9,0.9,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   AText = ptstats->AddText("#chi^{2} / ndf = 8.811 / 7");
   AText = ptstats->AddText("p0       = 0.2352 #pm 0.08074 ");
   AText = ptstats->AddText("p1       = 0.003685 #pm 0.5674 ");
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




   pt = new TPaveText(0.2194177,0.9304839,0.7805823,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("0.67<-t<0.90 [GeV^{2}/c^{2}]");
   pt->Draw();
   c17_4->Modified();
   c17->cd();
   c17->Modified();
   c17->cd();
   c17->SetSelected(c17);
}