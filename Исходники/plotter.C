void DrawFreeCMSLabels(char* text, double textSize) {

  //const char *text = "%2.1f #times 10^{6} clusters (fiducial) (%1.1f GeV)";
  //char *text = "%2.1f #times 10^{6} clusters (fiducial)";
    
  TPaveText *label = new TPaveText();
  label->SetX1NDC(gStyle->GetPadLeftMargin());
  label->SetY1NDC(1.0-gStyle->GetPadTopMargin());
  label->SetX2NDC(1.0-gStyle->GetPadRightMargin());
  label->SetY2NDC(1.0);
  label->SetTextFont(42);
  label->AddText(text);
  label->SetFillStyle(0);
  label->SetBorderSize(0);
  if (textSize!=0) label->SetTextSize(textSize);
  label->SetTextAlign(32);
  label->Draw("same");
}