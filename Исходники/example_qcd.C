int main() {
   float lumi = 2260.;
   TString dir = "/Users/dygyun/Top/HET_v763";
   //TString dir = "/xrootd/store/user/tjkim/ntuples/hep/V6";
   TFile * fA = TFile::Open(dir+"/hep_TT_powheg.root");
   TFile * fB = TFile::Open(dir+"/hep_TT_powheg.root");
   TFile * fC = TFile::Open(dir+"/hep_WJets.root");
   TFile * fD = TFile::Open(dir+"/hep_DYJets.root");
   TFile * fE = TFile::Open(dir+"/hep_DYJets_10to50.root");
   TFile * fI = TFile::Open(dir+"/hep_SingleTop_t.root");
   TFile * fJ = TFile::Open(dir+"/hep_SingleTbar_t.root");
   TFile * fK = TFile::Open(dir+"/hep_SingleTop_tW.root");
   TFile * fL = TFile::Open(dir+"/hep_SingleTbar_tW.root");
   TFile * fN = TFile::Open(dir+"/hep_WW.root");
   TFile * fO = TFile::Open(dir+"/hep_WZ.root");
   TFile * fM = TFile::Open(dir+"/hep_ZZ.root");
//   TFile * fP = TFile::Open(dir+"/hep_qcd.root");
   
   TH1F * hBsemi = (TH1F*) fA->Get("TopTree/EventSummary");
   TH1F * hB = (TH1F*) fB->Get("TopTree/EventSummary");
   TH1F * hC = (TH1F*) fC->Get("TopTree/EventSummary");
   TH1F * hD = (TH1F*) fD->Get("TopTree/EventSummary");
   TH1F * hE = (TH1F*) fE->Get("TopTree/EventSummary");
   TH1F * hI = (TH1F*) fI->Get("TopTree/EventSummary");
   TH1F * hJ = (TH1F*) fJ->Get("TopTree/EventSummary");
   TH1F * hK = (TH1F*) fK->Get("TopTree/EventSummary");
   TH1F * hL = (TH1F*) fL->Get("TopTree/EventSummary");
   TH1F * hN = (TH1F*) fN->Get("TopTree/EventSummary");
   TH1F * hO = (TH1F*) fO->Get("TopTree/EventSummary");
   TH1F * hM = (TH1F*) fM->Get("TopTree/EventSummary");
 //  TH1F * hP = (TH1F*) fP->Get("");
   int nevt = -1;

   MyAnalysis *A = new MyAnalysis();
   TChain* ch = new TChain("TopTree/events");
   ch->Add(Form("%s/hep_data_json.root",dir.Data()), nevt);
   ch->Process(A);
   
   MyAnalysis_others *B = new MyAnalysis_others(1,1,831.8,lumi,hB->GetBinContent(1));
   TChain* ch2 = new TChain("TopTree/events");
   ch2->Add(Form("%s/hep_TT_powheg.root",dir.Data()), nevt);
   ch2->Process(B);
   //////
   MyAnalysis_Sig *Bsemi = new MyAnalysis_Sig(1,1,831.8,lumi,hBsemi->GetBinContent(1));
   TChain* ch2semi = new TChain("TopTree/events");
   ch2semi->Add(Form("%s/hep_TT_powheg.root",dir.Data()), nevt);
ch2semi->Process(Bsemi);
///////// 
   MyAnalysis *C = new MyAnalysis(1,1,61524,lumi,hC->GetBinContent(2));
   TChain* ch3 = new TChain("TopTree/events");
   ch3->Add(Form("%s/hep_WJets.root",dir.Data()),nevt);
   ch3->Process(C);
   
   MyAnalysis *D = new MyAnalysis(1,1,6025.2,lumi,hD->GetBinContent(1));
   TChain* ch4 = new TChain("TopTree/events");
   ch4->Add(Form("%s/hep_DYJets.root",dir.Data()),nevt);
   ch4->Process(D);
  
   MyAnalysis *E = new MyAnalysis(1,1,18610.0,lumi,hE->GetBinContent(1));
   TChain* ch5 = new TChain("TopTree/events");
   ch5->Add(Form("%s/hep_DYJets_10to50.root",dir.Data()),nevt);
   ch5->Process(E);
 
   MyAnalysis *I = new MyAnalysis(1,1,44.33,lumi,hI->GetBinContent(1));
   TChain* ch6 = new TChain("TopTree/events");
   ch6->Add(Form("%s/hep_SingleTop_t.root",dir.Data()),nevt);
   ch6->Process(I);
  
   MyAnalysis *J = new MyAnalysis(1,1,26.38,lumi,hJ->GetBinContent(1));
   TChain* ch7 = new TChain("TopTree/events");
   ch7->Add(Form("%s/hep_SingleTbar_t.root",dir.Data()),nevt);
   ch7->Process(J);

   MyAnalysis *K = new MyAnalysis(1,1,35.6,lumi,hK->GetBinContent(1));
   TChain* ch8 = new TChain("TopTree/events");
   ch8->Add(Form("%s/hep_SingleTop_tW.root",dir.Data()),nevt);
   ch8->Process(K);

   MyAnalysis *L = new MyAnalysis(1,1,35.6,lumi,hL->GetBinContent(1));
   TChain* ch9 = new TChain("TopTree/events");
   ch9->Add(Form("%s/hep_SingleTbar_tW.root",dir.Data()),nevt);
   ch9->Process(L);
   
   MyAnalysis *N = new MyAnalysis(1,1,118.7,lumi,hN->GetBinContent(1));
   TChain* ch10 = new TChain("TopTree/events");
   ch10->Add(Form("%s/hep_WW.root",dir.Data()),nevt);
   ch10->Process(N);

   MyAnalysis *O = new MyAnalysis(1,1,47.13,lumi,hO->GetBinContent(1));
   TChain* ch11 = new TChain("TopTree/events");
   ch11->Add(Form("%s/hep_WZ.root",dir.Data()),nevt);
   ch11->Process(O);
   
   MyAnalysis *M = new MyAnalysis(1,1,16.523,lumi,hM->GetBinContent(1));
   TChain* ch12 = new TChain("TopTree/events");
   ch12->Add(Form("%s/hep_ZZ.root",dir.Data()),nevt);
   ch12->Process(M);
 
Plotter P;

   for (int i=0; i < 6 ;i++) {
   //for (int i=0; i < D->histograms.size() ;i++) {
     //merge for DY
     D->histograms[i]->Add(E->histograms[i]);
     //merge for SingleTop
     I->histograms[i]->Add(J->histograms[i]);
     I->histograms[i]->Add(K->histograms[i]);
     I->histograms[i]->Add(L->histograms[i]);
    //////merge for VV 
     N->histograms[i]->Add(O->histograms[i]);
     N->histograms[i]->Add(M->histograms[i]);
////tt bkg     
  //   B->histograms[i]->Add(Bhad->histograms[i]);

} 
   P.SetData(A->histograms, std::string("Data"));
   P.AddBg(Bsemi->histograms, std::string("TTbar"));
   P.AddBg(C->histograms, std::string("Wjets"));
   P.AddBg(D->histograms, std::string("DY"));
   P.AddBg(I->histograms, std::string("Single Top"));
   P.AddBg(N->histograms, std::string("VV"));
   
  P.AddBg(B->histograms, std::string("TTOthers"));

   P.Plot(string("results_ABCD.pdf"));

   TFile * outA = TFile::Open("hist_data.root","RECREATE");
   for(int i=0; i < A->histograms.size(); i++){
     TH1F * tmp = (TH1F *) A->histograms[i];
     tmp->Write();
   }
   for(int i=0; i < A->histograms_2D.size(); i++){
     TH2D * tmp = (TH2D *) A->histograms_2D[i];
     tmp->Write();
   }
   outA->Write();
   outA->Close();

   TFile * outB = TFile::Open("hist_TT_others.root","RECREATE");
   for(int i=0; i < B->histograms.size(); i++){
     TH1F * tmp = (TH1F *) B->histograms[i];
     tmp->Write();
   }
   for(int i=0; i < B->histograms_2D.size(); i++){
     TH2D * tmp = (TH2D *) B->histograms_2D[i];
     tmp->Write();
   }
   outB->Write();
   outB->Close();

   TFile * outBsemi = TFile::Open("hist_TT_SemiLeptonic.root","RECREATE");
   for(int i=0; i < Bsemi->histograms.size(); i++){
     TH1F * tmp = (TH1F *) Bsemi->histograms[i];
     tmp->Write();
   }
   for(int i=0; i < Bsemi->histograms_2D.size(); i++){
     TH2D * tmp = (TH2D *) Bsemi->histograms_2D[i];
     tmp->Write();
   }
   outBsemi->Write();
   outBsemi->Close();
   
  TFile * outC = TFile::Open("hist_WJets.root","RECREATE");
   for(int i=0; i < C->histograms.size(); i++){
     TH1F * tmp = (TH1F *) C->histograms[i];
     tmp->Write();
   }
   for(int i=0; i < C->histograms_2D.size(); i++){
     TH2D * tmp = (TH2D *) C->histograms_2D[i];
     tmp->Write();
   }
   outC->Write();
   outC->Close();

   TFile * outD = TFile::Open("hist_DY.root","RECREATE");
   for(int i=0; i < D->histograms.size(); i++){
     TH1F * tmp = (TH1F *) D->histograms[i];
     tmp->Write();
    }
   for(int i=0; i < D->histograms_2D.size(); i++){
     TH2D * tmp = (TH2D *) D->histograms_2D[i];
     tmp->Write();
   }
   outD->Write();
   outD->Close();
   
    TFile * outI = TFile::Open("hist_SingleTop.root","RECREATE");
    for(int i=0; i < I->histograms.size(); i++){
      TH1F * tmp = (TH1F *) I->histograms[i];
      tmp->Write();
    }
   for(int i=0; i < I->histograms_2D.size(); i++){
     TH2D * tmp = (TH2D *) I->histograms_2D[i];
     tmp->Write();
   }
    outI->Write();
    outI->Close();

  TFile * outN = TFile::Open("hist_VV.root","RECREATE");
   for(int i=0; i < N->histograms.size(); i++){
     TH1F * tmp = (TH1F *) N->histograms[i];
     tmp->Write();
   }
   for(int i=0; i < N->histograms_2D.size(); i++){
     TH2D * tmp = (TH2D *) N->histograms_2D[i];
     tmp->Write();
   }
   outN->Write();
   outN->Close();
}