void TMVAClassification( TString myMethodList = "" ) 
{
  // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
  // if you use your private .rootrc, or run from a different directory, please copy the 
  // corresponding lines from .rootrc

  // methods to be processed can be given as an argument; use format:
  //
  // mylinux~> root -l TMVAClassification.C\(\"myMethod1,myMethod2,myMethod3\"\)
  //
  // if you like to use a method via the plugin mechanism, we recommend using
  // 
  // mylinux~> root -l TMVAClassification.C\(\"P_myMethod\"\)
  // (an example is given for using the BDT as plugin (see below),
  // but of course the real application is when you write your own
  // method based)

  // this loads the library
  TMVA::Tools::Instance();

  //---------------------------------------------------------------
  // default MVA methods to be trained + tested
  std::map<std::string,int> Use;

  Use["Cuts"]            = 1;
  Use["CutsD"]           = 1;
  Use["CutsPCA"]         = 1;
  Use["CutsGA"]          = 1;
  Use["CutsSA"]          = 1;
  // ---
  Use["Likelihood"]      = 1;
  Use["LikelihoodD"]     = 1; // the "D" extension indicates decorrelated input variables (see option strings)
  Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
  Use["LikelihoodKDE"]   = 1;
  Use["LikelihoodMIX"]   = 1;
  // ---
  Use["PDERS"]           = 1;
  Use["PDERSD"]          = 1;
  Use["PDERSPCA"]        = 1;
  Use["PDERSkNN"]        = 1; // depreciated until further notice
  Use["PDEFoam"]         = 1;
  // --
  Use["KNN"]             = 1;
  // ---
  Use["HMatrix"]         = 1;
  Use["Fisher"]          = 1;
  Use["FisherG"]         = 1;
  Use["BoostedFisher"]   = 1;
  Use["LD"]              = 1;
  // ---
  Use["FDA_GA"]          = 1;
  Use["FDA_SA"]          = 1;
  Use["FDA_MC"]          = 1;
  Use["FDA_MT"]          = 1;
  Use["FDA_GAMT"]        = 1;
  Use["FDA_MCMT"]        = 1;
  // ---
  Use["MLP"]             = 1; // this is the recommended ANN
  Use["MLPBFGS"]         = 1; // recommended ANN with optional training method
  Use["CFMlpANN"]        = 1; // *** missing
  Use["TMlpANN"]         = 1; 
  // ---
  Use["SVM"]             = 1;
  // ---
  Use["BDT"]             = 1;
  Use["BDTD"]            = 0;
  Use["BDTG"]            = 1;
  Use["BDTB"]            = 0;
  // ---
  Use["RuleFit"]         = 1;
  // ---
  Use["Plugin"]          = 0;
  // ---------------------------------------------------------------

  std::cout << std::endl;
  std::cout << "==> Start TMVAClassification" << std::endl;

  if (myMethodList != "") {
    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

    std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
    for (UInt_t i=0; i<mlist.size(); i++) {
      std::string regMethod(mlist[i]);

      if (Use.find(regMethod) == Use.end()) {
        std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
        for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
        std::cout << std::endl;
        return;
      }
      Use[regMethod] = 1;
    }
  }

  // Create a new root output file.
  TString outfileName = "TMVA";
  int toAppNum = 1;
  char name[1024];

  TSystemDirectory dir("",".");
  TList *files = dir.GetListOfFiles();
  vector<string> vfname;
  if (files) {
     TIter next(files);
     TSystemFile *file;
     TString fname;
     
     while ((file=(TSystemFile*)next())) {
        fname = file->GetName();
        if (!file->IsDirectory() && fname.EndsWith(".root") && fname.BeginsWith("TMVA")) {
           vfname.push_back(string(fname));
        }
      }
     delete files;
     if (vfname.size()>0) {
        std::sort(vfname.begin(),vfname.end());
        TString num = TString(vfname[vfname.size()-1]);
        num.ReplaceAll(".root","");
        num.ReplaceAll("TMVA","");
        toAppNum = num.Atoi()+1;
     }
  }
  sprintf(name,"%d",toAppNum);
  outfileName = outfileName + name + ".root";
  //TString outfileName( "TMVA.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

  // Create the factory object. Later you can choose the methods
  // whose performance you'd like to investigate. The factory will
  // then run the performance analysis for you.
  //
  // The first argument is the base of the name of all the
  // weightfiles in the directory weight/ 
  //
  // The second argument is the output file for the training results
  // All TMVA output can be suppressed by removing the "!" (not) in 
  // front of the "Silent" argument in the option string
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, 
                                              "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D" );

  // If you wish to modify default settings 
  // (please check "src/Config.h" to see all available global options)
  //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
  //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";


  // Define the input variables that shall be used for the MVA training
  factory->AddVariable("tEventProbSig := tEventProb[0]+tEventProb[1]+tEventProb[2]","F",0,0);
  factory->AddVariable("tEventProbBkg := tEventProb","F",0,0);
  
  // You can add so-called "Spectator variables", which are not used in the MVA training, 
  // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the 
  // input variables, the response values of all trained MVAs, and the spectator variables
  factory->AddSpectator("run := m_run", "I");
  factory->AddSpectator("event := m_event", "I");


  // read training and test data
  TFile *input1 = TFile::Open( "/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microWW_EPDv01.root" );
  TFile *input2 = TFile::Open( "/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microWZ_EPDv01.root" );
  TFile *input3 = TFile::Open( "/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microWJets_EPDv01.root" );
  TFile *input4 = TFile::Open( "/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microZJets_EPDv01.root" );
  TFile *input5 = TFile::Open( "/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microTTbar_EPDv01.root" );
  TFile *input6 = TFile::Open( "/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microHWWMH150_EPDv01.root" );

 
  std::cout << "--- TMVAClassification : Using input file: " << input1->GetName() << std::endl;
  std::cout << "--- TMVAClassification : Using input file: " << input2->GetName() << std::endl;
  std::cout << "--- TMVAClassification : Using input file: " << input3->GetName() << std::endl;
  std::cout << "--- TMVAClassification : Using input file: " << input4->GetName() << std::endl;
  std::cout << "--- TMVAClassification : Using input file: " << input5->GetName() << std::endl;
  std::cout << "--- TMVAClassification : Using input file: " << input6->GetName() << std::endl;
   
  //TTree *signal     = (TTree*)input1->Get("WJet");
  //TTree *background = (TTree*)input3->Get("WJet");
  TChain *signal = new TChain("METree");
  signal->Add("/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microHWWMH150_EPDv01.root");
  TChain *background = new TChain("METree"); 
  background->Add("/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microWW_EPDv01.root");
  background->Add("/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microWZ_EPDv01.root");
  background->Add("/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microWJets_EPDv01.root");
  background->Add("/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microZJets_EPDv01.root");
  background->Add("/uscms/home/ilyao/nobackup/Spring12ME7TeV/MEResults/microNtuples/microTTbar_EPDv01.root");

  // global event weights per tree (see below for setting event-wise weights)
  Double_t signalWeight     = 1.0;
  Double_t backgroundWeight = 1.0;

  // ====== register trees ====================================================
  //
  // the following method is the prefered one:
  // you can add an arbitrary number of signal or background trees
  factory->AddSignalTree    ( signal,     signalWeight     );
  factory->AddBackgroundTree( background, backgroundWeight );

  // To give different trees for training and testing, do as follows:
  //    factory->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
  //    factory->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );

  // Use the following code instead of the above two or four lines to add signal and background 
  // training and test events "by hand"
  // NOTE that in this case one should not give expressions (such as "var1+var2") in the input 
  //      variable definition, but simply compute the expression before adding the event
  // 
  //    // --- begin ----------------------------------------------------------
  //    std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
  //    Float_t  treevars[4];
  //    for (Int_t ivar=0; ivar<4; ivar++) signal->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
  //    for (Int_t i=0; i<signal->GetEntries(); i++) {
  //       signal->GetEntry(i);
  //       for (Int_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
  //       // add training and test events; here: first half is training, second is testing
  //       // note that the weight can also be event-wise	
  //       if (i < signal->GetEntries()/2) factory->AddSignalTrainingEvent( vars, signalWeight ); 
  //       else                            factory->AddSignalTestEvent    ( vars, signalWeight ); 
  //    }
  //
  //    for (Int_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
  //    for (Int_t i=0; i<background->GetEntries(); i++) {
  //       background->GetEntry(i); 
  //       for (Int_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
  //       // add training and test events; here: first half is training, second is testing
  //       // note that the weight can also be event-wise	
  //       if (i < background->GetEntries()/2) factory->AddBackgroundTrainingEvent( vars, backgroundWeight ); 
  //       else                                factory->AddBackgroundTestEvent    ( vars, backgroundWeight ); 
  //    }
  //    // --- end ------------------------------------------------------------
  //
  // ====== end of register trees ==============================================

   
  // This would set individual event weights (the variables defined in the 
  // expression need to exist in the original TTree)
  //    for signal    : factory->SetSignalWeightExpression("weight1*weight2");
  //    for background: factory->SetBackgroundWeightExpression("weight1*weight2");
  // factory->SetBackgroundWeightExpression("weight");

  // Apply additional cuts on the signal and background samples (can be different)
  //   TCut mycuts = "abs(eta)>1.5"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
  //   TCut mycutb = "abs(eta)>1.5"; // for example: TCut mycutb = "abs(var1)<0.5";

  //Acceptance/Base cuts
  //TCut goodW("W_electron_et>30. && TMath::Abs(W_electron_eta)<2.5 && event_met_pfmet>25.");
  TCut goodW("W_muon_pt>25. && TMath::Abs(W_muon_eta)<2.5 && event_met_pfmet>25.");
  TCut twojets("numPFCorJets==2");
  TCut jetPt("JetPFCor_Pt[0]>30. && JetPFCor_Pt[1]>30.");
  TCut jetEta("TMath::Abs(JetPFCor_Eta[0])<2.5 && TMath::Abs(JetPFCor_Eta[1])<2.5");
  TCut deltaR1("TMath::Sqrt(TMath::Power(TMath::Abs(TMath::Abs(TMath::Abs(JetPFCor_Phi[0]-W_muon_phi)-TMath::Pi())-TMath::Pi()),2)+TMath::Power(JetPFCor_Eta[0]-W_muon_eta,2))>0.5");
  TCut deltaR2("TMath::Sqrt(TMath::Power(TMath::Abs(TMath::Abs(TMath::Abs(JetPFCor_Phi[1]-W_muon_phi)-TMath::Pi())-TMath::Pi()),2)+TMath::Power(JetPFCor_Eta[1]-W_muon_eta,2))>0.5");
  TCut noBJets("numPFCorJetBTags==0");
  TCut null("");

  //TCut mycuts (goodW && twojets && jetPt && jetEta && deltaR1 && deltaR2 && noBJets);
  TCut mycuts (null);

  // tell the factory to use all remaining events in the trees after training for testing:
  factory->PrepareTrainingAndTestTree( mycuts, mycuts,
                                       "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

  // If no numbers of events are given, half of the events in the tree are used for training, and 
  // the other half for testing:
  //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );  
  // To also specify the number of testing events, use:
  //    factory->PrepareTrainingAndTestTree( mycut, 
  //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );  

  // ---- Book MVA methods
  //
  // please lookup the various method configuration options in the corresponding cxx files, eg:
  // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
  // it is possible to preset ranges in the option string in which the cut optimisation should be done:
  // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

  // Cut optimisation
  if (Use["Cuts"])
    factory->BookMethod( TMVA::Types::kCuts, "Cuts", 
                         "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

  if (Use["CutsD"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsD", 
                         "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

  if (Use["CutsPCA"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsPCA", 
                         "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

  if (Use["CutsGA"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
                         "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );
   
  if (Use["CutsSA"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsSA",
                         "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
   
  // Likelihood
  if (Use["Likelihood"])
     factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood", 
                          "H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" ); 

  // test the decorrelated likelihood
  if (Use["LikelihoodD"])
    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD", 
                         "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" ); 

  if (Use["LikelihoodPCA"])
    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodPCA", 
                         "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" ); 
 
  // test the new kernel density estimator
  if (Use["LikelihoodKDE"])
    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodKDE", 
                         "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 

  // test the mixed splines and kernel density estimator (depending on which variable)
  if (Use["LikelihoodMIX"])
    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodMIX", 
                         "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" ); 

  // test the multi-dimensional probability density estimator
  // here are the options strings for the MinMax and RMS methods, respectively:
  //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );   
  //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );   
  if (Use["PDERS"])
    factory->BookMethod( TMVA::Types::kPDERS, "PDERS", 
                         "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );

  if (Use["PDERSkNN"])
    factory->BookMethod( TMVA::Types::kPDERS, "PDERSkNN", 
                         "!H:!V:VolumeRangeMode=kNN:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );

  if (Use["PDERSD"])
    factory->BookMethod( TMVA::Types::kPDERS, "PDERSD", 
                         "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );

  if (Use["PDERSPCA"])
    factory->BookMethod( TMVA::Types::kPDERS, "PDERSPCA", 
                         "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );
  /*
  // Multi-dimensional likelihood estimator using self-adapting phase-space binning
  if (Use["PDEFoam"])
    factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoam", 
                         "H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0333:nActiveCells=500:nSampl=2000:nBin=5:CutNmin=T:Nmin=100:Kernel=None:Compress=T" );
  */
  // K-Nearest Neighbour classifier (KNN)
  if (Use["KNN"])
    factory->BookMethod( TMVA::Types::kKNN, "KNN", 
                         "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
  // H-Matrix (chi2-squared) method
  if (Use["HMatrix"])
    factory->BookMethod( TMVA::Types::kHMatrix, "HMatrix", "!H:!V" ); 

  // Fisher discriminant   
  if (Use["Fisher"])
    factory->BookMethod( TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=60:NsmoothMVAPdf=10" );

  // Fisher with Gauss-transformed input variables
  if (Use["FisherG"])
    factory->BookMethod( TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );

  // Composite classifier: ensemble (tree) of boosted Fisher classifiers
  if (Use["BoostedFisher"])
    factory->BookMethod( TMVA::Types::kFisher, "BoostedFisher", "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2");
  /*
  // Linear discriminant (same as Fisher)
  if (Use["LD"])
    factory->BookMethod( TMVA::Types::kLD, "LD", "H:!V:VarTransform=None" );
  */
  // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
  if (Use["FDA_MC"])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_MC",
                         "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );
   
  if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_GA",
                         "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );

  if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_SA",
                         "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

  if (Use["FDA_MT"])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_MT",
                         "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

  if (Use["FDA_GAMT"])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_GAMT",
                         "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

  if (Use["FDA_MCMT"])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_MCMT",
                         "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

  // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
  if (Use["MLP"])
    factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=500:HiddenLayers=N+5:TestRate=10:EpochMonitoring" );

  if (Use["MLPBFGS"])
    factory->BookMethod( TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=500:HiddenLayers=N+5:TestRate=10:TrainingMethod=BFGS:!EpochMonitoring" );


  // CF(Clermont-Ferrand)ANN
  if (Use["CFMlpANN"])
    factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...  
  
  // Tmlp(Root)ANN
  if (Use["TMlpANN"])
    factory->BookMethod( TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...
  
  // Support Vector Machine
  if (Use["SVM"])
    factory->BookMethod( TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );
   
  // Boosted Decision Trees
  if (Use["BDTG"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG", 
                         "!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.30:UseBaggedGrad:GradBaggingFraction=0.6:SeparationType=GiniIndex:nCuts=20:NNodesMax=5" );

  if (Use["BDT"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT", 
                         "!H:!V:NTrees=400:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
   
  if (Use["BDTB"]) // Bagging
    factory->BookMethod( TMVA::Types::kBDT, "BDTB", 
                         "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );

  if (Use["BDTD"]) // Decorrelation + Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTD", 
                         "!H:!V:NTrees=400:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );
   
  // RuleFit -- TMVA implementation of Friedman's method
  if (Use["RuleFit"])
    factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit",
                         "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );
   
  // For an example of the category classifier, see: TMVAClassificationCategory

  // --------------------------------------------------------------------------------------------------

  // As an example how to use the ROOT plugin mechanism, book BDT via
  // plugin mechanism
  if (Use["Plugin"]) {
    //
    // first the plugin has to be defined, which can happen either through the following line in the local or global .rootrc:
    //
    // # plugin handler          plugin name(regexp) class to be instanciated library        constructor format
    // Plugin.TMVA@@MethodBase:  ^BDT                TMVA::MethodBDT          TMVA.1         "MethodBDT(TString,TString,DataSet&,TString)"
    // 
    // or by telling the global plugin manager directly
    gPluginMgr->AddHandler("TMVA@@MethodBase", "BDT", "TMVA::MethodBDT", "TMVA.1", "MethodBDT(TString,TString,DataSet&,TString)");
    factory->BookMethod( TMVA::Types::kPlugins, "BDT",
                         "!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=50" );
  }

  // --------------------------------------------------------------------------------------------------

  // ---- Now you can tell the factory to train, test, and evaluate the MVAs

  // Train MVAs using the set of training events
  factory->TrainAllMethods();

  // ---- Evaluate all MVAs using the set of test events
  factory->TestAllMethods();

  // ----- Evaluate and compare performance of all configured MVAs
  factory->EvaluateAllMethods();    

  // --------------------------------------------------------------
   
  // Save the output
  outputFile->Close();

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;      

  delete factory;

  // Launch the GUI for the root macros
  if (!gROOT->IsBatch()) TMVAGui( outfileName );
}