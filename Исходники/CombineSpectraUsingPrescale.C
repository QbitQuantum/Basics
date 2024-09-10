void drawText(const char *text, float xp, float yp, int textSize=20){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(textSize); 
  tex->SetTextColor(kBlack); 
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw(); 
}