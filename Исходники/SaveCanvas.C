TLatex* AddLabel(const char*txt,float x,float y,int color,float size)
{
  TLatex* lt = new TLatex(x,y,txt); 
  lt->SetNDC(); 
  lt->SetTextColor(color);
  lt->SetTextSize(size);
  lt->Draw();
  return lt;
}