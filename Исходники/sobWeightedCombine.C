void 
CMSPrelim(const char* dataset, const char* channel,const char* cat)
{
  double lowX=0.16;
  double lowY=0.835;

  int color=1; int font = 62;
  
  TPaveText* cmsprel  = new TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC");
  cmsprel->SetBorderSize(   0 );
  cmsprel->SetFillStyle(    0 );
  cmsprel->SetTextAlign(   12 );
  cmsprel->SetTextColor( color );
  cmsprel->SetTextFont ( font );
  //cmsprel->SetTextSize ( 0.035 );
  //cmsprel->SetTextSize ( 0.027 );
  cmsprel->SetTextSize ( 0.030 );
  cmsprel->AddText(dataset);
  cmsprel->Draw();

  TPaveText* chan     = new TPaveText(lowX+0.05, lowY-0.002, lowX+0.45, lowY+0.028, "NDC");
  chan->SetBorderSize(   0 );
  chan->SetFillStyle(    0 );
  chan->SetTextAlign(   12 );
  chan->SetTextSize ( 0.035 );
  chan->SetTextColor( color );
  chan->SetTextFont ( font );
  chan->AddText(channel);
  chan->Draw();

  TPaveText* category     = new TPaveText(lowX+0.05, lowY-0.002-0.06, lowX+0.45, lowY+0.028-0.06, "NDC");
  category->SetBorderSize(   0 );
  category->SetFillStyle(    0 );
  category->SetTextAlign(   12 );
  category->SetTextSize ( 0.035 );
  category->SetTextColor( color );
  category->SetTextFont ( font );
  category->AddText(cat);
  category->Draw();
}