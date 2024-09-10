void drawMeasurement(int i, double m[5], char label[2][100], int aux[5],
		     double vstep, TH2F* histo, TCanvas* canvas) {

 
    double lowY = (i+1)*vstep;
    double uppY = (i+2)*vstep;

  //double lowX = histo->GetBinLowEdge(1);
  //double uppX = histo->GetBinLowEdge(histo->GetNbinsX()) +
  //              histo->GetBinWidth(histo->GetNbinsX());
    double lowX = 0.25;
    double uppX = 2.80;
    double widthX = uppX - lowX;

 
  // y-range of the histogram is [0...1]

  double startX = lowX + 0.04*widthX;
  
  TPaveText* text = new TPaveText(startX, lowY,
				  startX, uppY, "BR");
  text->SetTextAlign(12);
  text->SetFillColor(aux[1]);
  text->SetTextColor(aux[0]);
  text->SetLineColor(1);
  text->SetBorderSize(0);
  TText* t0 = text->AddText("    ");
  t0->SetTextSize(0.08);
  t0->SetTextFont(aux[2]);
  TText* t1 = text->AddText(label[0]);
  t1->SetTextSize(0.08);
  t1->SetTextFont(aux[2]);
  TText* t2 = text->AddText(label[1]);
  t2->SetTextSize(0.08);
  t2->SetTextFont(aux[2]);
  text->Draw();


  double ypos = 0.5*(lowY+uppY);
  double mean = m[0];
  double nErr1 = m[1];
  double pErr1 = m[2];
  double nErr2 = sqrt(m[1]*m[1]+m[3]*m[3]);
  double pErr2 = sqrt(m[2]*m[2]+m[4]*m[4]);

  // draw TGraphAsymmErrors 1 (stat only) |---*---|
  TMarker* measurement = new TMarker(mean, ypos, aux[4]);
  measurement->SetMarkerColor(aux[0]);
  measurement->SetMarkerStyle(aux[4]);

  measurement->SetMarkerSize(1.5);
  //measurement->SetMarkerSize(1.75);
  measurement->Draw();

  double vsizeErr1 = 0.09*vstep;
  TLine* l1 = new TLine(mean, ypos, mean-nErr1, ypos);
  l1->SetLineWidth(aux[3]);
  l1->SetLineColor(aux[0]);
  l1->Draw();
  TLine* l2 = new TLine(mean, ypos, mean+pErr1, ypos);
  l2->SetLineWidth(aux[3]);
  l2->SetLineColor(aux[0]);
  l2->Draw();
  TLine* l3 = new TLine(mean-nErr1, ypos-vsizeErr1,
			mean-nErr1, ypos+vsizeErr1);
  l3->SetLineWidth(aux[3]);
  l3->SetLineColor(aux[0]);
  l3->Draw();
  TLine* l4 = new TLine(mean+pErr1, ypos-vsizeErr1,
			mean+pErr1, ypos+vsizeErr1);
  l4->SetLineWidth(aux[3]);
  l4->SetLineColor(aux[0]);
  l4->Draw();

  // overlay TGraphAsymmErrors 2 (stat+syst) |----*-----|
  double vsizeErr2 = 0.12*vstep; 
  TLine* l5 = new TLine(mean, ypos, mean-nErr2, ypos);
  l5->SetLineWidth(aux[3]);
  l5->SetLineColor(aux[0]);
  l5->Draw();
  TLine* l6 = new TLine(mean, ypos, mean+pErr2, ypos);
  l6->SetLineWidth(aux[3]);
  l6->SetLineColor(aux[0]);
  l6->Draw();
  TLine* l7 = new TLine(mean-nErr2, ypos-vsizeErr2,
			mean-nErr2, ypos+vsizeErr2);
  l7->SetLineWidth(aux[3]);
  l7->SetLineColor(aux[0]);
  l7->Draw();
  TLine* l8 = new TLine(mean+pErr2, ypos-vsizeErr2,
			mean+pErr2, ypos+vsizeErr2);
  l8->SetLineWidth(aux[3]);
  l8->SetLineColor(aux[0]);
  l8->Draw();

  // draw measurement label "XXX+/-YY+/-ZZ"
  TPaveText* num = new TPaveText(uppX-0.32*widthX,
				 lowY, uppX-0.02*widthX, uppY, "BR");
  num->SetTextAlign(12);
  num->SetFillColor(aux[1]);
  num->SetTextColor(aux[0]);
  num->SetLineColor(aux[0]);
  num->SetBorderSize(0);
  TString str;
  char s[100];

  sprintf(s, "%4.2f#color[%d]{X}", m[0], aux[1]); str +=s;
  if (m[1]==m[2]) { // sym. stat. errors
    sprintf(s, "#pm %4.2f",  m[1]); str +=s;
  } else {
    sprintf(s, "^{+%4.2f}",  m[2]); str +=s;
    sprintf(s, "_{-#color[%d]{|}%4.2f}", aux[1], m[1]); str +=s;
  }
  str += " (stat)";
  if (m[3]!=0.0 || m[4]!=0.0) {
    if (m[3]==m[4]) { // sym. syst. errors
      sprintf(s, "#color[%d]{X}#pm% 4.2f", aux[1], m[3]); str +=s;
    } else {
      sprintf(s, "#color[%d]{X}", aux[1]); str +=s;
      sprintf(s, "^{+%4.2f}",  m[4]); str +=s;
      sprintf(s, "_{-#color[%d]{|}%4.2f}", aux[1], m[3]); str +=s;
    }
  }
  str += " (syst)";


  TText* n0 = num->AddText(str);
  n0->SetTextFont(aux[2]);
  num->Draw();

  return;
}