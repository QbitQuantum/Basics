TH1* getHistogram(TFile* inputFile, const TString& dqmDirectory, const TString& meName)
{
    TString histogramName = dqmDirectory;
    if ( histogramName.Length() > 0 && !histogramName.EndsWith("/") ) histogramName.Append("/");
    histogramName.Append(meName);
    std::cout << "histogramName = " << histogramName.Data() << std::endl;

    TH1* histogram = (TH1*)inputFile->Get(histogramName.Data());
    std::cout << "histogram = " << histogram << std::endl;

    return histogram;
}