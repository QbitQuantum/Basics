void runTheTree(TString theName){
/*TFile *c = TFile::Open("ElecIDtree_9_1_mz8.root");

TTree *theTree = (TTree*) c->Get("eventsTree");*/

//theTree->Print();
    
    TChain *theTree = new TChain("eventsTree");

theTree->Add("/tmp/hbrun/"+theName+"/fichier_*.root");

    cout << "full nb of events " << theTree->GetEntries() << endl;

theTree->Process("createMuonTree.C+");
//
//
}