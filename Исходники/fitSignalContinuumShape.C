void plotRegrVsNoRegr(int channel, int massBin) {
  stringstream filenom, filenoregr;
  filenom << "m4lplots/nominal/fitM" << massBin << "_channel" << channel << ".root";
  filenoregr << "m4lplots/noregr/fitM" << massBin << "_channel" << channel << ".root";

  int col;
  if(channel==0) col=kOrange+7;
  if(channel==1) col=kAzure+2;
  if(channel==2) col=kGreen+3;

  TCanvas *c1 = new TCanvas("c1","c1",750,750);

  TFile *tfilenom = TFile::Open(filenom.str().c_str());
  RooPlot *plotnom = (RooPlot*)tfilenom->Get("m4lplot");
  plotnom->SetMarkerStyle(kOpenSquare);
  plotnom->Draw();
  TPaveText *pavenom = (TPaveText*)tfilenom->Get("TPave");
  pavenom->SetTextColor(col);
  pavenom->Draw("same");

  TFile *tfilenoregr = TFile::Open(filenoregr.str().c_str());
  RooPlot *plotnoregr = (RooPlot*)tfilenoregr->Get("m4lplot");
  plotnoregr->Draw("same");
  TPaveText *pavenoregr = (TPaveText*)tfilenoregr->Get("TPave");
  pavenoregr->Draw("same");

  // cosmetics
  TLegend *legend = new TLegend(0.20,0.45,0.45,0.60,NULL,"brNDC");
  legend->SetBorderSize(     0);
  legend->SetFillColor (     0);
  legend->SetTextAlign (    12);
  legend->SetTextFont  (    42);
  legend->SetTextSize  (0.03);

  TH1F *dummyPointsNom = new TH1F("dummyPNom","dummyPNom",1,0,1);
  TH1F *dummyPointsNoRegr = new TH1F("dummyPNoregr","dummyPNoregr",1,0,1);
  TH1F *dummyLine = new TH1F("dummyL","dummyL",1,0,1);
  dummyPointsNoRegr->SetMarkerStyle(kFullCircle);
  dummyPointsNoRegr->SetMarkerSize(1.1);
  dummyPointsNom->SetMarkerStyle(kFullSquare);
  dummyPointsNom->SetMarkerColor(col);
  dummyPointsNom->SetLineColor(col);
  dummyPointsNom->SetMarkerSize(1.1);
  dummyLine->SetLineColor(col);
  
  legend->AddEntry(dummyPointsNoRegr, "Simulation (E_{std}-p comb.)", "pel");
  legend->AddEntry(dummyPointsNom, "Simulation (E_{regr}-p comb.)", "pel");

  legend->Draw();

  TPaveText *text = new TPaveText(0.15,0.90,0.77,0.98,"brNDC");
  text->AddText("CMS Simulation");
  text->SetBorderSize(0);
  text->SetFillStyle(0);
  text->SetTextAlign(12);
  text->SetTextFont(42);
  text->SetTextSize(0.03);

  text->Draw();

  stringstream frameTitle;
  if(channel==0){frameTitle << "4#mu, m_{H} = ";}
  if(channel==1){frameTitle << "4e, m_{H} = ";}
  if(channel==2){frameTitle << "2e2#mu, m_{H} = ";}
  frameTitle << massBin << " GeV";

  TPaveText *titlet = new TPaveText(0.15,0.80,0.60,0.85,"brNDC");
  titlet->AddText(frameTitle.str().c_str());
  titlet->SetBorderSize(0);
  titlet->SetFillStyle(0);
  titlet->SetTextAlign(12);
  titlet->SetTextFont(132);
  titlet->SetTextSize(0.045);

  titlet->Draw();

  c1->SaveAs("comp.pdf");

}