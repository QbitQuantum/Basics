void drawCanvas()
{
  cPhase = new TCanvas("cPhase","cPhase",0,0,500,500);
  cPhase->SetLeftMargin(0.2);
  cPhase->SetBottomMargin(0.2);
  
  cPhase->Range(-0.2,-0.2,1.1,1.1);
  TLatex *latex = new TLatex(1.0,-0.1,"#mu_{B}");
  latex->SetTextAlign(31);
  latex->Draw();
  latex = new TLatex(-0.1,1.0,"T");
  latex->SetTextAlign(31);
  latex->SetTextAngle(90);
  latex->Draw();
}