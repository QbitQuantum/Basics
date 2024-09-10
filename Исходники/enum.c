void Enum() {
   TTree *t = new TTree;
   WithEnum *e = new WithEnum;
   t->Branch("test",&e);
   t->Fill();
   t->Fill();
#ifdef ClingWorkAroundCallfuncAndInline2
   t->Scan("test.val");
#else
   t->Scan("test.val:test.GetVal()");
#endif
}