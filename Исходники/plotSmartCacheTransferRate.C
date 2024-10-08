//--------------------------------------------------------------------------------------------------
void plot(long int xStart, long int xEnd, TString text, TString pngFileName)
{
  // Make sure we have the right styles
  MitRootStyle::Init();
  MitRootStyle::SetStyleWide();
  gStyle->SetPadRightMargin(0.07); // to make sure the exponent is on the picture

  // will execute a shell command to get the data
  TString timeSeriesFile("timeSeriesOfRates.txt");

  // Now open our database output
  ifstream input;
  input.open(timeSeriesFile.Data());

  Int_t time=0, nConn=0, nLines=0;
  Double_t rate=0, xMin=double(xStart), xMax=double(xEnd), maxRate=1.0;

  // First loop to determine the boundaries (could be done in one round, dynamically)
  //---------------------------------------------------------------------------------
  while (1) {
    // read in 
    input >> time >> rate >> nConn;
    // check it worked
    if (! input.good())
      break;

    //printf(" Min / Time / Max: %d %d %d\n",xStart,time,xEnd);

    // check whether in our requested time window
    if (xStart>0 && xStart>time)
      continue;
    if (xEnd>0 && xEnd<time)
      continue;
    
    // Show what we are reading
    if (nLines < 5)
      printf(" time=%d, rate=%8f nConnections=%d\n",time, rate, nConn);

    // Determine plot maximum
    if (rate > maxRate)
      maxRate = rate;
    if (nConn > maxRate)
      maxRate = double(nConn);

    nLines++;
  }
  input.close();

  printf(" \n");
  printf(" Found %d measurements.\n",nLines);
  printf(" Maximum tranfer rate at: %6.2f MB/sec\n",maxRate);
  printf(" \n");

  // Open a canvas
  TCanvas *cv = new TCanvas();
  cv->Draw();

  if (nLines<1) {
    printf(" WARNING - no measurements selected.\n");
    plotFrame(double(xStart),double(xEnd));
    double dX = double(xEnd)-double(xStart);
    TText *plotText = new TText(xMin-dX*0.14,0.-(maxRate*1.2*0.14),text.Data());
    printf("Text size: %f\n",plotText->GetTextSize());
    plotText->SetTextSize(0.04);
    plotText->SetTextColor(kBlue);
    plotText->Draw();
    cv->SaveAs(pngFileName.Data());
    return;
  }

  const int numVals = nLines;
  double xVals[numVals];
  double y1Vals[numVals];
  double y2Vals[numVals];

  input.open(timeSeriesFile.Data());

  // Second loop to register the measured values
  //--------------------------------------------
  Int_t i = 0;
  while (1) {
    // read in 
    input >> time >> rate >> nConn;
    // check it worked
    if (!input.good())
      break;

    // check whether in our requested time window
    if (xStart>0 && xStart>time)
      continue;
    if (xEnd>0 && xEnd<time)
      continue;

    xVals[i] = time;
    y1Vals[i] = rate;
    y2Vals[i] = nConn;

    i++;
  }
  input.close();

  // Make a good frame
  plotFrame(xMin,xMax,maxRate);
  double dX = double(xEnd)-double(xStart);
  TText *plotText = new TText(xMin-dX*0.14,0.-(maxRate*1.2*0.14),text.Data());
  plotText->SetTextSize(0.04);
  plotText->SetTextColor(kBlue);
  plotText->Draw();

  // Prepare our graphs
  TGraph* graph1 = new TGraph(numVals, xVals, y1Vals);
  graph1->SetLineColor(2);
  graph1->SetLineWidth(2);
  graph1->SetMarkerColor(4);
  graph1->SetMarkerStyle(21);
  graph1->SetMarkerSize(0.4);
  TGraph* graph2 = new TGraph(numVals, xVals, y2Vals);
  graph2->SetLineColor(3);
  graph2->SetLineWidth(2);
  graph2->SetMarkerColor(4);
  graph2->SetMarkerStyle(20);
  graph2->SetMarkerSize(0.4);

  // Through them into the multigraph
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(graph1,"lp");
  mg->Add(graph2,"lp");

  // Draw the graphs
  mg->Draw("CP");

  // Add a nice legend to the picture
  TLegend *leg = new TLegend(0.4,0.6,0.89,0.89);
  //leg->SetTextSize(0.036);
  leg->SetX1(0.15);
  leg->SetX2(0.30);
  leg->SetY1(0.95);
  leg->SetY2(0.85);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(graph2,"number of tranfers","lp");
  leg->AddEntry(graph1,"data tranfer rate","lp");
  leg->Draw();

  cv->SaveAs(pngFileName);
}