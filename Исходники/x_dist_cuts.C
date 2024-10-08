void x_dist_cuts()
{
//=========Macro generated from canvas: c/
//=========  (Fri Jul 24 12:08:10 2015) by ROOT version6.04/00
   TCanvas *c = new TCanvas("c", "",0,45,600,500);
   c->SetHighLightColor(2);
   c->Range(-187.5,-2144.494,187.5,19300.44);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *hist__1 = new TH1D("hist__1","Worry Later",100,-150,150);
   hist__1->SetBinContent(0,37);
   hist__1->SetBinContent(1,11);
   hist__1->SetBinContent(2,6);
   hist__1->SetBinContent(3,9);
   hist__1->SetBinContent(4,11);
   hist__1->SetBinContent(5,17);
   hist__1->SetBinContent(6,29);
   hist__1->SetBinContent(7,31);
   hist__1->SetBinContent(8,40);
   hist__1->SetBinContent(9,65);
   hist__1->SetBinContent(10,62);
   hist__1->SetBinContent(11,79);
   hist__1->SetBinContent(12,132);
   hist__1->SetBinContent(13,148);
   hist__1->SetBinContent(14,184);
   hist__1->SetBinContent(15,187);
   hist__1->SetBinContent(16,257);
   hist__1->SetBinContent(17,316);
   hist__1->SetBinContent(18,354);
   hist__1->SetBinContent(19,449);
   hist__1->SetBinContent(20,495);
   hist__1->SetBinContent(21,568);
   hist__1->SetBinContent(22,607);
   hist__1->SetBinContent(23,624);
   hist__1->SetBinContent(24,686);
   hist__1->SetBinContent(25,704);
   hist__1->SetBinContent(26,739);
   hist__1->SetBinContent(27,738);
   hist__1->SetBinContent(28,743);
   hist__1->SetBinContent(29,732);
   hist__1->SetBinContent(30,730);
   hist__1->SetBinContent(31,706);
   hist__1->SetBinContent(32,773);
   hist__1->SetBinContent(33,716);
   hist__1->SetBinContent(34,788);
   hist__1->SetBinContent(35,760);
   hist__1->SetBinContent(36,900);
   hist__1->SetBinContent(37,945);
   hist__1->SetBinContent(38,1039);
   hist__1->SetBinContent(39,1194);
   hist__1->SetBinContent(40,1368);
   hist__1->SetBinContent(41,1682);
   hist__1->SetBinContent(42,1928);
   hist__1->SetBinContent(43,2500);
   hist__1->SetBinContent(44,3260);
   hist__1->SetBinContent(45,4389);
   hist__1->SetBinContent(46,5759);
   hist__1->SetBinContent(47,7620);
   hist__1->SetBinContent(48,9955);
   hist__1->SetBinContent(49,13012);
   hist__1->SetBinContent(50,16339);
   hist__1->SetBinContent(51,16048);
   hist__1->SetBinContent(52,13155);
   hist__1->SetBinContent(53,10318);
   hist__1->SetBinContent(54,7953);
   hist__1->SetBinContent(55,6143);
   hist__1->SetBinContent(56,4420);
   hist__1->SetBinContent(57,3422);
   hist__1->SetBinContent(58,2687);
   hist__1->SetBinContent(59,2027);
   hist__1->SetBinContent(60,1643);
   hist__1->SetBinContent(61,1359);
   hist__1->SetBinContent(62,1189);
   hist__1->SetBinContent(63,1057);
   hist__1->SetBinContent(64,929);
   hist__1->SetBinContent(65,840);
   hist__1->SetBinContent(66,792);
   hist__1->SetBinContent(67,759);
   hist__1->SetBinContent(68,719);
   hist__1->SetBinContent(69,673);
   hist__1->SetBinContent(70,702);
   hist__1->SetBinContent(71,769);
   hist__1->SetBinContent(72,693);
   hist__1->SetBinContent(73,728);
   hist__1->SetBinContent(74,719);
   hist__1->SetBinContent(75,698);
   hist__1->SetBinContent(76,729);
   hist__1->SetBinContent(77,695);
   hist__1->SetBinContent(78,732);
   hist__1->SetBinContent(79,692);
   hist__1->SetBinContent(80,620);
   hist__1->SetBinContent(81,592);
   hist__1->SetBinContent(82,525);
   hist__1->SetBinContent(83,463);
   hist__1->SetBinContent(84,407);
   hist__1->SetBinContent(85,357);
   hist__1->SetBinContent(86,300);
   hist__1->SetBinContent(87,229);
   hist__1->SetBinContent(88,192);
   hist__1->SetBinContent(89,154);
   hist__1->SetBinContent(90,113);
   hist__1->SetBinContent(91,123);
   hist__1->SetBinContent(92,73);
   hist__1->SetBinContent(93,55);
   hist__1->SetBinContent(94,41);
   hist__1->SetBinContent(95,27);
   hist__1->SetBinContent(96,27);
   hist__1->SetBinContent(97,18);
   hist__1->SetBinContent(98,14);
   hist__1->SetBinContent(99,8);
   hist__1->SetBinContent(100,11);
   hist__1->SetBinContent(101,55);
   hist__1->SetEntries(173117);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("hist");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 173117 ");
   AText = ptstats->AddText("Mean  = 0.6933");
   AText = ptstats->AddText("Std Dev   =  34.33");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   hist__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hist__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hist__1->SetLineColor(ci);
   hist__1->GetXaxis()->SetTitle("#DeltaZ [cm]");
   hist__1->GetXaxis()->SetLabelFont(42);
   hist__1->GetXaxis()->SetLabelSize(0.035);
   hist__1->GetXaxis()->SetTitleSize(0.035);
   hist__1->GetXaxis()->SetTitleFont(42);
   hist__1->GetYaxis()->SetLabelFont(42);
   hist__1->GetYaxis()->SetLabelSize(0.035);
   hist__1->GetYaxis()->SetTitleSize(0.035);
   hist__1->GetYaxis()->SetTitleFont(42);
   hist__1->GetZaxis()->SetLabelFont(42);
   hist__1->GetZaxis()->SetLabelSize(0.035);
   hist__1->GetZaxis()->SetTitleSize(0.035);
   hist__1->GetZaxis()->SetTitleFont(42);
   hist__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.3779599,0.9368947,0.6220401,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("Worry Later");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}