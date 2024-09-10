TH1* getHistogram(TFile* inputFile, const TString& dqmDirectory, const TString& meName)
{  
  TString histogramName = dqmDirectory;
  if ( histogramName.Length() > 0 && !histogramName.EndsWith("/") ) histogramName.Append("/");
  histogramName.Append(meName);

  TH1* histogram = (TH1*)inputFile->Get(histogramName.Data());
  std::cout << "histogramName = " << histogramName.Data() << ": histogram = " << histogram;
  if ( histogram ) std::cout << ", integral = " << histogram->Integral();
  std::cout << std::endl; 

  if ( !histogram->GetSumw2N() ) histogram->Sumw2();

  if ( histogram->GetDimension() == 1 ) histogram->Rebin(5);

  return histogram;
}