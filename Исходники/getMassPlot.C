void DrawTLatex(Double_t x,Double_t y, Double_t tsize, Short_t align, TString  text){
  TLatex* tl = new TLatex(x, y, text);
  tl->SetNDC      (true);
  tl->SetTextAlign( align);
  tl->SetTextFont (    42);
  tl->SetTextSize ( tsize);
  tl->Draw("same");
}