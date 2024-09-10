////CMS Preliminary label and luminosity + any aditional inline title
void cmsPrelim(const char * label)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"CMS 2012, #sqrt{s} = 8 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96, label );
}