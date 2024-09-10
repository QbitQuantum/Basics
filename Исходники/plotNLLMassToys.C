void CMSPrelim()
{
  
  
  TPaveText* cmsprel  = new TPaveText(0.19, 0.895 , 0.19 + 0.30, 0.895 + 0.10, "NDC");
  cmsprel->SetBorderSize(   0 );
  cmsprel->SetFillStyle(    0 );
  cmsprel->SetTextAlign(   12 );
  cmsprel->SetTextColor( 1 );
  cmsprel->SetTextFont ( 62 );

  //cmsprel->SetTextSize ( 0.035 );
  //cmsprel->AddText("CMS Preliminary,  #sqrt{s}=7-8 TeV,  L=24.3 fb^{-1},  H#rightarrow#tau#tau");

  //cmsprel->SetTextSize ( 0.027 );
  //cmsprel->AddText("CMS Preliminary, L=4.9 fb^{-1}@#sqrt{s}=7 TeV, L=19.3 fb^{-1}@#sqrt{s}=8 TeV, H#rightarrow#tau#tau");
  //cmsprel->AddText("CMS Preliminary,  #sqrt{s}=7 TeV, L=4.9 fb^{-1}; #sqrt{s}=8 TeV, L=19.3 fb^{-1}; H#rightarrow#tau#tau");

  cmsprel->SetTextSize ( 0.030 );
  cmsprel->AddText("CMS Preliminary,  H#rightarrow#tau#tau,  4.9 fb^{-1} at 7 TeV, 19.4 fb^{-1} at 8 TeV");

  cmsprel->Draw();

}