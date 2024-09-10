//------------------------------------------------------------//
// Make TLatex
//------------------------------------------------------------//
TLatex* makeLatex()
{

  TLatex* lat = new TLatex();
  lat->SetTextSize(0.04);
  lat->SetTextFont(42);
  lat->SetTextColor(kBlack);
  lat->SetNDC();
  return lat;
}