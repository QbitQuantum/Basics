//==================================================================================================
void makeTablesEleFake()
{
  // setup graphics stuff before starting
  MitStyle::Init();

  // read all environment variables
  TString here   = getEnv("PWD");
  TString home   = getEnv("HOME");
  TString mitHgg = getEnv("MIT_MONOPH_DIR");
  TString hstDir = getEnv("MIT_ANA_HIST");
  TString anaCfg = getEnv("MIT_PLOTE_CFG");
  TString prdCfg = getEnv("MIT_PROD_CFG");

  // define samples
  TaskSamples* samples = new TaskSamples(prdCfg.Data(),hstDir.Data());
  samples->SetNameTxt(anaCfg.Data());
  samples->ReadFile((mitHgg + TString("/config")).Data());
  vector<const Sample*> listOfSamples;
  for (UInt_t iSample=0; iSample < *samples->NSamples(); iSample++) listOfSamples.push_back(samples->GetSample(iSample));  
  vector<const Sample*> listOfDatasets;
  for (UInt_t iSample=0; iSample < *samples->NDataSamples(); iSample++) listOfDatasets.push_back(samples->GetDataSample(iSample));
  // define infolder
  TString inFileName =  "../monoph-2013-Nov18_reduced_EleFake.root";
  std::cout << "inFileName " << inFileName << std::endl;
  
  //Make the tables
  //Default cut
  TString thisCut = "*(phoEt > 160 && metCor > 140 && nlep == 0 && phoMetDeltaPhi > 0.5 && (nalljets == 0 || (nalljets == 1 && jetMetDeltaPhi > 0.5 && jetMetDeltaPhi < 2.65 && phoJetDeltaPhi < 2.9)))";
  thisCut += "*(metFilterWord == 1023 || metFilterWord == 511)";
  cout << "table in control region" << endl;
  makeTable("nphotons", thisCut, "nphotons", "nphotons", "", 
               listOfSamples, listOfDatasets, inFileName,
               1, false, 
               1, -1, 10,
               0);
        
  return;
}