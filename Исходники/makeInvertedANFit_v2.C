RooWorkspace* makeInvertedANFit(TTree* tree, float forceSigma=-1, bool constrainMu=false, float forceMu=-1) {
  RooWorkspace *ws = new RooWorkspace("ws","");

  std::vector< TString (*)(TString, RooRealVar&, RooWorkspace&) > bkgPdfList;
  bkgPdfList.push_back(makeSingleExp);
  bkgPdfList.push_back(makeDoubleExp);
#if DEBUG==0
  //bkgPdfList.push_back(makeTripleExp);
  bkgPdfList.push_back(makeModExp);
  bkgPdfList.push_back(makeSinglePow);
  bkgPdfList.push_back(makeDoublePow);
  bkgPdfList.push_back(makePoly2);
  bkgPdfList.push_back(makePoly3);
#endif



  RooRealVar mgg("mgg","m_{#gamma#gamma}",103,160,"GeV");
  mgg.setBins(38);

  mgg.setRange("sideband_low", 103,120);
  mgg.setRange("sideband_high",131,160);
  mgg.setRange("signal",120,131);

  RooRealVar MR("MR","",0,3000,"GeV");
  MR.setBins(60);
  
  RooRealVar Rsq("t1Rsq","",0,1,"GeV");
  Rsq.setBins(20);

  RooRealVar hem1_M("hem1_M","",-1,2000,"GeV");
  hem1_M.setBins(40);

  RooRealVar hem2_M("hem2_M","",-1,2000,"GeV");
  hem2_M.setBins(40);

  RooRealVar ptgg("ptgg","p_{T}^{#gamma#gamma}",0,500,"GeV");
  ptgg.setBins(50);

  RooDataSet data("data","",tree,RooArgSet(mgg,MR,Rsq,hem1_M,hem2_M,ptgg));

  RooDataSet* blind_data = (RooDataSet*)data.reduce("mgg<121 || mgg>130");

  std::vector<TString> tags;
  //fit many different background models
  for(auto func = bkgPdfList.begin(); func != bkgPdfList.end(); func++) {
    TString tag = (*func)("bonly",mgg,*ws);
    tags.push_back(tag);
    ws->pdf("bonly_"+tag+"_ext")->fitTo(data,RooFit::Strategy(0),RooFit::Extended(kTRUE),RooFit::Range("sideband_low,sideband_high"));
    RooFitResult* bres = ws->pdf("bonly_"+tag+"_ext")->fitTo(data,RooFit::Strategy(2),RooFit::Save(kTRUE),RooFit::Extended(kTRUE),RooFit::Range("sideband_low,sideband_high"));
    bres->SetName(tag+"_bonly_fitres");
    ws->import(*bres);

    //make blinded fit
    RooPlot *fmgg_b = mgg.frame();
    blind_data->plotOn(fmgg_b,RooFit::Range("sideband_low,sideband_high"));
    TBox blindBox(121,fmgg_b->GetMinimum()-(fmgg_b->GetMaximum()-fmgg_b->GetMinimum())*0.015,130,fmgg_b->GetMaximum());
    blindBox.SetFillColor(kGray);
    fmgg_b->addObject(&blindBox);
    ws->pdf("bonly_"+tag+"_ext")->plotOn(fmgg_b,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("sideband_low,sideband_high"));
    fmgg_b->SetName(tag+"_blinded_frame");
    ws->import(*fmgg_b);
    delete fmgg_b;
    

    //set all the parameters constant
    RooArgSet* vars = ws->pdf("bonly_"+tag)->getVariables();
    RooFIter iter = vars->fwdIterator();
    RooAbsArg* a;
    while( (a = iter.next()) ){
      if(string(a->GetName()).compare("mgg")==0) continue;
      static_cast<RooRealVar*>(a)->setConstant(kTRUE);
    }

    //make the background portion of the s+b fit
    (*func)("b",mgg,*ws);

    RooRealVar sigma(tag+"_s_sigma","",5,0,100);
    if(forceSigma!=-1) {
      sigma.setVal(forceSigma);
      sigma.setConstant(true);
    }
    RooRealVar mu(tag+"_s_mu","",126,120,132);
    if(forceMu!=-1) {
      mu.setVal(forceMu);
      mu.setConstant(true);
    }
    RooGaussian sig(tag+"_sig_model","",mgg,mu,sigma);
    RooRealVar Nsig(tag+"_sb_Ns","",5,0,100);
    RooRealVar Nbkg(tag+"_sb_Nb","",100,0,100000);
    

    RooRealVar HiggsMass("HiggsMass","",125.1);
    RooRealVar HiggsMassError("HiggsMassError","",0.24);
    RooGaussian HiggsMassConstraint("HiggsMassConstraint","",mu,HiggsMass,HiggsMassError);


    RooAddPdf fitModel(tag+"_sb_model","",RooArgList( *ws->pdf("b_"+tag), sig ),RooArgList(Nbkg,Nsig));

    RooFitResult* sbres;
    RooAbsReal* nll;
    if(constrainMu) {
      fitModel.fitTo(data,RooFit::Strategy(0),RooFit::Extended(kTRUE),RooFit::ExternalConstraints(RooArgSet(HiggsMassConstraint)));
      sbres = fitModel.fitTo(data,RooFit::Strategy(2),RooFit::Save(kTRUE),RooFit::Extended(kTRUE),RooFit::ExternalConstraints(RooArgSet(HiggsMassConstraint)));
      nll = fitModel.createNLL(data,RooFit::NumCPU(4),RooFit::Extended(kTRUE),RooFit::ExternalConstraints(RooArgSet(HiggsMassConstraint)));
    } else {
      fitModel.fitTo(data,RooFit::Strategy(0),RooFit::Extended(kTRUE));
      sbres = fitModel.fitTo(data,RooFit::Strategy(2),RooFit::Save(kTRUE),RooFit::Extended(kTRUE));
      nll = fitModel.createNLL(data,RooFit::NumCPU(4),RooFit::Extended(kTRUE));
    }
    sbres->SetName(tag+"_sb_fitres");
    ws->import(*sbres);
    ws->import(fitModel);

    RooPlot *fmgg = mgg.frame();
    data.plotOn(fmgg);
    fitModel.plotOn(fmgg);
    ws->pdf("b_"+tag+"_ext")->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
    fmgg->SetName(tag+"_frame");
    ws->import(*fmgg);
    delete fmgg;


    RooMinuit(*nll).migrad();

    RooPlot *fNs = Nsig.frame(0,25);
    fNs->SetName(tag+"_Nsig_pll");
    RooAbsReal *pll = nll->createProfile(Nsig);
    //nll->plotOn(fNs,RooFit::ShiftToZero(),RooFit::LineColor(kRed));
    pll->plotOn(fNs);
    ws->import(*fNs);

    delete fNs;

    RooPlot *fmu = mu.frame(125,132);
    fmu->SetName(tag+"_mu_pll");
    RooAbsReal *pll_mu = nll->createProfile(mu);
    pll_mu->plotOn(fmu);
    ws->import(*fmu);

    delete fmu;

  }

  RooArgSet weights("weights");
  RooArgSet pdfs_bonly("pdfs_bonly");
  RooArgSet pdfs_b("pdfs_b");

  RooRealVar minAIC("minAIC","",1E10);
  //compute AIC stuff
  for(auto t = tags.begin(); t!=tags.end(); t++) {
    RooAbsPdf *p_bonly = ws->pdf("bonly_"+*t);
    RooAbsPdf *p_b = ws->pdf("b_"+*t);
    RooFitResult *sb = (RooFitResult*)ws->obj(*t+"_bonly_fitres");
    RooRealVar k(*t+"_b_k","",p_bonly->getParameters(RooArgSet(mgg))->getSize());
    RooRealVar nll(*t+"_b_minNll","",sb->minNll());
    RooRealVar Npts(*t+"_b_N","",blind_data->sumEntries());
    RooFormulaVar AIC(*t+"_b_AIC","2*@0+2*@1+2*@1*(@1+1)/(@2-@1-1)",RooArgSet(nll,k,Npts));
    ws->import(AIC);
    if(AIC.getVal() < minAIC.getVal()) {
      minAIC.setVal(AIC.getVal());
    }
    //aicExpSum+=TMath::Exp(-0.5*AIC.getVal()); //we will need this precomputed  for the next step
    pdfs_bonly.add(*p_bonly);
    pdfs_b.add(*p_b);
  }
  ws->import(minAIC);
  //compute the AIC weight
  float aicExpSum=0;
  for(auto t = tags.begin(); t!=tags.end(); t++) {
    RooFormulaVar *AIC = (RooFormulaVar*)ws->obj(*t+"_b_AIC");
    aicExpSum+=TMath::Exp(-0.5*(AIC->getVal()-minAIC.getVal())); //we will need this precomputed  for the next step    
  }
  std::cout << "aicExpSum: " << aicExpSum << std::endl;

  for(auto t = tags.begin(); t!=tags.end(); t++) {
    RooFormulaVar *AIC = (RooFormulaVar*)ws->obj(*t+"_b_AIC");
    RooRealVar *AICw = new RooRealVar(*t+"_b_AICWeight","",TMath::Exp(-0.5*(AIC->getVal()-minAIC.getVal()))/aicExpSum);
    if( TMath::IsNaN(AICw->getVal()) ) {AICw->setVal(0);}
    ws->import(*AICw);
    std::cout << *t << ":  " << AIC->getVal()-minAIC.getVal() << "    " << AICw->getVal() << std::endl;
    weights.add(*AICw);
  }
  RooAddPdf bonly_AIC("bonly_AIC","",pdfs_bonly,weights);
  RooAddPdf b_AIC("b_AIC","",pdfs_b,weights);

  //b_AIC.fitTo(data,RooFit::Strategy(0),RooFit::Extended(kTRUE),RooFit::Range("sideband_low,sideband_high"));
  //RooFitResult* bres = b_AIC.fitTo(data,RooFit::Strategy(2),RooFit::Save(kTRUE),RooFit::Extended(kTRUE),RooFit::Range("sideband_low,sideband_high"));
  //bres->SetName("AIC_b_fitres");
  //ws->import(*bres);

  //make blinded fit
  RooPlot *fmgg_b = mgg.frame(RooFit::Range("sideband_low,sideband_high"));
  blind_data->plotOn(fmgg_b,RooFit::Range("sideband_low,sideband_high"));
  TBox blindBox(121,fmgg_b->GetMinimum()-(fmgg_b->GetMaximum()-fmgg_b->GetMinimum())*0.015,130,fmgg_b->GetMaximum());
  blindBox.SetFillColor(kGray);
  fmgg_b->addObject(&blindBox);
  bonly_AIC.plotOn(fmgg_b,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("sideband_low,sideband_high"));
  fmgg_b->SetName("AIC_blinded_frame");
  ws->import(*fmgg_b);
  delete fmgg_b;
    
#if 1

  RooRealVar sigma("AIC_s_sigma","",5,0,100);
  if(forceSigma!=-1) {
    sigma.setVal(forceSigma);
    sigma.setConstant(true);
  }
  RooRealVar mu("AIC_s_mu","",126,120,132);
  if(forceMu!=-1) {
    mu.setVal(forceMu);
    mu.setConstant(true);
  }
  RooGaussian sig("AIC_sig_model","",mgg,mu,sigma);
  RooRealVar Nsig("AIC_sb_Ns","",5,0,100);
  RooRealVar Nbkg("AIC_sb_Nb","",100,0,100000);
  
  
  RooRealVar HiggsMass("HiggsMass","",125.1);
  RooRealVar HiggsMassError("HiggsMassError","",0.24);
  RooGaussian HiggsMassConstraint("HiggsMassConstraint","",mu,HiggsMass,HiggsMassError);
  
  
  RooAddPdf fitModel("AIC_sb_model","",RooArgList( b_AIC, sig ),RooArgList(Nbkg,Nsig));

  RooFitResult* sbres;
  RooAbsReal *nll;

  if(constrainMu) {
    fitModel.fitTo(data,RooFit::Strategy(0),RooFit::Extended(kTRUE),RooFit::ExternalConstraints(RooArgSet(HiggsMassConstraint)));
    sbres = fitModel.fitTo(data,RooFit::Strategy(2),RooFit::Save(kTRUE),RooFit::Extended(kTRUE),RooFit::ExternalConstraints(RooArgSet(HiggsMassConstraint)));
    nll = fitModel.createNLL(data,RooFit::NumCPU(4),RooFit::Extended(kTRUE),RooFit::ExternalConstraints(RooArgSet(HiggsMassConstraint)));
  } else {
    fitModel.fitTo(data,RooFit::Strategy(0),RooFit::Extended(kTRUE));
    sbres = fitModel.fitTo(data,RooFit::Strategy(2),RooFit::Save(kTRUE),RooFit::Extended(kTRUE));
    nll = fitModel.createNLL(data,RooFit::NumCPU(4),RooFit::Extended(kTRUE));
  }

  assert(nll!=0);
  
  sbres->SetName("AIC_sb_fitres");
  ws->import(*sbres);
  ws->import(fitModel);
  
  RooPlot *fmgg = mgg.frame();
  data.plotOn(fmgg);
  fitModel.plotOn(fmgg);
  ws->pdf("b_AIC")->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
  fmgg->SetName("AIC_frame");
  ws->import(*fmgg);
  delete fmgg;

  RooMinuit(*nll).migrad();
  
  RooPlot *fNs = Nsig.frame(0,25);
  fNs->SetName("AIC_Nsig_pll");
  RooAbsReal *pll = nll->createProfile(Nsig);
  //nll->plotOn(fNs,RooFit::ShiftToZero(),RooFit::LineColor(kRed));
  pll->plotOn(fNs);
  ws->import(*fNs);
  delete fNs;


  RooPlot *fmu = mu.frame(125,132);
  fmu->SetName("AIC_mu_pll");
  RooAbsReal *pll_mu = nll->createProfile(mu);
  pll_mu->plotOn(fmu);
  ws->import(*fmu);

  delete fmu;

  std::cout << "min AIC: " << minAIC.getVal() << std::endl;
  for(auto t = tags.begin(); t!=tags.end(); t++) {
    RooFormulaVar *AIC = (RooFormulaVar*)ws->obj(*t+"_b_AIC");
    RooRealVar *AICw = ws->var(*t+"_b_AICWeight");
    RooRealVar* k = ws->var(*t+"_b_k");
    printf("%s & %0.0f & %0.2f & %0.2f \\\\\n",t->Data(),k->getVal(),AIC->getVal()-minAIC.getVal(),AICw->getVal());
    //std::cout << k->getVal() << " " << AIC->getVal()-minAIC.getVal() << " " << AICw->getVal() << std::endl;
  }
#endif
  return ws;
}