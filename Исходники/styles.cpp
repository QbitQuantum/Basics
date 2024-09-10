// ----------------------------------------------------------------------
void styles::setTitles(TH1 *h, TString xTitle, TString yTitle, TString Left, TString Right) {
  if (0==h) {
    cout << " Histogram not defined" << endl;
  } else {
    h->SetXTitle(xTitle); h->SetYTitle(yTitle);
    TLatex label; label.SetNDC(kTRUE);
    label.SetTextSize(0.06);
    label.SetTextAlign(11);
    label.DrawLatex(PadLeftMargin,1-PadTopMargin+0.02,Left);  
    label.SetTextAlign(31);
    label.DrawLatex(1-PadRightMargin,1-PadTopMargin+0.02,Right);  
  }
}