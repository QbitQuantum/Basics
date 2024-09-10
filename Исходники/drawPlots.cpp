// *************************************** //
// draw the ATLAS label                    //
// *************************************** //
void drawPlots::ATLAS_LABEL(Double_t x,Double_t y,Color_t color) 
{
   TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
   l.SetNDC();
   l.SetTextFont(72);
   l.SetTextColor(color);
   l.DrawLatex(x,y,"ATLAS");
}