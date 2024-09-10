TLatex* NewLatex()
{
  TLatex *latex = new TLatex;
  latex->SetNDC(kTRUE);
  latex->SetTextSize(0.06);
  latex->SetTextColor(kRed);
  return latex;
}