//--------------------------------------------------------------------------------------------------
void overlayFrame(TString text)
{
  // Overlay a linear frame from user coordinates (0 - 1, 0 - 1) and put the frame text

  // create new transparent pad for the text
  TPad *transPad = new TPad("transPad","Transparent Pad",0,0,1,1);
  transPad->SetFillStyle(4000);
  transPad->Draw();
  transPad->cd();

  // overlay the text in a well defined frame
  TText *plotText = new TText(0.01,0.01,text.Data());
  plotText->SetTextSize(0.04);
  plotText->SetTextColor(kBlue);
  plotText->Draw();

  return;
}