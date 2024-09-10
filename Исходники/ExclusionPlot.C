void process_syst_plot(TH2F *rhisto,string saveto,int scantype, std::string scanx = "") {
  TH2F *histo = prep_histo(rhisto,scantype); // this is to be independent of the style used at creation time
  float rightmargin=gStyle->GetPadRightMargin();
  gStyle->SetPadRightMargin(0.20);
  TString name = rhisto->GetName();
  if(name.Contains("Nevents")) gStyle->SetPadRightMargin(0.22);
  TCanvas *can = new TCanvas("syst_plot","Systematics Plot");
  set_range(histo,scantype,true);
  
  histo->GetZaxis()->CenterTitle();
  gStyle->SetStripDecimals(false);
  histo->GetXaxis()->SetDecimals(true);
  
  if(name.Contains("efficiency")) {
    histo->GetZaxis()->SetTitle("A #times #varepsilon (#geq 1 Z(ll))");
    histo->GetZaxis()->CenterTitle(0);
    //histo->GetZaxis()->SetRangeUser(0.0,0.15);
  }
  if(name.Contains("Nevents")) {
     histo->GetZaxis()->SetTitle("N(events)");
     histo->GetZaxis()->SetTitleOffset(histo->GetZaxis()->GetTitleOffset()+0.4);
  }
  if(name.Contains("sysjes")) {
    histo->GetZaxis()->SetTitle("Jet Energy Scale");
    histo->GetZaxis()->SetRangeUser(0.0,0.2);
  }
  if(name.Contains("sysjsu")) {
    histo->GetZaxis()->SetTitle("JZB Scale Uncertainty");
    histo->GetZaxis()->SetRangeUser(0.0,0.5);
  }
  if(name.Contains("sysresmap")) {
    histo->GetZaxis()->SetTitle("Resulution");
    histo->GetZaxis()->SetRangeUser(0.0,0.5);
  }
  if(name.Contains("sysstatmap")) {
    histo->GetZaxis()->SetTitle("Statistical Error");
    histo->GetZaxis()->SetRangeUser(0.0,0.01);
  }
  if(name.Contains("systotmap")) {
    histo->GetZaxis()->SetTitle("All Systematic Errors");
    histo->GetZaxis()->SetRangeUser(0.0,0.5);
  }
  
  
  histo->Draw("COLZ");
  DrawPrelim();
  float xpos_of_text = 0.22;
  if(name.Contains("_noscefficiencymap"))  {
    // Add some more decorations on these publication plots
    write_SMS_text( scantype, scanx, xpos_of_text );
    // Decode name and get JZB cut
    TPRegexp pat("\\d+$");
    size_t index = name.Index(pat,0);
    string cut = string("JZB > ")+(name(index,name.Length()-index).Data())+" GeV";
    //string cut = string("#splitline{JZB > ")+(name(index,name.Length()-index).Data())+" GeV}{n_{jets} #geq 3}"; //paper style
    TText *text = write_text(xpos_of_text,0.73,cut);
    text->SetTextAlign(11);
    text->SetTextSize(0.035);
    text->Draw();
    draw_diagonal_xchange( scantype, scanx );
  }
  
  CompleteSave(can,(saveto+(string)histo->GetName()));

  gStyle->SetPadRightMargin(rightmargin);
  
  delete can;
}