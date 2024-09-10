TPaveText *GetPaveKineInfo2(Int_t identifier){
  //TPaveText *pvKineInfo = new TPaveText(0.01/gPad->GetWNDC()+gPad->GetLeftMargin(),0.18/gPad->GetHNDC()+gPad->GetBottomMargin(),0.3/gPad->GetWNDC()+gPad->GetLeftMargin(),0.22/gPad->GetHNDC()+gPad->GetBottomMargin(),"NDC");
  //  TPaveText *pvKineInfo = new TPaveText(0.4,0.56,0.7,0.65,"NDC");//in pad 0
  //  TPaveText *pvKineInfo = new TPaveText(0.24,0.56,0.6,0.65,"NDC");//in pad 0
  // TPaveText *pvKineInfo = new TPaveText(0.01,0.6,0.5,0.8,"brNDC");//in pad 1
TPaveText *  pvKineInfo = new TPaveText(0.02/gPad->GetWNDC()+gPad->GetLeftMargin(),0.197/gPad->GetHNDC()+gPad->GetBottomMargin(),0.19/gPad->GetWNDC()+gPad->GetLeftMargin(),0.21/gPad->GetHNDC()+gPad->GetBottomMargin(),"NDC");
  
  SetPaveStyle(pvKineInfo);
  pvKineInfo->SetTextAlign(12);
  //pvKineInfo->SetTextSize(0.06/(gPad->GetHNDC())*scaleHeightPads);
  pvKineInfo->SetTextFont(43);
  pvKineInfo->SetTextSize(21.9*innerPadHeight/referencePadHeight*resizeTextFactor);// settings for font 42: 0.07/(gPad->GetHNDC())*scaleHeight
  
  pvKineInfo->AddText(strYText.Data());
  //  pvKineInfo->AddText("|#it{y}^{D}|<0.5, |#Delta#it{#eta}| < 1.0 ");
  pvKineInfo->SetName(Form("pvKineInf0_%d",identifier));
  return pvKineInfo;
}