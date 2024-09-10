// -----------------------------------------------------------------------------
//
TCanvas* createPlot( TDirectory* output_file,
		     std::string output_canvas, 
		     //std::vector< std::vector<std::string> > input_files, 
		     std::vector<std::string> input_files, 
		     std::vector<std::string> input_histos, 
		     std::vector<std::string> input_legend, 
 		     std::vector<int> marker_style, 
 		     std::vector<int> marker_colour, 
 		     std::vector<float> marker_size, 
 		     std::vector<float> lumis, 
		     double lumi,
		     int rebin, 
		     bool norm, 
		     bool log,
		     double min = -1.,
		     double max = -1.,
		     int integral = -1 )
{

  // SetSomeStyles();

  // Check integral
  if ( integral >= input_files.size() ) { integral = -1; }

  // Loop through histogram names
  std::vector<TH1D*> his;
  for ( uint ihis = 0; ihis < input_histos.size(); ++ihis ) {
    if ( integral < 0 || ihis <= integral ) {
      his.push_back( (TH1D*)getHisto( input_files[ihis], input_histos[ihis], "QcdBkgdEst", rebin ) );
    } else {
      his.back()->Add( (TH1D*)getHisto( input_files[ihis], input_histos[ihis], "QcdBkgdEst", rebin ) );
    }
  }
  
  // Create legend
  TLegend* legend = new TLegend( 0.65, 0.52-0.03*his.size(), 0.9, 0.52,  NULL, "brNDC" );
  legend->SetFillColor(0);
  legend->SetLineColor(0); 
  legend->SetTextAlign(31);
  legend->SetTextSize(0.025);
  
  // Create canvas
  TCanvas* aCanvas = createCanvas( output_canvas, output_file, log );
  
  TPaveText* stats = new TPaveText( 0.65, 0.54, 0.9, 0.54+0.03*his.size(), "brNDC" );
  stats->SetFillColor(0);
  stats->SetLineColor(0);

  TLatex* prelim = new TLatex( 0.15, 0.96, "#scale[0.8]{CMS preliminary 2011}" );
  prelim->SetTextSize(0.03);
  prelim->SetNDC();
  std::stringstream ssl; ssl << "#scale[0.8]{#int L dt = " << lumi/1000. << " fb^{-1}, #sqrt{s} = 7 TeV}";
  TLatex* lumistxt = new TLatex( 0.95, 0.96, ssl.str().c_str() );
  lumistxt->SetTextSize(0.03);
  lumistxt->SetNDC();
  lumistxt->SetTextAlign(31);
  
  // For Ted
  bool print_ted = true;
  std::stringstream ted;
  if ( print_ted ) { ted << "self._htMeans = ("; }

  // Loop through histograms
  double aMax = 0.;
  double aMin = 1.e12;
  for ( uint ihis = 0; ihis < his.size(); ++ihis ) {
    if ( !his[ihis] ) { continue; }
    
    // Line colour and fill
    his[ihis]->Scale(lumis[ihis]/100.);
    his[ihis]->SetMarkerStyle(marker_style[ihis]);
    his[ihis]->SetMarkerColor(marker_colour[ihis]);
    his[ihis]->SetMarkerSize(marker_size[ihis]);
    his[ihis]->SetLineColor(marker_colour[ihis]);
    his[ihis]->SetLineStyle(0);
    his[ihis]->SetLineWidth(0);
    
    // Populate legend
    if ( input_legend.size() > ihis ) { legend->AddEntry( his[ihis], input_legend[ihis].c_str(), "ep" ); }
    else                              { legend->AddEntry( his[ihis], input_histos[ihis].c_str(), "ep" ); }

    // Populate stats box
    std::stringstream ss;
    //ss << "Mean=" << int(his[ihis]->GetMean()*100.)/100. << ", RMS=" << int(his[ihis]->GetRMS()*100.)/100.;
    ss << "Entries=" << his[ihis]->GetEntries();
    TText* text = stats->AddText(ss.str().c_str());
    text->SetTextAlign(11);
    text->SetTextSize(0.025);
    text->SetTextColor(marker_colour[ihis]);

    // For Ted
    if ( print_ted ) ted << std::setw(9) << std::scientific << std::setprecision(3) << his[ihis]->GetMean() << ", ";
    
    // Calc min/max number of entries
    if ( his[ihis]->GetMaximum() > aMax ) { aMax = his[ihis]->GetMaximum(); }
    if ( his[ihis]->GetMinimum(1.e-12) < aMin ) { aMin = his[ihis]->GetMinimum(1.e-12); }

  }

  // For Ted
  if ( print_ted ) { 
    ted << ")" << std::endl;
    std::cout << ted.str() << std::endl;
  }

  if ( !his.empty() ) {
    if ( his[0] ) his[0]->GetYaxis()->SetTitleOffset(1.43);
    if ( his[0] ) his[0]->GetYaxis()->SetTitleSize(0.06);
    if ( his[0] ) his[0]->GetXaxis()->SetTitleSize(0.06);
    if ( his[0] ) his[0]->GetXaxis()->SetTitleOffset(0.9);
  }

  // First histo be drawn
  bool first = true;
  for ( uint ihis = 0; ihis < his.size(); ++ihis ) {

    if ( !his[ihis] ) { continue; }
    
    //his[ihis]->GetYaxis()->SetTitle("a.u.");
    
    if ( log ) {
      his[ihis]->SetMaximum( aMax * 10. );
      his[ihis]->SetMinimum( aMin * 0.1 );
    } else {
      his[ihis]->SetMaximum( aMax * 1.1 );
      his[ihis]->SetMinimum( aMin * 0.9 );
    }

    if ( min > 0. ) his[ihis]->SetMinimum( min );
    if ( max > 0. ) his[ihis]->SetMaximum( max );
    
    if ( norm ) {
      std::string options = "";
      if ( first ) { options = "Ehist"; first = false; }
      else { options = "psame"; }
      if ( his[ihis]->GetEntries() > 0. ) { his[ihis]->DrawNormalized(options.c_str()); }
    } else {
      std::string options = "";
      if ( first ) { options = "Ehist"; first = false; }
      else { options = "psame"; }
      his[ihis]->Draw(options.c_str());
    }
    
  } // Loop through histos

  output_file->cd();
  legend->Draw("same");
  stats->Draw("same");
  prelim->Draw("same");
  lumistxt->Draw("same");
  aCanvas->Modified();
  //aCanvas->SaveAs( std::string(output_canvas+".png").c_str() );
  aCanvas->SaveAs( std::string(output_canvas+".pdf").c_str() );
  aCanvas->SaveAs( std::string(output_canvas+".C").c_str() );
  aCanvas->Write();
  return aCanvas;

}