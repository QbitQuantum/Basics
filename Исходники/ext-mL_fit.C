void Draw_yield_treeeff(char EBEE[20]="EB", int jetbin=0){

  int ptbin_int=0;
  float ptcut[30] = {22, 30, 36, 50, 75, 90, 105,  120, 135, 150, 165, 175, 185,
		     190, 200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000}; //22 bins
  //                  13   14   15   16   17   18   19   20   21    22    23    24    25     26

  int nbin=22;

  TH1F *h_yield = new TH1F("h_yield","",nbin, ptcut);
  TH1F *h_purity = new TH1F("h_purity","",nbin, ptcut);
  TH1F *h_purity_tight = new TH1F("h_purity_tight","",nbin, ptcut);

  TH1F *h_sig_yield = new TH1F("h_sig_yield","",nbin, ptcut);
  TH1F *h_sig_yield_tight = new TH1F("h_sig_yield_tight","",nbin, ptcut);
  TH1F *h_bkg_yield = new TH1F("h_bkg_yield","",nbin, ptcut);
  TH1F *h_bkg_yield_tight = new TH1F("h_bkg_yield_tight","",nbin, ptcut);


  TH1F *h_xs = new TH1F("h_xs","",nbin,ptcut);
  double *fitted;
  float lumi = 2568.83;
  float lumi_err = lumi*0.046;
  float deta = 1.4442*2.; 
  float template_sys = TMath::Sqrt(3.2*3.2+3.*3.)*0.01;
  int ebeebin=0;
  if(strcmp(EBEE,"EE")==0) {
    deta = (2.5-1.566)*2.;
    ebeebin=1;
  }

  TTree *tt = new TTree();
  tt->ReadFile("eff.dat");
  Int_t   ptbin_;
  Int_t   ebee_;
  Int_t   jetbin_;
  Float_t trigeff;
  Float_t trigeff_err;
  Float_t recoeff;
  Float_t recoeff_err;
  Float_t preseleff;
  Float_t preseleff_err;
  Float_t SF;
  Float_t SF_err;       

  tt->SetBranchAddress("ptbin", &ptbin_);
  tt->SetBranchAddress("EBEE", &ebee_);
  tt->SetBranchAddress("jetbin", &jetbin_);
  tt->SetBranchAddress("trigeff", &trigeff);
  tt->SetBranchAddress("trigeff_err", &trigeff_err);
  tt->SetBranchAddress("recoeff", &recoeff);
  tt->SetBranchAddress("recoeff_err", &recoeff_err);
  tt->SetBranchAddress("preseleff", &preseleff);
  tt->SetBranchAddress("preseleff_err", &preseleff_err);
  tt->SetBranchAddress("SF", &SF);
  tt->SetBranchAddress("SF_err", &SF_err);

  char txt[100];
  for(int ii=13; ii<22; ii++){
    //perform fit for yield
    fitted=Ifit(ii, EBEE,1, jetbin);
    if(fitted[0]>0.) {

      h_yield->SetBinContent(ii+1, fitted[0]/h_yield->GetBinWidth(ii+1));
      h_yield->SetBinError(ii+1, fitted[1]/h_yield->GetBinWidth(ii+1));

      Long64_t jentry = ii-13 + 9*3*ebeebin + 9*jetbin;
      tt->GetEntry(jentry);
      printf("bin %d, %d, %d \n", ptbin_, ebee_, jetbin_);
    
      float djet_eta=1.5*2.;
      if(jetbin==1) djet_eta = 0.9*2.;
      if(jetbin==2) djet_eta = 1;
      printf("bin %d, ptcut %.1f,  fit %.0f , bkg %.0f , eff %.2f, %2.f, binwidth %.1f, deta %.2f \n", ii, ptcut[ii], fitted[0], fitted[2], recoeff, preseleff, h_yield->GetBinWidth(ii+1), deta );
      printf(" %f %f %f %f %f %f %f %f %f \n",  fitted[0] , lumi , trigeff, recoeff , preseleff , h_yield->GetBinWidth(ii+1) ,SF ,deta , djet_eta);
      float xs = fitted[0] / lumi / trigeff/ recoeff / preseleff / h_yield->GetBinWidth(ii+1) /SF /deta / djet_eta ; //xs per GeV
      float xs_err = (fitted[1]/fitted[0])*(fitted[1]/fitted[0]) + (lumi_err/lumi)*(lumi_err/lumi) + 
	(preseleff_err/preseleff)*(preseleff_err/preseleff) + 
	(recoeff_err/recoeff)*(recoeff_err/recoeff) + 
	(trigeff_err/trigeff)*(trigeff_err/trigeff) +
	(SF_err/SF)*(SF_err/SF) +
	(template_sys*template_sys);
      xs_err = TMath::Sqrt(xs_err)*xs;
      printf("xs %f , xs_err %f \n", xs, xs_err);
      h_xs->SetBinContent(ii+1, xs);
      h_xs->SetBinError(ii+1, xs_err);

      h_sig_yield->SetBinContent(ii+1, fitted[0]);
      h_bkg_yield->SetBinContent(ii+1, fitted[2]);

      h_sig_yield_tight->SetBinContent(ii+1, fitted[4]);
      h_bkg_yield_tight->SetBinContent(ii+1, fitted[6]);

      // //perform fit for purity in WP90 region
      // h_purity_tight->SetBinContent(ii+1, fitted[4]/(fitted[4]+fitted[6]));
      // float err = TMath::Sqrt(fitted[4]*fitted[6]/(fitted[4]+fitted[6])/(fitted[4]+fitted[6])/(fitted[4]+fitted[6]));
      // h_purity_tight->SetBinError(ii+1, err);    
      // h_purity->SetBinContent(ii+1, fitted[0]/(fitted[0]+fitted[2]));
      // err = TMath::Sqrt(fitted[0]*fitted[2]/(fitted[0]+fitted[2])/(fitted[0]+fitted[2])/(fitted[0]+fitted[2]));
      // h_purity->SetBinError(ii+1, err);    
    }
  }
  for(int ii=13; ii<nbin; ii++){
    //   printf("ptbin %d, %.2f, xs %f , xs_err %f \n", ii, ptcut[ii], h_xs->GetBinContent(ii+1), h_xs->GetBinError(ii+1));
    printf("ptbin %d, %.2f, yield, %.2f, %.2f \n", ii, ptcut[ii], h_sig_yield_tight->GetBinContent(ii+1), h_bkg_yield_tight->GetBinContent(ii+1));
  }

  TCanvas *c10 = new TCanvas("c10","",600,600);
  c10->Draw();
  gPad->SetLogy();
  h_yield->SetNdivisions(505,"XY");
  h_yield->SetXTitle("p_{T} (GeV)");
  h_yield->SetYTitle("Entries / GeV");
  h_yield->SetMarkerStyle(8);
  h_yield->GetXaxis()->SetRangeUser(150.,1000.);
  h_yield->Draw("pe");

  char pho_text[100];
  char jet_text[100];
  if(ebeebin==0) sprintf(pho_text,"|#eta_{#gamma}|<1.4442");
  else sprintf(pho_text,"1.566<|#eta_{#gamma}|<2.5");
  if(jetbin==0) sprintf(jet_text,"|#eta_{jet}|<1.5");
  else sprintf(jet_text,"1.5<|#eta_{jet}|<2.4");


  TLegend *tleg = new TLegend(0.4, 0.65, 0.85, 0.85);
  char text[50];
  sprintf(text,"CMS 13TeV, %.0f pb^{-1}",lumi);
  tleg->SetHeader(text);
  tleg->SetFillColor(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);  
  sprintf(text,"%s, %s",pho_text, jet_text);
  if(jetbin==2)   sprintf(text,"%s",pho_text);
  tleg->AddEntry(h_yield,text,"pl");
  tleg->Draw();
  

  TLatex *tlx = new TLatex();
  tlx->SetTextSize(0.04);
  tlx->DrawLatex(100, h_yield->GetMaximum()*1.3, "CMS Preliminary #sqrt{s} = 13TeV");

  // //purity plot
  // TCanvas *c11 = new TCanvas("c11","",600,600);
  // h_purity->SetNdivisions(505,"XY");
  // h_purity->SetXTitle("P_{T} (GeV)");
  // h_purity->SetYTitle("Purity");
  // h_purity->SetMarkerStyle(8);
  // h_purity->GetXaxis()->SetRangeUser(150.,1000.);
  // h_purity->GetYaxis()->SetRangeUser(0., 1.01);
  // h_purity->Draw();
  // // h_purity_tight->SetMarkerStyle(8);
  // // h_purity_tight->SetMarkerColor(4);
  // // h_purity_tight->SetLineColor(4);
  // // h_purity_tight->Draw("pe same");

  
  // TGraphAsymmErrors *tgrs = new TGraphAsymmErrors();
  // h_bkg_yield->Add(h_sig_yield);

  // tgrs->BayesDivide(h_sig_yield, h_bkg_yield);
  // tgrs->SetMarkerStyle(8);
  // tgrs->Draw("pe same");

  // TGraphAsymmErrors *tgrs_tight = new TGraphAsymmErrors();
  // h_bkg_yield_tight->Add(h_sig_yield_tight);
  // for(int ii=13; ii<nbin; ii++){
  //   //   printf("ptbin %d, %.2f, xs %f , xs_err %f \n", ii, ptcut[ii], h_xs->GetBinContent(ii+1), h_xs->GetBinError(ii+1));
  //   printf("ptbin %d, %.2f, yield, %.2f, %.2f \n", ii, ptcut[ii], h_sig_yield_tight->GetBinContent(ii+1), h_bkg_yield_tight->GetBinContent(ii+1));
  // }

  // tgrs_tight->BayesDivide(h_sig_yield_tight, h_bkg_yield_tight,"v");
  // tgrs_tight->SetMarkerStyle(8);
  // tgrs_tight->SetMarkerColor(4);
  // tgrs_tight->SetLineColor(4);
  // tgrs_tight->Draw("pe same");

  // tleg = new TLegend(0.3, 0.15, 0.85, 0.35);
  // char text[50];
  // sprintf(text,"Single Photon PD %.0f pb^{-1}", lumi);
  // tleg->SetHeader(text);
  // tleg->SetFillColor(0);
  // tleg->SetShadowColor(0);
  // tleg->SetBorderSize(0);
  // sprintf(text,"%s, %s",pho_text, jet_text);
  // tleg->AddEntry(tgrs,text,"pl");
  // sprintf(text,"%s, %s, BDT>0.37",pho_text, jet_text);
  // tleg->AddEntry(tgrs_tight,text,"pl");
  // tleg->Draw();

  // tlx->SetTextSize(0.04);
  // tlx->DrawLatex(200, 1.01, "CMS Preliminary #sqrt{s} = 13TeV");
  

  //Draw XS plot
  TCanvas *c12 = new TCanvas("c12","",600,700);  
  c12->Draw();

  TPad* pad1 = new TPad("pad1","",0.02, 0.25, 0.99, 0.99);
  TPad* pad2 = new TPad("pad1","",0.02, 0.02, 0.99, 0.25);


  // pad1->SetLeftMargin(0.02);
  pad1->SetRightMargin(0.035);
  // pad1->SetTopMargin(0.02);
  pad1->SetBottomMargin(0.0);
  pad1->SetFrameBorderMode(0);
  pad1->SetBorderMode(0);
  pad1->SetBorderSize(0);

  // pad2->SetLeftMargin(0.02);
  pad2->SetRightMargin(0.035);
  pad2->SetTopMargin(0.0);
  pad2->SetBottomMargin(0.275);
  pad2->SetFrameBorderMode(0);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(0);

  pad1->Draw();
  pad2->Draw();
  
  pad1->cd();

  gPad->SetLogy();

  TH2F *hh2 = new TH2F("hh2","",100, 150, 1000, 100, 2e-7, 1.);
  if(ebeebin==0) hh2 = new TH2F("hh2","",100, 150, 1000, 100, 2e-7, 1.);

  hh2->SetNdivisions(505,"XY");
  hh2->SetXTitle("P_{T} (GeV)");
  hh2->SetYTitle("d^{3}#sigma / d^{#gamma}p_{T}d^{#gamma}#eta d^{jet}#eta [pb/GeV]");
  if(jetbin==2)   hh2->SetYTitle("d^{2}#sigma / d^{#gamma}p_{T}d^{#gamma}#eta [pb/GeV]");
  hh2->GetXaxis()->SetLabelSize(0.035);
  hh2->GetYaxis()->SetLabelSize(0.035);
  hh2->GetYaxis()->SetTitleSize(0.04);
  hh2->GetYaxis()->SetTitleOffset(1.1);
  hh2->Draw();
  
  h_xs->SetMarkerStyle(8);
  h_xs->Draw("pel same");
  //Draw JetPhox value
  TTree *t_th = new TTree();
  t_th->ReadFile("jetphox.dat");
  t_th->Print();

  Int_t ptbin_1;
  Int_t ebee_1;
  Int_t jetbin_1;
  Double_t xs_th;
  Double_t xs_th_err;
  
  
  t_th->SetBranchAddress("ptbin", &ptbin_1);
  t_th->SetBranchAddress("EBEE", &ebee_1);
  t_th->SetBranchAddress("jetbin", &jetbin_1);
  t_th->SetBranchAddress("xs", &xs_th);
  t_th->SetBranchAddress("xs_err", &xs_th_err);
  
  
  TH1F *h_th_xs = new TH1F("h_th_xs","",nbin, ptcut);
  TH1F *h_th_xs_err = new TH1F("h_th_xs_err","",nbin, ptcut);

  for(int ii=13; ii<22; ii++){
    Long64_t jentry = ii-13 + 9*3*ebeebin + 9*jetbin;
    t_th->GetEntry(jentry);
    //printf("bin %d, %d, %d \n", ptbin_1, ebee_1, jetbin_1);
    h_th_xs->SetBinContent(ii+1, xs_th);
    h_th_xs->SetBinError(ii+1, xs_th_err);
    h_th_xs_err->SetBinContent(ii+1, xs_th_err);

    if(jetbin==2){
      if(ebeebin==0){
	h_th_xs->SetBinContent(ii+1, xs_th/deta);
	h_th_xs->SetBinError(ii+1, xs_th_err/deta);
	h_th_xs_err->SetBinContent(ii+1, xs_th_err/deta);
      }else{
	h_th_xs->SetBinContent(ii+1, xs_th/deta*2.);
	h_th_xs->SetBinError(ii+1, xs_th_err/deta*2.);
	h_th_xs_err->SetBinContent(ii+1, xs_th_err/deta*2.);
      }
    }
  }

  h_th_xs->SetMarkerStyle(25);
  h_th_xs->SetMarkerColor(2);
  h_th_xs->SetLineColor(2);
  h_th_xs->Draw("same ple");

  TLegend *tleg = new TLegend(0.4, 0.65, 0.85, 0.85);
  char text[50];
  sprintf(text,"CMS 13TeV, %.0f pb^{-1}",lumi);
  tleg->SetHeader(text);
  tleg->SetFillColor(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);  
  sprintf(text,"%s, %s",pho_text, jet_text);
  if(jetbin==2)   sprintf(text,"%s",pho_text);
  tleg->AddEntry(h_xs,text,"pl");
  tleg->AddEntry(h_th_xs,"JETPHOX","pl");
  tleg->Draw();
  
  tlx->DrawLatex(150, 1., "CMS Preliminary #sqrt{s} = 13TeV");

  
  //Draw data/th XS ratio
  // TCanvas *c15 = new TCanvas("c15","",600,600);
  // c15->Draw();
  pad2->cd();
  gPad->SetGridy();
  TH1F *h_xs_ratio = (TH1F*)h_xs->Clone();
  h_xs_ratio->Draw();


  h_xs_ratio->Divide(h_th_xs);
  // TGraphAsymmErrors *tgrs = new TGraphAsymmErrors();
  // tgrs->Divide(h_xs, h_th_xs);
  // TH1F *h_xs_ratio = new TH1F("h_xs_ratio","",nbin,ptcut);
  h_xs_ratio->SetMinimum(0.);
  h_xs_ratio->SetMaximum(2.);
  h_xs_ratio->SetNdivisions(505,"XY");
  h_xs_ratio->SetXTitle("P_{T} (GeV)");
  h_xs_ratio->SetYTitle("Data / MC");
  h_xs_ratio->GetXaxis()->SetLabelSize(0.12);
  h_xs_ratio->GetYaxis()->SetLabelSize(0.1);
  h_xs_ratio->GetXaxis()->SetTitleSize(0.12);
  h_xs_ratio->GetYaxis()->SetTitleSize(0.12);
  h_xs_ratio->GetXaxis()->SetTitleOffset(1.);
  h_xs_ratio->GetYaxis()->SetTitleOffset(0.4);

  h_xs_ratio->GetXaxis()->SetRangeUser(150,1000);
  h_xs_ratio->GetYaxis()->SetRangeUser(0.55, 1.45);
  if(ebeebin==1) h_xs_ratio->GetYaxis()->SetRangeUser(0., 2.2);
  if(jetbin==1) h_xs_ratio->GetYaxis()->SetRangeUser(0., 2.2);

  //h_xs_ratio->GetYaxis()->SetNdivisions(102,"Y");
  h_xs_ratio->Draw("pe");
  // tgrs->SetMarkerStyle(8);
  // tgrs->Draw("pe same");
  
}