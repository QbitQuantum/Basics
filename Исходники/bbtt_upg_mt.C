void bbtt_upg_mt(std::string var,int nbins, double xmin, double xmax,std::string xtitle, std::string ytitle, double sigscale=1,int hist=1)
{
  double massLEdges[14]    = {-0.5,-0.45,-0.4,-0.35,-0.3,-0.25,-0.2,-0.15,-0.1,-0.05,0.0,0.05,0.1,0.2};
  TFile *outDC = new TFile("hh_mt_inputs.root","RECREATE");

  //SetStyle(); gStyle->SetLineStyleString(11,"20 10");
  setTDRStyle();
  TH1::SetDefaultSumw2(1);

  std::string dir = "/data/blue/Bacon/029a/Upgrade/sep-2-bbtt/";
  
  std::stringstream scale; scale << sigscale;
  
  //Cut definitions
  double luminosity = 3000;
  std::stringstream lumi; lumi << luminosity;
  std::string objcut = "(tauCat1==1 && tauCat2==3 && ptTau1>30 && ptTau2>30 && (bTag1==2||bTag1==3||bTag1==6||bTag1==7) && (bTag2==2||bTag2==3||bTag2==6||bTag2==7) && ptB1>30 && ptB2>30)*(abs(etaB1)<2.5 && abs(etaB2)<2.5 && abs(etaTau1)<2.1 && abs(etaTau2)<2.5 && ptTrk1>0)";//*(tauIso2<0.15)";

  std::string jetcut = objcut+"*(m_svpileup>100 && m_svpileup<150 && mBB1>90 && mBB1<130 && mt2pileup>100)";
  //std::string jetcut = objcut+"*(m_svpileup>100 && m_svpileup<150 && mBB1>90 && mBB1<130)";
  //std::string jetcut = objcut+"*(1.0)";

  //signal region
  std::string mccut = jetcut+"*eventWeight*"+lumi.str();
  std::string sigcut = jetcut+"*eventWeight*"+lumi.str();
  std::string zjetcut = jetcut+"*eventWeight*(eventType!=3&&eventType!=1)*"+lumi.str();
  std::string wjetcut = jetcut+"*eventWeight*(eventType==3&&eventType!=1)*"+lumi.str();
  std::string ewkcut = jetcut+"*eventWeight*(eventType!=1)*"+lumi.str();
  std::string vbfcut = jetcut+"*eventWeight*49470*0.0632*"+lumi.str();
  
  //--------------------------------------------------------------------------
  
  //Get the trees
  TTree *hhtree = load(dir+"gFHHTobbtautau.root");
  TTree *hhtree_m1 = load(dir+"gFHHTobbtautaulam1m.root");
  TTree *hhtree_m5 = load(dir+"gFHHTobbtautaulam5m.root");
  TTree *hhtree_0 = load(dir+"gFHHTobbtautaulam0.root");
  TTree *hhtree_p5 = load(dir+"gFHHTobbtautaulam5p.root");
  TTree *hhtree_vbf = load("/data/blue/Bacon/029a/Upgrade/sep-10-bbtt/vbfHHTobbtautau.root");
  TTree *tttree = load(dir+"tt.root");
  TTree *vbfhtree = load(dir+"VBFHToTauTau.root");
  TTree *gfhtree = load(dir+"ggFHToTauTau.root");
  TTree *assohtree = load(dir+"vH_ttH.root");
  TTree *vjettree = load(dir+"Bjets.root");
  TTree *ewktree = load(dir+"ewk.root");
  
  //-------------------------------------------------------------------------
  
  //Get histograms
  TCanvas *canv0 = MakeCanvas("canv", "histograms", 600, 600);
  canv0->cd();
  std::string vardraw;
  TH1F *Ztt;
  if(hist)
    Ztt = new TH1F("DY","",nbins,xmin,xmax);
  else 
    Ztt = new TH1F("DY","",13, massLEdges);
  vardraw = var+">>"+"DY";
  vjettree->Draw(vardraw.c_str(),zjetcut.c_str());
  InitHist(Ztt  , xtitle.c_str(), ytitle.c_str(), TColor::GetColor(248,206,104), 1001);
  TH1F *ttbar;
  if(hist)
    ttbar = new TH1F("TTbar","",nbins,xmin,xmax);
  else 
    ttbar = new TH1F("TTbar","",13, massLEdges);
  vardraw = var+">>"+"TTbar";
  tttree->Draw(vardraw.c_str(),mccut.c_str());
  InitHist(ttbar, xtitle.c_str(), ytitle.c_str(), TColor::GetColor(155,152,204), 1001);
  TH1F *wjets;
  if(hist)
    wjets= new TH1F("Wjets","",nbins,xmin,xmax);
  else
    wjets = new TH1F("Wjets","",13, massLEdges);
  vardraw = var+">>"+"Wjets";
  vjettree->Draw(vardraw.c_str(),wjetcut.c_str());
  InitHist(wjets, xtitle.c_str(), ytitle.c_str(), TColor::GetColor(222,90,106), 1001);
  TH1F *ewk;
  if(hist)
    ewk = new TH1F("Ewk","",nbins,xmin,xmax);
  else
    ewk = new TH1F("Ewk","",13,massLEdges);
  vardraw = var+">>"+"Ewk";
  ewktree->Draw(vardraw.c_str(),ewkcut.c_str());
  InitHist(ewk, xtitle.c_str(), ytitle.c_str(),  TColor::GetColor(222,90,106), 1001);
  TH1F *vbfh;
  if(hist)
    vbfh = new TH1F("VBFH","",nbins,xmin,xmax);
  else
    vbfh = new TH1F("VBFH","",13,massLEdges);
  vardraw = var+">>"+"VBFH";
  vbfhtree->Draw(vardraw.c_str(),vbfcut.c_str());
  InitHist(vbfh, xtitle.c_str(), ytitle.c_str(),  TColor::GetColor(250,202,255), 1001);
  TH1F *ggh;
  if(hist)
    ggh = new TH1F("GGH","",nbins,xmin,xmax);
  else
    ggh = new TH1F("GGH","",13,massLEdges);
  vardraw = var+">>"+"GGH";
  gfhtree->Draw(vardraw.c_str(),mccut.c_str());
  InitHist(ggh, xtitle.c_str(), ytitle.c_str(),  TColor::GetColor(250,202,255), 1001);
  TH1F *assoh;
  if(hist)
    assoh = new TH1F("AH","",nbins,xmin,xmax);
  else
    assoh = new TH1F("AH","",13,massLEdges);
  vardraw = var+">>"+"AH";
  assohtree->Draw(vardraw.c_str(),mccut.c_str());
  InitHist(assoh, xtitle.c_str(), ytitle.c_str(),  TColor::GetColor(250,202,255), 1001);
  TH1F *smhh;
  if(hist)
    smhh= new TH1F("SMhh","",nbins,xmin,xmax);
  else
    smhh= new TH1F("SMhh","",13,massLEdges);
  vardraw = var+">>"+"SMhh";
  hhtree->Draw(vardraw.c_str(),sigcut.c_str());
  InitSignal(smhh);
  smhh->SetLineColor(kBlack);
  TH1F *hh_0 = new TH1F("hh_0","",nbins,xmin,xmax);
  vardraw = var+">>"+"hh_0";
  hhtree_0->Draw(vardraw.c_str(),sigcut.c_str());
  InitSignal(hh_0);
  hh_0->SetLineColor(kBlack);
  TH1F *hh_m1;
  if(hist)
    hh_m1 = new TH1F("hh_m1","",nbins,xmin,xmax);
  else
    hh_m1 = new TH1F("hh_m1","",13,massLEdges);
  vardraw = var+">>"+"hh_m1";
  hhtree_m1->Draw(vardraw.c_str(),sigcut.c_str());
  InitSignal(hh_m1);
  hh_m1->SetLineColor(kBlack);
  TH1F *hh_m5;
  if(hist)
    hh_m5 = new TH1F("hh_m5","",nbins,xmin,xmax);
  else
    hh_m5 = new TH1F("hh_m5","",13,massLEdges);
  vardraw = var+">>"+"hh_m5";
  hhtree_m5->Draw(vardraw.c_str(),sigcut.c_str());
  InitSignal(hh_m5);
  hh_m5->SetLineColor(kBlack);
  TH1F *hh_p5;
  if(hist)
    hh_p5= new TH1F("hh_p5","",nbins,xmin,xmax);
  else
    hh_p5= new TH1F("hh_p5","",13,massLEdges);
  vardraw = var+">>"+"hh_p5";
  hhtree_p5->Draw(vardraw.c_str(),sigcut.c_str());
  InitSignal(hh_p5);
  hh_p5->SetLineColor(kBlack);
  TH1F *hh_vbf;
  if(hist)
    hh_vbf= new TH1F("hh_vbf","",nbins,xmin,xmax);
  else
    hh_vbf= new TH1F("hh_vbf","",13,massLEdges);
  vardraw = var+">>"+"hh_vbf";
  hhtree_vbf->Draw(vardraw.c_str(),sigcut.c_str());
  InitSignal(hh_vbf);
  hh_vbf->SetLineColor(kBlue);
  delete canv0;
  //for(int i0 = 0; i0 < ewk->GetNbinsX()+1; i0++)
  //  if(ewk->GetBinContent(i0) == 0)
  //    ewk->SetBinError(i0,2.8);
  //---------------------------------------------------------------------------
  //Print out the yields
  Double_t error=999;
  Double_t sigN=0;
  Double_t sigSig=0;
  Double_t bgdN=0;
  Double_t bgdSig=0;
  //ofstream outfile;
  //outfile.open("yields.txt");
  //outfile << "Yields for the signal region." << std::endl;
  cout << jetcut << endl;
  cout << "SM hh   "  << smhh->IntegralAndError(0,smhh->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  cout << " VBF HH "  << hh_vbf->IntegralAndError(0,hh_vbf->GetNbinsX(),error) << "+/-";
  sigN+=smhh->IntegralAndError(0,smhh->GetNbinsX(),error);
  sigSig+=error;
  cout << error << endl; error=999;
  cout << "ttbar   "  << ttbar->IntegralAndError(0,ttbar->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  bgdN+=ttbar->IntegralAndError(0,ttbar->GetNbinsX(),error);bgdSig+=error*error;
  cout << "Ztt     "  << Ztt->IntegralAndError(0,Ztt->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  bgdN+=Ztt->IntegralAndError(0,Ztt->GetNbinsX(),error);bgdSig+=error*error;
  cout << "ewk     "  << ewk->IntegralAndError(0,ewk->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  bgdN+=ewk->IntegralAndError(0,ewk->GetNbinsX(),error);bgdSig+=error*error;
  cout << "wjets   "  << wjets->IntegralAndError(0,wjets->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  bgdN+=wjets->IntegralAndError(0,wjets->GetNbinsX(),error);bgdSig+=error*error;
  cout << "ggH     "  << ggh->IntegralAndError(0,ggh->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  bgdN+=ggh->IntegralAndError(0,ggh->GetNbinsX(),error);bgdSig+=error*error;
  cout << "vbfH    "  << vbfh->IntegralAndError(0,vbfh->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  bgdN+=vbfh->IntegralAndError(0,vbfh->GetNbinsX(),error);bgdSig+=error*error;
  cout << "vH/ttH  "  << assoh->IntegralAndError(0,assoh->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  bgdN+=assoh->IntegralAndError(0,assoh->GetNbinsX(),error); bgdSig+=error*error;
  cout << "S = " << sigN << "+/-" << sigSig << endl;
  cout << "B = " << bgdN << "+/-" << TMath::Sqrt(bgdSig) << endl;
  cout << "S/sqrt(B) = " << sigN/TMath::Sqrt(bgdN) << endl;

  //--------------------------------------------------------------------------
  //outfile.close();
  outDC->cd();
  TDirectory* lTD = outDC->mkdir("mutau");
  outDC->cd(lTD->GetPath());
  ttbar->SetName("data_obs");
  ttbar->SetTitle("data_obs");
  ttbar->Write();
  Ztt->SetName("ZTT");
  Ztt->SetTitle("ZTT");
  Ztt->Write();
  ttbar->SetName("TT");
  ttbar->SetTitle("TT");
  ttbar->Write();
  wjets->SetName("W");
  wjets->SetTitle("W");
  wjets->Write();
  ewk->SetName("VV");
  ewk->SetTitle("VV");
  ewk->Write();
  vbfh->SetName("qqH");
  vbfh->SetTitle("qqH");
  vbfh->Write();
  ggh->SetName("ggH");
  ggh->SetTitle("ggH");
  ggh->Write();
  assoh->SetName("assoH");
  assoh->SetTitle("assoH");
  assoh->Write();
  smhh->SetName("ggHH");
  smhh->SetTitle("ggHH");
  smhh->Write();
  hh_0->SetName("lam0");
  hh_0->SetTitle("lam0");
  hh_0->Write();
  hh_m5->SetName("lamm5");
  hh_m5->SetTitle("lamm5");
  hh_m5->Write();
  hh_m1->SetName("lamm1");
  hh_m1->SetTitle("lamm1");
  hh_m1->Write();
  hh_p5->SetName("lamp5");
  hh_p5->SetTitle("lamp5");
  hh_p5->Write();
  hh_vbf->SetName("qqHH");
  hh_vbf->SetTitle("qqHH");
  hh_vbf->Write();
  outDC->Close();
  //stack some  histtograms together
  vbfh->Add(ggh);
  vbfh->Add(assoh);
  cout << "Single H    "  << vbfh->IntegralAndError(0,vbfh->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  wjets->Add(ewk); 
  cout << "Total  Electroweak    "  << wjets->IntegralAndError(0,wjets->GetNbinsX(),error) << "+/-";
  cout << error << endl; error=999;
  //-----------------------------------------------------------------------
  smhh->Scale(sigscale);
  //Draw the histograms
  TCanvas *canv = MakeCanvas("canv", "histograms", 800, 600);
  canv->cd();
  wjets->Add(ttbar);
  Ztt->Add(wjets);
  vbfh->Add(Ztt);
  //Error band stat
  TH1F* errorBand = (TH1F*)vbfh->Clone("errorBand");
  errorBand  ->SetMarkerSize(0);
  errorBand  ->SetFillColor(13);
  errorBand  ->SetFillStyle(3013);
  errorBand  ->SetLineWidth(1);
  //  for(int idx=0; idx<errorBand->GetNbinsX(); ++idx){
  //     if(errorBand->GetBinContent(idx)>0){
  //       std::cout << "Uncertainties on summed background samples: " << errorBand->GetBinError(idx)/errorBand->GetBinContent(idx) << std::endl;
  //       break;
  //     }
  //}
  vbfh->SetMaximum(1.0*std::max(maximum(vbfh, 0), maximum(smhh, 0)));
  //blind(data,75,150);
  //data->Draw("e");
  vbfh->Draw("hist");
  Ztt->Draw("histsame");
  wjets->Draw("histsame");
  //ggh->Draw("histsame");
  ttbar->Draw("histsame");
  //qcd->Draw("histsame");
  //data->Draw("esame");
  errorBand->Draw("e2same");
  smhh->Draw("histsame");
  canv->RedrawAxis();
  //canv->SetLogy(1);
  //---------------------------------------------------------------------------
  //Adding a legend
  TLegend* leg = new TLegend(0.65, 0.65, 0.95, 0.90);
  SetLegendStyle(leg);
  leg->AddEntry(smhh  , TString::Format("%.0f#timeshh#rightarrow#tau#tau bb", sigscale) , "L" );
  leg->AddEntry(vbfh  , "SM H#rightarrow#tau#tau"   , "F" );
  leg->AddEntry(Ztt  , "Z#rightarrow#tau#tau"           , "F" );
  leg->AddEntry(wjets  , "Electroweak"                    , "F" );
  leg->AddEntry(ttbar, "t#bar{t}"                       , "F" );
  leg->AddEntry(errorBand,"bkg. uncertainty","F");
  leg->Draw();
  //---------------------------------------------------------------------------
   
  //CMS_lumi_v2( canv, 14, 11 );
  //CMS preliminary 
  //const char* dataset = "CMS Simulation, 3000 fb^{-1} at 14 TeV";
  const char* category = "";
  //CMSPrelim(dataset, "#tau_{#mu}#tau_{h}", 0.17, 0.835);
  //CMSPrelim(dataset, "", 0.16, 0.835);
  TPaveText* chan     = new TPaveText(0.52, 0.35, 0.91, 0.55, "tlbrNDC");
  chan->SetBorderSize(   0 );
  chan->SetFillStyle(    0 );
  chan->SetTextAlign(   12 );
  chan->SetTextSize ( 0.05 );
  chan->SetTextColor(    1 );
  chan->SetTextFont (   62 );
  chan->AddText(category);
  //chan->Draw();
  //-------------------------------------------------------------------------
  //Save histograms
  canv->Print((var+"_mt.png").c_str());

  /*
    Ratio Data over MC
  */
  /*
  TCanvas *canv1 = MakeCanvas("canv0", "histograms", 600, 400);
  canv1->SetGridx();
  canv1->SetGridy();
  canv1->cd();

  TH1F* model = (TH1F*)Ztt ->Clone("model");
  TH1F* test1 = (TH1F*)vbfh->Clone("test1"); 
  for(int ibin=0; ibin<test1->GetNbinsX(); ++ibin){
    //the small value in case of 0 entries in the model is added to prevent the chis2 test from failing
    model->SetBinContent(ibin+1, model->GetBinContent(ibin+1)>0 ? model->GetBinContent(ibin+1)*model->GetBinWidth(ibin+1) : 0.01);
    //model->SetBinError  (ibin+1, CONVERVATIVE_CHI2 ? 0. : model->GetBinError  (ibin+1)*model->GetBinWidth(ibin+1));
    model->SetBinError  (ibin+1, 0);
    test1->SetBinContent(ibin+1, test1->GetBinContent(ibin+1)*test1->GetBinWidth(ibin+1));
    test1->SetBinError  (ibin+1, test1->GetBinError  (ibin+1)*test1->GetBinWidth(ibin+1));
  }
  double chi2prob = test1->Chi2Test      (model,"PUW");        std::cout << "chi2prob:" << chi2prob << std::endl;
  double chi2ndof = test1->Chi2Test      (model,"CHI2/NDFUW"); std::cout << "chi2ndf :" << chi2ndof << std::endl;
  double ksprob   = test1->KolmogorovTest(model);              std::cout << "ksprob  :" << ksprob   << std::endl;
  double ksprobpe = test1->KolmogorovTest(model,"DX");         std::cout << "ksprobpe:" << ksprobpe << std::endl;  

  std::vector<double> edges;
  TH1F* zero = (TH1F*)ttbar->Clone("zero"); zero->Clear();
  TH1F* rat1 = (TH1F*)vbfh->Clone("rat1"); 
  for(int ibin=0; ibin<rat1->GetNbinsX(); ++ibin){
    rat1->SetBinContent(ibin+1, Ztt->GetBinContent(ibin+1)>0 ? vbfh->GetBinContent(ibin+1)/Ztt->GetBinContent(ibin+1) : 0);
    rat1->SetBinError  (ibin+1, Ztt->GetBinContent(ibin+1)>0 ? vbfh->GetBinError  (ibin+1)/Ztt->GetBinContent(ibin+1) : 0);
    zero->SetBinContent(ibin+1, 0.);
    zero->SetBinError  (ibin+1, Ztt->GetBinContent(ibin+1)>0 ? Ztt ->GetBinError  (ibin+1)/Ztt->GetBinContent(ibin+1) : 0);
  }
  for(int ibin=0; ibin<rat1->GetNbinsX(); ++ibin){
    if(rat1->GetBinContent(ibin+1)>0){
      edges.push_back(TMath::Abs(rat1->GetBinContent(ibin+1)-1.)+TMath::Abs(rat1->GetBinError(ibin+1)));
      // catch cases of 0 bins, which would lead to 0-alpha*0-1
      rat1->SetBinContent(ibin+1, rat1->GetBinContent(ibin+1)-1.);
    }
  }
  float range = 0.1;
  std::sort(edges.begin(), edges.end());
  if (edges[edges.size()-2]>0.1) { range = 0.2; }
  if (edges[edges.size()-2]>0.2) { range = 0.5; }
  if (edges[edges.size()-2]>0.5) { range = 1.0; }
  if (edges[edges.size()-2]>1.0) { range = 1.5; }
  if (edges[edges.size()-2]>1.5) { range = 2.0; }
  rat1->SetLineColor(kBlack);
  rat1->SetFillColor(kGray );
  rat1->SetMaximum(+range);
  rat1->SetMinimum(-range);
  rat1->GetYaxis()->CenterTitle();
  rat1->GetYaxis()->SetTitle("#bf{Data/MC-1}");
  rat1->GetXaxis()->SetTitle("#bf{m_{#tau#tau} [GeV]}");
  rat1->Draw();
  zero->SetFillStyle(  3013);
  zero->SetFillColor(kBlack);
  zero->SetLineColor(kBlack);
  zero->SetMarkerSize(0.1);
  zero->Draw("e2histsame");
  canv1->RedrawAxis();

  TPaveText* stat1 = new TPaveText(0.20, 0.76+0.061, 0.32, 0.76+0.161, "NDC");
  stat1->SetBorderSize(   0 );
  stat1->SetFillStyle(    0 );
  stat1->SetTextAlign(   12 );
  stat1->SetTextSize ( 0.05 );
  stat1->SetTextColor(    1 );
  stat1->SetTextFont (   62 );
  stat1->AddText(TString::Format("#chi^{2}/ndf=%.3f,  P(#chi^{2})=%.3f", chi2ndof, chi2prob));
  //stat1->AddText(TString::Format("#chi^{2}/ndf=%.3f,  P(#chi^{2})=%.3f, P(KS)=%.3f", chi2ndof, chi2prob, ksprob));
  //stat1->Draw();
  canv1->Print((var+"_ratio.png").c_str());
  */
}