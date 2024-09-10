//==========================================
//==========================================
void plotPair(TH1F *h1,TH1F *h0 ) {
  h1->Draw();

  // edit fonts/sizes
  TAxis *ax =h1->GetYaxis(); 
  float ss=ax->GetTitleSize();
  //printf("ss=%f\n",ss);
  ax->SetTitleSize(2*ss);
  ax->SetTitleOffset(0.5);
  ax =h1->GetXaxis(); 
 ax->SetTitleSize(1.5*ss);
 ax->SetLabelSize(1.5*ss);
 ax->SetTitleOffset(0.7);
 

  // edit fonts/sizes DONE



  gPad->Update();
  //scale hint1 to the pad coordinates
  Float_t rightmax = 1.1*h0->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
  h0->Scale(scale);
  h0->Draw("same");
   
  //draw an axis on the right side
  TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	      gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"-R");
  int col=h0->GetLineColor();
  axis->SetLineColor(col);
  
  axis->SetTextColor(col);
  axis->SetLabelColor(col);
  axis ->SetTitle("LCP yield");
 axis->SetTitleSize(2*ss);
 axis->SetTitleOffset(.5);

  axis->Draw();
  
  
  TPaveStats *st =( TPaveStats *)gPad->GetPrimitive("stats");
  st->SetX1NDC(0.35);
  st->SetX2NDC(0.5);
  st->SetY1NDC(0.7);
  st->SetY2NDC(1.);
}