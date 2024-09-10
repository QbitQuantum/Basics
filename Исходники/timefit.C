/************************************************************
*  Fit ADC spectrum
************************************************************/
int FitAdcHist(TH1F *h, float data[NDATA], const int print ) {
  TF1 *fadc;
  TPaveText *adcPT;

  // Protect for null histograms
  if( h == 0 || h->GetEntries()<1000. ) return -1;
  printf("Fitting %s\n",h->GetName());

  gStyle->SetOptStat("emr"); 
  adcPT = new TPaveText(0.58,0.315,0.98,0.635,"NDC");

//  Refit ADC
  Double_t n    = h->GetEntries();
  Double_t rms  = h->GetRMS();
  Double_t mean = h->GetMean();
  Double_t ymin = mean-2*rms;
  if( ymin < 60. ) ymin=60.;
  Double_t ymax = mean+1.5*rms;
  fadc = new TF1("adc_fun",skewnormal,ymin,ymax,4);
  fadc->SetParameters(n,mean,rms,1.5);
  fadc->SetParLimits(1,mean-rms,mean+0.5*rms);
  fadc->SetParLimits(2,rms*0.5,rms*1.5);
  fadc->SetParLimits(3,1.,4.);
  h->Fit("adc_fun","r"); 
//  If skew is too high refit with fixed skew
  if( fadc->GetParameter(3) > 2.5 ) {
    printf("REFIT %s\n",h->GetName());
    fadc->SetParameter(3,1.6);
    fadc->SetParLimits(3,1.6,1.6);
    h->Fit("adc_fun","r") ;
  }
// if have enough hits use fit results  
  if( n > MINHITS ) {
    data[13] = fadc->GetParameter(1);
    data[14] = fadc->GetParError(1);
    data[15] = fadc->GetParameter(2);
    data[16] = fadc->GetParError(2);
    data[17] = fadc->GetParameter(3);
    data[18] = fadc->GetParError(3);
    double dof = fadc->GetNDF();
    if( dof > 0. ) data[19] = fadc->GetChisquare()/dof;
    adcPT->AddText(Form("Peak %.1lf #pm %.1lf",data[13],data[14]));
    adcPT->AddText(Form("Width %.1lf #pm %.1lf",data[15],data[16]));
    adcPT->AddText(Form("Skew %.2lf #pm %.2lf",	data[17],data[18]));
    if( dof > 0. ) adcPT->AddText(Form("#Chi^{2}/DoF     %.2lf",data[19]));
    adcPT->SetTextColor(2);
    adcPT->Draw();
// if have too few hits use fit stats instead of fit results  
  } else {
    data[12] = mean;
    data[13] = h->GetMeanError();
    data[14] = rms;
    data[15] = h->GetRMSError();
    data[16] = h->GetSkewness();
  }
  if( print ) c1->Print(Form("%s_%s.png",fname,h->GetName()));
  return 0;
}    //end FitAdcHist