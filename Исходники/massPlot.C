void massPlot(double lumi=-1., double maxInstLumi=-1.) {

  setTDRStyle();
  //tdrGrid(false, tdrStyle);

  writeExtraText = true;
  //extraText  = "Preliminary Simulation"; 
  //lumi_8TeV = ""; 
  int iPeriod = 2; // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
  //int iPos=0;
  int iPos=11;
  //int iPos=22;
	
  if (lumi<0)
    lumi=LUMI;
  if (maxInstLumi<0)
    maxInstLumi=MAXINSTLUMI;
  DifferentXSLimitPlots plots(lumi);

  //mchamp index 0 is used, corresponds to 0th mass point = 100 GeV
  plots.calculateCrossSections(0,0,0,39,9);
    
  // three points on counting expt curve
  //TGraph* g_obs_gluino = plots.getMassLimitGluino();
  TGraph* g_gluino = plots.getExpMassLimitGluino();

  //TGraph* g_obs_stop = plots.getMassLimitStop();
  TGraph* g_stop = plots.getExpMassLimitStop();

  TGraph* g_obs_mchamp = plots.getMassLimitMchamp();
  TGraph* g_mchamp = plots.getExpMassLimitMchamp();

  //TGraphAsymmErrors* g_expGluino_1sig = plots.getExpMassLimitGluino1Sig();  
  //TGraphAsymmErrors* g_expGluino_2sig = plots.getExpMassLimitGluino2Sig();  

  //TGraphAsymmErrors* g_expStop_1sig = plots.getExpMassLimitStop1Sig();  
  //TGraphAsymmErrors* g_expStop_2sig = plots.getExpMassLimitStop2Sig();  

  TGraphAsymmErrors* g_exp_1sig = plots.getExpMassLimitMchamp1Sig();  
  TGraphAsymmErrors* g_exp_2sig = plots.getExpMassLimitMchamp2Sig();  

  // one point from lifetime fit
  TGraph* g_tpg = plots.getMassLimitGluinoTP();
  TGraph* g_tps = plots.getMassLimitStopTP();
  
  // theory prediction
  TGraph* g_thGluino = plots.getGluinoTheory();
  TGraph* g_thStop = plots.getStopTheory();
  TGraph* g_thMchamp = plots.getMchampTheory();
  
  TCanvas* canvas = new TCanvas("canvas","",10,10,575,500);

  Double_t x[10], yMinus[10], x2[10], y[10], yPlus[10], z[10];
  cout<<"MCHAMP LIMITS ARE: "<<endl;
  for(Int_t i=0; i<g_mchamp->GetN(); i++){
    g_mchamp->GetPoint(i, x[i], y[i]);
    yPlus[i] = g_exp_1sig->GetErrorYhigh(i);
    yMinus[i] = g_exp_1sig->GetErrorYlow(i);
    g_obs_mchamp->GetPoint(i, x2[i], z[i]);
    cout<<" mass is: "<<x[i]<<", expected limit is: "<<y[i]<<", expected +1 sigma is: "<<yPlus[i]<<", expected -1 sigma is: "<<yMinus[i]<<", observed limit is: "<<z[i]<<endl;
  }

  //canvas->SetGrid();
  canvas->SetLogy();
  
  TH1 * h;
  //h = canvas->DrawFrame(100., 1e-5, 1500., 1e6); //2DSA gluios and stops
  h = canvas->DrawFrame(100., 1e-5, 1000., 1e3); //2DSA
  //h = canvas->DrawFrame(100., 1e-5, 1000., 1e4); //1DSA
  //h->SetTitle(";m [GeV];#sigma [pb]");
  h->SetTitle(";m_{mchamp} [GeV];#sigma(pp #rightarrow mchamp mchamp) [pb]");
  //h->SetTitle(";m_{mchamp} [GeV];#sigma(pp #rightarrow mch mch) #times BF(mch #rightarrow #mu#mu)  [pb]");
  //h->SetTitle("Beamgap Expt;m_{#tilde{g}} [GeV/c^{2}]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");
  
  // not covered region
  TBox* nc = new TBox(100., .1, 150., 5e2);
  nc->SetFillStyle(3354);
  nc->SetFillColor(kRed-4);
  //nc->Draw();
  
  /*
  // details
  //TPaveText* blurb = new TPaveText(305., 1.e1, 550., 4.5e2);
  TPaveText* blurb = new TPaveText(0.25, 0.70, 0.50, 0.92, "NDC");
  blurb->AddText("CMS Preliminary 2012");
  
  std::stringstream label;
  label<<"#int L dt = 19.7 fb^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");
  double peakInstLumi=maxInstLumi;
  int exponent=30;
  while (peakInstLumi>10) {
    peakInstLumi/=10.;
    ++exponent;
  }
  //label<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
  //blurb->AddText(label.str().c_str());
  //label.str("");
  label << "#sqrt{s} = " << ENERGY << " TeV";
  blurb->AddText(label.str().c_str());
  //blurb->AddText("m_{#tilde{g}} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{t}} - m_{#tilde{#chi}^{0}} = 180 GeV/c^{2}");	
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.033);
  */
  
  // legend
  TBox *legbg = new TBox(600., 1.e1, 900., 4e2);
  //legbg->Draw();
  //TLegend *leg = new TLegend(600., 1.e1, 900., 4e2,"95% C.L. Limits","");
  //TLegend* leg = new TLegend(0.67, 0.70, 0.82, 0.92,"95% CL Limits:","NDC");
  /////////TLegend* leg = new TLegend(0.52, 0.70, 0.77, 0.92,"95% CL Limits:","NDC");
  TLegend* leg = new TLegend(0.45, 0.70, 0.70, 0.92,"95% CL Limits:","NDC");
  leg->SetTextSize(0.033);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);

  leg->AddEntry(g_obs_mchamp, "Observed, 10 #mus - 1000 s", "lp");
  leg->AddEntry(g_mchamp, "Expected, 10 #mus - 1000 s", "l");
  leg->AddEntry(g_exp_1sig, "Expected #pm1#sigma, 10 #mus - 1000 s", "lf");
  leg->AddEntry(g_exp_2sig, "Expected #pm2#sigma, 10 #mus - 1000 s", "lf");
  leg->AddEntry(g_thMchamp, "LO Prediction", "l");
  /*
  leg->AddEntry(g_gluino, "Expected Gluino Limit, 10 #mus - 1000 s", "l");
  leg->AddEntry(g_thGluino, "Gluino LO Prediction", "l");
  leg->AddEntry(g_stop, "Expected Stop Limit, 10 #mus - 1000 s", "l");
  leg->AddEntry(g_thStop, "Stop LO Prediction", "l");
  */
  //leg->AddEntry(g_thGluino, "NLO+NLL #tilde{g}", "l");
  //leg->AddEntry(g_gluino, "Obs.: 10 #mus - 1000 s Counting Exp. (#tilde{g})", "l");
  //leg->AddEntry(g_tpg, "Obs.: 10 #mus Timing Profile (#tilde{g})", "l");
  //leg->AddEntry(g_thStop, "NLO+NLL #tilde{t}", "l");
  //leg->AddEntry(g_stop, "Obs.: 10 #mus - 1000 s Counting Exp. (#tilde{t})", "l");
  //leg->AddEntry(g_tps, "Obs.: 10 #mus Timing Profile (#tilde{t})", "l");
  //leg->AddEntry(graph_em, "Obs.: 10 #mus - 1000 s Counting Exp. (EM only)", "l");
  //  leg->AddEntry(graph1, "Obs.: 570 ns Counting Exp.", "l");
  leg->Draw();
  
  
  
  /*
  // gluino curves
  g_gluino->SetLineColor(kBlue);
  g_gluino->SetLineStyle(2);
  g_gluino->SetLineWidth(3);
  g_gluino->Draw("l");

  g_tpg->SetLineColor(kBlue);
  g_tpg->SetLineStyle(3);
  g_tpg->SetLineWidth(3);
  //g_tpg->Draw("l");

  // theory line
  g_thGluino->SetLineColor(kGreen);
  g_thGluino->SetLineStyle(1);
  g_thGluino->SetLineWidth(2);
  g_thGluino->SetFillStyle(3001);
  g_thGluino->SetFillColor(kGreen-4);
  g_thGluino->Draw("l3");


  
   // stop curves
  g_stop->SetLineColor(kRed);
  g_stop->SetLineStyle(2);
  g_stop->SetLineWidth(2);
  g_stop->Draw("l");

  g_tps->SetLineColor(kRed);
  g_tps->SetLineStyle(3);
  g_tps->SetLineWidth(3);
  //g_tps->Draw("l");
   
  g_thStop->SetLineColor(kOrange);
  g_thStop->SetLineStyle(1);
  g_thStop->SetLineWidth(2);
  g_thStop->SetFillStyle(3001);
  g_thStop->SetFillColor(kOrange-4);
  g_thStop->Draw("l3");
  */

  // mchamp curves
  // 2 sigma band
  g_exp_2sig->SetLineColor(0);
  g_exp_2sig->SetLineStyle(0);
  g_exp_2sig->SetLineWidth(0);
  g_exp_2sig->SetFillColor(kYellow);
  g_exp_2sig->SetFillStyle(1001);
  g_exp_2sig->Draw("3");

  // 1 sigma band 
  // g_exp_1sig->SetLineColor(8);                                                                                                                                                           
  g_exp_1sig->SetLineColor(0);
  g_exp_1sig->SetLineStyle(0);
  g_exp_1sig->SetLineWidth(0);
  // g_exp_1sig->SetFillColor(8);                                                                                                                                                           
  g_exp_1sig->SetFillColor(kGreen);
  g_exp_1sig->SetFillStyle(1001);
  // g_exp_1sig->SetFillStyle(3005);                                                                                                                                                        
  g_exp_1sig->Draw("3");
  // g_exp_1sig->Draw("lX");                                                                                                                                                                

  g_obs_mchamp->SetLineStyle(1);
  g_obs_mchamp->SetLineWidth(2);
  g_obs_mchamp->SetMarkerStyle(20);
  g_obs_mchamp->SetMarkerSize(1);
  g_obs_mchamp->Draw("pl");

  //g_mchamp->SetLineColor(kBlue);
  g_mchamp->SetLineStyle(2);
  //g_mchamp->SetLineStyle(1);
  g_mchamp->SetLineWidth(3);
  g_mchamp->SetMarkerStyle(20);
  g_mchamp->SetMarkerSize(1);
  g_mchamp->Draw("l");

  // theory line
  g_thMchamp->SetLineColor(kRed);
  g_thMchamp->SetLineStyle(1);
  g_thMchamp->SetLineWidth(2);
  g_thMchamp->SetFillStyle(3001);
  g_thMchamp->SetFillColor(kRed-4);
  g_thMchamp->Draw("l3");

  // theory line label
  TLatex* th = new TLatex(480., 4., "NLO+NLL #tilde{g}");
  th->SetTextColor(kBlue);
  th->SetTextFont(42);
  th->SetTextSize(0.035);
  //th->Draw();

  TLatex* ths = new TLatex(330., 2., "NLO+NLL #tilde{t}");
  ths->SetTextColor(kRed);
  ths->SetTextFont(42);
  ths->SetTextSize(0.035);
  //ths->Draw();

  TLatex* thm = new TLatex(480., 4., "NLO+NLL mchamp");
  //thm->SetTextColor(kBlue);
  thm->SetTextFont(42);
  thm->SetTextSize(0.035);
  //thm->Draw();

  // not explored label
  TText* ne = new TText(125., .2, "Not Sensitive");
  ne->SetTextColor(kRed+1);
  ne->SetTextFont(42);
  ne->SetTextAngle(90);
  ne->SetTextSize(0.035);
  //ne->Draw();

  //blurb->Draw();

  canvas->RedrawAxis();

  CMS_lumi(canvas, iPeriod, iPos);

  canvas->Print("massLimit.pdf");
  canvas->Print("massLimit.png");
  canvas->Print("massLimit.C");

  plots.calculateIntercepts();

  TFile* fnew = new TFile("histos.root", "recreate");
  fnew->cd();
  g_obs_mchamp->Write();
  g_mchamp->Write();
  g_thMchamp->Write();

}