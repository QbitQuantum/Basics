//--------------------------------------------------------------------------------------------------
void overlayFrame(TString text, bool align)
{
  // Overlay a linear frame from user coordinates (0 - 1, 0 - 1) and put the frame text

  // Create new transparent pad for the text
  TPad *transPad = new TPad("transPad","Transparent Pad",0,0,1,1);
  transPad->SetFillStyle(4000);
  transPad->Draw();
  transPad->cd();

  // Overlay the text in a well defined frame
  TText *plotText = new TText();
  plotText->SetTextColor(kBlue);
  plotText->SetTextSize(0.04);
  plotText->SetNDC();

  // Draw text at top right
  if (align) {
    plotText->SetTextColor(kBlack);
    plotText->SetTextAlign(33);
    plotText->DrawText(0.92,0.95,text.Data());
  }
  // Draw text at bottom left
  else
    plotText->DrawText(0.01,0.01,text.Data());

  return;
}