////////////////////////////////////////////////////////////
//
// This function performs a compatibility test between two
// histogram based on the Kolmogorov-Smirnof algorithm. It
// also prints the value in a TPaveLabel at the upper-right
// corner.
// The return value contains the result of the test
//
double KolmogorovTest(TH1 *h1, TH1 *h2){

  double mya_array[1300], myb_array[1300];
  vector<double> mya;
  vector<double> myb;
  
  
  for (int i=0; i<h1->GetNbinsX(); i++){
    mya.push_back(h1->GetBinContent(i+1));
    myb.push_back(h2->GetBinContent(i+1));
  }

  sort(mya.begin(),mya.end());
  sort(myb.begin(),myb.end()); 
  copy(mya.begin(),mya.end(),mya_array);
  copy(myb.begin(),myb.end(),myb_array);
  
  const int nbinsa = h1->GetNbinsX();
  const int nbinsb = h2->GetNbinsX();
   
  double kstest = TMath::KolmogorovTest(nbinsa, mya_array,
					nbinsb, myb_array,
					"UOX");
  if (DEBUGP) cout << "   + KS value = " << kstest << endl;

  // Create text with the value
  TString legend = Form("KS=%4.2f", kstest);

  // Create a pave text to put the value inside

  TPaveLabel* pl = new TPaveLabel(0.79,0.91,0.93,0.96, legend.Data(), "NDC");

  // Tune style
  //pl->SetTextSize(0.04);
  pl->SetLineColor(41);
  pl->SetLineWidth(1);
  pl->SetLineStyle(1);
  pl->SetFillColor(41);
  pl->SetBorderSize(3);

  if (kstest < 0.7)
    pl->SetTextColor(kRed);

  pl->Draw();
  
  return kstest;
}