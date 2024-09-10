void make_overlay_Plot(TH1D *SS_hist, TH1D *OS_hist, configuration *myconfig){
  TCanvas *c1 = new TCanvas("c1","C1",10,10,1280,960);
  gPad->SetTopMargin(0.08);
  gPad->SetRightMargin(0.04);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTickx();
  gPad->SetTicky();
  //gPad->SetLogy();
  //hist->GetYaxis()->SetTitleOffset(0.8);

  double ymax = TMath::Max(SS_hist->GetMaximum(),OS_hist->GetMaximum());

  //SS_hist->SetLineWidth(2);
  SS_hist->SetLineColor(kOrange+1);

  //OS_hist->SetLineWidth(2);
  OS_hist->SetLineColor(kBlue+2);

  OS_hist->GetXaxis()->SetLabelSize(0.05);
  OS_hist->GetYaxis()->SetLabelSize(0.05);
  OS_hist->GetXaxis()->SetTitleSize(0.05);
  OS_hist->GetYaxis()->SetTitleSize(0.05);
  OS_hist->GetYaxis()->SetRangeUser(0,1.2*ymax);

  //SS_hist->SetFillColorAlpha(kOrange+1, 0.35);
  //SS_hist->SetFillColor(kOrange+1);
  OS_hist->Draw("hist");
  SS_hist->Draw("histsame");

  TPaveText *blank_box = new TPaveText(1.001-gPad->GetRightMargin(),gPad->GetBottomMargin(),1.0,gPad->GetBottomMargin()+0.05,"BRNDC");
  blank_box->SetBorderSize(0);blank_box->SetFillColor(kWhite);blank_box->SetTextAlign(12);blank_box->SetFillStyle(1001);
  blank_box->AddText(" ");
  blank_box->Draw();
  OS_hist->Draw("axis same");

  if(myconfig->get_particle().Contains("Xic") && static_cast<TString>(OS_hist->GetName()).Contains("pi")){

    c1->Update();
    double Xic_2645_mass = 2646;
    double Xic_2790_mass = 2790 - 107.5;//107.5 : Xic' - Xic mass diffrrence
    double LQCD_Xicc_mass = 3610;

    TArrow Xic_arrows;
    Xic_arrows.SetAngle(40);
    Xic_arrows.SetLineWidth(2);
    Xic_arrows.DrawArrow(Xic_2645_mass,0.85*gPad->GetUymax(),Xic_2645_mass,0.88*gPad->GetUymax(),0.03,"<|");
    Xic_arrows.DrawArrow(Xic_2790_mass,0.6*gPad->GetUymax(),Xic_2790_mass,0.7*gPad->GetUymax(),0.03,"<|");
    Xic_arrows.DrawArrow(LQCD_Xicc_mass,0.10*gPad->GetUymax(),LQCD_Xicc_mass,0.2*gPad->GetUymax(),0.03,"<|");

    TLatex Xic_labels;Xic_labels.SetTextAlign(12);Xic_labels.SetTextFont(42);Xic_labels.SetTextSize(0.05);
    Xic_labels.DrawLatex(Xic_2645_mass-10,0.93*gPad->GetUymax(),"#Xi_{c}(2645)");
    Xic_labels.DrawLatex(Xic_2790_mass-10,0.75*gPad->GetUymax(),"#Xi_{c}(2790)#rightarrow#Xi_{c}'#pi");
    Xic_labels.SetTextAlign(22);
    Xic_labels.DrawLatex(LQCD_Xicc_mass,0.25*gPad->GetUymax(),"LQCD #Xi_{cc}");

  }

  if(myconfig->get_particle().CompareTo("Xic") == 0 && static_cast<TString>(OS_hist->GetName()).Contains("K")){

    c1->Update();

    double Marco_1_QVal = 40.0;
    double Marco_2_QVal = 90.0;
    double Marco_3_QVal = 105.0;
    double Marco_4_QVal = 128.0;
    double Marco_5_QVal = 160.0;

    double peak1_mass = Marco_1_QVal + 2469 + 494;
    double peak2_mass = Marco_2_QVal + 2469 + 494;
    double peak3_mass = Marco_3_QVal + 2469 + 494;
    double peak4_mass = Marco_4_QVal + 2469 + 494;
    double peak5_mass = Marco_5_QVal + 2469 + 494;

    TArrow OmegacStar_arrows;
    OmegacStar_arrows.SetAngle(40);
    OmegacStar_arrows.SetLineWidth(2);
    OmegacStar_arrows.DrawArrow(peak1_mass,0.85*gPad->GetUymax(),peak1_mass,0.88*gPad->GetUymax(),0.03,"<|");
    OmegacStar_arrows.DrawArrow(peak2_mass,0.85*gPad->GetUymax(),peak2_mass,0.88*gPad->GetUymax(),0.03,"<|");
    OmegacStar_arrows.DrawArrow(peak3_mass,0.85*gPad->GetUymax(),peak3_mass,0.88*gPad->GetUymax(),0.03,"<|");
    OmegacStar_arrows.DrawArrow(peak4_mass,0.85*gPad->GetUymax(),peak4_mass,0.88*gPad->GetUymax(),0.03,"<|");
    OmegacStar_arrows.DrawArrow(peak5_mass,0.85*gPad->GetUymax(),peak5_mass,0.88*gPad->GetUymax(),0.03,"<|");

    TLatex OmegacStar_labels;OmegacStar_labels.SetTextAlign(21);OmegacStar_labels.SetTextFont(42);OmegacStar_labels.SetTextSize(0.05);
    OmegacStar_labels.DrawLatex(peak1_mass,0.90*gPad->GetUymax(),"1");
    OmegacStar_labels.DrawLatex(peak2_mass,0.90*gPad->GetUymax(),"2");
    OmegacStar_labels.DrawLatex(peak3_mass,0.90*gPad->GetUymax(),"3");
    OmegacStar_labels.DrawLatex(peak4_mass,0.90*gPad->GetUymax(),"4");
    OmegacStar_labels.DrawLatex(peak5_mass,0.90*gPad->GetUymax(),"5");

  }

  TLegend *leg;
  if(static_cast<TString>(SS_hist->GetName()).Contains("SB"))leg = new TLegend(gPad->GetLeftMargin()+0.06,0.82-gPad->GetTopMargin(),0.40-gPad->GetLeftMargin(),0.97-gPad->GetTopMargin());
  else leg = new TLegend(0.6,0.82-gPad->GetTopMargin(),0.97-gPad->GetRightMargin(),0.97-gPad->GetTopMargin());
  leg->SetBorderSize(0);leg->SetFillColor(kWhite);leg->SetFillStyle(1001);leg->SetTextAlign(12);leg->SetTextSize(0.05);leg->SetTextFont(42);
  if(static_cast<TString>(OS_hist->GetName()).Contains("IPfail"))leg->SetHeader("Multiple candidates");
  if(static_cast<TString>(OS_hist->GetName()).Contains("pi")){
    temp = "#Xi_{c}^{#pm}#pi^{#mp} + c.c.";
    if(myconfig->get_particle().Contains("Xic0"))temp = "#Xi_{c}^{0}#pi^{#mp} + c.c.";
    if(myconfig->get_particle().Contains("Omega"))temp = "#Omega_{c}^{0}#pi^{#mp} + c.c.";
  }
  else if(static_cast<TString>(OS_hist->GetName()).Contains("K")){
    temp = "#Xi_{c}^{#pm}K^{#mp} + c.c.";
    if(myconfig->get_particle().Contains("Xic0"))temp = "#Xi_{c}^{0}K^{#mp} + c.c.";
    if(myconfig->get_particle().Contains("Omega"))temp = "#Omega_{c}^{0}K^{#mp} + c.c.";
  }
  else{
    temp = "from #Xi_{c}^{#pm} signal";
    if(myconfig->get_particle().Contains("Xic0"))temp = "from #Xi_{c}^{0} signal";
    if(myconfig->get_particle().Contains("Omega"))temp = "from #Omega_{c}^{0} signal";
  }
  leg->AddEntry(OS_hist,temp,"l");
  if(static_cast<TString>(OS_hist->GetName()).Contains("pi")){
    temp = "#Xi_{c}^{#pm}#pi^{#pm} + c.c.";
    if(myconfig->get_particle().Contains("Xic0"))temp = "#Xi_{c}^{0}#pi^{#pm} + c.c.";
    if(myconfig->get_particle().Contains("Omega"))temp = "#Omega_{c}^{0}#pi^{#pm} + c.c.";
  }
  else if(static_cast<TString>(OS_hist->GetName()).Contains("K")){
    temp = "#Xi_{c}^{#pm}K^{#pm} + c.c.";
    if(myconfig->get_particle().Contains("Xic0"))temp = "#Xi_{c}^{0}K^{#pm} + c.c.";
    if(myconfig->get_particle().Contains("Omega"))temp = "#Omega_{c}^{0}K^{#pm} + c.c.";
  }
  else temp = "from sidebands";
  leg->AddEntry(SS_hist,temp,"l");
  leg->Draw();

  temp = myconfig->get_dumpdir()+"/Plots/";
  if(!gSystem->OpenDirectory(temp))gSystem->mkdir(temp);

  temp += static_cast<TString>(OS_hist->GetName()) + "_" + myconfig->get_current_cs() + ".pdf";
  if(!myconfig->is_debug()) c1->SaveAs(temp);
  delete c1;
  return;
}