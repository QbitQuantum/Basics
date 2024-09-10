//------------------------------------------------------------------------------
// DrawTLegend
//------------------------------------------------------------------------------
TLegend* DrawTLegend(Float_t x1,
		     Float_t y1,
		     TH1*    hist,
		     TString label,
		     TString option,
		     Float_t tsize,
		     Float_t xoffset,
		     Float_t yoffset)
{
  TLegend* legend = new TLegend(x1,
				y1,
				x1 + xoffset,
				y1 + yoffset);
  
  legend->SetBorderSize(    0);
  legend->SetFillColor (    0);
  legend->SetTextAlign (   12);
  legend->SetTextFont  (   42);
  legend->SetTextSize  (tsize);

  legend->AddEntry(hist, label.Data(), option.Data());
  legend->Draw();

  return legend;
}