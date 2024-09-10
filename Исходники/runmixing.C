void runmixing(bool scan = false) 
{
   int len = 5;

   std::vector<MyClass> *p = new std::vector<MyClass>;

   TTree *t = new TTree("tree","bad vector");
   
   t->Branch("checked_value", "vector<MyClass>", &p);
   t->Branch("value", "vector<MyClass>", (void*)&p);

   for(int i = 0; i<len; ++i) {
      p->push_back( MyClass( i*12 ) );
      if (scan) t->Fill();
   }
   t->SetBranchAddress("value",&p);

   if (scan) {
      //t->Print();
      t->Scan("*");
   }
}