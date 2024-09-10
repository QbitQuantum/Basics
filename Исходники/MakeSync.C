//#include "EffMaker.h"
void MakeSync()
{
	// Use this sample for sync: /SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/MINIAODSIM
  // 	TProof *proof = TProof::Open("workers=10");
  TChain *Effchain = new TChain("TreeMaker2/PreSelection");
//   Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/*.root");
//   Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/WJetsToLNu_HT-200to400/*root");
//   Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/WJetsToLNu_HT-400to600/*root");
//   Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/WJetsToLNu_HT-600toInf/*root");
  
  // 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/oldLeptonDefinitionAndNotMergedCode/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/*.root");
  // 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/oldLeptonDefinitionAndNotMergedCode/WJetsToLNu_HT-200to400/*root");
  // 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/oldLeptonDefinitionAndNotMergedCode/WJetsToLNu_HT-400to600/*root");
  // 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/oldLeptonDefinitionAndNotMergedCode/WJetsToLNu_HT-600toInf/*root");
  
  // 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/SMS-T1bbbb_2J_mGl-1000_mLSP-900/*root");
    	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/SMS-T1tttt_2J_mGl-1500_mLSP-100/*root");
  // 	Effchain->SetProof();
  //	Effchain->Process("ExpecMaker.C+",0,80000);
  Effchain->Process("SyncMaker.C++g");
  // 	Effchain->SetProof(0);
  // 	delete proof;
}