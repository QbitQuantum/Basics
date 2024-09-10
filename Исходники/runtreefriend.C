void DrawFriend() {
  // Draw a scatter plot of variable x in the parent TTree versus
  // the same variable in the subtree.
  // This should produce points along a straight line.
   
   TFile *f  = TFile::Open("treeparent.root");
   TTree *T  = (TTree*)f->Get("T");
   T->AddFriend("TF","treefriend.root");
   T->SetScanField(0);
   T->Scan("x:TF.x","","",20);
}