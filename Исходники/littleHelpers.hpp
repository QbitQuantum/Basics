// überladen: Statbox-Größen manuell eingeben
void drawStatBox(int& step, TH1D* histo, int color = -1, double statboxHeight = 0.1,  double statboxSpacing = 0.15){
  TPaveStats* statBox = dynamic_cast<TPaveStats*>( histo->GetListOfFunctions()->FindObject("stats") );
  
  if(color == -1) color = step+1;
  statBox->SetX1NDC(0.80);
  statBox->SetX2NDC(0.99);
  statBox->SetY2NDC(0.95-step*statboxSpacing);
  statBox->SetY1NDC(0.95-step*statboxSpacing-statboxHeight);
  statBox->SetTextColor(color);
  statBox->Draw();
  step++;
}