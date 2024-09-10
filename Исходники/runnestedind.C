int runnestedind() {
   TTree *t = create();
   t->SetScanField(0);

   t->Scan("type[]:type[sonind[]]","type[]==3");
   TH1I* hgood = new TH1I("hgood","works",10,0,10);
   TH1I* hbad = new TH1I("hbad","used to fail",10,0,10);
   TCanvas *c = new TCanvas("c1");
   c->Divide(1,2);
   c->cd(1);
   t->Draw("type[sonind[]]>>hbad","type[]==3");
   c->cd(2);   
   t->Draw("type[sonind[]]>>hgood","type[]==3 && sonind[]>=0");

   if (hgood->GetMean()!=hbad->GetMean()) {
      cout << "Drawing \"type[sonind[]]>>hbad\",\"type[]==3\" failed!\n";
      return 1;
   }
#ifdef ClingWorkAroundErracticValuePrinter
   printf("(int)0\n");
#endif
   return 0;
}