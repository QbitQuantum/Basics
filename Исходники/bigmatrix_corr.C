void bigmatrix_corr(std::string eikoName="h_jety",
		    bool update=false,
		    bool acceptanceCorr=true,
		    double correlation=1.0, 
		    bool logScale=false 
		    )
{
  // declare histograms
  TH1D* h_e;
  TH1D* h_ejes;
  TH1D* h_ejesup;
  TH1D* h_ejesdn;
  TH1D* heff_e;

  TH1F* h_mu;
  TH1F* h_mujes;
  TH1F* h_mujesup;
  TH1F* h_mujesdn;
  TH1D* heff_mu;

  TH1D* h_combine; // for combining electron and muon channels  
  TH1D* h_corr; // for correction of acceptance

  std::string remword3  ="h_";
  std::string corrName = eikoName;
  size_t pos3  = corrName.find(remword3);
  if(pos3!= std::string::npos)
    corrName.replace(pos3,remword3.length(),"");

  // acceptance correction for electrons
  TFile f_crack("mainCore/ave_sherpamadgraph.root");
  if (f_crack.IsZombie()) {
    cout << endl << "Error opening file" << f_crack.GetName() << endl;
    return;
  }
  else
    cout << endl << "Opened " << f_crack.GetName() << endl << endl;

  h_corr = (TH1D*)(f_crack.Get(Form("have_%s",corrName.data())));

  // for debugging
  if( !acceptanceCorr )
    h_corr->Reset();
  for(int i=1; i<= h_corr->GetNbinsX(); i++)
    {
      if( !acceptanceCorr )
	{
	  h_corr->SetBinContent(i,1.0);
	  h_corr->SetBinError(i,1e-6);
	}
      cout << "Correction for bin " << i << " = " 
	   << h_corr->GetBinContent(i) << " +- " << h_corr->GetBinError(i) 
	   << endl;
    }


  //================================================================
  // efficiency errors
  //================================================================
 
  std::string xtitle;
  std::string muName;
  std::string kengName;
  std::string effElectronName;
  std::string effMuonName;

  if(eikoName=="h_ystar")
    {
      xtitle = "0.5|Y_{Z}-Y_{jet}|";
      muName = "YDiff";
      kengName = "DEta_per2_Z1jets_BE";
      
      effElectronName = "EfficienyVsYdif";
      effMuonName = "EffCorr_Ydiff";
    }

  else if(eikoName=="h_yB")
    {
      xtitle = "0.5|Y_{Z}+Y_{jet}|";
      muName = "YSum";
      kengName = "SumEta_per2_Z1jets_BE";

      effElectronName = "EfficienyVsYsum";
      effMuonName = "EffCorr_Ysum";
    }
  else if(eikoName=="h_jety")
    {
      xtitle = "|Y(jet)|";
      muName = "Yjet";
      kengName = "Z1jets_1jeta_BE";

      effElectronName = "EfficienyVsYjet";
      effMuonName = "EffCorr_Yjet";
    }
  else if(eikoName=="h_zy")
    {
      xtitle = "|Y(Z)|";
      muName = "YZ";
      kengName ="dimuoneta1jet_BE";

      effElectronName = "EfficienyVsYz";
      effMuonName = "EffCorr_Yz";
    }

  TFile f_eff_electron("mainCore/EffiZCut_Jer0.root");
  if(f_eff_electron.IsZombie()){
    cout << endl << "Error opening file" << f_eff_electron.GetName() << endl << endl;
    return;
  }
  else
    cout << endl << "Opened " << f_eff_electron.GetName() << endl << endl;

  heff_e = (TH1D*)(f_eff_electron.Get(effElectronName.data()));
  heff_e -> SetName(Form("heff_e_%s",corrName.data()));


  TFile f_eff_muon("mainCore/EffCorr_root_091912.root");
  if(f_eff_muon.IsZombie()){
    cout << endl << "Error opening file" << f_eff_muon.GetName() << endl << endl;
    return;
  }
  else
    cout << endl << "Opened " << f_eff_muon.GetName() << endl << endl;

  heff_mu = (TH1D*)(f_eff_muon.Get(effMuonName.data()));
  heff_mu -> SetName(Form("heff_mu_%s",corrName.data()));




  //===========================================================
  // electron channel
  //===========================================================
  TFile f_e("mainCore/cts_CorrectedPlotsZCut.root");
  if (f_e.IsZombie()) {
    cout << endl << "Error opening file" << f_e.GetName() << endl << endl;
    return;
  }
  else
    cout << endl << "Opened " << f_e.GetName() << endl << endl;

  h_e  = (TH1D*)(f_e.Get(eikoName.data()));
  h_e  -> SetName(Form("h_e_%s",corrName.data()));
  h_e  -> SetTitle("");
  h_e  -> Sumw2();

  //-------------------------------------------------------------------
  // use electron channel to count the number of non-zero bins
  // so to avoid singular error matrix
  int nbins = 0; 
  const double threshold = 1.0;
  for(int ie=1; ie<= h_e->GetNbinsX(); ie++)
    if(h_e->GetBinContent(ie)> threshold)nbins++;
  cout << "There are " << nbins << " bins with non-zero content" << endl;  
  //-------------------------------------------------------------------

  h_e  -> Divide(h_corr);
  h_e  -> Scale(1.0/h_e->Integral());
  h_e  -> SetYTitle("Arbitrary Unit");
  h_e  -> SetTitleOffset(2.0,"Y");
  h_e  -> GetYaxis()->SetDecimals();
  h_e  -> GetXaxis()->SetDecimals();
  h_e  -> SetLineColor(kBlue-7);
  h_e  -> SetMarkerColor(kBlue-7);
  h_e  -> SetMarkerSize(1);
  h_e  -> SetMarkerStyle(24);

  cout << "h_e integral = " << h_e->Integral() << endl;

  h_ejes= (TH1D*)(f_e.Get(eikoName.data()));
  h_ejes    -> SetName("h_ejes");
  h_ejes    -> Sumw2();
  h_ejes    -> Scale(1.0/h_ejes->Integral());
  cout << "h_ejes integral = " << h_ejes->Integral() << endl;

  TFile f_ejesup("mainCore/cts_CorrectedPlotsZCut_JesUp_NoBkgSub.root");
  if (f_ejesup.IsZombie()) {
    cout << endl << "Error opening file" << f_ejesup.GetName() << endl << endl;
    return;
  }
  else
    cout << endl << "Opened " << f_ejesup.GetName() << endl << endl;

  h_ejesup  = (TH1D*)(f_ejesup.Get(eikoName.data()));
  h_ejesup  -> SetName("h_ejesup");
  h_ejesup  -> SetTitle("");
  h_ejesup  -> Sumw2();
  h_ejesup  -> Scale(1.0/h_ejesup->Integral());


  cout << "h_ejesup integral = " << h_ejesup->Integral() << endl;

  TFile f_ejesdn("mainCore/cts_CorrectedPlotsZCut_JesDn_NoBkgSub.root");
  if (f_ejesdn.IsZombie()) {
    cout << endl << "Error opening file" << f_ejesdn.GetName() << endl << endl;
    return;
  }
  else
    cout << endl << "Opened " << f_ejesdn.GetName() << endl << endl;

  h_ejesdn  = (TH1D*)(f_ejesdn.Get(eikoName.data()));
  h_ejesdn  -> SetName("h_ejesdn");
  h_ejesdn  -> SetTitle("");
  h_ejesdn  -> Sumw2();
  h_ejesdn  -> Scale(1.0/h_ejesdn->Integral());

  cout << "h_ejesdn integral = " << h_ejesdn->Integral() << endl;

  h_combine= (TH1D*)h_e->Clone(Form("h_combine_%s",corrName.data()));
  h_combine  -> Reset();
  h_combine  -> SetTitle("");
  h_combine  -> SetLineColor(1);
  h_combine  -> SetMarkerColor(1);
  h_combine  -> SetMarkerSize(1);
  h_combine  -> SetMarkerStyle(8);


  //===========================================================
  // muon channel
  //===========================================================

  TFile f_mu("mainCore/DoubleMu2011_EffCorr_091812.root");
  if (f_mu.IsZombie()) {
    cout << endl << "Error opening file" << f_mu.GetName() << endl << endl;
    return;
  }
  else
    cout << endl << "Opened " << f_mu.GetName() << endl << endl;

  h_mu = (TH1F*)(f_mu.Get(muName.data()));
  h_mu -> Sumw2();
  h_mu -> SetName(Form("h_mu_%s",corrName.data()));
  h_mu  -> SetTitle("");
  h_mu -> Scale(1.0/h_mu->Integral());
  h_mu -> SetLineColor(kRed-7);
  h_mu -> SetMarkerColor(kRed-7);
  h_mu -> SetMarkerSize(1);
  h_mu -> SetMarkerStyle(21);

  cout << "h_mu integral = " << h_mu->Integral() << endl;

  TFile f_jetsys_mu("mainCore/DoubleMu2011_JESuncertainty_JetY_061712.root");
  if (f_jetsys_mu.IsZombie()) {
    cout << endl << "Error opening file" << f_jetsys_mu.GetName() << endl << endl;
    return;
  }
  else
    cout << endl << "Opened " << f_jetsys_mu.GetName() << endl << endl;

  h_mujes = (TH1F*)(f_jetsys_mu.Get(kengName.data()));
  h_mujes -> Sumw2();
  h_mujes -> Scale(1.0/h_mujes->Integral());

  cout << "h_mujes integral = " << h_mujes->Integral() << endl;

  h_mujesup = (TH1F*)(f_jetsys_mu.Get(Form("%sUp",kengName.data())));
  h_mujesup -> Sumw2();
  h_mujesup -> Scale(1.0/h_mujesup->Integral());

  cout << "h_mujesup integral = " << h_mujesup->Integral() << endl;

  h_mujesdn = (TH1F*)(f_jetsys_mu.Get(Form("%sDn",kengName.data())));
  h_mujesdn -> Sumw2();
  h_mujesdn -> Scale(1.0/h_mujesdn->Integral());

  cout << "h_mujesdn integral = " << h_mujesdn->Integral() << endl;


  // declare the big matrix
  const int NELE=2*nbins;
  TMatrixD errorM(NELE,NELE);

  TMatrixD U(NELE,nbins);
  for(int irow=0; irow < NELE; irow++)
    for(int icol=0; icol < nbins; icol++)
      U(irow,icol) = ( (irow== icol) || (irow== icol+nbins) )? 1:0;
  // debug
  //   dumpElements(U);

  TMatrixD transposeU(nbins,NELE);
  transposeU.Transpose(U);
  //   dumpElements(transposeU);

  
  TVectorD measurement(NELE);


  // jet energy scale for electron channel
  TVectorD jesSys_ele(nbins);
  TVectorD jesSys_muo(nbins);

  // now loop over bins to set the matrix content
  for(int ibin=0; ibin<nbins; ibin++){

    // electron channel
    double value_e = h_e->GetBinContent(ibin+1);
    if(value_e < 1e-10)continue;

    double stat_mc_eff_e = heff_e->GetBinContent(ibin+1)<1e-6? 0: 
      value_e*heff_e->GetBinError(ibin+1)/heff_e->GetBinContent(ibin+1);
  
    double stat_e  = sqrt( pow(h_e->GetBinError(ibin+1),2) + 
			   pow(stat_mc_eff_e,2));

    double value_e_jes = h_ejes->GetBinContent(ibin+1);
    if(value_e_jes <1e-10)continue;

    double rel_syse_up = fabs(h_ejesup->GetBinContent(ibin+1) -
			      value_e_jes)/value_e_jes;
    
    double rel_syse_dn = fabs(h_ejesdn->GetBinContent(ibin+1) -
			      value_e_jes)/value_e_jes;
   
    double rel_syse = rel_syse_up > rel_syse_dn?
      rel_syse_up: rel_syse_dn;

    double sys_e = value_e*rel_syse;
    jesSys_ele(ibin) = sys_e;

    double total_e_2 = stat_e*stat_e+ sys_e*sys_e;


    // muon channel
    double value_m = h_mu->GetBinContent(ibin+1);
    if(value_m < 1e-10)continue;

    double stat_mc_eff_m = heff_mu->GetBinContent(ibin+1)<1e-6? 0: 
      value_m*heff_mu->GetBinError(ibin+1)/heff_mu->GetBinContent(ibin+1);
    
    double stat_m  = sqrt( pow(h_mu->GetBinError(ibin+1),2) + 
			   pow(stat_mc_eff_m,2));

    double value_m_jes = h_mujes->GetBinContent(ibin+1);
    if(value_m_jes <1e-10)continue;

    double rel_sysm_up = fabs(h_mujesup->GetBinContent(ibin+1) -
			      value_m_jes)/value_m_jes;
    
    double rel_sysm_dn = fabs(h_mujesdn->GetBinContent(ibin+1) -
			      value_m_jes)/value_m_jes;
   
    double rel_sysm = rel_sysm_up > rel_sysm_dn?
      rel_sysm_up: rel_sysm_dn;

    double sys_m = value_m*rel_sysm;
    jesSys_muo(ibin) = sys_m;

    double total_m_2 = stat_m*stat_m+ sys_m*sys_m;

    measurement(ibin) = value_e;
    measurement(nbins+ibin) = value_m;

    // first put electron error matrix component
    errorM(ibin,ibin) = total_e_2; 

    // then muon
    errorM(nbins+ibin,nbins+ibin) = total_m_2; 

    errorM(ibin,nbins+ibin) = errorM(nbins+ibin,ibin) = 
      correlation*sys_e*sys_m;


  } // loop over the number of bins


  // debug

  dumpElements(jesSys_ele);
  dumpElements(jesSys_muo);
  // print out measurement value  
  //   dumpElements(measurement);

  //   // print out error matrix component
  dumpElements(errorM);


  // assign the correlation between different bins due to JES
  // 100% correlation
  for(int ibin=0; ibin < nbins; ibin++){
    for(int jbin=0; jbin<nbins; jbin++)
      {
	if(jbin!=ibin){	
	  // electron channel
	  errorM(ibin,jbin)= correlation*jesSys_ele(ibin)*jesSys_ele(jbin);   
	  // muon channel
	  errorM(nbins+ibin,nbins+jbin)= correlation*jesSys_muo(ibin)*
	    jesSys_muo(jbin);
	  
	  // electron-muon channel
	  errorM(ibin,nbins+jbin)= correlation*jesSys_ele(ibin)*jesSys_muo(jbin);
	  // muon-electron channel
	  errorM(nbins+ibin,jbin)= correlation*jesSys_muo(ibin)*jesSys_ele(jbin); 
	}	
      }
  }

  dumpElements(errorM);

  TMatrixD errorInverse = errorM;
  double* det;
  errorInverse.Invert(det);
  dumpElements(errorInverse);

  //   TMatrixD Unit = errorInverse*errorM;
  // dumpElements(Unit);
  

  TMatrixD matrixRight(nbins,NELE);  
  matrixRight = transposeU*errorInverse;
  //   dumpElements(matrixRight);

  TMatrixD matrixLeft(nbins,nbins);
  matrixLeft = transposeU*(errorInverse*U);
  //   dumpElements(matrixLeft);

  TMatrixD matrixLeftInverse = matrixLeft;
  double* det2;
  matrixLeftInverse.Invert(det2);
  //   dumpElements(matrixLeftInverse);

  TMatrixD lambda(nbins,NELE);
  lambda= matrixLeftInverse*matrixRight;
  //   dumpElements(lambda);
  
  TMatrixD transposeLambda(NELE,nbins);
  transposeLambda.Transpose(lambda);
  //   dumpElements(transposeLambda);

  //   dumpElements(lambda);

  TVectorD combined_value(nbins);
  combined_value = lambda*measurement;
  //   dumpElements(combined_value);

  TMatrixD combined_error(nbins,nbins);
  combined_error = lambda*(errorM*transposeLambda);
  

  // after all matrix operation, now set the histogram
  for(int i=0; i<nbins;i++){

    h_combine->SetBinContent(i+1, combined_value(i));
  
    double error = combined_error(i,i);
  
    if(error>1e-10)error = sqrt(error);
    else error=1e-10;

    h_combine->SetBinError(i+1,error);

  }
  
  for(int i=1; i <= h_combine->GetNbinsX(); i++){

    if(h_combine->GetBinContent(i)>1e-10)
      cout << "Bin " << i << ": " << h_combine->GetBinContent(i) 
	   << " +- " << h_combine->GetBinError(i) << "\t"
	   << "rele = " << 
	(h_combine->GetBinError(i)/h_combine->GetBinContent(i)) 
	   << endl;

  }


  h_e      ->SetXTitle(xtitle.data());
  h_mu     ->SetXTitle(xtitle.data());
  h_combine->SetXTitle(xtitle.data());

  std::string command = "recreate";
  if(update)command="update";
  TFile* outFile = new TFile("bigmatrix_corr.root", command.data());
  h_e      ->Write();
  h_mu     ->Write();
  h_combine->Write();
  heff_e   ->Write();
  heff_mu  ->Write();
  outFile->Close();


  TCanvas* c1 = new TCanvas("c1","",500,500);
  if(logScale)
    c1->SetLogy(1);
  float x1NDC = 0.67;
  float y1NDC = 0.764831;
  float x2NDC = 0.830;
  float y2NDC = 0.908898;

  h_e->Draw("e");
  h_mu->Draw("esame");
  h_combine->Draw("e1same");

  TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);  
  
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->SetBorderSize(0);
  leg->AddEntry(h_combine, "combined");
  leg->AddEntry(h_e, "e");
  leg->AddEntry(h_mu, "#mu");
  leg->Draw("same");

  std::string remword  ="h_";
  std::string remword2 ="h";
  size_t pos  = eikoName.find(remword);
  if(pos!= std::string::npos)
    eikoName.replace(pos,remword2.length(),"");

  string dirName = "fig";
  gSystem->mkdir(dirName.data());

  string fileName = dirName + "/" + "final_emu" + eikoName;
  c1->Print(Form("%s.eps",fileName.data()));
  c1->Print(Form("%s.gif",fileName.data()));
  c1->Print(Form("%s.pdf",fileName.data()));

}