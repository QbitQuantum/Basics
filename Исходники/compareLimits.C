void compareLimits(const char* filename, const char* channelstr, bool expected, bool observed, const char* type, double minimum=0., double maximum=20., bool log=false, const char* label="#scale[1.5]{CMS}   h,H,A#rightarrow#tau#tau                     19.7 fb^{-1} (8 TeV) + 4.9 fb^{-1} (7 TeV)", bool legendOnRight=true, bool legendOnTop=true, bool ggH=true)
{
  SetStyle();

  std::map<std::string, unsigned int> colors;
  colors["0jet"       ] = kBlue;
  colors["1jet"       ] = kRed;
  colors["2jet"       ] = kMagenta;
  colors["vbf"        ] = kMagenta;
  colors["boost"      ] = kGreen;
  colors["btag"       ] = kRed; 
  colors["nobtag"     ] = kBlue; 
  colors["em"         ] = kBlue;
  colors["et"         ] = kRed;
  colors["mt"         ] = kGreen;
  colors["mm"         ] = kMagenta;
  colors["ee"         ] = kCyan;
  colors["tt"         ] = kMagenta+3;
  colors["vhtt"       ] = kCyan-6;
  colors["cmb"        ] = kBlack;
  colors["htt"        ] = kBlack;
  colors["ggH"        ] = kRed;
  colors["bbH"        ] = kBlue;
  colors["HIG-11-020" ] = kBlue+2;
  colors["HIG-11-029" ] = kRed+2;
  colors["HIG-12-018" ] = kBlue;
  colors["HIG-12-032" ] = kRed+2;
  colors["HIG-12-043" ] = kRed;
  colors["HIG-12-050" ] = kRed;

  std::cout << " *******************************************************************************************************\n"
	    << " * Usage     : root -l                                                                                  \n"
	    << " *             .x MitLimits/Higgs2Tau/macros/compareLimits.C+(file, chn, exp, obs, type, min, max, log) \n"
	    << " *                                                                                                      \n"
	    << " * Arguments :  + file     const char*      full path to the input file                                 \n"
	    << " *              + chn      const char*      list of channels; choose between: 'cmb', 'htt', 'emu',      \n"
	    << " *                                          'etau', 'mutau', 'mumu', 'vhtt', 'hgg', 'hww', 'ggH',       \n"
	    << " *                                          'bbH', 'nomix[-200, +200]', 'mhmax[-400, -200, +200]'       \n"
	    << " *                                          'mhmax[+400, +600, +800]', 'test-0...5', 'saeff', 'gluph'   \n"
	    << " *                                          The list should be comma separated and may contain          \n"
	    << " *                                          whitespaces                                                 \n"
	    << " *              + exp       bool            compare expected limits                                     \n"
	    << " *              + obs       bool            compare observed limits                                     \n"
	    << " *              + type      const char*     type of plot; choose between 'sm-xsec', 'mssm-xsec' and     \n"
	    << " *                                          'mssm-tanb'                                                 \n"
	    << " *              + max       double          maximum of the plot (default is 20.)                        \n"
	    << " *                                                                                                      \n"
	    << " *              + min       double          minimum of the plot (default is  0.)                        \n"
	    << " *                                                                                                      \n"
	    << " *              + log       bool            set log scale yes or no (default is false)                  \n"
	    << " *                                                                                                      \n"
	    << " *******************************************************************************************************\n";

  /// open input file  
  TFile* inputFile = new TFile(filename); if(inputFile->IsZombie()){ std::cout << "ERROR:: file: " << filename << " does not exist.\n"; }
  
  /// prepare input parameters
  std::vector<std::string> channels;
  string2Vector(cleanupWhitespaces(channelstr), channels);

  /// prepare histograms
  std::vector<TGraph*> hobs, hexp;
  for(unsigned i=0; i<channels.size(); ++i){
    if(observed) hobs.push_back(get<TGraph>(inputFile, std::string(channels[i]).append("/observed").c_str()));
    if(expected) hexp.push_back(get<TGraph>(inputFile, std::string(channels[i]).append("/expected").c_str()));
  }

  /// do the drawing
  TCanvas* canv1 = new TCanvas("canv1", "Limit Comparison", 600, 600);
  canv1->cd();
  canv1->SetGridx(1);
  canv1->SetGridy(1);
  if((std::string(type) == std::string("mssm-xsec") || std::string(type) == std::string("mssm-tanb")) && log) canv1->SetLogx(1); 

  bool firstPlot=true;
  for(unsigned int i=0; i<hexp.size(); ++i){
    if(firstPlot){
	if(log){ canv1->SetLogy(1); }
	hexp[i]->SetMaximum(maximum);
	hexp[i]->SetMinimum(minimum);
      
      // format x-axis
      std::string x_title;
      if(std::string(type) == std::string("mssm-tanb")){
	x_title = std::string("m_{A} [GeV]");
      }
      else if(std::string(type) == std::string("mssm-xsec")){
	x_title = std::string("m_{#phi} [GeV]");
      }
      else{
	x_title = std::string("m_{H} [GeV]");
      }
      hexp[i]->GetXaxis()->SetTitle(x_title.c_str());
      hexp[i]->GetXaxis()->SetLabelFont(62);
      hexp[i]->GetXaxis()->SetTitleFont(62);
      hexp[i]->GetXaxis()->SetTitleColor(1);
      hexp[i]->GetXaxis()->SetTitleOffset(1.05);
      if((std::string(type) == std::string("mssm-xsec") || std::string(type) == std::string("mssm-tanb")) && log){
	hexp[i]->GetXaxis()->SetNdivisions(50005, "X");
	hexp[i]->GetXaxis()->SetMoreLogLabels();
	hexp[i]->GetXaxis()->SetNoExponent();
	hexp[i]->GetXaxis()->SetLabelSize(0.040);
      }
      hexp[i]->GetXaxis()->SetLimits(hexp[i]->GetX()[0]-.1, hexp[i]->GetX()[hexp[i]->GetN()-1]+.1);
      if(std::string(type) == std::string("mssm-xsec") || std::string(type) == std::string("mssm-tanb")){
	if(log){
	  hexp[i]->GetXaxis()->SetLimits(hexp[i]->GetX()[0], hexp[i]->GetX()[hexp[i]->GetN()-1]+.1);
	}
	else{
	  hexp[i]->GetXaxis()->SetLimits(hexp[i]->GetX()[0]-.1, hexp[i]->GetX()[hexp[i]->GetN()-1]+.1);
	}      
      }

      // format y-axis
      std::string y_title;
      if( std::string(type) == std::string("mssm-xsec") ){
	if(ggH) y_title = std::string("95% CL limit on #sigma(gg#rightarrow#phi)#timesBR [pb]");
	else y_title = std::string("95% CL limit on #sigma(gg#rightarrowbb#phi)#timesBR [pb]");
      }
      else if(  std::string(type) == std::string("mssm-tanb")  ){
	y_title = std::string("#bf{tan#beta}");
      }
      else{
	y_title = std::string("95% CL limit on #sigma/#sigma_{SM}");
      }
      hexp[i]->GetYaxis()->SetTitle(y_title.c_str());
      hexp[i]->GetYaxis()->SetLabelFont(62);
      hexp[i]->GetYaxis()->SetTitleFont(62);
      hexp[i]->GetYaxis()->SetTitleOffset(1.05);
      hexp[i]->GetYaxis()->SetLabelSize(0.03);
    }
    hexp[i]->SetLineStyle(11.);
    hexp[i]->SetLineWidth( 3.); 
    hexp[i]->SetLineColor(colors.find(channels[i])->second);
    hexp[i]->SetMarkerStyle(20);
    hexp[i]->SetMarkerSize(MARKER_SIZE);
    hexp[i]->SetMarkerColor(colors.find(channels[i])->second);
    hexp[i]->Draw(firstPlot ? "APL" : "PLsame");
    //hexp[i]->Draw(firstPlot ? "AL" : "Lsame");
    firstPlot=false;
  }
  for(unsigned int i=0; i<hobs.size(); ++i){
    if(firstPlot){
      if(log){ canv1->SetLogy(1); }
      hobs[i]->SetMaximum(maximum);
      hobs[i]->SetMinimum(minimum);
      
      // format x-axis
      std::string x_title;
      if(std::string(type) == std::string("mssm-tanb")){
	x_title = std::string("m_{A} [GeV]");
      }
      else if(std::string(type) == std::string("mssm-xsec")){
	x_title = std::string("m_{#phi} [GeV]");
      }
      else{
	x_title = std::string("m_{H} [GeV]");
      }
      hobs[i]->GetXaxis()->SetTitle(x_title.c_str());
      hobs[i]->GetXaxis()->SetLabelFont(62);
      hobs[i]->GetXaxis()->SetTitleFont(62);
      hobs[i]->GetXaxis()->SetTitleColor(1);
      hobs[i]->GetXaxis()->SetTitleOffset(1.05);
      if((std::string(type) == std::string("mssm-xsec") || std::string(type) == std::string("mssm-tanb")) && log){
	hobs[i]->GetXaxis()->SetNdivisions(50005, "X");
	hobs[i]->GetXaxis()->SetMoreLogLabels();
	hobs[i]->GetXaxis()->SetNoExponent();
	hobs[i]->GetXaxis()->SetLabelSize(0.040);
      }
      hobs[i]->GetXaxis()->SetLimits(hobs[i]->GetX()[0]-.1, hobs[i]->GetX()[hobs[i]->GetN()-1]+.1);
      if(std::string(type) == std::string("mssm-xsec") || std::string(type) == std::string("mssm-tanb")){
	if(log){
	  hobs[i]->GetXaxis()->SetLimits(hobs[i]->GetX()[0], hobs[i]->GetX()[hobs[i]->GetN()-1]+.1);
	}
	else{
	  hobs[i]->GetXaxis()->SetLimits(hobs[i]->GetX()[0]-.1, hobs[i]->GetX()[hobs[i]->GetN()-1]+.1);
	}      
      }
      
      // format y-axis
      std::string y_title;
      if( std::string(type) == std::string("mssm-xsec") ){
	if(ggH) y_title = std::string("95% CL limit on #sigma#font[42]{(gg#phi)}#upoint#font[52]{B}#font[42]{(#phi#rightarrow#tau#tau)} [pb]");
	else y_title = std::string("95% CL limit on #sigma#font[42]{(bb#phi)}#upoint#font[52]{B}#font[42]{(#phi#rightarrow#tau#tau)} [pb]");
      }
      else if(  std::string(type) == std::string("mssm-tanb")  ){
	y_title = std::string("#bf{tan#beta}");
      }
      else{
	y_title = std::string("95% CL limit on #sigma/#sigma_{SM}");
      }
      hobs[i]->GetYaxis()->SetTitle(y_title.c_str());
      hobs[i]->GetYaxis()->SetLabelFont(62);
      hobs[i]->GetYaxis()->SetTitleOffset(1.05);
      hobs[i]->GetYaxis()->SetLabelSize(0.03);
    }
    hobs[i]->SetLineStyle(11.);
    hobs[i]->SetLineWidth( 3.); 
    hobs[i]->SetLineColor(colors.find(channels[i])->second);
    hobs[i]->SetMarkerStyle(20);
    hobs[i]->SetMarkerSize(MARKER_SIZE);
    hobs[i]->SetMarkerColor(colors.find(channels[i])->second);
    hobs[i]->Draw(firstPlot ? "APL" : "PLsame");
    //hobs[i]->Draw(firstPlot ? "AL" : "Lsame");
    firstPlot=false;
  }
  canv1->RedrawAxis();

  TPaveText* extra;
  if( std::string(type) == std::string("mssm-xsec") ){
    extra = new TPaveText(legendOnRight ? 0.6 : 0.18, 0.50, legendOnRight ? 0.95 : 0.605, 0.60, "NDC");
    extra->SetBorderSize(   0 );
    extra->SetFillStyle (   0 );
    extra->SetTextAlign (  12 );
    extra->SetTextSize  (0.04 );
    extra->SetTextColor (   1 );
    extra->SetTextFont  (  62 );
    if(ggH) extra->AddText("gg#phi");
    else extra->AddText("bb#phi");
    extra->Draw();
  }

  bool firstLeg=true;
  if(observed){
    TLegend* leg1;
    if(expected && observed){
      /// setup the CMS Preliminary
       if(std::string(type) == std::string("mssm-tanb")){
	  if (firstLeg) CMSPrelim(label, "", 0.15, 0.835);
	  leg1 = new TLegend(firstLeg ? 0.60 : 0.20, hobs.size()<5 ? 0.20-0.06*hobs.size() : 0.4, firstLeg ? 0.93 : 0.60, 0.20);
       }
       else{
	  if (firstLeg) CMSPrelim(label, "", 0.135, 0.835);
	  leg1 = new TLegend(firstLeg ? 0.20 : 0.20, hobs.size()<5 ? 0.90-0.08*hobs.size() : 0.6, firstLeg ? 0.63 : 0.60, 0.90);
       }
    }
    else{
      /// setup the CMS Preliminary
      if(std::string(type) == std::string("mssm-tanb")){
	CMSPrelim(label, "", 0.15, 0.835);
	leg1 = new TLegend(legendOnRight?0.60:0.20, hobs.size()<5 ? (legendOnTop?0.90:0.40)-0.04*hobs.size() : (legendOnTop?0.6:0.2), legendOnRight?0.94:0.45, (legendOnTop?0.90:0.40));
	   }
      else{
	CMSPrelim(label, "", 0.135, 0.835);
	leg1 = new TLegend(legendOnRight ? 0.50 : 0.20, hobs.size()<5 ? 0.90-0.08*hobs.size() : 0.6, legendOnRight ? 0.94 : 0.64, 0.90);
      }
    }
    if(std::string(type) == std::string("mssm-tanb")) {leg1->SetTextSize(0.03);}
    //leg1->SetTextSize(0.02);
    leg1->SetBorderSize( 0 );
    leg1->SetFillStyle ( 1001 );
    //leg1->SetFillColor ( 0 );
    leg1->SetFillColor (kWhite);
    leg1->SetHeader( "#bf{observed}" );
    for(unsigned int i=0; i<hobs.size(); ++i){
      leg1->AddEntry( hobs[i] , channel(channels[i]) ? legendEntry(channels[i]).c_str() : legendEntry(channels[i]).append("-Channel").c_str(),  "PL" );
    }
    leg1->Draw("same");
    firstLeg=false;
  }
  if(expected){
    TLegend* leg0;
    if(expected && observed){
      /// setup the CMS Preliminary
      if(std::string(type) == std::string("mssm-tanb")){
	CMSPrelim(label, "", 0.15, 0.835);
	leg0 = new TLegend(legendOnRight ? 0.60 : 0.20, hexp.size()<5 ? 0.20-0.06*hexp.size() : 0.4, legendOnRight ? 0.94 : 0.63, 0.20);
      }
      else{
	CMSPrelim(label, "", 0.135, 0.835);
	leg0 = new TLegend(legendOnRight ? 0.20 : 0.20, hexp.size()<5 ? 0.75-0.08*hexp.size() : 0.6, legendOnRight ? 0.94 : 0.63, 0.75);
      }
    }
    else{
      /// setup the CMS Preliminary
      if(std::string(type) == std::string("mssm-tanb")){
	CMSPrelim(label, "", 0.15, 0.835);
	leg0 = new TLegend(legendOnRight?0.60:0.20, hexp.size()<5 ? (legendOnTop?0.90:0.40)-0.04*hexp.size() : (legendOnTop?0.6:0.2), legendOnRight?0.94:0.45, (legendOnTop?0.90:0.40));
	   }
      else{
	CMSPrelim(label, "", 0.135, 0.835);
	leg0 = new TLegend(legendOnRight ? 0.50 : 0.20, hexp.size()<5 ? 0.90-0.06*hexp.size() : 0.6, legendOnRight ? 0.74 : 0.63, 0.90);
	//leg0 = new TLegend(legendOnRight ? 0.50 : 0.20, hexp.size()<5 ? 0.90-0.08*hexp.size() : 0.6, legendOnRight ? 0.94 : 0.80, 0.90);
      }
    }
    if(std::string(type) == std::string("mssm-tanb")) {leg0->SetTextSize(0.03);}
    leg0->SetBorderSize( 0 );
    leg0->SetFillStyle ( 1001 );
    leg0->SetFillColor (kWhite);
    leg0->SetHeader( "#bf{expected}" );
    for(unsigned int i=0; i<hexp.size(); ++i){
      leg0->AddEntry( hexp[i] , channel(channels[i]) ? legendEntry(channels[i]).c_str() : legendEntry(channels[i]).append("-Channel").c_str(),  "PL" );
    }
    leg0->Draw("same");
    firstLeg=false;
  }
  canv1->Print(std::string("singleLimits").append(expected ? "_expected" : "").append(observed ? "_observed" : "").append(std::string(type).find("mssm")!=std::string::npos ? "_mssm.png" : "_sm.png").c_str());
  canv1->Print(std::string("singleLimits").append(expected ? "_expected" : "").append(observed ? "_observed" : "").append(std::string(type).find("mssm")!=std::string::npos ? "_mssm.pdf" : "_sm.pdf").c_str());
  canv1->Print(std::string("singleLimits").append(expected ? "_expected" : "").append(observed ? "_observed" : "").append(std::string(type).find("mssm")!=std::string::npos ? "_mssm.pdf" : "_sm.eps").c_str());
  return;
}