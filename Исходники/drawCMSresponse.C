void drawCMSresponse() {

  // New style settings
  // #include "tdrstyle_mod14.C"
  setTDRStyle();
  // call cmsPrel(iPeriod, iPos);
  // int iPeriod = 2;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)

  if (!_jec) {

    const char *sd = "CondFormats/JetMETObjects/data";
    //const char *st = "Winter14_V5_MC";
    //const char *st = "Winter14_V8_MC"; // 2012
    //const char *st = "Winter14_V8_DATA";
    //const char *st = "Summer15_25nsV3_DATA";
    //const char *st = "Summer15_25nsV6_DATA";
    //const char *st = "Summer15_25nsV7_DATA";
    //const char *st = "Fall15_25nsV1_DATA";
    //const char *st = "Spring16_25nsV3_MC";
    //const char *st = "Summer16_23Sep2016GV3_DATA"; // 2017
    //const char *st = "Summer16_03Feb2017G_V3_DATA"; // 2017 03FebV3
    const char *st = "Summer16_03Feb2017BCD_V7_DATA"; // 2017 03FebV7
    const char *s;

    //s = Form("%s/%s_L1FastJet_AK5PFchs.txt",sd,st); cout << s << endl;
    //JetCorrectorParameters *l1 = new JetCorrectorParameters(s);
    s = Form("%s/%s_L1FastJet_AK4PFchs.txt",sd,st); cout << s << endl;
    JetCorrectorParameters *l1 = new JetCorrectorParameters(s);
    //s = Form("%s/%s_L2Relative_AK5PFchs.txt",sd,st); cout << s << endl;
    s = Form("%s/%s_L2Relative_AK4PFchs.txt",sd,st); cout << s << endl;
    JetCorrectorParameters *l2 = new JetCorrectorParameters(s);
    //s = Form("%s/%s_L3Absolute_AK5PFchs.txt",sd,st); cout << s << endl;
    s = Form("%s/%s_L3Absolute_AK4PFchs.txt",sd,st); cout << s << endl;
    JetCorrectorParameters *l3 = new JetCorrectorParameters(s);
    s = Form("%s/%s_L2L3Residual_AK4PFchs.txt",sd,st); cout << s << endl;
    JetCorrectorParameters *l2l3 = new JetCorrectorParameters(s);

    vector<JetCorrectorParameters> v;
    v.push_back(l1);
    v.push_back(*l2);
    v.push_back(*l3);
    v.push_back(*l2l3);
    _jec = new FactorizedJetCorrector(v);
  }
  if (!_jecpt) {
    _jecpt = new TF1("jecpt",fJECPt,0,6500,3);
  }

  //double ergs[] = {30, 60, 110, 400, 2000};
  //const int ne = sizeof(ergs)/sizeof(ergs[0]);
  double pts[] = {10, 30, 100, 400, 2000};
  const int npt = sizeof(pts)/sizeof(pts[0]);
  const int neta = 48;//52;
  const int jeta = TMath::Pi()*0.4*0.4;
  const int mu = 0;

  TGraph *gs[npt];
  //for (int ie = 0; ie != ne; ++ie) {
  for (int ipt = 0; ipt != npt; ++ipt) {

    //double energy = ergs[ie];
    double pt = pts[ipt];

    TGraph *g = new TGraph(0); gs[ipt] = g;
    for (int ieta = 0; ieta != neta; ++ieta) {
      
      double eta = (ieta+0.5)*0.1;
      //double pt = energy / cosh(eta);
      double energy = pt * cosh(eta);
      if (pt >= 10. && energy < 6500.) { // 13 TeV

	double jes = getResp(pt, eta, jeta, mu);
	int n = g->GetN();
	g->SetPoint(n, eta, jes);
      }
    } // for ie
  } // for ieta


  // Draw results
  //TH1D *h = new TH1D("h",";Jet |#eta|;Simulated jet response",40,0,4.8);
  //TH1D *h = new TH1D("h",";Jet |#eta|;Data jet response",40,0,4.8);
  TH1D *h = new TH1D("h",";Jet |#eta|;Data response+offset",40,0,4.8);
  h->SetMaximum(1.25);
  h->SetMinimum(0.5);
  extraText = "Simulation";
  //extraText = "Simulation Preliminary";
  //extraText = "Preliminary";
  lumi_8TeV = "";
  lumi_13TeV = "";
  //lumi_13TeV = "2.1 fb^{-1}";
  //TCanvas *c1 = tdrCanvas("c1",h,2,0,kSquare);
  TCanvas *c1 = tdrCanvas("c1",h,4,0,kSquare);

  TLegend *leg1 = tdrLeg(0.25,0.25,0.55,0.30);
  TLegend *leg2 = tdrLeg(0.25,0.20,0.55,0.25);
  TLegend *leg3 = tdrLeg(0.25,0.15,0.55,0.20);
  TLegend *leg4 = tdrLeg(0.55,0.25,0.85,0.30);
  TLegend *leg5 = tdrLeg(0.55,0.20,0.85,0.25);
  TLegend *legs[npt] = {leg1, leg2, leg3, leg4, leg5};

  int colors[] = {kGreen+2, kBlack, kOrange+1, kBlue, kRed+1};
  int markers[] = {kFullCircle, kOpenCircle, kFullSquare, kOpenSquare,
		   kFullTriangleUp};

  for (int ipt = 0; ipt != npt; ++ipt) {
    
    TGraph *g = gs[ipt];
    g->SetMarkerColor(colors[ipt]);
    g->SetMarkerStyle(markers[ipt]);
    g->Draw("SAMEP");

    //TLegend *leg = (ie<3 ? leg1 : leg2);
    TLegend *leg = legs[ipt];
    leg->SetTextColor(colors[ipt]);
    //leg->AddEntry(g, Form("E = %1.0f GeV",ergs[ie]), "P");
    leg->AddEntry(g, Form("p_{T} = %1.0f GeV",pts[ipt]), "P");
  }


  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.045);
  
  TLine *l = new TLine();
  l->DrawLine(1.3,0.7,1.3,1.1);
  l->DrawLine(2.5,0.7,2.5,1.1);
  l->DrawLine(3.0,0.7,3.0,1.1);
  l->DrawLine(4.5,0.7,4.5,1.1);
  l->SetLineStyle(kDashed);
  l->DrawLine(3.2,0.7,3.2,1.1);

  //tex->DrawLatex(0.23,0.86,"2012 JES: Anti-k_{t} R = 0.5, PF+CHS");
  //tex->DrawLatex(0.30,0.86,"53X JES: Anti-k_{t} R = 0.5, PF+CHS");
  //tex->DrawLatex(0.30,0.86,"74X JES: Anti-k_{t} R = 0.4, PF+CHS");
  //tex->DrawLatex(0.30,0.86,"76X JES: Anti-k_{t} R = 0.4, PF+CHS");
  //tex->DrawLatex(0.23,0.86,"2016 JES: Anti-k_{T} R=0.4, PF+CHS");
  tex->DrawLatex(0.23,0.86,"2017 JES: Anti-k_{t} R = 0.4, PF+CHS");
  //tex->DrawLatex(0.23,0.86,"2017 03FebV3: Anti-k_{t} R = 0.4, PF+CHS");
 
  tex->DrawLatex(0.19,0.78,"Barrel");
  tex->DrawLatex(0.47,0.78,"Endcap"); //0.42
  tex->DrawLatex(0.73,0.78,"Forward");

  tex->DrawLatex(0.21,0.73,"BB");
  tex->DrawLatex(0.43,0.73,"EC1");
  tex->DrawLatex(0.57,0.73,"EC2");
  tex->DrawLatex(0.77,0.73,"HF");

  c1->SaveAs("pdf/drawCMSresponse.pdf");
} // drawCMSresponse