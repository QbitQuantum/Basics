void OneSidedFrequentistUpperLimitWithBands_intermediate(const char* infile = "",
					    const char* workspaceName = "combined",
					    const char* modelConfigName = "ModelConfig",
					    const char* dataName = "obsData"){


  double confidenceLevel=0.95;
  // degrade/improve number of pseudo-experiments used to define the confidence belt.  
  // value of 1 corresponds to default number of toys in the tail, which is 50/(1-confidenceLevel)
  double additionalToysFac = 1.;  
  int nPointsToScan = 30; // number of steps in the parameter of interest 
  int nToyMC = 100; // number of toys used to define the expected limit and band

  TStopwatch t;
  t.Start();
  /////////////////////////////////////////////////////////////
  // First part is just to access a user-defined file 
  // or create the standard example file if it doesn't exist
  ////////////////////////////////////////////////////////////
  const char* filename = "";
  if (!strcmp(infile,""))
    filename = "results/example_combined_GaussExample_model.root";
  else
    filename = infile;
  // Check if example input file exists
  TFile *file = TFile::Open(filename);

  // if input file was specified byt not found, quit
  if(!file && strcmp(infile,"")){
    cout <<"file not found" << endl;
    return;
  } 

  // if default file not found, try to create it
  if(!file ){
    // Normally this would be run on the command line
    cout <<"will run standard hist2workspace example"<<endl;
    gROOT->ProcessLine(".! prepareHistFactory .");
    gROOT->ProcessLine(".! hist2workspace config/example.xml");
    cout <<"\n\n---------------------"<<endl;
    cout <<"Done creating example input"<<endl;
    cout <<"---------------------\n\n"<<endl;
  }

  // now try to access the file again
  file = TFile::Open(filename);
  if(!file){
    // if it is still not there, then we can't continue
    cout << "Not able to run hist2workspace to create example input" <<endl;
    return;
  }

  
  /////////////////////////////////////////////////////////////
  // Now get the data and workspace
  ////////////////////////////////////////////////////////////

  // get the workspace out of the file
  RooWorkspace* w = (RooWorkspace*) file->Get(workspaceName);
  if(!w){
    cout <<"workspace not found" << endl;
    return;
  }

  // get the modelConfig out of the file
  ModelConfig* mc = (ModelConfig*) w->obj(modelConfigName);

  // get the modelConfig out of the file
  RooAbsData* data = w->data(dataName);

  // make sure ingredients are found
  if(!data || !mc){
    w->Print();
    cout << "data or ModelConfig was not found" <<endl;
    return;
  }

  cout << "Found data and ModelConfig:" <<endl;
  mc->Print();

  /////////////////////////////////////////////////////////////
  // Now get the POI for convenience
  // you may want to adjust the range of your POI
  ////////////////////////////////////////////////////////////
  RooRealVar* firstPOI = (RooRealVar*) mc->GetParametersOfInterest()->first();
  //  firstPOI->setMin(0);
  //  firstPOI->setMax(10);

  /////////////////////////////////////////////
  // create and use the FeldmanCousins tool
  // to find and plot the 95% confidence interval
  // on the parameter of interest as specified
  // in the model config
  // REMEMBER, we will change the test statistic
  // so this is NOT a Feldman-Cousins interval
  FeldmanCousins fc(*data,*mc);
  fc.SetConfidenceLevel(confidenceLevel); 
  fc.AdditionalNToysFactor(additionalToysFac); // improve sampling that defines confidence belt
  //  fc.UseAdaptiveSampling(true); // speed it up a bit, but don't use for expectd limits
  fc.SetNBins(nPointsToScan); // set how many points per parameter of interest to scan
  fc.CreateConfBelt(true); // save the information in the belt for plotting

  /////////////////////////////////////////////
  // Feldman-Cousins is a unified limit by definition
  // but the tool takes care of a few things for us like which values
  // of the nuisance parameters should be used to generate toys.
  // so let's just change the test statistic and realize this is 
  // no longer "Feldman-Cousins" but is a fully frequentist Neyman-Construction.
  //  ProfileLikelihoodTestStatModified onesided(*mc->GetPdf());
  //  fc.GetTestStatSampler()->SetTestStatistic(&onesided);
  // ((ToyMCSampler*) fc.GetTestStatSampler())->SetGenerateBinned(true);
  ToyMCSampler*  toymcsampler = (ToyMCSampler*) fc.GetTestStatSampler(); 
  ProfileLikelihoodTestStat* testStat = dynamic_cast<ProfileLikelihoodTestStat*>(toymcsampler->GetTestStatistic());
  testStat->SetOneSided(true);


  // test speedups:
  testStat->SetReuseNLL(true);
  //  toymcsampler->setUseMultiGen(true); // not fully validated

  // Since this tool needs to throw toy MC the PDF needs to be
  // extended or the tool needs to know how many entries in a dataset
  // per pseudo experiment.  
  // In the 'number counting form' where the entries in the dataset
  // are counts, and not values of discriminating variables, the
  // datasets typically only have one entry and the PDF is not
  // extended.  
  if(!mc->GetPdf()->canBeExtended()){
    if(data->numEntries()==1)     
      fc.FluctuateNumDataEntries(false);
    else
      cout <<"Not sure what to do about this model" <<endl;
  }

  // We can use PROOF to speed things along in parallel
  ProofConfig pc(*w, 4, "",false); 
  if(mc->GetGlobalObservables()){
    cout << "will use global observables for unconditional ensemble"<<endl;
    mc->GetGlobalObservables()->Print();
    toymcsampler->SetGlobalObservables(*mc->GetGlobalObservables());
  }
  toymcsampler->SetProofConfig(&pc);	// enable proof


  // Now get the interval
  PointSetInterval* interval = fc.GetInterval();
  ConfidenceBelt* belt = fc.GetConfidenceBelt();
 
  // print out the iterval on the first Parameter of Interest
  cout << "\n95% interval on " <<firstPOI->GetName()<<" is : ["<<
    interval->LowerLimit(*firstPOI) << ", "<<
    interval->UpperLimit(*firstPOI) <<"] "<<endl;

  // get observed UL and value of test statistic evaluated there
  RooArgSet tmpPOI(*firstPOI);
  double observedUL = interval->UpperLimit(*firstPOI);
  firstPOI->setVal(observedUL);
  double obsTSatObsUL = fc.GetTestStatSampler()->EvaluateTestStatistic(*data,tmpPOI);


  // Ask the calculator which points were scanned
  RooDataSet* parameterScan = (RooDataSet*) fc.GetPointsToScan();
  RooArgSet* tmpPoint;

  // make a histogram of parameter vs. threshold
  TH1F* histOfThresholds = new TH1F("histOfThresholds","",
				    parameterScan->numEntries(),
				    firstPOI->getMin(),
				    firstPOI->getMax());
  histOfThresholds->GetXaxis()->SetTitle(firstPOI->GetName());
  histOfThresholds->GetYaxis()->SetTitle("Threshold");

  // loop through the points that were tested and ask confidence belt
  // what the upper/lower thresholds were.
  // For FeldmanCousins, the lower cut off is always 0
  for(Int_t i=0; i<parameterScan->numEntries(); ++i){
    tmpPoint = (RooArgSet*) parameterScan->get(i)->clone("temp");
    double arMax = belt->GetAcceptanceRegionMax(*tmpPoint);
    double poiVal = tmpPoint->getRealValue(firstPOI->GetName()) ;
    histOfThresholds->Fill(poiVal,arMax);
  }
  TCanvas* c1 = new TCanvas();
  c1->Divide(2);
  c1->cd(1);
  histOfThresholds->SetMinimum(0);
  histOfThresholds->Draw();
  c1->cd(2);

  /////////////////////////////////////////////////////////////
  // Now we generate the expected bands and power-constriant
  ////////////////////////////////////////////////////////////

  // First: find parameter point for mu=0, with conditional MLEs for nuisance parameters
  RooAbsReal* nll = mc->GetPdf()->createNLL(*data);
  RooAbsReal* profile = nll->createProfile(*mc->GetParametersOfInterest());
  firstPOI->setVal(0.);
  profile->getVal(); // this will do fit and set nuisance parameters to profiled values
  RooArgSet* poiAndNuisance = new RooArgSet();
  if(mc->GetNuisanceParameters())
    poiAndNuisance->add(*mc->GetNuisanceParameters());
  poiAndNuisance->add(*mc->GetParametersOfInterest());
  w->saveSnapshot("paramsToGenerateData",*poiAndNuisance);
  RooArgSet* paramsToGenerateData = (RooArgSet*) poiAndNuisance->snapshot();
  cout << "\nWill use these parameter points to generate pseudo data for bkg only" << endl;
  paramsToGenerateData->Print("v");


  double CLb=0;
  double CLbinclusive=0;

  // Now we generate background only and find distribution of upper limits
  TH1F* histOfUL = new TH1F("histOfUL","",100,0,firstPOI->getMax());
  histOfUL->GetXaxis()->SetTitle("Upper Limit (background only)");
  histOfUL->GetYaxis()->SetTitle("Entries");
  for(int imc=0; imc<nToyMC; ++imc){

    // set parameters back to values for generating pseudo data
    w->loadSnapshot("paramsToGenerateData");

    // in 5.30 there is a nicer way to generate toy data  & randomize global obs
    RooAbsData* toyData = toymcsampler->GenerateToyData(*paramsToGenerateData);

    // get test stat at observed UL in observed data
    firstPOI->setVal(observedUL);
    double toyTSatObsUL = fc.GetTestStatSampler()->EvaluateTestStatistic(*toyData,tmpPOI);
    //    toyData->get()->Print("v");
    //    cout <<"obsTSatObsUL " <<obsTSatObsUL << "toyTS " << toyTSatObsUL << endl;
    if(obsTSatObsUL < toyTSatObsUL) // (should be checked)
      CLb+= (1.)/nToyMC;
    if(obsTSatObsUL <= toyTSatObsUL) // (should be checked)
      CLbinclusive+= (1.)/nToyMC;


    // loop over points in belt to find upper limit for this toy data
    double thisUL = 0;
    for(Int_t i=0; i<parameterScan->numEntries(); ++i){
      tmpPoint = (RooArgSet*) parameterScan->get(i)->clone("temp");
      double arMax = belt->GetAcceptanceRegionMax(*tmpPoint);
      firstPOI->setVal( tmpPoint->getRealValue(firstPOI->GetName()) );
      double thisTS = fc.GetTestStatSampler()->EvaluateTestStatistic(*toyData,tmpPOI);

      if(thisTS<=arMax){
	thisUL = firstPOI->getVal();
      } else{
	break;
      }
    }
    

    histOfUL->Fill(thisUL);

    
    delete toyData;
  }
  histOfUL->Draw();
  c1->SaveAs("one-sided_upper_limit_output.pdf");

  // if you want to see a plot of the sampling distribution for a particular scan point:

  // Now find bands and power constraint
  Double_t* bins = histOfUL->GetIntegral();
  TH1F* cumulative = (TH1F*) histOfUL->Clone("cumulative");
  cumulative->SetContent(bins);
  double band2sigDown=0, band1sigDown=0, bandMedian=0, band1sigUp=0,band2sigUp=0;
  for(int i=1; i<=cumulative->GetNbinsX(); ++i){
    if(bins[i]<RooStats::SignificanceToPValue(2))
      band2sigDown=cumulative->GetBinCenter(i);
    if(bins[i]<RooStats::SignificanceToPValue(1))
      band1sigDown=cumulative->GetBinCenter(i);
    if(bins[i]<0.5)
      bandMedian=cumulative->GetBinCenter(i);
    if(bins[i]<RooStats::SignificanceToPValue(-1))
      band1sigUp=cumulative->GetBinCenter(i);
    if(bins[i]<RooStats::SignificanceToPValue(-2))
      band2sigUp=cumulative->GetBinCenter(i);
  }

  t.Stop();
  t.Print();

  cout << "-2 sigma  band " << band2sigDown << endl;
  cout << "-1 sigma  band " << band1sigDown  << endl;
  cout << "median of band " << bandMedian << " [Power Constriant)]" << endl;
  cout << "+1 sigma  band " << band1sigUp << endl;
  cout << "+2 sigma  band " << band2sigUp << endl;

  // print out the iterval on the first Parameter of Interest
  cout << "\nobserved 95% upper-limit "<< interval->UpperLimit(*firstPOI) <<endl;
  cout << "CLb strict [P(toy>obs|0)] for observed 95% upper-limit "<< CLb <<endl;
  cout << "CLb inclusive [P(toy>=obs|0)] for observed 95% upper-limit "<< CLbinclusive <<endl;

  delete profile;
  delete nll;

}