//==================================================================================================
void makePlotsLepton(bool isBlind=0, bool drawSignal=0)
{
  // setup graphics stuff before starting
  MitStyle::Init();

  // read all environment variables
  TString here   = getEnv("PWD");
  TString home   = getEnv("HOME");
  TString mitHgg = getEnv("MIT_MONOPH_DIR");
  TString hstDir = getEnv("MIT_ANA_HIST");
  TString anaCfg = getEnv("MIT_PLOTW_CFG");
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
  TString inFileName = "../monoph-2013-Nov18_reduced_Lepton.root";
  std::cout << "inFileName " << inFileName << std::endl;
  
  //Make the histos
  //==Ele cut 0/1==
  //TString thisCut = "*(phoHasPixelSeed == 0 && abs(TMath::ACos(TMath::Cos(phoPhi-bosonPhi))) > 2 && metBosCor > 140 && phoEt > 160 && nlep == 1 && lep1Mass < 0.05 && phoMetDeltaPhi > 0.5 && ((abs(TMath::ACos(TMath::Cos(lep1Phi-phoPhi))) < 2.9 && nalljets == 0) || (nalljets == 1 && jetMetDeltaPhi > 0.5 && jetMetDeltaPhi < 2.65 && phoJetDeltaPhi < 2.9)))";
  //==Mu cut==
  TString thisCut = "*(abs(TMath::ACos(TMath::Cos(phoPhi-bosonPhi))) > 2 && metBosCor > 140 && phoEt > 160 && nlep == 1 && lep1Mass > 0.05 && phoMetDeltaPhi > 0.5 && (nalljets == 0 || (nalljets == 1 && jetMetDeltaPhi > 0.5 && jetMetDeltaPhi < 2.65 && phoJetDeltaPhi < 2.9)))";
  thisCut += "*(metFilterWord == 1023 || metFilterWord == 511)";

  //==All cut==
  //TString thisCut = "*(abs(TMath::ACos(TMath::Cos(phoPhi-bosonPhi))) > 2 && metBosCor > 140 && phoEt > 160 && nlep == 1 && phoMetDeltaPhi > 0.5 && (";
  //thisCut += "(lep1Mass < 0.05 && ((abs(TMath::ACos(TMath::Cos(lep1Phi-phoPhi))) < 2.9 && nalljets == 0) || (nalljets == 1 && jetMetDeltaPhi > 0.5 && jetMetDeltaPhi < 2.65 && phoJetDeltaPhi < 2.9))) || ";
  //thisCut += "(lep1Mass > 0.05 && (nalljets == 0 || (nalljets == 1 && jetMetDeltaPhi > 0.5 && jetMetDeltaPhi < 2.65 && phoJetDeltaPhi < 2.9)))))";

  //TString thisCut = "*(phoEt > 160 && nlep == 1)";
  //==Mu cat zero==
  //TString thisCut = "*(phoEt > 160 && nlep == 1 && phoMetDeltaPhi > 2. && (nalljets == 0) && abs(lep1Id) == 13)";
  //==Ele cat zero==
  //TString thisCut = "*(phoEt > 160 && nlep == 1 && phoMetDeltaPhi > 2. && (nalljets == 0) && abs(lep1Id) == 11)";
  //==Mu cat one==
  //TString thisCut = "*(phoEt > 160 && nlep == 1 && (nalljets == 1) && abs(lep1Id) == 13)";
  //==Ele cat one==
  //TString thisCut = "*(phoEt > 160 && nlep == 1 && (nalljets == 1) && abs(lep1Id) == 13)";

  // One bin histo (only for counting)
  makeStack("nphotons", thisCut, "nphotons", "nphotons", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               1, -1, 10,
               0);
  // lepJetDeltaPhi: fixed binning
  makeStack("abs(TMath::ACos(TMath::Cos(lep1Phi-jet1Phi)))", thisCut, "lepJetDeltaPhi", "#Delta#phi(#lep-jet)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, false,
               30, 0, 3.15,
               0);
  // lepMetDeltaPhi: fixed binning
  makeStack("abs(TMath::ACos(TMath::Cos(lep1Phi-metCorPhi)))", thisCut, "lepMetDeltaPhi", "#Delta#phi(lep-MET)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, false,
               30, 0, 3.15,
               0);
  // lepPhoDeltaPhi: fixed binning
  makeStack("abs(TMath::ACos(TMath::Cos(lep1Phi-phoPhi)))", thisCut, "lepPhoDeltaPhi", "#Delta#phi(#lep-#gamma)", "", 
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
  float xlowMET[7] = {140,170,190,250,400,700,1000};        
  makeStack("metBosCor", thisCut, "met", "MET [GeV]", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, true, drawSignal, true,
               6, -1, -1,
               xlowMET);
  // photon ET: variable binning
  float xlowPhET[6] = {160,190,250,400,700,1000};        
  makeStack("phoEt", thisCut, "phoEt", "#gamma_{ET} [GeV]", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, true, drawSignal, true,
               5, -1, -1,
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
               25, 0, 100,
               0);
  // bosonPt: fixed binning
  makeStack("bosonPt", thisCut, "bosonPt", "p_{T}(W) [GeV]", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               15, 100, 400,
               0);
  // bosonEta: fixed binning
  makeStack("bosonEta", thisCut, "bosonEta", "#eta(W)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               20, -3, 3,
               0);
  // bosonMass: fixed binning
  makeStack("bosonMass", thisCut, "bosonMass", "m_{T}(W) [GeV]", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               10, 0, 100,
               0);
  // phoBosDeltaPhi: fixed binning
  makeStack("abs(TMath::ACos(TMath::Cos(phoPhi-bosonPhi)))", thisCut, "phoWDeltaPhi", "#Delta#phi(#gamma-W)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, false,
               15, 2, 3.15,
               0);
  // lepPt: fixed binning
  makeStack("lep1Pt", thisCut, "lep1Pt", "p_{T}(lep) [GeV]", "GeV", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               30, 0, 300,
               0);
  // lepEta: fixed binning
  makeStack("lep1Eta", thisCut, "lep1Eta", "#eta(lep)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               20, -3, 3,
               0);
  // phoIso1: fixed binning
  makeStack("phoCombIso1", thisCut, "phoCombIso1", "PFIso_{1} (#gamma)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               20, 0, 6,
               0);
  // phoIso2: fixed binning
  makeStack("phoCombIso2", thisCut, "phoCombIso2", "PFIso_{2} (#gamma)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               20, 0, 6,
               0);
  // phoIso3: fixed binning
  makeStack("phoCombIso3", thisCut, "phoCombIso3", "PFIso_{3} (#gamma)", "", 
               listOfSignals, listOfSamples, listOfDatasets, 
               inFileName,
               isBlind, false, drawSignal, true,
               20, 0, 4,
               0);

        
  return;
}