//----------------------------------------------------------------------
/// show the jets contained in filename (as produced by
/// ClusterSequence::print_jets_for_root()), with an optional label
TCanvas * showjets (const char * filename, const char * label = 0) {

  // display the various 2-d drawing options
  gROOT->Reset();

  // set up canvas
  TCanvas * lego = new TCanvas("lego","lego options",400,50,800,600);
  lego->SetTheta(30.0);
  lego->SetPhi(20.0);

  // orientation used for plots in subtraction paper
  //lego->SetTheta(62.15);
  //lego->SetPhi(9.15);

  ////vector<double> col 

  set_default_colours(lego);

  TPaveLabel pl;
   
  JetHist * jets = new JetHist(filename);
  jets->stack.Draw("lego1"); // cyl does not work with 5.16
  if (label != 0) {
    Float_t x1=0.63, y1=0.875, x2=0.95, y2=0.925;
    pl.DrawPaveLabel(x1,y1,x2,y2,label,"brNDC");
  } else if (jets->comment() != "") {
    Float_t x1=0.15, y1=0.875, x2=0.95, y2=0.925;
    pl.DrawPaveLabel(x1,y1,x2,y2,jets->comment().c_str(),"brNDC");
  }

  // normal histogram labels not working, so draw them by hand
  TLatex l;
  l.SetTextAlign(22);
  l.SetTextSize(0.05);
  //l.DrawLatex(0.0,0.85,"anti-k_{t}, R=1");

  l.SetTextSize(0.04);
  l.DrawLatex(0.20,-0.98,"y");
  l.SetTextAlign(32);
  l.DrawLatex(-0.7,0.8,"p_{t} [GeV]");
  l.DrawLatex(-0.6,-0.78,"#phi");

  // do not delete jets -- otherwise you lose everything!;

  return lego;
  ///
  lego->Update();
}