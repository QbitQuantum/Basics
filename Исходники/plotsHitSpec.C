TCanvas* pHitSpecDet(const std::string& s)
{
  TCanvas* c = new TCanvas( ("HitSpecDet"+s).c_str(), ("HitSpecDet"+s).c_str(), -2);
  c->SetLogx();
  TH2D* h = (TH2D*)gROOT->FindObject(s.c_str());
  h->GetXaxis()->SetRange(4,32);
  std::stringstream str;
  str<<h->GetTitle();
  TText t;
  t.SetTextColor(4);
  t.SetTextAlign(11);
  t.SetTextSize(0.035);
  h->DrawCopy("box");
  t.DrawTextNDC(0.17,0.2, str.str().c_str());
  return c;
}