void plotxsec_CommonBins(seq_t seq/*=ACC_CORR*/, bool sim/*=kFALSE*/, int Q2Wbin/*=0*/){
  if (setup("vm")==kFALSE) return;

  //! Stats. Box option for this function
  if (Q2Wbin>0) gStyle->SetOptStat("nemMrRi");
  else          gStyle->SetOptStat(0);
  
  //!sim or data
  TFile* fy[5];
  if (sim) memcpy(fy,_fysim,sizeof(_fysim));
  else     memcpy(fy,_fyexp,sizeof(_fyexp));
 
  //!data objects for 5D yields for each Top
  THnSparse* hY5D[nTOP];

  //![Q2,W] binning information
  TString wbng   = _q2w_bng.Tokenize("__")->At(1)->GetName();
  TString nwbins = wbng.Tokenize("-")->At(0)->GetName();
  TString wmin   = wbng.Tokenize("-")->At(1)->GetName();
  TString wmax   = wbng.Tokenize("-")->At(2)->GetName();

  //! Some constants needed to define good variable names
  //! Yield(all-bins)= Yield(com-bins) + Yield(noncom-bins)
  const int kNumBinGrps = 3;
  enum BinGrps {kAll=0,kCom=1,kNonCom=2};
  TString bingrp_name[kNumBinGrps] ={"all_bins","com_bins","noncom_bins"};
  TString bingrp_title[kNumBinGrps]={"All Bins", "Common Bins", "NonCommon Bins"};

  //! Per Q2W bin: Data Objects for Yield vs W for each Top and each BinGrp therein
  TH1F* hYvW[nTOP][kNumBinGrps];
  
  TLegend* leg[kNumBinGrps];
  for (int ibingrp=0;ibingrp<kNumBinGrps;ibingrp++){
      leg[ibingrp] = new TLegend(0.1,0.7,0.5,0.9);
      leg[ibingrp]->SetHeader(TString::Format("%s Yield(%s)", seqTitle[seq].Data(), bingrp_title[ibingrp].Data()));
  }

  for(int iTop=0;iTop<nTOP;iTop++){
    for (int ibingrp=0;ibingrp<kNumBinGrps;ibingrp++){
      //TString hname = TString::Format("hYvW_%d_%s",iTop+1,bingrp_name[ibingrp].Data());
      //TString hname = TString::Format("hYvW_%s",bingrp_name[ibingrp].Data());
      TString hname = TString::Format("hYvW");
      TString htitle = hname;
      hYvW[iTop][ibingrp] = new TH1F(hname,htitle, nwbins.Atoi(), wmin.Atof(), wmax.Atof());
      hYvW[iTop][ibingrp]->SetXTitle("W[GeV]");
      hYvW[iTop][ibingrp]->SetMarkerStyle(20+iTop); //+5
      hYvW[iTop][ibingrp]->SetMarkerColor(2+iTop);
      leg[ibingrp]->AddEntry( hYvW[iTop][ibingrp], TString::Format("%s", _topNames[iTop].Data()) );
    }
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
    for(int iTop=0;iTop<nTOP;iTop++){
      hY5D[iTop] = (THnSparse*)fy[iTop]->Get(hname);
    }

    //! Reset Data structures 
    float    intg_hY5D[nTOP][kNumBinGrps] = {0.0};
    float intgErr_hY5D[nTOP][kNumBinGrps] = {0.0};
    
    myTHnTool hntool(kFALSE);

    //!F1. Get integral over all bins
    //printf("Integral over all bins\n");
    for(int iTop=0;iTop<nTOP;iTop++){
      if (iTop==2 || iTop==3) continue; //not doing for now
      hntool.GetIntegral(hY5D[iTop], intg_hY5D[iTop][kAll], intgErr_hY5D[iTop][kAll]);
      //printf("Top%d = %f\n",iTop+1,intg_hY5D[iTop][kAll]);
    }

    //!2. Get integral over only common-bins
    //NOTE, in hntool.GetIntegralCommonBins(), currently, hY5D[2] & hY5D[3] are not considered
    int num_combins = hntool.GetIntegralCommonBins(
                  hY5D[0],              hY5D[1],              hY5D[2],              hY5D[3],
             intg_hY5D[0][kCom],   intg_hY5D[1][kCom],   intg_hY5D[2][kCom],   intg_hY5D[3][kCom],
          intgErr_hY5D[0][kCom],intgErr_hY5D[1][kCom],intgErr_hY5D[2][kCom],intgErr_hY5D[3][kCom],
          draw);
    printf("Number of common bins for q2w bin %s = %d\n", Q2Wdirname.Data(), num_combins);
    
    //!2. Get integral over non-common-bins
    for(int iTop=0;iTop<nTOP;iTop++){
      if (iTop==2 || iTop==3) continue; //not doing for now
      intg_hY5D[iTop][kNonCom] = intg_hY5D[iTop][kAll] - intg_hY5D[iTop][kCom];
      intgErr_hY5D[iTop][kNonCom] = TMath::Sqrt(TMath::Power(intgErr_hY5D[iTop][kAll],2)+
                                                TMath::Power(intgErr_hY5D[iTop][kCom],2));
    }

    //! Now fill Histogram Objects
    for(int iTop=0;iTop<nTOP;iTop++){
      if (iTop==2 || iTop==3) continue; //not doing for now
      for (int ibingrp=0; ibingrp<kNumBinGrps;ibingrp++){
        hYvW[iTop][ibingrp]->SetBinContent(hYvW[iTop][ibingrp]->FindBin(w+.005), intg_hY5D[iTop][ibingrp]); //+5Mev = _instrinsic.Wbinw
        hYvW[iTop][ibingrp]->  SetBinError(hYvW[iTop][ibingrp]->FindBin(w+.005), intgErr_hY5D[iTop][ibingrp]); //+5Mev = _instrinsic.Wbinw
      }
    }
  }

  //!Now Draw the Histogram Objects
  TString cname = TString::Format("%s Yield Analysis", seqTitle[seq].Data());
  TCanvas* cy = new TCanvas(cname, cname);
  cy->Divide(kNumBinGrps,1);
  for(int iTop=0;iTop<nTOP;iTop++){
    if (iTop==2 || iTop==3) continue; //not doing for now
    for (int ibingrp=0; ibingrp<kNumBinGrps;ibingrp++){
      cy->cd(ibingrp+1);
      if (iTop==0) {
        if (seq==HOLE) {
          gPad->SetLogy();
          hYvW[iTop][ibingrp]->SetMinimum(.0001);
        }else{
          hYvW[iTop][ibingrp]->SetMinimum(0);
          //set max of histograms as per [Top=2][kAll]
          float max_t1 = hYvW[0][kAll]->GetBinContent(hYvW[0][kAll]->GetMaximumBin()) + 100;
          float max_t2 = hYvW[1][kAll]->GetBinContent(hYvW[1][kAll]->GetMaximumBin()) + 100;
          if (max_t2>max_t1) hYvW[iTop][ibingrp]->SetMaximum(max_t2);
          //printf("max_t2 = %f\n",max_t2);
        }
        hYvW[iTop][ibingrp]->Draw("p");
      }else {
        hYvW[iTop][ibingrp]->Draw("p sames");
      }
    }
  }
  //!Finally draw the Legend
  for (int ibingrp=0; ibingrp<kNumBinGrps;ibingrp++){
    cy->cd(ibingrp+1);
    leg[ibingrp]->Draw("same");
  }
}