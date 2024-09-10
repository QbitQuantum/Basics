//==================================================================================================
void makePlotsDiLepton(bool isBlind=0, bool drawSignal=0)
{
  // setup graphics stuff before starting
  MitStyle::Init();

  // read all environment variables
  TString here   = getEnv("PWD");
  TString home   = getEnv("HOME");
  TString mitHgg = getEnv("MIT_MONOPH_DIR");
  TString hstDir = getEnv("MIT_ANA_HIST");
  TString anaCfg = getEnv("MIT_PLOTZ_CFG");
  TString prdCfg = getEnv("MIT_PROD_CFG");

  // define samples
  TaskSamples* samples = new TaskSamples(prdCfg.Data(),hstDir.Data());
  samples->SetNameTxt(anaCfg.Data());
  samples->ReadFile((mitHgg + TString("/config")).Data());
  vector<const Sample*> listOfSignals;
  vector<const Sample*> listOfSamples;
  for (UInt_t iSample=0; iSample < *samples->NSamples(); iSample++) {
    if (samples->GetSample(iSample)->Name()->Contains("addmpho") ||
        samples->GetSample(iSample)->Name()->Contains("dmmpho") )
      listOfSignals.push_back(samples->GetSample(iSample));  
    else
      listOfSamples.push_back(samples->GetSample(iSample));  
  }
  vector<const Sample*> listOfDatasets;
  for (UInt_t iSample=0; iSample < *samples->NDataSamples(); iSample++) listOfDatasets.push_back(samples->GetDataSample(iSample));
  // define infolder
  TString inFileName = here + "/monoph-2013-Oct1_reduced_DiLepton.root";
  std::cout << "inFileName " << inFileName << std::endl;
  
  //Make the histos
  //==Default cut==
  //TString thisCut = "*(phoEt > 160 && metBosCor > 140 && nalljets < 2 && ((nlep > 0 && lep1Mass < 0.05 && lepAsPho > 0.5 && bosonMass > 10) || (nlep > 1 && lep1Mass > 0.05 && lep1Mass > 0.05)))";
  //==Ele only check ele veto==
  TString thisCut = "*(phoEt > 160 && metBosCor > 140 && nalljets < 2 && ((nlep > 0 && lep1Mass < 0.05 && bosonMass > 60 && bosonMass < 120) ))";
  //TString thisCut = "*(phoEt > 160 && nalljets < 2 && nlep > 1 && bosonPt > 140 && lep1Mass > 0.05 && lep1Mass > 0.05)";
  //TString thisCut = "*(phoEt > 160 && metBosCor > 140 && nalljets < 2 && ((nlep > 0 && lep1Mass < 0.05 && lepAsPho > 0.5 && bosonMass > 10) || (nlep > 1 && lep1Mass > 0.05 && lep1Mass > 0.05)))";
  //TString thisCut = "*(phoEt > 160 && nalljets < 2 && bosonPt > 140 && ((nlep > 0 && lep1Mass < 0.05 && lepAsPho > 0.5 && bosonMass > 10) || (nlep > 1 && lep1Mass > 0.05 && lep1Mass > 0.05)))";
  //TString thisCut = "*(phoEt > 160 && nalljets < 2 && bosonPt > 140 && nlep > 1 && abs(lep1Id) == 11 && abs(lep1Id) == 11)";
  //TString thisCut = "*(phoEt > 160 && nlep > 0 && abs(lep1Id) == 13 && abs(lep2Id) == 13)";

  //TString thisCut = "*(phoEt > 160 && nlep > 1)";

  //// One bin histo (only for counting)
  //makeStack("nphotons", thisCut, "nphotons", "nphotons", "", 
               //listOfSignals, listOfSamples, listOfDatasets, 
               //inFileName,
               //isBlind, false, drawSignal, true,
               //1, -1, 10,
               //0);
  // lepMetDeltaPhi: fixed binning
  makeStack("abs(TMath::ACos(TMath::Cos(lep1Phi-metCorPhi)))", thisCut, "lepMetDeltaPhi", "#Delta#phi(lep-MET)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, false,
               30, 0, 3.15,
               0);
  // phoMetDeltaPhi: fixed binning
  makeStack("phoMetDeltaPhi", thisCut, "phoMetDeltaPhi", "#Delta#phi(#gamma-MET)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, false,
               30, 0, 3.15,
               0);
  makeStack("jetMetDeltaPhi", thisCut, "jetMetDeltaPhi", "#Delta#phi(jet-MET)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, false,
               30, 0, 3.15,
               0);
  makeStack("phoJetDeltaPhi", thisCut, "phoJetDeltaPhi", "#Delta#phi(#gamma-jet)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, false,
               30, 0, 3.15,
               0);
  // MET: variable binning
  float xlowMET[6] = {140,150,165,195,260,500};        
  makeStack("metBosCor", thisCut, "met", "MET [GeV]", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               5, -1, -1,
               xlowMET);
  // photon ET: variable binning
  float xlowPhET[5] = {160,175,195,260,500};        
  makeStack("phoEt", thisCut, "phoEt", "#gamma_{ET} [GeV]", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, true, drawSignal, true,
               4, -1, -1,
               xlowPhET);
  // MET/photonET: fixed binning
  makeStack("metBosCor/phoEt", thisCut, "metOverPhET", "MET/#gamma_{ET}", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               30, 0, 2,
               0);
  // nVtx: fixed binning
  makeStack("nvtx", thisCut, "nvtx", "N_{vtx}", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               20, 0, 40,
               0);
  // jetEt: fixed binning
  makeStack("jet1Pt", thisCut, "jetPt", "Lead Jet_{PT}", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               40, 0, 200,
               0);
  // nJets: fixed binning
  makeStack("nalljets", thisCut, "njets", "N_{jets}", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               5, 0, 5,
               0);
  // metSig: fixed binning
  makeStack("metSig", thisCut, "metSig", "MET Significance", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               50, 0, 100,
               0);
  // bosonMass: fixed binning
  makeStack("bosonMass", thisCut, "bosonMass", "m(Z)", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               80, 0, 400,
               0);
  // bosonPt: fixed binning
  makeStack("bosonPt", thisCut, "bosonPt", "p_{T}(Z)", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               40, 0, 400,
               0);
  // bosonEta: fixed binning
  makeStack("bosonEta", thisCut, "bosonEta", "#eta(Z)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               40, -4, 4,
               0);
  // bosonMass: fixed binning
  makeStack("bosonPhoMass", thisCut, "bosonPhoMass", "m(Z#gamma)", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               40, 0, 1000,
               0);
  // ele->pho fake rate: fixed binning
  makeStack("lepAsPho", thisCut, "lepAsPho", "ele is pho", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               3, -1, 2,
               0);
        
  return;
}