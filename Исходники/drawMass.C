TPaveText *text(const char *txt, float x1, float y1, float x2, float y2) {
  TPaveText *text = new TPaveText(x1,y1,x2,y2,"brNDC");
  text->AddText(txt);
  text->SetBorderSize(0);
  text->SetFillStyle(0);
  text->SetTextAlign(12);
  text->SetTextFont(42);
  text->SetTextSize(0.05);
  return text;
}