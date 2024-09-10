//*************************************************************
void arrangeCanvas(TCanvas *canv,TH1F* meanplots[100],TH1F* widthplots[100],Int_t nFiles, TString LegLabels[10], bool onlyBias){
//*************************************************************

  TPaveText *ali = new TPaveText(0.18,0.87,0.50,0.93,"NDC");  
  ali->SetFillColor(10);
  ali->SetTextColor(1);
  ali->SetTextFont(42);
  ali->SetMargin(0.);
  ali->SetLineColor(10);
  ali->SetShadowColor(10);
  // pt->SetTextAlign(11);
  TText *alitext = ali->AddText("Alignment: PCL"); //"Preliminary 2015 - 0T collision data");
  alitext->SetTextSize(0.04);

  TLegend *lego = new TLegend(0.18,0.80,0.78,0.92);
  lego-> SetNColumns(2);
  //TLegend *lego = new TLegend(0.18,0.77,0.50,0.86);
  lego->SetFillColor(10);
  lego->SetTextSize(0.04);
  lego->SetTextFont(42);
  lego->SetFillColor(10);
  lego->SetLineColor(10);
  lego->SetShadowColor(10);

  TPaveText *pt  = NULL;
  TPaveText *pt2 = NULL;
  TPaveText *pt3 = NULL;

  if(!onlyBias){ 
    pt =new TPaveText(0.179,0.955,0.260,0.985,"NDC");
  } else {
    pt =new TPaveText(0.179,0.955,0.260,0.985,"NDC");
  }

  pt->SetFillColor(10);
  pt->SetTextColor(1);
  pt->SetTextFont(61);
  // pt->SetTextAlign(11);
  TText *text1 = pt->AddText("CMS"); //"Preliminary 2015 - 0T collision data");
  text1->SetTextSize(0.05);
 
  float extraOverCmsTextSize  = 0.76;

  if(!onlyBias){ 
    pt2 =new TPaveText(0.3,0.95,0.503,0.98,"NDC");
  } else {
    pt2 =new TPaveText(0.3,0.95,0.503,0.98,"NDC");
  }

  pt2->SetFillColor(10);
  pt2->SetTextColor(1);
  pt2->SetTextFont(52);
  pt2->SetTextAlign(22);
  TText *text2 = pt2->AddText("work in progress");
  text2->SetTextSize(0.05*extraOverCmsTextSize);

  if(!onlyBias){ 
    pt3 =new TPaveText(0.6,0.95,0.98,0.98,"NDC");
  } else {
    pt3 =new TPaveText(0.6,0.95,0.98,0.98,"NDC");
  }

  pt3->SetFillColor(10);
  pt3->SetTextColor(1);
  pt3->SetTextFont(42);
  // pt2->SetTextAlign(11);
  TText *text3 = pt3->AddText("3.8T collision data 2015");
  text3->SetTextSize(0.05*extraOverCmsTextSize);

  canv->SetFillColor(10);  
  if(!onlyBias) {
    canv->Divide(2,1);
    
    canv->cd(1)->SetBottomMargin(0.12);
    canv->cd(1)->SetLeftMargin(0.17);
    canv->cd(1)->SetRightMargin(0.02);
    canv->cd(1)->SetTopMargin(0.06);  
    
    canv->cd(2)->SetBottomMargin(0.12);
    canv->cd(2)->SetLeftMargin(0.17);
    canv->cd(2)->SetRightMargin(0.02);
    canv->cd(2)->SetTopMargin(0.06);  
  
    canv->cd(1);
  } else {
    
    canv->cd()->SetBottomMargin(0.14);
    canv->cd()->SetLeftMargin(0.17);
    canv->cd()->SetRightMargin(0.02);
    canv->cd()->SetTopMargin(0.06);  
    canv->cd();

  }

  Double_t absmin(999.);
  Double_t absmax(-999.);

  for(Int_t i=0; i<nFiles; i++){
    if(meanplots[i]->GetMaximum()>absmax) absmax = meanplots[i]->GetMaximum();
    if(meanplots[i]->GetMinimum()<absmin) absmin = meanplots[i]->GetMinimum();
  }

  Double_t safeDelta=(absmax-absmin)/2.;
  Double_t theExtreme=std::max(absmax,TMath::Abs(absmin));

  for(Int_t i=0; i<nFiles; i++){

    TString myTitle = meanplots[i]->GetName();
    float axmin = -999;
    float axmax = 999.;
    int ndiv = 510;
    if(myTitle.Contains("eta")){
      axmin = -2.5;
      axmax = 2.5;
      ndiv = 505;
    } else if (myTitle.Contains("phi")){
      axmin = -TMath::Pi();
      axmax = TMath::Pi();
      ndiv = 510;
    } else  {
      std::cout<<"unrecongnized variable";
    }

    meanplots[i]->GetXaxis()->SetLabelOffset(999);
    meanplots[i]->GetXaxis()->SetTickLength(0);
    
    // Redraw the new axis 
    gPad->Update();
    TGaxis *newaxis =  new TGaxis(gPad->GetUxmin(),gPad->GetUymin(),
				  gPad->GetUxmax(),gPad->GetUymin(),
				  axmin,
				  axmax,
				  //meanplots[i]->GetXaxis()->GetXmin(),
				  //meanplots[i]->GetXaxis()->GetXmax(),
				  ndiv,"SDH");
    
    
    TGaxis *newaxisup =  new TGaxis(gPad->GetUxmin(),gPad->GetUymax(),
				    gPad->GetUxmax(),gPad->GetUymax(),
				    axmin,
				    axmax,
				    //meanplots[i]->GetXaxis()->GetXmin(),                                                                                                     
				    //meanplots[i]->GetXaxis()->GetXmax(),                                                                                                     
				    ndiv,"-SDH");
    
    newaxis->SetLabelOffset(0.02);
    newaxis->SetLabelFont(42);
    newaxis->SetLabelSize(.05);
    newaxis->Draw();

    newaxisup->SetLabelOffset(-0.02);
    newaxisup->SetLabelFont(42);
    newaxisup->SetLabelSize(0);
    newaxisup->Draw();
    
    if(i==0){
      //meanplots[i]->GetYaxis()->SetRangeUser(absmin-safeDelta/2.,absmax+safeDelta);
      std::cout<<"name is: "<< meanplots[i]->GetName() << " absmin:" <<absmin<<" absmax: "<<absmax<<" safeDelta: "<<safeDelta<<std::endl;
      TString theTitle = meanplots[i]->GetName();
      if( theTitle.Contains("Norm")){
	meanplots[i]->GetYaxis()->SetRangeUser(std::min(-0.48,absmin-safeDelta),std::max(0.48,absmax+safeDelta));
      } else {
	if(!onlyBias){
	  meanplots[i]->GetYaxis()->SetRangeUser(absmin-safeDelta,absmax+safeDelta);
	} else {
	  meanplots[i]->GetYaxis()->SetRangeUser(-theExtreme-(TMath::Abs(absmin)/10.),theExtreme+(TMath::Abs(absmax/10.)));
	}
	//meanplots[i]->GetYaxis()->SetRangeUser(-theExtreme,theExtreme);
      } 
      meanplots[i]->Draw("e1");

      if(onlyBias){
	Int_t nbins =  meanplots[i]->GetNbinsX();
	Double_t lowedge  = meanplots[i]->GetBinLowEdge(1);
	Double_t highedge = meanplots[i]->GetBinLowEdge(nbins+1);
	
	TH1F* hzero = DrawZero(meanplots[i],nbins,lowedge,highedge);
	hzero->Draw("PLsame");
      }

    }
    else meanplots[i]->Draw("e1sames");
    lego->AddEntry(meanplots[i],LegLabels[i]); 
  }  
  

  //ali->Draw();
  lego->Draw();
  pt->Draw("same");
  pt2->Draw("same");
  pt3->Draw("same");


  if(!onlyBias){

    canv->cd(2);
    Double_t absmax2(-999.);
    
    for(Int_t i=0; i<nFiles; i++){
      if(widthplots[i]->GetMaximum()>absmax2) absmax2 = widthplots[i]->GetMaximum();
    }
    
    Double_t safeDelta2=absmax2/3.;
    
    for(Int_t i=0; i<nFiles; i++){

      TString myTitle = widthplots[i]->GetName();
      float axmin = -999;
      float axmax = 999.;
      int ndiv = 510;
      if(myTitle.Contains("eta")){
	axmin = -2.5;
	axmax = 2.5;
	ndiv = 505;
      } else if (myTitle.Contains("phi")){
	axmin = -TMath::Pi();
	axmax = TMath::Pi();
	ndiv = 510;
      } else  {
	std::cout<<"unrecongnized variable";
      }
      
      widthplots[i]->GetXaxis()->SetLabelOffset(999);
      widthplots[i]->GetXaxis()->SetTickLength(0);
      
      // Redraw the new axis 
      gPad->Update();
      TGaxis *newaxis2 = new TGaxis(gPad->GetUxmin(),gPad->GetUymin(),
				    gPad->GetUxmax(),gPad->GetUymin(),
				    axmin,
				    axmax,
				    //widthplots[i]->GetXaxis()->GetXmin(),
				    //widthplots[i]->GetXaxis()->GetXmax(),
				    ndiv,"SDH");
      
      newaxis2->SetLabelOffset(0.02);
      newaxis2->SetLabelFont(42);
      newaxis2->SetLabelSize(.05);
      newaxis2->Draw();

      TGaxis *newaxis2up = new TGaxis(gPad->GetUxmin(),gPad->GetUymax(),
				      gPad->GetUxmax(),gPad->GetUymax(),
				      axmin,
				      axmax,
				      //widthplots[i]->GetXaxis()->GetXmin(),
				      //widthplots[i]->GetXaxis()->GetXmax(),
				      ndiv,"-SDH");
      
      newaxis2up->SetLabelOffset(-0.02);
      newaxis2up->SetLabelFont(42);
      newaxis2up->SetLabelSize(0.);
      newaxis2up->Draw();

      if(i==0) widthplots[i]->Draw("e1");
      else widthplots[i]->Draw("e1sames");
      widthplots[i]->SetMinimum(0.5);
      widthplots[i]->SetMaximum(absmax2+safeDelta2);
    }
    
    lego->Draw();
    pt->Draw("same");
    pt2->Draw("same");
    pt3->Draw("same");

  }
}