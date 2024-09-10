void read_tpvar(const char* file, int YS, 
      const char* inputtable_pt, const char* outputtable_pt, 
      const char* inputtable_rap, const char* outputtable_rap, 
      const char* inputtable_cent="nocentrality", const char* outputtable_cent="nocentrality")
{
   // YS decides on the binning.
   // YS=1 -> fine binning
   // YS=2 -> coarse binning
   // YS=0 -> both
   // YS=4 -> both, except centrality where only fine (for 1S in pbpb)
   TFile *f = new TFile("tpvar.root","RECREATE");
   TTree *tr = new TTree("tree","tree");
   tr->ReadFile(file,"name/C:binlow/F:binhigh/F:eff/F:stat/F:syst/F");

   unsigned int NPTNS = YS==1 ? NPT1S : NPT2S;
   unsigned int NRAPNS = YS==1 ? NRAP1S : NRAP2S;
   unsigned int NCENTNS = YS==1 ? NCENT1S : NCENT2S;

   double *ptbins_NS = YS==1 ? ptbins_1S : ptbins_2S;
   double *rapbins_NS = YS==1 ? rapbins_1S : rapbins_2S;
   int *centbins_NS = YS==1 ? centbins_1S : centbins_2S;

   bool docentrality=strcmp(inputtable_cent,"nocentrality");
   ifstream intable_pt(inputtable_pt);
   ifstream intable_rap(inputtable_rap);
   ifstream intable_cent; if (docentrality) intable_cent.open(inputtable_cent);
   ofstream outtable_pt(outputtable_pt);
   ofstream outtable_rap(outputtable_rap);
   ofstream outtable_cent; if (docentrality) outtable_cent.open(outputtable_cent);
   double binmin, binmax, eff0, efferr, effmean;

   TString var("pt_SF");
   tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),ptbins_NS[0],ptbins_NS[NPTNS]),"PROFs");
   // tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),ptbins_NS[0],40.),"PROFs"); // ugly fix
   TProfile *htemp = (TProfile*) gDirectory->Get("htemp");
   binmin=ptbins_NS[0];
   binmax=ptbins_NS[NPTNS]; //40.;//(ugly fix)
   eff0=firsteff(tr,var.Data(),binmin,binmax);
   efferr=htemp->GetBinError(1);
   effmean=htemp->GetBinContent(1);
   cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
   if (dotables) print(intable_pt,outtable_pt,binmin,binmax,eff0,efferr);
   delete htemp;

   skip_lines(intable_pt,1);// \hline

   if (YS==0||YS==4)
   {
      NPTNS=NPT2S; ptbins_NS=ptbins_2S;
   }
   for (unsigned int i=0; i<NPTNS; i++)
   {
      // cout << setprecision(3)<<fixed << Form("name==\"%s\"&&binlow==%f&&binhigh==%f",var.Data(),ptbins_1S[i],ptbins_1S[i+1]) << endl;
      tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),ptbins_1S[i],ptbins_1S[i+1]),"PROFs");
      htemp = (TProfile*) gDirectory->Get("htemp");
      binmin=ptbins_NS[i];
      binmax=ptbins_NS[i+1];
      eff0=firsteff(tr,var.Data(),ptbins_NS[i],ptbins_NS[i+1]);
      efferr=htemp->GetBinError(1);
      effmean=htemp->GetBinContent(1);
      cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
      if (dotables) print(intable_pt,outtable_pt,binmin,binmax,eff0,efferr);
      delete htemp;
   }

   if (YS==0||YS==4)
   {
      NPTNS=NPT1S; ptbins_NS=ptbins_1S;
      outtable_pt << "\\hline" << endl;
      skip_lines(intable_pt,1);// \hline

      for (unsigned int i=0; i<NPT1S; i++)
      {
         // cout << setprecision(3)<<fixed << Form("name==\"%s\"&&binlow==%f&&binhigh==%f",var.Data(),ptbins_1S[i],ptbins_1S[i+1]) << endl;
         tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),ptbins_1S[i],ptbins_1S[i+1]),"PROFs");
         htemp = (TProfile*) gDirectory->Get("htemp");
         binmin=ptbins_NS[i];
         binmax=ptbins_NS[i+1];
         eff0=firsteff(tr,var.Data(),ptbins_NS[i],ptbins_NS[i+1]);
         efferr=htemp->GetBinError(1);
         effmean=htemp->GetBinContent(1);
         cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
         if (dotables) print(intable_pt,outtable_pt,binmin,binmax,eff0,efferr);
         delete htemp;
      }
   }

   var = TString("rapidity_SF");
   tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),rapbins_NS[0],rapbins_NS[NRAPNS]),"PROFs");
   htemp = (TProfile*) gDirectory->Get("htemp");
   binmin=rapbins_NS[0];
   binmax=rapbins_NS[NRAPNS];
   eff0=firsteff(tr,var.Data(),rapbins_NS[0],rapbins_NS[NRAPNS]);
   efferr=htemp->GetBinError(1);
   effmean=htemp->GetBinContent(1);
   cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
   delete htemp;

   if (YS==0||YS==4)
   {
      NRAPNS=NRAP2S; rapbins_NS=rapbins_2S;
   }
   for (unsigned int i=0; i<NRAPNS; i++)
   {
      // cout << setprecision(3)<<fixed << Form("name==\"%s\"&&binlow==%f&&binhigh==%f",var.Data(),rapbins_NS[i],rapbins_NS[i+1]) << endl;
      tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),rapbins_NS[i],rapbins_NS[i+1]),"PROFs");
      htemp = (TProfile*) gDirectory->Get("htemp");
      binmin=rapbins_NS[i];
      binmax=rapbins_NS[i+1];
      eff0=firsteff(tr,var.Data(),rapbins_NS[i],rapbins_NS[i+1]);
      efferr=htemp->GetBinError(1);
      effmean=htemp->GetBinContent(1);
      cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
      if (dotables) print(intable_rap,outtable_rap,binmin,binmax,eff0,efferr);
      delete htemp;
   }

   if (YS==0||YS==4)
   {
      outtable_rap << "\\hline" << endl;
      skip_lines(intable_rap,1);// \hline
      NRAPNS=NRAP1S; rapbins_NS=rapbins_1S;
      for (unsigned int i=0; i<NRAPNS; i++)
      {
         // cout << setprecision(3)<<fixed << Form("name==\"%s\"&&binlow==%f&&binhigh==%f",var.Data(),rapbins_NS[i],rapbins_NS[i+1]) << endl;
         tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),rapbins_NS[i],rapbins_NS[i+1]),"PROFs");
         htemp = (TProfile*) gDirectory->Get("htemp");
         binmin=rapbins_NS[i];
         binmax=rapbins_NS[i+1];
         eff0=firsteff(tr,var.Data(),rapbins_NS[i],rapbins_NS[i+1]);
         efferr=htemp->GetBinError(1);
         effmean=htemp->GetBinContent(1);
         cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
         if (dotables) print(intable_rap,outtable_rap,binmin,binmax,eff0,efferr);
         delete htemp;
      }
   }

   if (!docentrality) return;

   var = TString("centrality_SF");
   tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),centbins_NS[0]*2.5,centbins_NS[NCENTNS]*2.5),"PROFs");
   htemp = (TProfile*) gDirectory->Get("htemp");
   binmin=centbins_NS[0]*2.5;
   binmax=centbins_NS[NCENTNS]*2.5;
   eff0=firsteff(tr,var.Data(),centbins_NS[0]*2.5,centbins_NS[NCENTNS]*2.5);
   efferr=htemp->GetBinError(1);
   effmean=htemp->GetBinContent(1);
   cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
   delete htemp;

   if (YS==0)
   {
      NCENTNS=NCENT2S; centbins_NS=centbins_2S;
   }
   else if (YS==4)
   {
      NCENTNS=NCENT1S; centbins_NS=centbins_1S;
   }
   for (unsigned int i=0; i<NCENTNS; i++)
   {
      // cout << setprecision(3)<<fixed << Form("name==\"%s\"&&binlow==%f&&binhigh==%f",var.Data(),centbins_NS[i],centbins_NS[i+1]) << endl;
      tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),centbins_NS[i]*2.5,centbins_NS[i+1]*2.5),"PROFs");
      htemp = (TProfile*) gDirectory->Get("htemp");
      binmin=centbins_NS[i]*2.5;
      binmax=centbins_NS[i+1]*2.5;
      eff0=firsteff(tr,var.Data(),centbins_NS[i]*2.5,centbins_NS[i+1]*2.5);
      efferr=htemp->GetBinError(1);
      effmean=htemp->GetBinContent(1);
      cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
      if (dotables) print(intable_cent,outtable_cent,binmin,binmax,eff0,efferr);
      delete htemp;
   }
   if (YS==0)
   {
      NCENTNS=NCENT1S; centbins_NS=centbins_1S;
      outtable_cent << "\\hline" << endl;
      skip_lines(intable_cent,1);// \hline
      for (unsigned int i=0; i<NCENTNS; i++)
      {
         // cout << setprecision(3)<<fixed << Form("name==\"%s\"&&binlow==%f&&binhigh==%f",var.Data(),centbins_NS[i],centbins_NS[i+1]) << endl;
         tr->Draw("eff:1>>htemp(1,0,2)",Form("name==\"%s\"&&abs(binlow-%f)<.1&&abs(binhigh-%f)<.1",var.Data(),centbins_NS[i]*2.5,centbins_NS[i+1]*2.5),"PROFs");
         htemp = (TProfile*) gDirectory->Get("htemp");
         binmin=centbins_NS[i]*2.5;
         binmax=centbins_NS[i+1]*2.5;
         eff0=firsteff(tr,var.Data(),centbins_NS[i]*2.5,centbins_NS[i+1]*2.5);
         efferr=htemp->GetBinError(1);
         effmean=htemp->GetBinContent(1);
         cout << setprecision(3)<<fixed << var << " " << binmin << " " << binmax << " " << eff0 << " " << efferr << " " << effmean << endl;
         if (dotables) print(intable_cent,outtable_cent,binmin,binmax,eff0,efferr);
         delete htemp;
      }
   }

   f->Write();
   f->Close();
}