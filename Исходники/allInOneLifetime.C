ExtraAxis anotherScale (const TH1* refHist, double scale, int color, const char* title, double offset) {
  ExtraAxis result;
  double x0 = refHist->GetXaxis()->GetXmin();
  double x1 = refHist->GetXaxis()->GetXmax();
  double y0 = refHist->GetMinimum();
  double y1 = refHist->GetMaximum();
  // double y0 = refHist->GetYaxis()->GetXmin();
  // double y1 = refHist->GetYaxis()->GetXmax();
  double xoffset = exp (log(x0) - (log(x1) - log(x0))*offset);

  TGaxis* axis = new TGaxis(xoffset, y0, xoffset, y1, y0*scale,y1*scale,510,"-GS");
  axis->ImportAxisAttributes (refHist->GetXaxis());
  axis->SetTitle(title);
  axis->SetTextColor (color);
  axis->SetLineColor (color);
  axis->SetLineWidth (1);
  axis->SetTextColor (color);
  axis->SetLabelColor (color);
  axis->SetLabelOffset (0.);
  axis->SetTitleOffset (0.65);
  axis->SetTickSize(0.015);	
  result.Add (axis);

  TLine* line = new TLine (xoffset, y0, xoffset, y1);
  line->SetLineColor (color);
  line->SetLineWidth (2);
  result.Add (line);

  line = new TLine (x0, y0, xoffset, y0);
  line->SetLineColor (kGray);
  line->SetLineWidth (2);
  result.Add (line);
  
  line = new TLine (x0, y1, xoffset, y1);
  line->SetLineColor (kGray);
  line->SetLineWidth (2);
  result.Add (line);

  return result;
}