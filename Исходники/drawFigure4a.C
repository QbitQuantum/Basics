//------------------------------------------------------------------------------
// DrawLegend
//------------------------------------------------------------------------------
void DrawLegend(Float_t x1,
		Float_t y1,
		TH1F*   hist,
		TString label,
		TString option)
{
  TLegend* legend = new TLegend(x1,
				y1,
				x1 + 0.22,
				y1 + 0.05);

  legend->SetBorderSize(    0);
  legend->SetFillColor (    0);
  legend->SetTextAlign (   12);
  legend->SetTextFont  (   42);
  legend->SetTextSize  (0.045);

  legend->AddEntry (hist, label.Data(), option.Data());
  //  legend->AddEntry (hist, label.Data());
  legend->Draw();
}