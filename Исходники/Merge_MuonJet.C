void Merge_MuonJet(TString type, int id = 0, int N = 1){

  gROOT->Reset();
  
  type.ToLower();
  if (type=="mc") MC = true; else
    if (type=="data") MC = false; else
      {cout<<"Choose mc or data"<<endl; return; }

  TString sample = "QCDPPb";//bJetPPb
  TString name,outname;
  
  if (MC) {name = Form("%s_AccCut.root",sample.Data());outname = "QCDPPb_genmuonmerged.root"; }
  else {name =  "jettrig_weight_AccCut.root"; outname = "jettrig_weight_AccCut_muons.root"; }


  vector<TString> newbranches = {"Njetmuon/I:jetmuonpt/F,jetmuoneta/F,jetmuonphi/F,jetmuonptrel/F,jetmuonip3d/F"};

  ProcessFile(name, outname, "jet", vector<TString> ({"muon"}), vector<TString> {"nref","Glb_nptl"}, newbranches, ProcessEvent, id, N);



  //  ProcessFile(name, outname, "jet", vector<TString> ({"QCDPPb_AccCut.root:m=muon","evt"}), jetbranches, newbranches, ProcessEvent);  
}