void plot_pll(TString fname="monoh_withsm_SRCR_bg11.7_bgslop-0.0_nsig0.0.root")
{
  SetAtlasStyle();



  TFile* file =  TFile::Open(fname);
  RooWorkspace* wspace = (RooWorkspace*) file->Get("wspace");

  cout << "\n\ncheck that eff and reco terms included in BSM component to make fiducial cross-section" <<endl;
  wspace->function("nsig")->Print();
  RooRealVar* reco = wspace->var("reco");
  if(  wspace->function("nsig")->dependsOn(*reco) ) {
    cout << "all good." <<endl;
  } else {
    cout << "need to rerun fit_withsm using DO_FIDUCIAL_LIMIT true" <<endl;
    return;
  }

  /*
  // DANGER
  // TEST WITH EXAGGERATED UNCERTAINTY
  wspace->var("unc_theory")->setMax(1);
  wspace->var("unc_theory")->setVal(1);
  wspace->var("unc_theory")->Print();
  */

  // this was for making plot about decoupling/recoupling approach
  TCanvas* tc = new TCanvas("tc","",400,400);
  RooPlot *frame = wspace->var("xsec_bsm")->frame();
  RooAbsPdf* pdfc = wspace->pdf("jointModeld");
  RooAbsData* data = wspace->data("data");
  RooAbsReal *nllJoint = pdfc->createNLL(*data, RooFit::Constrained()); // slice with fixed xsec_bsm
  RooAbsReal *profileJoint = nllJoint->createProfile(*wspace->var("xsec_bsm"));

  wspace->allVars().Print("v");
  pdfc->fitTo(*data);
  wspace->allVars().Print("v");
  wspace->var("xsec_bsm")->Print();
  double nllmin = 2*nllJoint->getVal();
  wspace->var("xsec_bsm")->setVal(0);
  double nll0 = 2*nllJoint->getVal();
  cout << Form("nllmin = %f, nll0 = %f, Z=%f", nllmin, nll0, sqrt(nll0-nllmin)) << endl;
  nllJoint->plotOn(frame, RooFit::LineColor(kGreen), RooFit::LineStyle(kDotted), RooFit::ShiftToZero(), RooFit::Name("nll_statonly")); // no error
  profileJoint->plotOn(frame,RooFit::Name("pll") );
  wspace->var("xsec_sm")->Print();
  wspace->var("theory")->Print();
  wspace->var("theory")->setConstant();
  profileJoint->plotOn(frame, RooFit::LineColor(kRed), RooFit::LineStyle(kDashed), RooFit::Name("pll_smfixed") );

  frame->GetXaxis()->SetTitle("#sigma_{BSM, fid} [fb]");
  frame->GetYaxis()->SetTitle("-log #lambda  ( #sigma_{BSM, fid} )");
  double temp = frame->GetYaxis()->GetTitleOffset();
  frame->GetYaxis()->SetTitleOffset( 1.1* temp );

  frame->SetMinimum(1e-7);
  frame->SetMaximum(4);


  // Legend
  double x1,y1,x2,y2;
  GetX1Y1X2Y2(tc,x1,y1,x2,y2);
  TLegend *legend_sr=FastLegend(x2-0.75,y2-0.3,x2-0.25,y2-0.5,0.045);
  legend_sr->AddEntry(frame->findObject("pll"),"with #sigma_{SM} uncertainty","L");
  legend_sr->AddEntry(frame->findObject("pll_smfixed"),"with #sigma_{SM} constant","L");
  legend_sr->AddEntry(frame->findObject("nll_statonly"),"no systematics","L");
  frame->Draw();
  legend_sr->Draw("SAME");



  // descriptive text
  vector<TString> pavetext11;
  pavetext11.push_back("#bf{#it{ATLAS Internal}}");
  pavetext11.push_back("#sqrt{#it{s}} = 8 TeV #scale[0.6]{#int}Ldt = 20.3 fb^{-1}");
  pavetext11.push_back("#it{H}+#it{E}_{T}^{miss} , #it{H #rightarrow #gamma#gamma}, #it{m}_{#it{H}} = 125.4 GeV");

  TPaveText* text11=CreatePaveText(x2-0.75,y2-0.25,x2-0.25,y2-0.05,pavetext11,0.045);
  text11->Draw();

  tc->SaveAs("pll.pdf");



  /*
  wspace->var("xsec_bsm")->setConstant(true);
  wspace->var("eff"     )->setConstant(true);
  wspace->var("mh"      )->setConstant(true);
  wspace->var("sigma_h" )->setConstant(true);
  wspace->var("lumi"    )->setConstant(true);
  wspace->var("xsec_sm" )->setVal(v_xsec_sm);
  wspace->var("eff"     )->setVal(1.0);
  wspace->var("lumi"    )->setVal(v_lumi);
  TH1* nllHist = profileJoint->createHistogram("xsec_bsm",100);
  TFile* out = new TFile("nllHist.root","REPLACE");
  nllHist->Write()
  out->Write();
  out->Close();
  */

}