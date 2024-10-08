void make_run_table(const char * infile="rtree.root")
{
  TFile * tf = new TFile(infile,"READ");
  TTree * tr = (TTree*) tf->Get("rellum");
  tr->SetScanField(0);
  char outfile[64];
  strcpy(outfile,"run_table.txt");
  gSystem->RedirectOutput(outfile,"w");
  tr->Scan("i:runnum:fi:fill");
  gSystem->RedirectOutput(0);
  printf("%s created\n",outfile);
};