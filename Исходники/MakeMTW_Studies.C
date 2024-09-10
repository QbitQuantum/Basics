//#include "EffMaker.h"
void MakeMTW_Studies()
{
	//  	TProof *proof = TProof::Open("workers=10");
	// 	TString connect = gSystem.GetFromPipe("pod-info -c");
	// 	TProof *proof = TProof::Open(connect);
	// 	TProof *proof = TProof::Open("workers=20");
	TChain *Effchain = new TChain("TreeMaker2/PreSelection");
	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/*.root");
	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/WJetsToLNu_HT-200to400/*root");
	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/WJetsToLNu_HT-400to600/*root");
	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/WJetsToLNu_HT-600toInf/*root");
	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/TBarToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/TBarToLeptons_t-channel_Tune4C_CSA14_13TeV-aMCatNLO-tauola/*.root");
	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/TToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/TToLeptons_t-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
	
	// //    	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/SMS-T1bbbb_2J_mGl-1000_mLSP-900/*root");
	//   	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/SMS-T1bbbb_2J_mGl-1500_mLSP-100/*root");
	//   	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/SMS-T1qqqq_2J_mGl-1000_mLSP-800/*root");
	//   	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/SMS-T1qqqq_2J_mGl-1400_mLSP-100/*root");
	//    	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/SMS-T1tttt_2J_mGl-1200_mLSP-800/*root");
	//    	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/SMS-T1tttt_2J_mGl-1500_mLSP-100/*root");
	
	// 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/QCD_HT_1000ToInf_13TeV-madgraph_v1/*root");
	// 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/QCD_HT_1000ToInf_13TeV-madgraph_v1_ext1/*root");
	// 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/QCD_HT_250To500_13TeV-madgraph_v1/*root");
	// 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/QCD_HT_250To500_13TeV-madgraph_v1_ext1/*root");
	// 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/QCD_HT-500To1000_13TeV-madgraph_v1/*root");
	// 	Effchain->Add("/nfs/dust/cms/user/adraeger/phys14/mc/QCD_HT-500To1000_13TeV-madgraph_v1_ext1/*root");
	
	//         	Effchain->SetProof();
	//	Effchain->Process("ExpecMaker.C+",0,80000);
	Effchain->Process("/afs/desy.de/user/a/adraeger/2015/MTW_studies.C++g");
	//         	Effchain->SetProof(0);
	//        	delete proof;
}