void rads2Hist(){
  TFile * output_file = new TFile("RADS_Data.root", "RECREATE"); //Pointer to ROOT output file 
  TH1D * hist = new TH1D("hist", "Radiation Dosimetry with Altitude", 100, 0, 10000); //1D histogram of doubles
  TTree * t = new TTree("t", "RADS_Data"); //Pointer to tree to store data
  t->ReadFile("RADS_long.dat", "RAD_cpm/I"); // Add integer variable to tree called RAD_cpm
  t->Write(); //Write tree to ROOT file
  output_file->Close();
  
  
}