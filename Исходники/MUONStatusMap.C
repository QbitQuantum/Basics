//______________________________________________________________________________
void DrawPeriod(int runmin, int runmax, int run1, int run2, double ymin, double ymax, const char* label)
{
  if ( run1 < runmin || run1 > runmax || run2 < runmin || run2 > runmax ) return;

  TBox* b = new TBox(run1,ymin,run2,ymax);
  b->SetFillColor(5);
  b->Draw();
  TText* text = new TText((run1+run2)/2.0,ymax*0.6,label);
  text->SetTextAlign(22);
  text->SetTextSize(0.02);
  text->Draw();
}