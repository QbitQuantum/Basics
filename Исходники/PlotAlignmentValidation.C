//------------------------------------------------------------------------------
void PlotAlignmentValidation::plotSubDetResiduals(bool plotNormHisto,unsigned int subDetId)
{
  setNiceStyle();
 
  gStyle->SetOptStat(11111);
  gStyle->SetOptFit(0000);

  TCanvas *c = new TCanvas("c", "c", 600,600);
  c->SetTopMargin(0.15);
  TString histoName= "";
  if (plotNormHisto) {histoName= "h_NormXprime";}
  else histoName= "h_Xprime_";
  switch (subDetId){
  case 1 : histoName+="TPBBarrel_0";break;
  case 2 : histoName+="TPEendcap_1";break;
  case 3 : histoName+="TPEendcap_2";break;
  case 4 : histoName+="TIBBarrel_0";break;
  case 5 : histoName+="TIDEndcap_1";break;
  case 6 : histoName+="TIDEndcap_2";break;
  case 7 : histoName+="TOBBarrel_3";break;
  case 8 : histoName+="TECEndcap_4";break;
  case 9 : histoName+="TECEndcap_5";break;
  }
  int tmpcounter = 0;
  TH1 *sumHisto = 0;
  for(std::vector<TkOfflineVariables*>::iterator it = sourceList.begin();
      it != sourceList.end(); ++it) {
    if (tmpcounter == 0 ) {
      TFile *f= (*it)->getFile();
      sumHisto =(TH1*) f->FindKeyAny(histoName)->ReadObj();//FindObjectAny(histoName.Data());
      sumHisto->SetLineColor(tmpcounter+1);
      sumHisto->SetLineStyle(tmpcounter+1);
      sumHisto->GetFunction("tmp")->SetBit(TF1::kNotDraw);
      sumHisto->Draw();
      
      //get statistic box coordinate to plot all boxes one below the other
      //gStyle->SetStatY(0.91);
      //gStyle->SetStatW(0.15);
      //gStyle->SetStatBorderSize(1);
      //gStyle->SetStatH(0.10);
      
      
      tmpcounter++;
    } else {
      sumHisto = (TH1*) (*it)->getFile()->FindObjectAny(histoName);
      sumHisto->SetLineColor(tmpcounter+1);
      sumHisto->SetLineStyle(tmpcounter+1);
      sumHisto->GetFunction("tmp")->SetBit(TF1::kNotDraw);
      //hstack->Add(sumHisto);
      
      c->Update();
      tmpcounter++;  
    }
    TObject *statObj = sumHisto->GetListOfFunctions()->FindObject("stats");
    if (statObj && statObj->InheritsFrom(TPaveStats::Class())) {
      TPaveStats *stats = static_cast<TPaveStats*>(statObj);
      stats->SetLineColor(tmpcounter+1);
      stats->SetTextColor(tmpcounter+1);
      stats->SetFillColor(10);
      stats->SetX1NDC(0.91-tmpcounter*0.1);
      stats->SetX2NDC(0.15);
      stats->SetY1NDC(1);
      stats->SetY2NDC(0.10);
      sumHisto->Draw("sames");
    }
  }
  //hstack->Draw("nostack");
  char PlotName[1000];
  sprintf( PlotName, "%s/%s.eps", outputDir.c_str(), histoName.Data() );
  
  c->Print(PlotName);
  //delete c;
  //c=0;
    
}