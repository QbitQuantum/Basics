int rate(std::string fileName)
{
  setGlobalStyle();
  
  //###############################
  //## run274200 ##
  unsigned int HT250Calo  = 9; //index of DST_HT250_CaloScouting_v   old:1 ref:9
  unsigned int HT410PF = 7; //index of DST_HT410_PFScouting_v   old:3 ref:7
  unsigned int MJJ200Calo = 12; //index of DST_DiCaloWideJetMass200_CaloScouting_v
  
  unsigned int HTT200 = 0; //index if L1_HTT200
  unsigned int HTT240 = 1; //index if L1_HTT240
  unsigned int HTT270 = 2; //index if L1_HTT270
  unsigned int HTT280 = 3; //index if L1_HTT280
  unsigned int DoubleJetC100 = 7; //index if L1_DoubleJetC100
  unsigned int DoubleJetC112 = 8; //index if L1_DoubleJetC112
  unsigned int DoubleIsoTau28er = 11; //index if L1_DoubleJetC112

  float instLumi = 0.71; //E34
  float targetLumi = 1; //E34
  float lumiScaleFactor = targetLumi/instLumi;

  float PDRate = 21986976; //unprescaled rate of ParkingZeroBias accordingly to:  nEv/(nLS*23.3)*hltPresc*l1Presc   [*nPDs?] = 2343149/(824*23,3)*12*15013

  unsigned int L1MjjThr = 150;
  //###############################

  TChain* tt = new TChain("MyAnalysis/HLTree");
  tt->Add(fileName.c_str());

  //set branches
  TBranch* b_lumi;
  
  TBranch* b_caloMjj;
  TBranch* b_PFMjj;
  TBranch* b_caloWMjj;
  TBranch* b_PFWMjj;
  TBranch* b_l1Mjj;

  TBranch* b_hltAccept;
  TBranch* b_l1Accept;
  TBranch* b_l1Names;

  TBranch* b_caloJet1Pt;
  TBranch* b_caloJet2Pt;
  TBranch* b_caloJet1Eta;
  TBranch* b_caloJet2Eta;
  TBranch* b_caloJet1Phi;
  TBranch* b_caloJet2Phi;
  TBranch* b_caloDeltaEta;
  TBranch* b_caloWJet1Pt;
  TBranch* b_caloWJet2Pt;
  TBranch* b_caloWJet1Eta;
  TBranch* b_caloWJet2Eta;
  TBranch* b_caloWJet1Phi;
  TBranch* b_caloWJet2Phi;
  TBranch* b_caloWDeltaEta;

  TBranch* b_PFJet1Pt;
  TBranch* b_PFJet2Pt;
  TBranch* b_PFJet1Eta;
  TBranch* b_PFJet2Eta;
  TBranch* b_PFJet1Phi;
  TBranch* b_PFJet2Phi;
  TBranch* b_PFDeltaEta;
  TBranch* b_PFWJet1Pt;
  TBranch* b_PFWJet2Pt;
  TBranch* b_PFWJet1Eta;
  TBranch* b_PFWJet2Eta;
  TBranch* b_PFWJet1Phi;
  TBranch* b_PFWJet2Phi;
  TBranch* b_PFWDeltaEta;

  TBranch* b_l1Jet1Pt;
  TBranch* b_l1Jet2Pt;
  TBranch* b_l1Jet1Eta;
  TBranch* b_l1Jet2Eta;
  TBranch* b_l1Jet1Phi;
  TBranch* b_l1Jet2Phi;
  TBranch* b_l1DeltaEta;

  TBranch* b_l1JetPt;
  TBranch* b_l1JetEta;
  TBranch* b_l1JetPhi;

  int lumi = 0;
  float caloMjj = 0;
  float PFMjj = 0;
  float caloWMjj = 0;
  float PFWMjj = 0;
  float l1Mjj = 0;

  float caloJet1Pt_ = 0;
  float caloJet2Pt_ = 0;
  float caloJet1Eta_ = -999;
  float caloJet2Eta_ = -999;
  float caloJet1Phi_ = -999;
  float caloJet2Phi_ = -999;
  float caloDeltaEta_ = -999;
  float caloWJet1Pt_ = 0;
  float caloWJet2Pt_ = 0;
  float caloWJet1Eta_ = -999;
  float caloWJet2Eta_ = -999;
  float caloWJet1Phi_ = -999;
  float caloWJet2Phi_ = -999;
  float caloWDeltaEta_ = -999;

  float PFJet1Pt_ = 0;
  float PFJet2Pt_ = 0;
  float PFJet1Eta_ = -999;
  float PFJet2Eta_ = -999;
  float PFJet1Phi_ = -999;
  float PFJet2Phi_ = -999;
  float PFDeltaEta_ = -999;
  float PFWJet1Pt_ = 0;
  float PFWJet2Pt_ = 0;
  float PFWJet1Eta_ = -999;
  float PFWJet2Eta_ = -999;
  float PFWJet1Phi_ = -999;
  float PFWJet2Phi_ = -999;
  float PFWDeltaEta_ = -999;

  float l1Jet1Pt_ = 0;
  float l1Jet2Pt_ = 0;
  float l1Jet1Eta_ = -999;
  float l1Jet2Eta_ = -999;
  float l1Jet1Phi_ = -999;
  float l1Jet2Phi_ = -999;
  float l1DeltaEta_ = -999;

  std::vector<float>* l1JetPt_ = 0;
  std::vector<float>* l1JetEta_ = 0;
  std::vector<float>* l1JetPhi_ = 0;
  
  std::vector<int>* hltAccept = 0;
  std::vector<int>* l1Accept = 0;
  std::vector<string>* l1Names = 0;

  tt->SetBranchAddress("lumi", &lumi, &b_lumi);

  tt->SetBranchAddress("caloMjj", &caloMjj, &b_caloMjj);
  tt->SetBranchAddress("PFMjj", &PFMjj, &b_PFMjj);
  tt->SetBranchAddress("caloWMjj", &caloWMjj, &b_caloWMjj);
  tt->SetBranchAddress("PFWMjj", &PFWMjj, &b_PFWMjj);
  tt->SetBranchAddress("l1Mjj", &l1Mjj, &b_l1Mjj);

  tt->SetBranchAddress("caloJet1Pt", &caloJet1Pt_, &b_caloJet1Pt);
  tt->SetBranchAddress("caloJet2Pt", &caloJet2Pt_, &b_caloJet2Pt);
  tt->SetBranchAddress("caloJet1Eta", &caloJet1Eta_, &b_caloJet1Eta);
  tt->SetBranchAddress("caloJet2Eta", &caloJet2Eta_, &b_caloJet2Eta);
  tt->SetBranchAddress("caloJet1Phi", &caloJet1Phi_, &b_caloJet1Phi);
  tt->SetBranchAddress("caloJet2Phi", &caloJet2Phi_, &b_caloJet2Phi);
  tt->SetBranchAddress("caloDeltaEta", &caloDeltaEta_, &b_caloDeltaEta);
  tt->SetBranchAddress("caloWJet1Pt", &caloWJet1Pt_, &b_caloWJet1Pt);
  tt->SetBranchAddress("caloWJet2Pt", &caloWJet2Pt_, &b_caloWJet2Pt);
  tt->SetBranchAddress("caloWJet1Eta", &caloWJet1Eta_, &b_caloWJet1Eta);
  tt->SetBranchAddress("caloWJet2Eta", &caloWJet2Eta_, &b_caloWJet2Eta);
  tt->SetBranchAddress("caloWJet1Phi", &caloWJet1Phi_, &b_caloWJet1Phi);
  tt->SetBranchAddress("caloWJet2Phi", &caloWJet2Phi_, &b_caloWJet2Phi);
  tt->SetBranchAddress("caloWDeltaEta", &caloWDeltaEta_, &b_caloWDeltaEta);

  tt->SetBranchAddress("PFJet1Pt", &PFJet1Pt_, &b_PFJet1Pt);
  tt->SetBranchAddress("PFJet2Pt", &PFJet2Pt_, &b_PFJet2Pt);
  tt->SetBranchAddress("PFJet1Eta", &PFJet1Eta_, &b_PFJet1Eta);
  tt->SetBranchAddress("PFJet2Eta", &PFJet2Eta_, &b_PFJet2Eta);
  tt->SetBranchAddress("PFJet1Phi", &PFJet1Phi_, &b_PFJet1Phi);
  tt->SetBranchAddress("PFJet2Phi", &PFJet2Phi_, &b_PFJet2Phi);
  tt->SetBranchAddress("PFDeltaEta", &PFDeltaEta_, &b_PFDeltaEta);
  tt->SetBranchAddress("PFWJet1Pt", &PFWJet1Pt_, &b_PFWJet1Pt);
  tt->SetBranchAddress("PFWJet2Pt", &PFWJet2Pt_, &b_PFWJet2Pt);
  tt->SetBranchAddress("PFWJet1Eta", &PFWJet1Eta_, &b_PFWJet1Eta);
  tt->SetBranchAddress("PFWJet2Eta", &PFWJet2Eta_, &b_PFWJet2Eta);
  tt->SetBranchAddress("PFWJet1Phi", &PFWJet1Phi_, &b_PFWJet1Phi);
  tt->SetBranchAddress("PFWJet2Phi", &PFWJet2Phi_, &b_PFWJet2Phi);
  tt->SetBranchAddress("PFWDeltaEta", &PFWDeltaEta_, &b_PFWDeltaEta);

  tt->SetBranchAddress("l1Jet1Pt", &l1Jet1Pt_, &b_l1Jet1Pt);
  tt->SetBranchAddress("l1Jet2Pt", &l1Jet2Pt_, &b_l1Jet2Pt);
  tt->SetBranchAddress("l1Jet1Eta", &l1Jet1Eta_, &b_l1Jet1Eta);
  tt->SetBranchAddress("l1Jet2Eta", &l1Jet2Eta_, &b_l1Jet2Eta);
  tt->SetBranchAddress("l1Jet1Phi", &l1Jet1Phi_, &b_l1Jet1Phi);
  tt->SetBranchAddress("l1Jet2Phi", &l1Jet2Phi_, &b_l1Jet2Phi);
  tt->SetBranchAddress("l1DeltaEta", &l1DeltaEta_, &b_l1DeltaEta);

  tt->SetBranchAddress("l1JetPt", &l1JetPt_, &b_l1JetPt);
  tt->SetBranchAddress("l1JetEta", &l1JetEta_, &b_l1JetEta);
  tt->SetBranchAddress("l1JetPhi", &l1JetPhi_, &b_l1JetPhi);

  tt->SetBranchAddress("hltAccept", &hltAccept, &b_hltAccept);
  tt->SetBranchAddress("l1Accept", &l1Accept, &b_l1Accept);
  tt->SetBranchAddress("l1Names", &l1Names, &b_l1Names);

  int nentries = tt->GetEntries();
  std::cout << "Number of entries: " << nentries << std::endl;
  
  //book graphs and plots
  float min = 0.;
  float max = 1000.;
  int nBins = 20;

  TF1* f1 = new TF1("f1","[0]*TMath::Erf((x-[1])/[2])-[0]*TMath::Erf((-x-[1])/[2])",min,max);
  f1->SetParameters(0.5,350,40);  
  f1->FixParameter(0,0.5);
  f1->SetLineWidth(2.);
  f1->SetLineColor(kRed);

  TF1* f2 = (TF1*)f1->Clone("f2");
  f2->SetParameters(0.5,150,10);
  f2->SetLineColor(kBlack);

  //##############################################
  //##############################################

  //book graphs and plots
  TGraphErrors* totL1RateVsCut = new TGraphErrors();
  totL1RateVsCut->SetMinimum(0);
  TGraphErrors* pureL1RateVsCut = new TGraphErrors();

  TGraphErrors* totHltRateVsCut = new TGraphErrors();
  totHltRateVsCut->SetMinimum(0);
  TGraphErrors* pureHltRateVsCut = new TGraphErrors();

  //loops
  int bin = 0;
  for (int cut = 200; cut < 350; cut=cut+10)
    {
      std::cout << "analyzing point at " << cut << " GeV" << std::endl;

      int mjjHltPassed = 0;
      int excl_mjjHltPassed = 0;

      int mjjL1Passed = 0;
      int excl_mjjL1Passed = 0;

      int HTT240Passed = 0;

      for (Long64_t jentry=0; jentry<nentries;++jentry) 
	{
	  tt->GetEntry(jentry);

	  //### Sanity checks ###
	  if (l1Accept->at(HTT240) == 1)
	    ++HTT240Passed;
	  
	  //### L1 ###
	  bool l1Pass = (l1Mjj>cut &&
			 l1Jet1Pt_ > 15. &&
			 l1Jet2Pt_ > 15. &&
			 fabs(l1Jet1Eta_) < 5.0 &&
			 fabs(l1Jet2Eta_) < 5.0 &&
			 l1DeltaEta_ < 2.0
			 );

	  bool L1RefPass = (l1Mjj>L1MjjThr &&
			    l1Jet1Pt_ > 15. &&
			    l1Jet2Pt_ > 15. &&
			    fabs(l1Jet1Eta_) < 5.0 &&
			    fabs(l1Jet2Eta_) < 5.0 &&
			    l1DeltaEta_ < 2.0
			    );


	  // if(l1Pass && l1Accept->at(HTT240) == 0 && caloWMjj < 100 && caloWMjj>0)
	  //   {
	  //     std::cout << std::endl;
	  //     std::cout << std::fixed << std::setprecision(2)
	  // 		<< "l1Mjj-caloWMjj = " << l1Mjj-caloWMjj << " l1Mjj = " << l1Mjj << " caloWMjj = " << caloWMjj << std::endl;
	  //     std::cout << "  caloWJet1Pt_    = " << caloWJet1Pt_     << " caloWJet1Eta_     = " << caloWJet1Eta_     << " caloWJet1Phi_     = " << caloWJet1Phi_ << std::endl;
	  //     std::cout << "  l1Jet1Pt        = " << l1Jet1Pt_        << " l1Jet1Eta         = " << l1Jet1Eta_        << " l1Jet1Phi         = " << l1Jet1Phi_ << std::endl;
	  //     std::cout << std::endl;
	  //     std::cout << "  caloWJet2Pt_     = " << caloWJet2Pt_     << " caloWJet2Eta_     = " << caloWJet2Eta_     << " caloWJet2Phi_     = " << caloWJet2Phi_ << std::endl;
	  //     std::cout << "  l1Jet2Pt         = " << l1Jet2Pt_        << " l1Jet2Eta         = " << l1Jet2Eta_        << " l1Jet2Phi         = " << l1Jet2Phi_ << std::endl;
	  //     std::cout << "==========================================================" << std::endl;
	  //   }
	  

		      
	  if (l1Pass)
	    ++mjjL1Passed;
	  if (l1Pass && l1Accept->at(HTT240) == 0)
	    ++excl_mjjL1Passed;


	  //### HLT ###
	  //Hypothesis of HLT rates with L1Mjj seed at L1MjjThr
	  if (caloWMjj > cut && L1RefPass)
	    ++mjjHltPassed;
	  if (caloWMjj > cut && L1RefPass && hltAccept->at(HT250Calo) == 0)
	    ++excl_mjjHltPassed;


	}
      float HTT240rate = (float)HTT240Passed/(float)nentries*PDRate;
      //std::cout << "HTT240rate = " << HTT240rate << std::endl;
      
      float sigmaNentries = sqrt((float)nentries);

      float sigmaMjjHltPassed = sqrt((float)mjjHltPassed);
      float excl_sigmaMjjHltPassed = sqrt((float)excl_mjjHltPassed);

      float sigmaMjjL1Passed = sqrt((float)mjjL1Passed);
      float excl_sigmaMjjL1Passed = sqrt((float)excl_mjjL1Passed);

      float mjjHltRate = (float)mjjHltPassed/(float)nentries*PDRate;
      float mjjHltRateE = PDRate*sqrt(pow((sigmaMjjHltPassed/nentries),2)+pow((sigmaNentries*mjjHltPassed/nentries/nentries),2));
      float excl_mjjHltRate = (float)excl_mjjHltPassed/(float)nentries*PDRate;
      float excl_mjjHltRateE = PDRate*sqrt(pow((excl_sigmaMjjHltPassed/nentries),2)+pow((sigmaNentries*excl_mjjHltPassed/nentries/nentries),2));

      float mjjL1Rate = (float)mjjL1Passed/(float)nentries*PDRate;
      float mjjL1RateE = PDRate*sqrt(pow((sigmaMjjL1Passed/nentries),2)+pow((sigmaNentries*mjjL1Passed/nentries/nentries),2));
      float excl_mjjL1Rate = (float)excl_mjjL1Passed/(float)nentries*PDRate;
      float excl_mjjL1RateE = PDRate*sqrt(pow((excl_sigmaMjjL1Passed/nentries),2)+pow((sigmaNentries*excl_mjjL1Passed/nentries/nentries),2));

      totHltRateVsCut->SetPoint(bin,cut,mjjHltRate);
      totHltRateVsCut->SetPointError(bin,0.,mjjHltRateE);
      pureHltRateVsCut->SetPoint(bin,cut,excl_mjjHltRate);
      pureHltRateVsCut->SetPointError(bin,0.,excl_mjjHltRateE);

      totL1RateVsCut->SetPoint(bin,cut,mjjL1Rate);
      totL1RateVsCut->SetPointError(bin,0.,mjjL1RateE);
      pureL1RateVsCut->SetPoint(bin,cut,excl_mjjL1Rate);
      pureL1RateVsCut->SetPointError(bin,0.,excl_mjjL1RateE);

      ++bin;
    }

  //plotting and styling
  TLegend* legHlt = new TLegend(0.62, 0.78, 0.83, 0.89);
  legHlt->AddEntry(totHltRateVsCut,"hlt total rate","P");
  legHlt->AddEntry(pureHltRateVsCut,"hlt pure rate wrt HT250","P");

  TLegend* legL1 = new TLegend(0.62, 0.78, 0.83, 0.89);
  legL1->AddEntry(totL1RateVsCut,"l1 total rate","P");
  legL1->AddEntry(pureL1RateVsCut,"l1 pure rate wrt HTT240","P");

  totHltRateVsCut->GetXaxis()->SetTitle("Mjj cut threshold [GeV]");
  totHltRateVsCut->GetYaxis()->SetTitle("Rate @7E33 [Hz]");
  totHltRateVsCut->SetMarkerColor(kRed);
  pureHltRateVsCut->SetMarkerColor(kOrange+1);

  totL1RateVsCut->GetXaxis()->SetTitle("Mjj cut threshold [GeV]");
  totL1RateVsCut->GetYaxis()->SetTitle("Rate @7E33 [Hz]");
  totL1RateVsCut->SetMarkerColor(kBlue);
  totL1RateVsCut->SetMarkerColor(kAzure);

  TCanvas* c4 = new TCanvas();
  c4->cd();
  totHltRateVsCut->Draw("AP");
  pureHltRateVsCut->Draw("P,sames");
  legHlt->Draw("sames");
  c4->Update();
  TGaxis *axisHlt = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(), gPad->GetUymax(),
    			    (totHltRateVsCut->GetYaxis()->GetBinLowEdge(1))*lumiScaleFactor,
			    (totHltRateVsCut->GetYaxis()->GetBinLowEdge(totHltRateVsCut->GetYaxis()->GetNbins())+totHltRateVsCut->GetYaxis()->GetBinWidth(1))*lumiScaleFactor,510,"+L");

  c4->SetTicky(0);
  axisHlt->SetLineColor(kRed);
  axisHlt->SetLabelColor(kRed);
  axisHlt->SetTextColor(kRed);
  axisHlt->SetTitleOffset(1.3);
  axisHlt->SetLabelSize(0.03);
  axisHlt->SetTitle("Rate @1E34 [Hz]");
  axisHlt->Draw();
  c4->Print("rates/hltRate.pdf","pdf");


  TCanvas* c5 = new TCanvas();
  c5->cd();
  totL1RateVsCut->Draw("AP");
  pureL1RateVsCut->Draw("P,sames");
  legL1->Draw("sames");
  c5->Update();
  TGaxis *axisL1 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(), gPad->GetUymax(),
			      (totL1RateVsCut->GetYaxis()->GetBinLowEdge(1))*lumiScaleFactor,
			      (totL1RateVsCut->GetYaxis()->GetBinLowEdge(totL1RateVsCut->GetYaxis()->GetNbins())+totL1RateVsCut->GetYaxis()->GetBinWidth(1))*lumiScaleFactor,510,"+L");

  c5->SetTicky(0);
  axisL1->SetLineColor(kRed);
  axisL1->SetLabelColor(kRed);
  axisL1->SetTextColor(kRed);
  axisL1->SetTitleOffset(1.3);
  axisL1->SetLabelSize(0.03);
  axisL1->SetTitle("Rate @1E34 [Hz]");
  axisL1->Draw();
  c5->Print("rates/l1Rate.pdf","pdf");

  return 0;
}