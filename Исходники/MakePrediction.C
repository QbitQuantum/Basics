void MakePrediction(TString infname)
{
  bool useTProof = false;
  TProof *proof = NULL;

  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");
  
  TChain *Effchain = new TChain("TreeMaker2/PreSelection");
  Effchain->Add(infname);

  if(useTProof){
    proof = TProof::Open("workers=2");
    Effchain->SetProof();     	
  }

  Effchain->Process("Prediction.C++g");

  delete proof;
}