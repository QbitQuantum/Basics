//
// Principal code segment
//
void pi0_HadCorrelations_Projections(const int iMultOption = 4,
				     const bool peakRegionFile = true,
				     const bool sideBandFile = false,
				     const bool usePbPbData = false,
				     const bool usepPbData = false,
				     const bool useSimReco = false,
				     const bool useGenEvts = true,
				     const bool useV1V2Fit = true,
                                     const bool useV2FitOnly = false) {
  // 
  //             Control Parameter Instructions
  // iMultOption = 0, 1, 2, 3, 4 controls the track multiplicity selection [120-150, 150-195, 185-220, 220-260, 120-260]
  // peakRegionFile = true means that the input file inputTrue.root will be used
  //                  it is assumed that inputTrue.root is soft-linked to a peak-region output ROOT file from the EDM
  //                  this could be either a PbPb, or a pPb, or a pPb simulation ROOT file from the EDM
  //
  // sideBandFile = true is the same logic for a side-band output ROOT file from the EDM analyzer
  //                the inputSide.root is to be soft-lined to a side-band output ROOT file from the EDM
  //
  // only one of peakRegionFile or sideBandFile can be true
  //
  // usePbPbData, usepPbData, useSimReco, or useGenEvts indicate which type of data or MC is being processed
  //
  // for the pPb data and the Sim data choices, there are 8 pT bins
  // for the PbPb data there are 6 pT bins
  //
 
  //
  //          Output results
  // The macro produces two sets of plots: two-dimensional correlation and Fourier-fitted one-dimension
  // The macro produces an output text file, either PeakRegion_ijkMultlmn.txt or SideBand_ijkMultlmn.txt
  //                  the ijk and lmn are the track multiplicity limits determined by the iOption choice
  //

  if(sideBandFile && useGenEvts) {
    cerr << "\n\n Error in input parameters: cannot have a side-band file for generator events" << endl << endl;
    return;
  }

  int nPtBins = 8;
  const float _PbPb_ptMin[6] = {0.7, 1.0, 1.5, 2.0, 2.5, 3.0};
  const float _PbPb_ptMax[6] = {1.0, 1.5, 2.0, 2.5, 3.0, 5.0};

  const float _pPb_ptMin[8] = {0.7, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0};
  const float _pPb_ptMax[8] = {1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0};

  float _ptMin[8] = {0.7, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0};
  float _ptMax[8] = {1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0};

  bool goodDataSource = false;
  char *dataText = new char[200];
  if(usePbPbData) {
    if(usepPbData || useSimReco || useGenEvts) {
      cerr << "\n Cannot only specify one data source as true" << endl;
      return;
    }
    nPtBins = 6;
    for(int kPt=0; kPt<nPtBins; kPt++) {
      _ptMin[kPt] = _PbPb_ptMin[kPt];
      _ptMax[kPt] = _PbPb_ptMax[kPt];
    }
    goodDataSource = true;
    cout << "\n Using PbPbData source with " << nPtBins << " pT bins" << endl;
    sprintf(dataText, "CMS PbPb #sqrt{s_{NN}}=2.76 TeV");
  }
  if(usepPbData) {
    if(usePbPbData || useSimReco || useGenEvts) {
      cerr << "\n Cannot only specify one data source as true" << endl;
      return;
    }
    nPtBins = 8;
    for(int kPt=0; kPt<nPtBins; kPt++) {
      _ptMin[kPt] = _pPb_ptMin[kPt];
      _ptMax[kPt] = _pPb_ptMax[kPt];
    }
    goodDataSource = true;
    cout << "\n Using pPbData source with " << nPtBins << " pT bins" << endl;
    sprintf(dataText, "CMS pPb #sqrt{s_{NN}}=5.0 TeV");
  }
  if(useSimReco) {
    if(usePbPbData || usepPbData || useGenEvts) {
      cerr << "\n Cannot only specify one data source as true" << endl;
      return;
    }
    nPtBins = 8;
    for(int kPt=0; kPt<nPtBins; kPt++) {
      _ptMin[kPt] = _pPb_ptMin[kPt];
      _ptMax[kPt] = _pPb_ptMax[kPt];
    }
    goodDataSource = true;
    cout << "\n Using SimData source with " << nPtBins << " pT bins" << endl;
    sprintf(dataText, "EPOS RECO pPb #sqrt{s_{NN}}=5.01 TeV");
  }

  if(useGenEvts) {
    if(usePbPbData || usepPbData || useSimReco) {
      cerr << "\n Cannot only specify one data source as true" << endl;
      return;
    }
    if(!peakRegionFile) {
      cerr << "\n The peakRegionFile must be set to true when useGenEvts is true" << endl;
      return;
    }
    nPtBins = 8;
    for(int kPt=0; kPt<nPtBins; kPt++) {
      _ptMin[kPt] = _pPb_ptMin[kPt];
      _ptMax[kPt] = _pPb_ptMax[kPt];
    }
    goodDataSource = true;
    cout << "\n Using GenEvts source with " << nPtBins << " pT bins" << endl;
    sprintf(dataText, "EPOS GEN pPb #sqrt{s_{NN}}=5.01 TeV");
  }

  if(!goodDataSource) {
    cerr << "\n The data source was not specified" << endl;
    return;
  }  

  if(peakRegionFile && sideBandFile) {
    cerr << "\n Cannot have the peakRegionFile and the sideBandFile both set to true"<< endl;
    return;
  }
  
  if(!peakRegionFile && !sideBandFile) {
    cerr << "\n Cannot have the peakRegionFile and the sideBandFile both set to false"<< endl;
    return;
  }
  
  TCanvas *c1 = new TCanvas("c1","",900,900);
  Canvas();
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetTopMargin(0.05);
  c1->SetBottomMargin(0.1);
  c1->SetLeftMargin(0.1742581);
  c1->SetRightMargin(0.05);
  c1->SetTheta(50.61189);
  c1->SetPhi(40.90062);

  if(nPtBins == 8)
    c1->Divide(3,3);

  if(nPtBins == 6)
    c1->Divide(3,2);

  TCanvas *c2 = new TCanvas("c2", "c2",900,900);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c2->Range(0,0,1,1);
  c2->SetFillColor(0);
  c2->SetBorderMode(0);
  c2->SetBorderSize(2);
  //c1->SetLogy();
  c2->SetTickx(1);
  c2->SetTicky(1);
  c2->SetLeftMargin(0.16);
  c2->SetRightMargin(0.16);
  c2->SetTopMargin(0.05);
  c2->SetBottomMargin(0.13);
  c2->SetFrameFillStyle(0);
  c2->SetFrameBorderMode(0);

  if(nPtBins == 8)
    c2->Divide(3,3);

  if(nPtBins == 6)
    c2->Divide(3,2);
    
  TH1::SetDefaultSumw2();
 
  char *inputFileName = new char[200];
  if(peakRegionFile) {
    sprintf(inputFileName, "inputTrue.root");
  }
  if(sideBandFile) {
    sprintf(inputFileName, "inputSide.root");
  }
  TFile *_fpPbData = new TFile(inputFileName, "r");
  if(!_fpPbData) {
    cerr << "\n Cannot find input file " << inputFileName << endl;
    return;
  }
  else {
    cout << "\n Found input file " << inputFileName << endl;
  }

  TH1F * _hEvent_pPb;
  double _nEvents_pPb;
  TH2D *_hSignal_pPb[8];
  TH2D *_hBackground_pPb[8];
    
  char *multText = new char[10];
  char *eventText = new char[100];
  char *signalText = new char[100];
  char *bkgText = new char[100];

  int lowMultiplicity = 120;
  int highMultiplicity = 150;
  char *multiplicityText = new char[200];
  bool goodMultOption = false;
  if(iMultOption == 0) {
    sprintf(multText, "EcalFlowNtpMult100");
    goodMultOption = true;
    sprintf(multiplicityText, "120 #leq N_{track}^{offline} < 150");
  }
  if(iMultOption == 1) {
    sprintf(multText, "EcalFlowNtpMult130");
    lowMultiplicity = 150;
    highMultiplicity = 185;
    goodMultOption = true;
    sprintf(multiplicityText, "150 #leq N_{track}^{offline} < 185");
  }
  if(iMultOption == 2) {
    sprintf(multText, "EcalFlowNtpMult160");
    lowMultiplicity = 185;
    highMultiplicity = 220;
    goodMultOption = true;
    sprintf(multiplicityText, "185 #leq N_{track}^{offline} < 220");
  }
  if(iMultOption == 3) {
    sprintf(multText, "EcalFlowNtpMult190");
    lowMultiplicity = 220;
    highMultiplicity = 260;
    goodMultOption = true;
    sprintf(multiplicityText, "220 #leq N_{track}^{offline} < 260");
  }
  if(iMultOption == 4) {
    sprintf(multText, "EcalFlowNtp");
    lowMultiplicity = 120;
    highMultiplicity = 260;
    goodMultOption = true;
    sprintf(multiplicityText, "120 #leq N_{track}^{offline} < 260");
  }

  if(goodMultOption) {
    if(!useGenEvts) {
      sprintf(eventText, "%s/ChargedParticles/tHPTracks_", multText);
      sprintf(signalText, "%s/pi0HadCorrFunc/hSignalPtBin", multText);
      sprintf(bkgText, "%s/pi0HadCorrFunc/hBackgroundPtBin", multText);
    }
    else {
      sprintf(eventText, "%s/ChargedParticles/tHPTracks_", multText);
      sprintf(signalText, "%s/pi0HadCorrFunc/hGenSignalPtBin", multText);
      sprintf(bkgText, "%s/pi0HadCorrFunc/hGenBackgroundPtBin", multText);
    }
  }
  else {
    cerr << "\n Multiplicity option " << iMultOption << " is not valid" << endl;
    return;
  } // safety check
   
  ofstream myfile;
  char *myFileName = new char[200];
  if(peakRegionFile) {
    sprintf(myFileName, "PeakRegion_%dMult%d.txt", lowMultiplicity, highMultiplicity);
  }
  if(sideBandFile) {
    sprintf(myFileName, "SideBand_%dMult%d.txt", lowMultiplicity, highMultiplicity);
  }
  cout << "\n Opening output text file " << myFileName << endl;
  myfile.open (myFileName);

  cout << "\n eventText = " << eventText;
  cout << "\n signalText= " << signalText;
  cout << "\n signalText = " << bkgText;
  cout << endl;

  char *_SignalHistoName1 = new char[200];
  char *_BkgHistoName1 = new char[200];

  //
  // Why are these numbers hard=coded here?
  //    
  float _SignalFraction[8] = {0.09, 0.23, 0.44, 0.59, 0.66, 0.71, 0.73, 0.74};
    
  _hEvent_pPb = (TH1F*)_fpPbData->Get(eventText);
  if(!_hEvent_pPb) {
    cerr << "\n Unable to find hEvent_pPb with name " << eventText << endl;
    return;
  }
  _nEvents_pPb = _hEvent_pPb->Integral();
    
  cout << "\n Number of events _nEvents_pPb = " << _nEvents_pPb << "; setting up 8 histogram names" << endl;
  for(int iCount=0; iCount<8; ++iCount)
    {
      sprintf(_SignalHistoName1, "%s%d", signalText, iCount);
      sprintf(_BkgHistoName1, "%s%d", bkgText, iCount);

      cout << " iCount = " << iCount << '\t' << "Signal name = " << _SignalHistoName1<<endl;
      cout << " iCount = " << iCount << '\t' << "Background name = " << _BkgHistoName1<<endl;
        
      _hSignal_pPb[iCount] = (TH2D*)_fpPbData->Get(_SignalHistoName1);
      if(!_hSignal_pPb[iCount]) {
	cerr << "\n Unable to find _hSignal_pPb[iCount]" << endl;
	return;
      }

      _hBackground_pPb[iCount] = (TH2D*)_fpPbData->Get(_BkgHistoName1);
      if(!_hBackground_pPb[iCount]) {
	cerr << "\n Unable to find _hBackground_pPb[iCount]" << endl;
	return;
      }
        
    } // loop over 8 histogram bins
    
  double  _etabinwidth = _hSignal_pPb[0]->GetXaxis()->GetBinWidth(1);
  double  _phibinwidth = _hSignal_pPb[0]->GetYaxis()->GetBinWidth(1);
    
  for(long iCount=0; iCount<nPtBins; ++iCount)
    {
      _hSignal_pPb[iCount]->Divide(_hBackground_pPb[iCount]);
      int _x0 = _hBackground_pPb[iCount]->GetXaxis()->FindBin(0.0);
      int _y0 = _hBackground_pPb[iCount]->GetYaxis()->FindBin(0.0);
      double _B0 = _hBackground_pPb[iCount]->GetBinContent(_x0,_y0);
      _hSignal_pPb[iCount]->Scale(_B0/(_nEvents_pPb));
      _hSignal_pPb[iCount]->Scale(1.0/_etabinwidth/_phibinwidth);
        
      c1->cd(iCount+1);
    
      _hSignal_pPb[iCount]->GetXaxis()->SetRange(5,29);
        
      _hSignal_pPb[iCount]->GetXaxis()->SetTitle("#Delta#eta");
      _hSignal_pPb[iCount]->GetXaxis()->SetRange(5,29);
      _hSignal_pPb[iCount]->GetXaxis()->CenterTitle(true);
      _hSignal_pPb[iCount]->GetXaxis()->SetLabelFont(42);
      _hSignal_pPb[iCount]->GetXaxis()->SetLabelSize(0.035);
      _hSignal_pPb[iCount]->GetXaxis()->SetTitleSize(0.05);
      _hSignal_pPb[iCount]->GetXaxis()->SetTitleOffset(1.38);
      _hSignal_pPb[iCount]->GetXaxis()->SetTitleFont(42);
      _hSignal_pPb[iCount]->GetYaxis()->SetTitle("#Delta#phi");
      _hSignal_pPb[iCount]->GetYaxis()->CenterTitle(true);
      _hSignal_pPb[iCount]->GetYaxis()->SetLabelFont(42);
      _hSignal_pPb[iCount]->GetYaxis()->SetLabelSize(0.035);
      _hSignal_pPb[iCount]->GetYaxis()->SetTitleSize(0.05);
      _hSignal_pPb[iCount]->GetYaxis()->SetTitleOffset(1.59);
      _hSignal_pPb[iCount]->GetYaxis()->SetTitleFont(42);
      _hSignal_pPb[iCount]->GetZaxis()->SetTitle("#frac{1}{N_{trig}} #frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}");
      _hSignal_pPb[iCount]->GetZaxis()->SetLabelFont(42);
      _hSignal_pPb[iCount]->GetZaxis()->SetLabelSize(0.035);
      _hSignal_pPb[iCount]->GetZaxis()->SetTitleSize(0.035);
      _hSignal_pPb[iCount]->GetZaxis()->SetTitleOffset(2.33);
      _hSignal_pPb[iCount]->GetZaxis()->SetTitleFont(42);
      _hSignal_pPb[iCount]->GetZaxis()->SetNdivisions(505);
      _hSignal_pPb[iCount]->Draw("SURF1");
        
      TLatex * tex = new TLatex(-0.8847018,0.9364877,Form("%5.1f < p_{T} < %5.1f (GeV/c)",_ptMin[iCount],_ptMax[iCount]));
      tex->SetTextSize(0.06);
      tex->Draw();

    } // loop over 8 histogram bins
    
  cout <<"\n Now drawing the projections..." << endl;
  float etaMin = 2.0;
  float etaMax = 3.6;
    
  TString _Name = "projClone";
  TString _Name2 = "_pi0HadProj";
  TString _Name4 = "FourierDecompose";
  TString _Name1, _Name3, _Name5;
    
  TH2D *_projCorrFunc[9];
  TH1D * _pi0HadCorrProj[9];
  TF1 *_FourierDecompose[9];
  const int n = 9;
  double _Parameter0[n];
  double _Par0Error[n];
  double _Parameter2[n];
  double _Par2Error[n];
  double _Ratio[n];
  double _Error[n];
    
  for(long iCount=0; iCount<nPtBins; ++iCount) {
    _Name1 = _Name + iCount;
    _Name3 = _Name2 + iCount;
    _Name5 = _Name4 + iCount;
        
    _projCorrFunc[iCount] = (TH2D*) _hSignal_pPb[iCount]->Clone(_Name1);
    Int_t etabin10m=_projCorrFunc[iCount]->GetXaxis()->FindBin(etaMin+0.01);
    Int_t etabin10p=_projCorrFunc[iCount]->GetXaxis()->FindBin(etaMax-0.01);
    
    _pi0HadCorrProj[iCount] = (TH1D *) _projCorrFunc[iCount]->ProjectionY(_Name3,etabin10m,etabin10p,"e");
    _pi0HadCorrProj[iCount]->GetXaxis()->SetRange(8,24);
            
    c2->cd(iCount+1);
   
    _pi0HadCorrProj[iCount]->SetMarkerColor(4);
    _pi0HadCorrProj[iCount]->SetMarkerStyle(20);
    _pi0HadCorrProj[iCount]->SetMarkerSize(1.0);
    _pi0HadCorrProj[iCount]->GetXaxis()->SetTitle("#Delta#phi");
    _pi0HadCorrProj[iCount]->GetXaxis()->SetLabelFont(42);
    _pi0HadCorrProj[iCount]->GetXaxis()->SetTitleSize(0.06);
    _pi0HadCorrProj[iCount]->GetXaxis()->SetTitleOffset(0.67);
    _pi0HadCorrProj[iCount]->GetXaxis()->SetTitleFont(42);
    _pi0HadCorrProj[iCount]->GetYaxis()->SetTitle("Associated yield");
    _pi0HadCorrProj[iCount]->GetYaxis()->SetLabelFont(42);
    _pi0HadCorrProj[iCount]->GetYaxis()->SetTitleSize(0.06);
    _pi0HadCorrProj[iCount]->GetYaxis()->SetTitleOffset(0.77);
    _pi0HadCorrProj[iCount]->GetYaxis()->SetTitleFont(42);

    _pi0HadCorrProj[iCount]->GetZaxis()->SetLabelFont(42);
    _pi0HadCorrProj[iCount]->GetZaxis()->SetLabelSize(0.035);
    _pi0HadCorrProj[iCount]->GetZaxis()->SetTitleSize(0.035);
    _pi0HadCorrProj[iCount]->GetZaxis()->SetTitleFont(42);

    float maximumHistogramValue = _pi0HadCorrProj[iCount]->GetMaximum();
    float minimumHistogramValue = _pi0HadCorrProj[iCount]->GetMinimum();
    _pi0HadCorrProj[iCount]->SetMaximum(maximumHistogramValue + 0.60*(maximumHistogramValue - minimumHistogramValue));

    _pi0HadCorrProj[iCount]->Draw("E1");
    (c2->cd(iCount+1))->SetGrid();

    if(useV1V2Fit) {
      _FourierDecompose[iCount] = new TF1(_Name5, v1v2Fit, -1.4, 4.88, 3);
      _FourierDecompose[iCount]->SetParNames("Norm","v1", "v2");
    }

    if(useV2FitOnly) {
      _FourierDecompose[iCount] = new TF1(_Name5, v2Fit, -1.4, 4.88, 2);
      _FourierDecompose[iCount]->SetParNames("Norm","v2");
    }
    
    if(!useV2FitOnly && !useV1V2Fit) {
    _FourierDecompose[iCount] = new TF1(_Name5, Function, -1.4, 4.88, 4);
    _FourierDecompose[iCount]->SetParNames("Par0","Par1","Par2","Par3");
    }

    _pi0HadCorrProj[iCount]->Fit(_Name5, "", "", -1.4, 4.84);
        
    double v1 = 0;
    double v1Error = 0;

    double v3 = 0;
    double v3Error = 0;

    if(useV1V2Fit) {
     v1 = ((_FourierDecompose[iCount]->GetParameter(1))/0.232);
     v1Error = ((_FourierDecompose[iCount]->GetParError(1))/0.232);

     _Ratio[iCount] = (_FourierDecompose[iCount]->GetParameter(2))/0.232;
     _Error[iCount] = (_FourierDecompose[iCount]->GetParError(2))/0.232;

   } // using a v1 + v2 fit function

    if(useV2FitOnly) {
      _Ratio[iCount] = (_FourierDecompose[iCount]->GetParameter(1))/0.232;
      _Error[iCount] = (_FourierDecompose[iCount]->GetParError(1))/0.232;
    } // using a pure v2 fit function
    
    if(!useV2FitOnly && !useV1V2Fit) {
      _Parameter0[iCount] = _FourierDecompose[iCount]->GetParameter(0);
      _Par0Error[iCount] = _FourierDecompose[iCount]->GetParError(0);
      _Parameter2[iCount] = _FourierDecompose[iCount]->GetParameter(2);
      _Par2Error[iCount] = _FourierDecompose[iCount]->GetParError(2);

      v3 = ((_FourierDecompose[iCount]->GetParameter(3))/0.232)/_Parameter0[iCount];
      v3Error = ((_FourierDecompose[iCount]->GetParError(3))/0.232)/_Parameter0[iCount];
    
      _Ratio[iCount] = _Parameter2[iCount]/_Parameter0[iCount];
        
      _Ratio[iCount] /= 0.232;  // v2 of the EPOS generator charged particles, 0.3 - 3.0 GeV/c, according to Z. Chen (May 4, 2014, K0-short analysis)
      
      _Error[iCount] = _Ratio[iCount]*(sqrt((_Par2Error[iCount]/_Parameter2[iCount])*(_Par2Error[iCount]/_Parameter2[iCount]) + 
					  (_Par0Error[iCount]/_Parameter0[iCount])*(_Par0Error[iCount]/_Parameter0[iCount]) + 
					  (0.0001364/0.08609)*(0.0001364/0.08609)));
    } // using Monika's fitting function

    TLegend *legend = new TLegend(0.15, 0.65, 0.88, 0.85);
    char *legendHeader = new char[200];
    sprintf(legendHeader, "%s, %s", dataText, multiplicityText); 
    legend->SetHeader(legendHeader);
    legend->SetTextSize(0.04);
    legend->SetTextColor(kBlue);
    char *ptRangeText = new char[200];

    if(sideBandFile) {
      sprintf(ptRangeText, "Bkg: %4.1f < p_{T} < %4.1f (GeV/c)", _ptMin[iCount], _ptMax[iCount]);
    }
    if(peakRegionFile) {
      sprintf(ptRangeText, "Peak for: %4.1f < p_{T} < %4.1f (GeV/c)", _ptMin[iCount], _ptMax[iCount]);
    }
 
    char *fitResults = new char[200];

    if(useV1V2Fit) {
      sprintf(fitResults, "v_{2} = %4.3f #pm %4.3f, v_{1} = %4.3f #pm %4.3f",_Ratio[iCount], _Error[iCount], v1, v1Error); 
    }

    if(useV2FitOnly) {
      sprintf(fitResults, "v_{2} = %4.3f #pm %4.3f (pure v_{2} fit)",_Ratio[iCount], _Error[iCount]); 
    }

    if(!useV2FitOnly && !useV1V2Fit) {
      sprintf(fitResults, "v_{2} = %4.3f #pm %4.3f, v_{3} = %4.3f #pm %4.3f",_Ratio[iCount], _Error[iCount], v3, v3Error); 
    }

    legend->AddEntry(_Name5, fitResults, "l");
    legend->AddEntry((TObject*)0, ptRangeText, "");
    legend->Draw();

  }  // loop over pT bins

  cout << "\n Now writing to the output text file " << myFileName << endl;
  cout << "------------------------****-------------------" << endl;
  for(long iCount=0; iCount<8; ++iCount)
    {

      cout << "Final v2(pi0) ["<< iCount << "] = " << _Ratio[iCount] << '\t' << _Error[iCount] << '\t' << _Error[iCount]/_SignalFraction[iCount] << endl;
      myfile << _Ratio[iCount] << '\t' << _Error[iCount] << endl;
    }
  cout <<"------------------------****-------------------" << endl;

  myfile.close();

}