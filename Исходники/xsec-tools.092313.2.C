void plotxsec_CommonBins(seq_t seq/*=ACC_CORR*/, bool sim/*=kFALSE*/, int Q2Wbin/*=0*/){
  if (setup("vm")==kFALSE) return;

  gStyle->SetOptStat("nemMrRi");

  //sim or data
  TFile* fy[5];
  if (sim) memcpy(fy,_fysim,sizeof(_fysim));
  else     memcpy(fy,_fyexp,sizeof(_fyexp));
 
  //data objects for 5D yields for each Top
  int nTops=4;
  THnSparse* hY5D[nTops];

  //data object yield vs W for each top (com- and noncom-bins seperated)
  TH1F* hYW_combins[nTops];
  TLegend* l_combins = new TLegend(0.1,0.7,0.5,0.9);
  l_combins->SetHeader("Yield - 5D Method(Common Bins)");

  TH1F* hYW_noncombins[nTops];
  TLegend* l_noncombins = new TLegend(0.1,0.7,0.5,0.9);
  l_noncombins->SetHeader("Yield - 5D Method(NonCommon Bins)");

  TH1F* hYW_allbins[nTops];
  TLegend* l_allbins = new TLegend(0.1,0.7,0.5,0.9);
  l_allbins->SetHeader("Yield - 5D Method(All Bins)");

  TString wbng   = _q2w_bng.Tokenize("__")->At(1)->GetName();
  TString nwbins = wbng.Tokenize("-")->At(0)->GetName();
  TString wmin   = wbng.Tokenize("-")->At(1)->GetName();
  TString wmax   = wbng.Tokenize("-")->At(2)->GetName();
  for(int iTop=0;iTop<nTops;iTop++){
    hYW_combins[iTop] = new TH1F(TString::Format("hYW_combins_%d",iTop+1),TString::Format("hYW_combins_%d",iTop+1), nwbins.Atoi(), wmin.Atof(), wmax.Atof());
    hYW_combins[iTop]->SetXTitle("W[GeV]");
    hYW_combins[iTop]->SetMarkerStyle(20+iTop); //+5
    hYW_combins[iTop]->SetMarkerColor(2+iTop);
    l_combins->AddEntry( hYW_combins[iTop], TString::Format("%s", _topNames[iTop].Data()) );

    hYW_noncombins[iTop] = new TH1F(TString::Format("hYW_noncombins_%d",iTop+1),TString::Format("hYW_noncombins_%d",iTop+1), nwbins.Atoi(), wmin.Atof(), wmax.Atof());
    hYW_noncombins[iTop]->SetXTitle("W[GeV]");
    hYW_noncombins[iTop]->SetMarkerStyle(20+iTop); //+5
    hYW_noncombins[iTop]->SetMarkerColor(2+iTop);
    l_noncombins->AddEntry( hYW_noncombins[iTop], TString::Format("%s", _topNames[iTop].Data()) );

    hYW_allbins[iTop] = new TH1F(TString::Format("hYW_allbins_%d",iTop+1),TString::Format("hYW_allbins_%d",iTop+1), nwbins.Atoi(), wmin.Atof(), wmax.Atof());
    hYW_allbins[iTop]->SetXTitle("W[GeV]");
    hYW_allbins[iTop]->SetMarkerStyle(20+iTop); //+5
    hYW_allbins[iTop]->SetMarkerColor(2+iTop);
    l_allbins->AddEntry( hYW_allbins[iTop], TString::Format("%s", _topNames[iTop].Data()) );
  }

  //!Loop over Q2W dirs, get h5Ds and their yields only common bins!
  TIter nextkey(fy[0]->GetListOfKeys());
  TKey *key;
  int counterQ2Wbin=0;
  bool draw=kFALSE;
  if (Q2Wbin>0) draw=kTRUE;

  while (key = (TKey*)nextkey()) {
    TString Q2Wdirname = key->GetName();
    if(Q2Wdirname.EqualTo("hYW_Dir") || Q2Wdirname.EqualTo("hYW"))continue;
    printf("Processing %s\n", Q2Wdirname.Data());
    counterQ2Wbin+=1;
    
    //!if Q2Wbin option > 0, then process only the specified Q2Wbin
    if (Q2Wbin>0 && (counterQ2Wbin != Q2Wbin)) continue; 

    TString wrange = Q2Wdirname.Tokenize("_")->At(1)->GetName();
    TString wlow = wrange.Tokenize(",")->At(0)->GetName();
    wlow.Remove(0,1); //remove "["
    double w = wlow.Atof();
      
    char hname[200];                 
    sprintf(hname, "%s/hY5D/Varset1/hY5D_%s", Q2Wdirname.Data(), seqTitle[seq].Data());
    for(int iTop=0;iTop<nTops;iTop++){
      hY5D[iTop] = (THnSparse*)fy[iTop]->Get(hname);
    }

    float intg_allbins_hY5D[nTops];
    float intgErr_allbins_hY5D[nTops];
    float intg_combins_hY5D[nTops];
    float intgErr_combins_hY5D[nTops];
    float intg_noncombins_hY5D[nTops];
    float intgErr_noncombins_hY5D[nTops];
    
    myTHnTool hntool(kFALSE);
    //!First get integral over all bins
    for(int iTop=0;iTop<nTops;iTop++){
      if (iTop==2 || iTop==3) continue; //not doing for now
      hntool.GetIntegral(hY5D[iTop], intg_allbins_hY5D[iTop], intgErr_allbins_hY5D[iTop]);
    }
    //!Now get integral over only common-bins
    int nComBins = hntool.GetIntegralCommonBins(hY5D[0],hY5D[1],hY5D[2],hY5D[3],
          intg_combins_hY5D[0],intg_combins_hY5D[1],intg_combins_hY5D[2],intg_combins_hY5D[3],
          intgErr_combins_hY5D[0],intgErr_combins_hY5D[1],intgErr_combins_hY5D[2],intgErr_combins_hY5D[3],
          draw);
    printf("Number of common bins for q2w bin %s = %d\n", Q2Wdirname.Data(), nComBins);
    //printf("intgs =  %.2f,%.2f,%.2f,%.2f\n",intg_hY5D[0],intg_hY5D[1],intg_hY5D[2],intg_hY5D[3]);
    //printf("intgs Errors =  %.2f,%.2f,%.2f,%.2f\n",intgErr_hY5D[0],intgErr_hY5D[1],intgErr_hY5D[2],intgErr_hY5D[3]);
    //! Now get integral over non-common-bins
    for(int iTop=0;iTop<nTops;iTop++){
      if (iTop==2 || iTop==3) continue; //not doing for now
      intg_noncombins_hY5D[iTop] = intg_allbins_hY5D[iTop] - intg_combins_hY5D[iTop];
      intgErr_noncombins_hY5D[iTop] = TMath::Sqrt(TMath::Power(intgErr_allbins_hY5D[iTop],2)+TMath::Power(intgErr_combins_hY5D[iTop],2));
    }


    for(int iTop=0;iTop<nTops;iTop++){
      hYW_allbins[iTop]->SetBinContent(hYW_allbins[iTop]->FindBin(w+.005), intg_allbins_hY5D[iTop]); //+5Mev = _instrinsic.Wbinw
      hYW_allbins[iTop]->  SetBinError(hYW_allbins[iTop]->FindBin(w+.005), intgErr_allbins_hY5D[iTop]); //+5Mev = _instrinsic.Wbinw
      hYW_combins[iTop]->SetBinContent(hYW_combins[iTop]->FindBin(w+.005), intg_combins_hY5D[iTop]); //+5Mev = _instrinsic.Wbinw
      hYW_combins[iTop]->  SetBinError(hYW_combins[iTop]->FindBin(w+.005), intgErr_combins_hY5D[iTop]); //+5Mev = _instrinsic.Wbinw
      hYW_noncombins[iTop]->SetBinContent(hYW_noncombins[iTop]->FindBin(w+.005), intg_noncombins_hY5D[iTop]); //+5Mev = _instrinsic.Wbinw
      hYW_noncombins[iTop]->  SetBinError(hYW_noncombins[iTop]->FindBin(w+.005), intgErr_noncombins_hY5D[iTop]); //+5Mev = _instrinsic.Wbinw
    }
  }
  TCanvas* cy = new TCanvas();
  cy->Divide(3,1);
  //if (seq==HOLE) cy->SetLogy();
  for(int iTop=0;iTop<nTops;iTop++){
    if (iTop==0) {
      //if (seq==HOLE) hYW_combins[iTop]->SetMinimum(1);
      cy->cd(1);
      if (seq==HOLE) {
        gPad->SetLogy();
        hYW_combins[iTop]->SetMinimum(1);
      }
      hYW_combins[iTop]->Draw("p");
      cy->cd(2);
      if (seq==HOLE) {
        gPad->SetLogy();
        hYW_noncombins[iTop]->SetMinimum(1);
      }
      hYW_noncombins[iTop]->Draw("p");
      cy->cd(3);
      if (seq==HOLE) {
        gPad->SetLogy();
        hYW_allbins[iTop]->SetMinimum(1);
      }
      hYW_allbins[iTop]->Draw("p");
    }else {
      cy->cd(1);
      hYW_combins[iTop]->Draw("p sames");
      cy->cd(2);
      hYW_noncombins[iTop]->Draw("p sames");
      cy->cd(3);
      hYW_allbins[iTop]->Draw("p sames");

    }
  }
  cy->cd(1);
  l_combins->Draw("same");
  cy->cd(2);
  l_noncombins->Draw("same");
  cy->cd(3);
  l_allbins->Draw("same");

}