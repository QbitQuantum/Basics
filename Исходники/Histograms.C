////CMS Preliminary label and lumu - Thanks to Kalanand
void Histograms::cmsPrelim()
{


  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.03);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"#sqrt{s} = 8 TeV, 2.0E34 cm^{-2}s^{-1}");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96,"CMS preliminary 2012");

}