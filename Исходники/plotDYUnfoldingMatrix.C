void plotDYUnfoldingMatrix(const TString input, int systematicsMode = DYTools::NORMAL, int randomSeed = 1, double reweightFsr = 1.0, double massLimit = -1.0)
//systematicsMode 0 (NORMAL) - no systematic calc
//1 (RESOLUTION_STUDY) - systematic due to smearing, 2 (FSR_STUDY) - systematics due to FSR, reweighting
//check mass spectra with reweightFsr = 0.95; 1.00; 1.05  
//mass value until which do reweighting
{

  // check whether it is a calculation
  if (input.Contains("_DebugRun_")) {
    std::cout << "plotDYUnfoldingMatrix: _DebugRun_ detected. Terminating the script\n";
    return;
  }

  // normal calculation

  gBenchmark->Start("plotDYUnfoldingMatrix");

  if (systematicsMode==DYTools::NORMAL)
    std::cout<<"Running script in the NORMAL mode"<<std::endl;
  else if (systematicsMode==DYTools::RESOLUTION_STUDY)
    std::cout<<"Running script in the RESOLUTION_STUDY mode"<<std::endl;
  else if (systematicsMode==DYTools::FSR_STUDY)
    std::cout<<"Running script in the FSR_STUDY mode"<<std::endl;
  else if (systematicsMode==DYTools::ESCALE_RESIDUAL) 
    std::cout << "Running script in the ESCALE_RESIDUAL mode\n";
  else { 
    std::cout<<"requested mode not recognized"<<std::endl;
    assert(0);
  }

  //--------------------------------------------------------------------------------------------------------------
  // Settings 
  //==============================================================================================================
  
  Bool_t doSave  = false;    // save plots?
  TString format = "png";   // output file format
  int saveMadePlots = 1;  // whether save produced canvases
  
  vector<TString> fnamev;   // file names   
  vector<TString> labelv;   // legend label
  vector<Int_t>   colorv;   // color in plots
  vector<Int_t>   linev;    // line style
  vector<Double_t> xsecv;
  vector<Double_t> lumiv;
  TString          dirTag;

  ifstream ifs;
  ifs.open(input.Data());
  if (!ifs.is_open()) std::cout << "failed to open a file <" << input.Data() << ">\n";
  assert(ifs.is_open());
  string line;
  Int_t state=0;
  const int inputFileMayContainEScaleDefinition = 1;
  int expectEscaleLine=1;
  ElectronEnergyScale escale((inputFileMayContainEScaleDefinition) ? 
	  ElectronEnergyScale::UNDEFINED : // read electron energy scale from the file
	  ElectronEnergyScale::Date20120101_default);
  while(getline(ifs,line)) {
    if(line[0]=='#') continue;
    if(state == 0){
      dirTag = TString(line);
      state++;
      continue;
    }else{
      if (inputFileMayContainEScaleDefinition && expectEscaleLine) {
	expectEscaleLine=0;
	// try to determine whether the input file was updated
	if (ElectronEnergyScale::DetermineCalibrationSet(line.c_str()) !=
	    ElectronEnergyScale::UNDEFINED) {
	  //std::cout << "got it ok: <" << line << ">" << std::endl;
	  escale.init(TString(line.c_str()));
	  if (!escale.isInitialized()) {
	    std::cout << "code error\n";
	    return;
	  }
	  // continue reading the file
	  getline(ifs,line);
	}
	else {
	  std::cout << "\n";
	  std::cout << "\n\tInput file does not contain electron energy scale. The expected file format:\n";
	  std::cout << "\tLine1: directory\n";
	  std::cout << "\tLine2: electron energy scale correction name (NEW from 2012 Jan 21)\n";
	  std::cout << "\tLine3: file_name.root xsect color linesty label\n";
	  std::cout << "using the default set\n\n";
	  escale.init("Date20120101_default");
	  if (!escale.isInitialized()) {
	    std::cout << "failed to correct the behavior\n";
	    return;
	  }
	}
	std::cout << "energy scale corrections: " << escale.calibrationSetName() << "\n";
      }
      string fname;
      Int_t color, linesty;
      stringstream ss(line);
      Double_t xsec;
      ss >> fname >> xsec >> color >> linesty;
      string label = line.substr(line.find('@')+1);
      fnamev.push_back(fname);
      labelv.push_back(label);
      colorv.push_back(color);
      linev.push_back(linesty);
      xsecv.push_back(xsec);
      lumiv.push_back(0);
    }
  }
  ifs.close();
  
  const Double_t kGAP_LOW  = 1.4442;
  const Double_t kGAP_HIGH = 1.566;


  //--------------------------------------------------------------------------------------------------------------
  // Main analysis code 
  //==============================================================================================================


  TRandom random;
  // The random seeds are needed only if we are running this script in systematics mode
  int seed = randomSeed;
  random.SetSeed(seed);
  gRandom->SetSeed(seed);
  // In the case of systematic studies, generate an array of random offsets
  TVectorD shift(escale._nEtaBins); // this vector is outdated by the new features in the escale obj.class
  shift = 0;
  if(systematicsMode==DYTools::RESOLUTION_STUDY) {
    escale.randomizeSmearingWidth(seed);
    for(int i=0; i<escale._nEtaBins; i++)
      shift[i] = gRandom->Gaus(0,1);
  }

  // prepare tools for ESCALE_RESIDUAL
  TH1F *shapeWeights=NULL;
  if (systematicsMode==DYTools::ESCALE_RESIDUAL) {
    TString shapeFName=TString("../root_files/yields/") + dirTag + TString("/shape_weights.root");
    std::cout << "Obtaining shape_weights.root from <" << shapeFName << ">\n";
    TFile fshape(shapeFName);
    if (!fshape.IsOpen()) {
      std::cout << "failed to open a file <" << shapeFName << ">\n";
      throw 2;
    }
    shapeWeights = (TH1F*)fshape.Get("weights");
    shapeWeights->SetDirectory(0);
    dirTag += TString("_escale_residual");
    std::cout << "changing dirTag to <" << dirTag << ">\n";
  }

  //  
  // Set up histograms
  //
  vector<TH1F*> hZMassv;//, hZMass2v, hZPtv, hZPt2v, hZyv, hZPhiv;  
  
  char hname[100];
  for(UInt_t ifile = 0; ifile<fnamev.size(); ifile++) {
    sprintf(hname,"hZMass_%i",ifile); hZMassv.push_back(new TH1F(hname,"",500,0,1500)); hZMassv[ifile]->Sumw2();
  }

  TH1F *hMassDiff   = new TH1F("hMassDiff","", 100, -30, 30);
  TH1F *hMassDiffBB = new TH1F("hMassDiffBB","", 100, -30, 30);
  TH1F *hMassDiffEB = new TH1F("hMassDiffEB","", 100, -30, 30);
  TH1F *hMassDiffEE = new TH1F("hMassDiffEE","", 100, -30, 30);

  TH1F *hMassDiffV[DYTools::nMassBins];
  for(int i=0; i<DYTools::nMassBins; i++){
    sprintf(hname,"hMassDiffV_%d",i);
    hMassDiffV[i] = new TH1F(hname,"",100,-50,50);
  }

  // MC spectra for storage in ROOT file
  // The FSR of RECO means that this is the spectrum of generator-level
  // post-FSR mass for events that were actually reconstructed (i.e. includes
  // efficiency and acceptances losses)
  TVectorD yieldsMcFsrOfRec    (DYTools::nMassBins);
  TVectorD yieldsMcFsrOfRecErr (DYTools::nMassBins);
  TVectorD yieldsMcRec         (DYTools::nMassBins);
  TVectorD yieldsMcRecErr      (DYTools::nMassBins);
  yieldsMcFsrOfRec     = 0;
  yieldsMcFsrOfRecErr  = 0;
  yieldsMcRec          = 0;
  yieldsMcRecErr       = 0;
  // The yields at generator level with mass bins defined by post-FSR di-leptons
  TVectorD yieldsMcFsr    (DYTools::nMassBins);
  yieldsMcFsr          = 0;

  // Vectors for bin to bin corrections
  TVectorD DetCorrFactorNumerator  (DYTools::nMassBins);
  TVectorD DetCorrFactorDenominator(DYTools::nMassBins);
  TVectorD DetCorrFactor           (DYTools::nMassBins);
  TVectorD DetCorrFactorErrPos     (DYTools::nMassBins);
  TVectorD DetCorrFactorErrNeg     (DYTools::nMassBins);
  DetCorrFactorNumerator   = 0;
  DetCorrFactorDenominator = 0;
  DetCorrFactor            = 0;
  DetCorrFactorErrPos      = 0;
  DetCorrFactorErrNeg      = 0;
  
  // Matrices for unfolding
  TMatrixD DetMigration(DYTools::nMassBins, DYTools::nMassBins);
  TMatrixD DetResponse(DYTools::nMassBins, DYTools::nMassBins);
  TMatrixD DetResponseErrPos(DYTools::nMassBins, DYTools::nMassBins);
  TMatrixD DetResponseErrNeg(DYTools::nMassBins, DYTools::nMassBins);
  for(int i=0; i<DYTools::nMassBins; i++){
    for(int j=0; j<DYTools::nMassBins; j++){
      DetMigration(i,j) = 0;
      DetResponse(i,j) = 0;
      DetResponseErrPos(i,j) = 0;
      DetResponseErrNeg(i,j) = 0;
    }
  }

  //
  // Access samples and fill histograms
  //  
  TFile *infile=0;
  TTree *eventTree=0;  
    
  // Data structures to store info from TTrees
  mithep::TEventInfo    *info = new mithep::TEventInfo();
  mithep::TGenInfo *gen  = new mithep::TGenInfo();
  TClonesArray *dielectronArr = new TClonesArray("mithep::TDielectron");
  
  // loop over samples  
  for(UInt_t ifile=0; ifile<fnamev.size(); ifile++) {
  
    // Read input file
    cout << "Processing " << fnamev[ifile] << "..." << endl;
    infile = new TFile(fnamev[ifile]); 
    assert(infile);

    // Get the TTrees
    eventTree = (TTree*)infile->Get("Events"); assert(eventTree);

    // Find weight for events for this file
    // The first file in the list comes with weight 1,
    // all subsequent ones are normalized to xsection and luminosity
    double xsec=xsecv[ifile];
    AdjustXSectionForSkim(infile,xsec,eventTree->GetEntries(),1);
    lumiv[ifile] = eventTree->GetEntries()/xsec;
    double scale = lumiv[0]/lumiv[ifile];
    cout << "       -> sample weight is " << scale << endl;

    // Set branch address to structures that will store the info  
    eventTree->SetBranchAddress("Info",&info);                TBranch *infoBr       = eventTree->GetBranch("Info");
    eventTree->SetBranchAddress("Gen",&gen);                  TBranch *genBr = eventTree->GetBranch("Gen");
    eventTree->SetBranchAddress("Dielectron",&dielectronArr); TBranch *dielectronBr = eventTree->GetBranch("Dielectron");
  
    // loop over events    
    for(UInt_t ientry=0; ientry<eventTree->GetEntries(); ientry++) {
      //if (ientry>100000) break;

      genBr->GetEntry(ientry);
      infoBr->GetEntry(ientry);

      double reweight;
      if (systematicsMode!=DYTools::FSR_STUDY) reweight=1.0;
      else if (((gen->mass)-(gen->vmass))>massLimit) reweight=1.0;
      else reweight=reweightFsr;

      if (ientry<20) std::cout<<"reweight="<<reweight<<std::endl;


      // Use post-FSR generator level mass in unfolding
      int ibinFsr = DYTools::findMassBin(gen->mass);
      if(ibinFsr != -1 && ibinFsr < yieldsMcFsr.GetNoElements()){
         yieldsMcFsr[ibinFsr] += reweight * scale * gen->weight;
      }


      /*
      // For EPS2011 for both data and MC (starting from Summer11 production)
      // we use an OR of the twi triggers below. Both are unpresecaled.
      ULong_t eventTriggerBit = kHLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL 
	| kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL;
      ULong_t leadingTriggerObjectBit = kHLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_Ele1Obj
	| kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele1Obj;
      ULong_t trailingTriggerObjectBit = kHLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_Ele2Obj
	| kHLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele2Obj;
      */

      const bool isData=kFALSE;
      TriggerConstantSet constantsSet = Full2011DatasetTriggers; // Enum from TriggerSelection.hh
      TriggerSelection requiredTriggers(constantsSet, isData, info->runNum);
      ULong_t eventTriggerBit = requiredTriggers.getEventTriggerBit(info->runNum);
      ULong_t leadingTriggerObjectBit = requiredTriggers.getLeadingTriggerObjectBit(info->runNum);
      ULong_t trailingTriggerObjectBit = requiredTriggers.getTrailingTriggerObjectBit(info->runNum);

      
      if(!(info->triggerBits & eventTriggerBit)) continue;  // no trigger accept? Skip to next event...                                   

      // loop through dielectrons
      dielectronArr->Clear();
      dielectronBr->GetEntry(ientry);    
      for(Int_t i=0; i<dielectronArr->GetEntriesFast(); i++) {

        const mithep::TDielectron *dielectron = (mithep::TDielectron*)((*dielectronArr)[i]);
	
	// Apply selection
	// Eta cuts
        if((fabs(dielectron->scEta_1)>kGAP_LOW) && (fabs(dielectron->scEta_1)<kGAP_HIGH)) continue;
        if((fabs(dielectron->scEta_2)>kGAP_LOW) && (fabs(dielectron->scEta_2)<kGAP_HIGH)) continue;
	if((fabs(dielectron->scEta_1) > 2.5)       || (fabs(dielectron->scEta_2) > 2.5))       continue;  // outside eta range? Skip to next event...
	
	// Asymmetric SC Et cuts
	if( ! ( ( dielectron->scEt_1 > DYTools::etMinLead  && dielectron->scEt_2 > DYTools::etMinTrail)
		|| ( dielectron->scEt_1 > DYTools::etMinTrail  && dielectron->scEt_2 > DYTools::etMinLead) )) continue;
    	
	// Both electrons must match trigger objects. At least one ordering
	// must match
	if( ! ( 
	       (dielectron->hltMatchBits_1 & leadingTriggerObjectBit && 
		dielectron->hltMatchBits_2 & trailingTriggerObjectBit )
	       ||
	       (dielectron->hltMatchBits_1 & trailingTriggerObjectBit && 
		dielectron->hltMatchBits_2 & leadingTriggerObjectBit ) ) ) continue;
	
	// The Smurf electron ID package is the same as used in HWW analysis
	// and contains cuts like VBTF WP80 for pt>20, VBTF WP70 for pt<10
	// with some customization, plus impact parameter cuts dz and dxy
	if(!passSmurf(dielectron)) continue;  

        // We have a Z candidate! HURRAY! 

	// Apply extra smearing to MC reconstructed dielectron mass
	// to better resemble the data
	/*
	  outdated lines. kept for reference
	double smear1 = escale.extraSmearingSigma(dielectron->scEta_1);
        double smear2 = escale::extraSmearingSigma(dielectron->scEta_2);
	// In systematics mode, overwrite the smear values with
	// shifted ones.
	if(systematicsMode==DYTools::RESOLUTION_STUDY){
	  smear1 = escale::extraSmearingSigmaShifted(dielectron->scEta_1,shift);
	  smear2 = escale::extraSmearingSigmaShifted(dielectron->scEta_2,shift);
	}
        double smearTotal = sqrt(smear1*smear1 + smear2*smear2);
        double massResmeared = dielectron->mass + random.Gaus(0.0,smearTotal);
	*/
	/* lines based on new features -- begin */
	double massSmear = (systematicsMode == DYTools::RESOLUTION_STUDY) ?
	  escale.generateMCSmearRandomized(dielectron->scEta_1,dielectron->scEta_2) :
	  escale.generateMCSmear(dielectron->scEta_1,dielectron->scEta_2);
        double massResmeared = dielectron->mass + massSmear;
	/* lines based on new features -- end */

	hZMassv[ifile]->Fill(massResmeared,scale * gen->weight);

	// Fill structures for response matrix and bin by bin corrections

	if(ibinFsr != -1 && ibinFsr < yieldsMcFsrOfRec.GetNoElements()){
	    yieldsMcFsrOfRec[ibinFsr] += reweight * scale * gen->weight;
	    DetCorrFactorDenominator(ibinFsr) += reweight * scale * gen->weight;
          }

	else if(ibinFsr >= yieldsMcFsrOfRec.GetNoElements())
	  cout << "ERROR: binning problem" << endl;

	int ibinRec = DYTools::findMassBin(massResmeared);
	double shape_weight = (shapeWeights && (ibinRec!=-1)) ? 
	  shapeWeights->GetBinContent(ibinRec+1) : 1.0;
	if(ibinRec != -1 && ibinRec < yieldsMcRec.GetNoElements()){
	    yieldsMcRec[ibinRec] += reweight * scale * gen->weight;
	    DetCorrFactorNumerator(ibinRec) += reweight * scale * gen->weight * shape_weight;
          }

	else if(ibinRec >= yieldsMcRec.GetNoElements())
	  cout << "ERROR: binning problem" << endl;
	
	if( ibinRec != -1 && ibinRec < yieldsMcRec.GetNoElements() 
	    && ibinFsr != -1 && ibinFsr < yieldsMcRec.GetNoElements() ){
          DetMigration(ibinFsr,ibinRec) += reweight * scale * gen->weight * shape_weight;
	}
	
        Bool_t isB1 = (fabs(dielectron->scEta_1)<kGAP_LOW);
        Bool_t isB2 = (fabs(dielectron->scEta_2)<kGAP_LOW);         
	hMassDiff->Fill(massResmeared - gen->mass);
	if( isB1 && isB2 )
	  hMassDiffBB->Fill(massResmeared - gen->mass);
	if( (isB1 && !isB2) || (!isB1 && isB2) )
	  hMassDiffEB->Fill(massResmeared - gen->mass);
	if( !isB1 && !isB2 )
	  hMassDiffEE->Fill(massResmeared - gen->mass);
	
	if(ibinFsr != -1){
	  hMassDiffV[ibinFsr]->Fill(massResmeared - gen->mass);
	}
// 	if(ibinRec == -1)
// 	  printf("Missed bin:  M_fsr=%f   M_reco=%f\n", gen->mass, massResmeared);
	
      } // end loop over dielectrons

    } // end loop over events 
    delete infile;
    infile=0, eventTree=0;
  } // end loop over files
  delete gen;


  //finish reweighting of mass spectra

  
  // Find bin by bin corrections and the errors
  double tCentral, tErrNeg, tErrPos;
  for(int i=0; i<DYTools::nMassBins; i++){
    if ( DetCorrFactorDenominator(i) != 0 ){
      // This method does not take into account correlation between numerator
      // and denominator in calculation of errors. This is a flaw to be corrected
      // in the future.
      SimpleDivide( DetCorrFactorNumerator(i), DetCorrFactorDenominator(i), tCentral, tErrNeg, tErrPos);
      DetCorrFactor(i) = tCentral;
      DetCorrFactorErrPos(i) = tErrPos;
      DetCorrFactorErrNeg(i) = tErrNeg;
    } else {
      DetCorrFactor(i) = 0;
      DetCorrFactorErrPos(i) = 0;
      DetCorrFactorErrNeg(i) = 0;
    }
  }
  
  // Find response matrix, which is simply the normalized migration matrix
  for(int ifsr = 0; ifsr < DetMigration.GetNrows(); ifsr++){
    double nEventsInFsrMassBin = 0;
    for(int ireco = 0; ireco < DetMigration.GetNcols(); ireco++)
      nEventsInFsrMassBin += DetMigration(ifsr,ireco);
    // Now normalize each element and find errors
    for(int ireco = 0; ireco < DetMigration.GetNcols(); ireco++){
      tCentral = 0;
      tErrPos  = 0;
      tErrNeg  = 0;
      // Note: the event counts supposedly are dominated with events with weight "1"
      // coming from the primary MC sample, so the error is assumed Poissonian in
      // the call for efficiency-calculating function below.
      if( nEventsInFsrMassBin != 0 ){
	EfficiencyDivide(DetMigration(ifsr,ireco), nEventsInFsrMassBin, tCentral, tErrNeg, tErrPos);
      // BayesEfficiency does not seem to be working in newer ROOT versions, 
      // so it is replaced by simler method
//         BayesEfficiency( DetMigration(ifsr,ireco), nEventsInFsrMassBin, tCentral, tErrNeg, tErrPos);
      }
      DetResponse      (ifsr,ireco) = tCentral;
      DetResponseErrPos(ifsr,ireco) = tErrPos;
      DetResponseErrNeg(ifsr,ireco) = tErrNeg;
    }
  }

  // Find inverted response matrix
  TMatrixD DetInvertedResponse = DetResponse;
  Double_t det;
  DetInvertedResponse.Invert(&det);
  TMatrixD DetInvertedResponseErr(DetInvertedResponse.GetNrows(), DetInvertedResponse.GetNcols());
  calculateInvertedMatrixErrors(DetResponse, DetResponseErrPos, DetResponseErrNeg, DetInvertedResponseErr);

  // Package bin limits into TVectorD for storing in a file
  TVectorD BinLimitsArray(DYTools::nMassBins+1);
  for(int i=0; i<DYTools::nMassBins+1; i++)
    BinLimitsArray(i) = DYTools::massBinLimits[i];

  // Store constants in the file
  TString outputDir(TString("../root_files/constants/")+dirTag);
  if((systematicsMode==DYTools::RESOLUTION_STUDY) || (systematicsMode==DYTools::FSR_STUDY))
    outputDir = TString("../root_files/systematics/")+dirTag;
  gSystem->mkdir(outputDir,kTRUE);
  TString unfoldingConstFileName(outputDir+TString("/unfolding_constants.root"));
  if(systematicsMode==DYTools::RESOLUTION_STUDY){
    unfoldingConstFileName = outputDir+TString("/unfolding_constants_seed_");
    unfoldingConstFileName += seed;
    unfoldingConstFileName += ".root";
  }
  if(systematicsMode==DYTools::FSR_STUDY){
    unfoldingConstFileName = outputDir+TString("/unfolding_constants_reweight_");
    unfoldingConstFileName += int(100*reweightFsr);
    unfoldingConstFileName += ".root";
  }

  TFile fConst(unfoldingConstFileName, "recreate" );
  DetResponse             .Write("DetResponse");
  DetInvertedResponse     .Write("DetInvertedResponse");
  DetInvertedResponseErr  .Write("DetInvertedResponseErr");
  BinLimitsArray          .Write("BinLimitsArray");
  DetCorrFactor           .Write("DetCorrFactor");
  DetCorrFactorErrPos     .Write("DetCorrFactorErrPos");
  DetCorrFactorErrNeg     .Write("DetCorrFactorErrNeg");
  fConst.Close();
  
  // Store reference MC arrays in a file
  TString refFileName(outputDir+TString("/yields_MC_unfolding_reference.root"));
  TFile fRef(refFileName, "recreate" );
  BinLimitsArray    .Write("BinLimitsArray");
  yieldsMcFsr       .Write("yieldsMcFsr");
  yieldsMcFsrOfRec  .Write("yieldsMcFsrOfRec");
  yieldsMcRec       .Write("yieldsMcRec");
  fRef.Close();


  //--------------------------------------------------------------------------------------------------------------
  // Make plots 
  //==============================================================================================================  

  std::vector<TCanvas*> canvasV; // holder for a quick saver
  canvasV.reserve(10);

  TCanvas *c = MakeCanvas("zMass1","zMass1",800,600);
  canvasV.push_back(c);

  // string buffers
  char ylabel[50];   // y-axis label

  // Z mass
  sprintf(ylabel,"a.u. / %.1f GeV/c^{2}",hZMassv[0]->GetBinWidth(1));
  CPlot plotZMass1("zmass1","","m(ee) [GeV/c^{2}]",ylabel);
  if (fnamev.size()) hZMassv[0]->GetXaxis()->SetLimits(10.,2000.);
  for(UInt_t i=0; i<fnamev.size(); i++) { 
    plotZMass1.AddHist1D(hZMassv[i],labelv[i],"hist",colorv[i],linev[i]); 
  }
  plotZMass1.SetLogy();
  plotZMass1.SetLogx(); 
  plotZMass1.TransLegend(0.02, 0.0);
  plotZMass1.Draw(c,doSave,format);

  // Create plots of how reco mass looks and how unfolded mass should look like
  TVectorD massBinCentral     (DYTools::nMassBins);
  TVectorD massBinHalfWidth   (DYTools::nMassBins);
  TVectorD yieldMcFsrOfRecErr (DYTools::nMassBins);
  TVectorD yieldMcRecErr      (DYTools::nMassBins);
  for(int i=0; i < DYTools::nMassBins; i++){
    massBinCentral  (i) = (DYTools::massBinLimits[i+1] + DYTools::massBinLimits[i])/2.0;
    massBinHalfWidth(i) = (DYTools::massBinLimits[i+1] - DYTools::massBinLimits[i])/2.0;
    yieldsMcFsrOfRecErr(i) = sqrt(yieldsMcFsrOfRec[i]);
    yieldsMcRecErr     (i) = sqrt(yieldsMcRec[i]);
  }
  TGraphErrors *grFsrOfRec = new TGraphErrors(massBinCentral, yieldsMcFsrOfRec, 
					      massBinHalfWidth, yieldsMcFsrOfRecErr);
  TGraphErrors *grRec      = new TGraphErrors(massBinCentral, yieldsMcRec, 
					      massBinHalfWidth, yieldsMcRecErr);
  TCanvas *d = MakeCanvas("zMass2","zMass2",800,600);
  canvasV.push_back(d);
  CPlot plotZMass2("zmass2","","m(ee) [GeV/c^{2}]","events");
  plotZMass2.SetLogx(1);
  plotZMass2.AddGraph(grFsrOfRec,"no detector effects","PE",kBlack);
  plotZMass2.AddGraph(grRec,"reconstructed","PE",kBlue);
  plotZMass2.Draw(d);

//   double xsize = 600;
//   double ysize = 600;
  int xsize = 600;
  int ysize = 400;

  // Create the plot of the response matrix
  TH2F *hResponse = new TH2F("hResponse","",DYTools::nMassBins, DYTools::massBinLimits,
			     DYTools::nMassBins, DYTools::massBinLimits);
  for(int i=1; i<=DYTools::nMassBins; i++)
    for(int j=1; j<=DYTools::nMassBins; j++)
      hResponse->SetBinContent(i,j,DetResponse(i-1,j-1));
  TCanvas *e = MakeCanvas("response","response",xsize,ysize);
  canvasV.push_back(e);
  CPlot plotResponse("response","",
		     "generator post-FSR m(ee) [GeV/c^{2}]",
		     "reconstructed  m(ee) [GeV/c^{2}]");
  plotResponse.AddHist2D(hResponse,"COLZ");
  e->cd();
  plotResponse.SetLogx();
  plotResponse.SetLogy();
  gPad->SetRightMargin(0.15);
  gStyle->SetPalette(1);
  hResponse->GetXaxis()->SetMoreLogLabels();
  hResponse->GetXaxis()->SetNoExponent();
  hResponse->GetYaxis()->SetNoExponent();
  plotResponse.Draw(e);

  // Create the plot of the inverted response matrix
  TH2F *hInvResponse = new TH2F("hInvResponse","",DYTools::nMassBins, DYTools::massBinLimits,
			     DYTools::nMassBins, DYTools::massBinLimits);
  for(int i=1; i<=DYTools::nMassBins; i++)
    for(int j=1; j<=DYTools::nMassBins; j++)
      hInvResponse->SetBinContent(i,j,DetInvertedResponse(i-1,j-1));
  TCanvas *f = MakeCanvas("invResponse","invResponse",xsize,ysize);
  canvasV.push_back(f);
  CPlot plotInvResponse("inverted response","",
			"reconstructed  m(ee) [GeV/c^{2}]",
			"generator post-FSR m(ee) [GeV/c^{2}]");
  plotInvResponse.AddHist2D(hInvResponse,"COLZ");
  f->cd();
  plotInvResponse.SetLogx();
  plotInvResponse.SetLogy();
  gPad->SetRightMargin(0.15);
  gStyle->SetPalette(1);
  hInvResponse->GetXaxis()->SetMoreLogLabels();
  hInvResponse->GetXaxis()->SetNoExponent();
  hInvResponse->GetYaxis()->SetNoExponent();
  plotInvResponse.Draw(f);

  // Create a plot of detector resolution without mass binning
  TCanvas *g = MakeCanvas("massDiff","massDiff",600,600);
  canvasV.push_back(g);
  CPlot plotMassDiff("massDiff","","reco mass - gen post-FSR mass [GeV/c^{2}]","a.u.");
  hMassDiffBB->Scale(1.0/hMassDiffBB->GetSumOfWeights());
  hMassDiffEB->Scale(1.0/hMassDiffEB->GetSumOfWeights());
  hMassDiffEE->Scale(1.0/hMassDiffEE->GetSumOfWeights());
  plotMassDiff.AddHist1D(hMassDiffBB,"EB-EB","hist",kBlack);
  plotMassDiff.AddHist1D(hMassDiffEB,"EE-EB","hist",kBlue);
  plotMassDiff.AddHist1D(hMassDiffEE,"EE-EE","hist",kRed);
  plotMassDiff.TransLegend(0.1, 0.0);
  plotMassDiff.Draw(g);



  // Create a plot of reco - gen post-FSR mass difference for several mass bins
  TCanvas *h = MakeCanvas("massDiffV","massDiffV",600,600);
  canvasV.push_back(h);
  CPlot plotMassDiffV("massDiffV","","reco mass - gen post-FSR mass [GeV/c^{2}]","a.u.");
  hMassDiffV[7]->Scale(1.0/hMassDiffV[7]->GetSumOfWeights());
  hMassDiffV[6]->Scale(1.0/hMassDiffV[6]->GetSumOfWeights());
  hMassDiffV[5]->Scale(1.0/hMassDiffV[5]->GetSumOfWeights());
  hMassDiffV[4]->Scale(1.0/hMassDiffV[4]->GetSumOfWeights());
  plotMassDiffV.AddHist1D(hMassDiffV[4],"50-60 GeV/c^{2}","hist",kBlack);
  plotMassDiffV.AddHist1D(hMassDiffV[5],"60-76 GeV/c^{2}","hist",kBlue);
  plotMassDiffV.AddHist1D(hMassDiffV[6],"76-86 GeV/c^{2}","hist",kRed);
  plotMassDiffV.AddHist1D(hMassDiffV[7],"86-96 GeV/c^{2}","hist",kMagenta);
  plotMassDiffV.SetXRange(-20,50);
  plotMassDiffV.Draw(h);

  // Create graph of bin-to-bin corrections
  TGraphAsymmErrors *grCorrFactor 
    = new TGraphAsymmErrors(massBinCentral, DetCorrFactor,
			    massBinHalfWidth, massBinHalfWidth,
			    DetCorrFactorErrNeg, DetCorrFactorErrPos);
  TCanvas *c11 = MakeCanvas("corrFactor","corrFactor",800,600);
  canvasV.push_back(c11);
  CPlot plotCorrFactor("corrFactor","","m(ee) [GeV/c^{2}]","correction factor");
  plotCorrFactor.AddGraph(grCorrFactor,"PE",kBlue);
  plotCorrFactor.SetLogx();
  plotCorrFactor.SetYRange(0,2.0);
  plotCorrFactor.Draw(c11);

  if (saveMadePlots) {
    TString plotPath=TString("../root_files/plots/") + dirTag; 
    TString name=plotPath + TString("/unfolding_plots.root");
    gSystem->mkdir(plotPath,true);
    TFile* fplots = TFile::Open(name,"RECREATE");
    for (unsigned int i=0; i<canvasV.size(); ++i) {
      canvasV[i]->Write();
    }
    fplots->Close();
  }

  //--------------------------------------------------------------------------------------------------------------
  // Summary print out
  //==============================================================================================================
  cout << endl;
  cout << "*" << endl;
  cout << "* SUMMARY" << endl;
  cout << "*--------------------------------------------------" << endl;
  cout << endl; 
  
  // Printout of all constants, uncomment if needed

  //printf("DetMigration:\n"); DetMigration.Print();
  //printf("DetResponse:\n"); DetResponse.Print();
  //printf("DetInvertedResponse:\n"); DetInvertedResponse.Print();

//   DetCorrFactor.Print();
//   DetResponse.Print();
  
//   printf("Detector corr factor numerator:\n");
//   DetCorrFactorNumerator.Print();
//   printf("yieldsMcRec:\n");
//   yieldsMcRec.Print();

//   printf("Detector corr factor denominator:\n");
//   DetCorrFactorDenominator.Print();
//   printf("yieldsMcFsrOfRec:\n");
//   yieldsMcFsrOfRec.Print();

  gBenchmark->Show("plotDYUnfoldingMatrix");
}