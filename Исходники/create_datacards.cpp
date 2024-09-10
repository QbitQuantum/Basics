void compareSystVariable( const std::string& dirName, const std::string& channel, const std::string& dataset, TTree* tree_central, TFile* file_systUp, TFile* file_systDown, const std::string& fullSelection, const std::string& systName, const std::string& varName, const std::string& axisTitle, const std::string& units, int nBins, float xMin, float xMax, const std::string& suffix) {


  DrawBase* db = new DrawBase("syst" );

  TTree* tree_systUp = (TTree*)file_systUp->Get(dataset.c_str());
  TTree* tree_systDown = (file_systDown!=0) ? (TTree*)file_systDown->Get(dataset.c_str()) : 0;

  TH1D* h1_central = new TH1D("central", "", nBins, xMin, xMax);
  TH1D* h1_systUp = new TH1D("systUp", "", nBins, xMin, xMax);
  TH1D* h1_systDown = new TH1D("systDown", "", nBins, xMin, xMax);

  h1_central->Sumw2();
  h1_systUp->Sumw2();
  h1_systDown->Sumw2();

  tree_central->Project( "central", varName.c_str(), fullSelection.c_str() );
  tree_systUp->Project( "systUp", varName.c_str(), fullSelection.c_str() );
  if( tree_systDown!=0 )
    tree_systDown->Project( "systDown", varName.c_str(), fullSelection.c_str() );

  h1_central ->SetLineColor(kBlack);
  h1_systUp  ->SetLineColor(kGreen);
  h1_systDown->SetLineColor(kRed);

  h1_central ->SetLineWidth(2);
  h1_systUp  ->SetLineWidth(2);
  h1_systDown->SetLineWidth(2);

  //h1_systUp  ->SetLineStyle(2);
  //h1_systDown->SetLineStyle(2);


  TLegend* legend = new TLegend( 0.6, 0.66, 0.9, 0.92, dataset.c_str() );
  legend->SetTextFont(42);
  legend->SetFillColor(kWhite);
  legend->SetTextSize(0.038);
  legend->SetTextColor(kBlack);
  legend->AddEntry( h1_central, "Central", "L" );
  std::string systUp_text = systName + " +1#sigma";
  std::string systDown_text = systName + " -1#sigma";
  legend->AddEntry( h1_systUp, systUp_text.c_str(), "L" );
  if( tree_systDown!=0 )
    legend->AddEntry( h1_systDown, systDown_text.c_str(), "L" );


  float yMax = 1.6*h1_central->GetMaximum();


  TH2D* h2_axes = new TH2D( "axes", "", 10, xMin, xMax, 10, 0., yMax);
  std::string xTitle = axisTitle;
  if( units!="" ) xTitle = xTitle + " [" + units + "]";
  h2_axes->SetXTitle(xTitle.c_str());
  h2_axes->SetYTitle( "Events" );

  TCanvas* c1 = new TCanvas("c1", "", 600, 600);
  c1->cd();


  TPaveText* labelTop = db->get_labelTop();

  h2_axes->Draw();
  legend->Draw("same");   
  labelTop->Draw("same");
  h1_central->Draw("h same");
  h1_systUp->Draw("h same");
  if( tree_systDown!=0 )
    h1_systDown->Draw("h same");


  gPad->RedrawAxis();

  std::string canvasName = dirName + "/" + channel + "/syst" + systName + "_" + varName + "_" + dataset + "_" + channel;
  if( suffix!="" ) canvasName = canvasName + "_" + suffix;
  std::string canvasName_eps = canvasName + ".eps";
  std::string canvasName_png = canvasName + ".png";

  c1->SaveAs(canvasName_eps.c_str());
  c1->SaveAs(canvasName_png.c_str());


  delete db;

  delete h1_central;
  delete h1_systUp;
  delete h1_systDown;

  delete h2_axes;

  delete legend;
  delete c1;



}