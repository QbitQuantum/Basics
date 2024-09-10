void ellipises(){

  TEllipse *e1 = new TEllipse(0.66, 0.66, 0.025, 0.2, 0., 360., 0.);
  e1->SetLineWidth(2);
  e1->SetFillStyle(3003);
  e1->SetFillColor(1);
  if(iColor)e1->SetFillColor(kBlue);
  if(iColor)e1->SetLineColor(kBlue);
  e1->SetNoEdges();
  e1->Draw();

  TEllipse *e2 = new TEllipse(0.33, 0.33, 0.025, 0.2, 0., 360., 180.);
  e2->SetLineWidth(2);
  e2->SetFillStyle(3003);
  e2->SetFillColor(1);
  if(iColor)e2->SetFillColor(kRed);
  if(iColor)e2->SetLineColor(kRed);
  e2->SetNoEdges();
  e2->Draw();

  TBox *b1 = new TBox(0.3, 0.6, 0.7, 0.4);
  b1->SetFillColor(0);
  b1->SetLineColor(0);
  b1->Draw();

  TEllipse *e3 = new TEllipse(0.5, 0.5, 0.1, 0.066, 0., 360., 0.);
  e3->SetLineWidth(2);
  if(iColor)e3->SetFillColor(kRed+2);
  if(iColor)e3->SetLineColor(kRed+2);
  e3->Draw();

  TLatex *xFire = new TLatex(0.445, 0.49, "Fireball");
  if(iColor)xFire->SetTextColor(0);
  xFire->SetTextSize(0.04);
  xFire->Draw();

  TLatex *xA1 = new TLatex(0.72, 0.665, "Nucleus");
  xA1->SetTextSize(0.04);
  if(iColor)xA1->SetTextColor(kBlue);
  xA1->Draw();

  TLatex *xA2 = new TLatex(0.77, 0.625, "A");
  xA2->SetTextSize(0.04);
  if(iColor)xA2->SetTextColor(kBlue);
  xA2->Draw();

  TLatex *xB1 = new TLatex(0.13, 0.37, "Nucleus");
  xB1->SetTextSize(0.04);
  if(iColor)xB1->SetTextColor(kRed);
  xB1->Draw();
  
  TLatex *xB2 = new TLatex(0.18, 0.33, "B");
  xB2->SetTextSize(0.04);
  if(iColor)xB2->SetTextColor(kRed);
  xB2->Draw();

  TLatex *xSide = new TLatex(0.45, 0.95, "#bf{Side View}");
  xSide->SetTextSize(0.04);
  xSide->Draw();
}