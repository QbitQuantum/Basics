//#include "EffMaker.h"
void MakeExpectation()
{
//  	TProof *proof = TProof::Open("workers=10");
// 	TString connect = gSystem.GetFromPipe("pod-info -c");
// 	TProof *proof = TProof::Open(connect);
// 	TProof *proof = TProof::Open("workers=20");
 	TChain *Effchain = new TChain("TreeMaker2/PreSelection");
      	Effchain->Add("../reduced_trees/13TeV/ttbar_arne/*.root");
       	// Effchain->Add("TreeMaker/mc_light/WJetsToLNu_HT-200to400/*root");
    	//   Effchain->Add("TreeMaker/mc_light/WJetsToLNu_HT-400to600/*root");
     	// Effchain->Add("TreeMaker/mc_light/WJetsToLNu_HT-600toInf/*root");
	// 		Effchain->Add("TreeMaker/mc_light/TBarToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
	// 		Effchain->Add("TreeMaker/mc_light/TBarToLeptons_t-channel_Tune4C_CSA14_13TeV-aMCatNLO-tauola/*.root");
	// 		Effchain->Add("TreeMaker/mc_light/TToLeptons_s-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
	// 		Effchain->Add("TreeMaker/mc_light/TToLeptons_t-channel-CSA14_Tune4C_13TeV-aMCatNLO-tauola/*.root");
			
// //    	Effchain->Add("TreeMaker/mc_light/SMS-T1bbbb_2J_mGl-1000_mLSP-900/*root");
//   	Effchain->Add("TreeMaker/mc_light/SMS-T1bbbb_2J_mGl-1500_mLSP-100/*root");
//   	Effchain->Add("TreeMaker/mc_light/SMS-T1qqqq_2J_mGl-1000_mLSP-800/*root");
//   	Effchain->Add("TreeMaker/mc_light/SMS-T1qqqq_2J_mGl-1400_mLSP-100/*root");
//    	Effchain->Add("TreeMaker/mc_light/SMS-T1tttt_2J_mGl-1200_mLSP-800/*root");
//    	Effchain->Add("TreeMaker/mc_light/SMS-T1tttt_2J_mGl-1500_mLSP-100/*root");
	
// 	Effchain->Add("TreeMaker/mc_light/QCD_HT_1000ToInf_13TeV-madgraph_v1/*root");
// 	Effchain->Add("TreeMaker/mc_light/QCD_HT_1000ToInf_13TeV-madgraph_v1_ext1/*root");
// 	Effchain->Add("TreeMaker/mc_light/QCD_HT_250To500_13TeV-madgraph_v1/*root");
// 	Effchain->Add("TreeMaker/mc_light/QCD_HT_250To500_13TeV-madgraph_v1_ext1/*root");
// 	Effchain->Add("TreeMaker/mc_light/QCD_HT-500To1000_13TeV-madgraph_v1/*root");
// 	Effchain->Add("TreeMaker/mc_light/QCD_HT-500To1000_13TeV-madgraph_v1_ext1/*root");
	
//         	Effchain->SetProof();
	//	Effchain->Process("ExpecMaker.C+",0,80000);
		Effchain->Process("ExpecMaker.C++g",0,990000000);
//         	Effchain->SetProof(0);
//        	delete proof;
}