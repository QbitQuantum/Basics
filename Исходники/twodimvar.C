void tscan(const char *input) {

   TFile* tf = new TFile(input);
   TTree* tree = (TTree*)tf->Get("tree");
   tree->Draw("aa[][]");
   tree->SetScanField(0);
   tree->Scan("aa");

}