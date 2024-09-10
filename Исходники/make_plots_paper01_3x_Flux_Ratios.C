void topTitle(const char *title)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.11);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.88, 0.70, title);

}