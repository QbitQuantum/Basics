//==================================================================================================
void makeSynchTree(double lumi = 19700.0) 
{
  // Define output files mode
  TString outFileMode = "RECREATE";

  // Read all environment variables
  TString anaDir = getEnv("MIT_MONOJET_DIR");
  TString hstDir = getEnv("MIT_ANA_HIST");
  TString anaCfg = "boostedv-ana";
  TString prdCfg = getEnv("MIT_PROD_CFG");
  
  // Fix data list for photons
  anaCfg = "boostedv-synch";

  // Define samples
  TaskSamples* samples = new TaskSamples(prdCfg.Data(),hstDir.Data());
  samples->SetNameTxt(anaCfg.Data());
  samples->ReadFile((anaDir + TString("/config")).Data());
  vector<const Sample*> listOfSamples;
  for (UInt_t iSample=0; iSample < samples->NDataSamples(); iSample++) listOfSamples.push_back(samples->GetDataSample(iSample));
  for (UInt_t iSample=0; iSample < samples->NSamples(); iSample++) listOfSamples.push_back(samples->GetSample(iSample));  

  // Prepare pointer to outfile
  TFile *fin;
  TFile *fout;
  TString outFileName = "synch.root";
  fout = new TFile(outFileName,outFileMode);
  
  // Prepare object to store outtree
  MitSynchTree outTree;
  
  // Generate reduced trees
  // loop through the samples and produce the reduced trees
  for (UInt_t iSample=0; iSample < listOfSamples.size(); iSample++) {
    TString inFilePath = hstDir+"/"+*listOfSamples.at(iSample)->File();
    fin = new TFile(inFilePath,"READ");
    cout << "INFO -- Reading sample file: " << *listOfSamples.at(iSample)->File() << endl;
    // Prepare event weight
    double thisXsec = *listOfSamples.at(iSample)->Xsec();
    double nGenEvts = ((TH1D*)fin->FindObjectAny("hDAllEvents"))->GetEntries();
    double baseWeight = lumi*thisXsec/nGenEvts;
    // Read input tree
    MitDMSTree inTree;
    inTree.LoadTree(inFilePath,1);
    inTree.InitTree(1);
    // Start a new sample group according to cfg file legend
    if (*listOfSamples.at(iSample)->Legend() != " ") {
      // Close previous group
      if (iSample > 0) {
        fout->cd();
        outTree.tree_->Write();
        fout->Close();
        fout = TFile::Open(outFileName,"UPDATE");     
      } 
      fout->cd();
      TString outTreeName = *listOfSamples.at(iSample)->Legend();
      outTree.CreateTree(outTreeName.Data());
      outTree.InitVariables();
    }
    // Scan on input and fill output ntuple
    cout << "INFO ---> Number of events passing the selection is: ";
    fillOutNtuples(outTree,inTree,baseWeight);
    
    // Close last group
    if (iSample == (listOfSamples.size()-1)) {
      fout->cd();
      outTree.tree_->Write(); 
      fout->Close();
      break;
    }      

    fin->Close();
  }  
  
  return;
}