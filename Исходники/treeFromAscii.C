void treeFromAscii(const char* filen) {

//  Read data from an ascii file and create a root file with a tree

  std::string rFile( filen ) ;
  rFile += ".root" ;
  TFile *f = new TFile( rFile.c_str() ,"RECREATE");

  TTree*  ntuple = new TTree("ntuple","") ;
  ntuple->ReadFile( filen ) ;
  
  f->Write() ;
  f->Close() ;
}