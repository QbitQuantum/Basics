void ATLASLabel(Double_t x,Double_t y, bool Preliminary) 
{
  float fTextScaleFactor=0.8;

  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  float siz=l.GetTextSize();
  l.SetTextSize(siz*fTextScaleFactor); // set the size here
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextColor(1);

  double delx = 0.115*696*gPad->GetWh()/(472*gPad->GetWw());
  l.DrawLatex(x,y,"ATLAS");
  if (Preliminary) {
    TLatex p; 
    siz=p.GetTextSize();
    p.SetTextSize(siz*fTextScaleFactor); // set the size here
    p.SetNDC();
    p.SetTextFont(42);
    p.SetTextColor(1);
    //  p.DrawLatex(x+delx-.03,y,"Preliminary");
    p.DrawLatex(x+delx,y,"Internal");
  }
}