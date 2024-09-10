bool check(int n = 2) {
   TFile *file = TFile::Open(TString::Format("merged%d.root",n));

   bool result = true;
   TH1F *h; file->GetObject("h1",h);
   if (!h) {
      Error("execFileMerger","h1 is missing\n");
      result = false;
   }
   if (h->GetBinContent(2) != n || h->GetBinContent(3) != n) {
      Error("execFileMerger","h1 not added properly");
      result = false;
   }
   
   THnSparseF *sparse; file->GetObject("sparse",sparse);
   if (!sparse) {
      Error("execFileMerger","sparse is missing\n");
      result = false;
   } else {
      Int_t coordIdx[5] = {1, 2, 3, 4, 5};
      Double_t cont = sparse->GetBinContent(coordIdx);
      if (cont > n + 0.4 || cont < n - 0.4) {
         Error("execFileMerger","sparse merge failed: expected bin content %g, read %g\n",
               (Double_t)n, cont);
         result = false;
      }
      Double_t entries = sparse->GetEntries();
      if (entries > n + 0.4 || entries < n - 0.4) {
         Error("execFileMerger","sparse merge failed: expected %g entries, read %g\n",
               (Double_t)n, entries);
         result = false;
      }
   }
   
   THStack *stack; file->GetObject("stack",stack);
   if (!stack) {
      Error("execFileMerger","stack is missing\n");
      result = false;
   }
   h = (TH1F*)stack->GetHists()->FindObject("hs_1");
   if (!h) {
      Error("execFileMerger","hs_1 is missing\n");
      result = false;
   }
   if (h->GetBinContent(2) != n || h->GetBinContent(3) != n) {
      Error("execFileMerger","hs_1 not added properly");
      result = false;
   }
   h = (TH1F*)stack->GetHists()->FindObject("hs_2");
   if (!h) {
      Error("execFileMerger","hs_2 is missing\n");
      result = false;
   }
   if (h->GetBinContent(4) != n || h->GetBinContent(5) != n) {
      Error("execFileMerger","hs_2 not added properly");
      result = false;
   }

   TGraph *gr; file->GetObject("exgraph",gr);
   if (!gr) {
      Error("execFileMerger","exgraph is missing\n");
      result = false;
   }
   if (gr->GetN() != ( n * 3)) {
      Error("execFileMerger","exgraph not added properly n=%d rather than %d",gr->GetN(),n*3);
      result = false;            
   } else {
      for(Int_t k = 0; k < gr->GetN(); ++k) {
         double x,y;
         gr->GetPoint(k,x,y);
         if ( x != ( (k%3)+1 ) ||  y != ( (k%3)+1 ) ) {
            Error("execFileMerger","exgraph not added properly");
            result = false;            
         }
      }
   }
   
   TTree *tree; file->GetObject("tree",tree);
   if (!tree) {
      Error("execFileMerger","tree is missing\n");
      result = false;
   }
   if (tree->GetEntries() != n*2) {
      Error("execFileMerger","tree does not have the expected number of entries: %lld rather than %d",tree->GetEntries(),n*2);
      result = false;            
   } else {
      if ( tree->GetEntries("data==1") != n ) {
         Error("execFileMerger","tree does not have the expected data. We got %lld entries with 'data==1' rather than %d",tree->GetEntries("data==1"),n);
         tree->Scan();
         result = false;
      }
   }   
   return result;
}