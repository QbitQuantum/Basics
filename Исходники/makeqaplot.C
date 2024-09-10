void plot2d(int hid) {
  gStyle->SetOptStat(0);
  char c[50];
  c1->Clear();
  if(hid!=2 && hid!=4){
    c1->Divide(2,3);
    for(int disc=0; disc<kFgtNumDiscs; disc++){
      TPad *pad = c1->cd(disc+1);
      pad->SetLogz(1);
      pad->SetTopMargin(0.01);   pad->SetBottomMargin(0.02);
      sprintf(c,"Disc%1d%s",disc+1,c2dHist[hid]);
      //printf("Getting %s\n",c);
      TH2F *h = hist2[disc][hid] = (TH2F*)file->Get(c);
      h->Draw("COLZ");  
    }
  }else if(hid==2){  // special case for timing per APVboard
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit(0);
    c1->Divide(2,1);
    char txt[100];
    //int disc=3; char name[100]="MaxAdc";
    int disc=4; char name[100]="LandauMPV";
    //int disc=5; char name[100]="LandauMPV-3Sing";
    TVirtualPad *pad2 = c1->cd(1);
    pad2->Divide(1,2); 
    TVirtualPad *pad3=pad2->cd(1);
    pad3->SetLogz(1);  pad2->SetLogz(0); 
    sprintf(c,"Disc%1d%s",disc,c2dHist[hid]);
    TH2F *h = hist2[disc][hid] = (TH2F*)file->Get(c);
    h->Draw("COLZ");
    TText *tt1= new TText(0.05,0.1,"(RDO-1)*12+ARM*2+GRP"); tt1->SetTextAngle(90); tt1->SetNDC(); tt1->Draw();    
    sprintf(txt,"Tbin for %s",name);
    TText *tt2= new TText(0.3,0,txt); tt2->SetNDC(); tt2->Draw();
    
    TVirtualPad* pad4 = c1->cd(2);
    pad4->SetTopMargin(0.01); pad4->SetBottomMargin(0.1);
    int maxid=0;
    float off,max=0;
    TH1D *h1[24];
    float mean[24];
    for(int i=0; i<24; i++){
      char ccc[10]; sprintf(ccc,"_%d_%d",disc,i);
      h1[i] = h->ProjectionX(ccc,i+1,i+1); 
      if(h1[i]->GetMaximum() > max && i!=0) {max=h1[i]->GetMaximum(); maxid=i; }
    }
    off=max/4.0;
    printf("max=%f off=%f\n",max,off);
    for(int i=0; i<24; i++){
      h1[i]->GetXaxis()->SetRangeUser(2,11);
      int res = h1[i]->Fit("gaus","0Q");
      TF1* f=h1[i]->GetFunction("gaus");
      if(h1[i]->GetMaximum()>max/3 && res==0){
	mean[i] = f->GetParameter(1);
	//mean[i]=h1[i]->GetMean();
      }else{mean[i]=0;};
      //printf("%d mean=%f\n",i,mean[i]);
    }
    //h1[maxid]->SetLineColor(maxid+1); h1[maxid]->SetLineWidth(2); h1[maxid]->Draw("PL");
    for(int rdo=1; rdo<=2; rdo++){
      for(int arm=0; arm<6; arm++){
	for(int grp=0; grp<2; grp++){
	  i=(rdo-1)*12+arm*2+grp;
	  int nb=h1[i]->GetNbinsX();
	  for(int t=0; t<nb; t++){ h1[i]->AddBinContent(t+1,off*i); }
	  h1[i]->SetLineColor(i%6+1); h1[i]->SetLineWidth(3);
	  if(i==0) {
	    h1[i]->SetMinimum(0);
	    h1[i]->SetMaximum(max*6.5);
	    h1[i]->Draw("PL");
	  } else {h1[i]->Draw("PL same");}	
	  char name[100]; 
	  sprintf(name,"Rdo%1dArm%1dGrp%1d",rdo,arm,grp);
	  TText *tx = new TText(8.5,(max/4.0)*(i+0.2),name); tx->SetTextColor(i%6+1); tx->SetTextSize(0.03);
	  tx->Draw();
	}
      }
    }
    //    TText *tt3= new TText(0.95,0.1,"offsets added by (RDO-1)*12+ARM*2+GRP"); tt3->SetTextAngle(90); tt3->SetNDC(); tt3->Draw();
    TText *tt4= new TText(0.4,0,txt); tt4->SetNDC(); tt4->Draw();
    
    //correlation
    float t2[24]={-8.47, -5.16, -0.21, -2.23,  1.11, -4.09, 
		  -3.13, -9.08, -5.88, -7.01, -6.22, -9.79,  
		  0.75, -8.91,  0.16,  1.12, -0.99, -4.56,  
		  7.57, -3.68,  7.12, -6.54, -4.08, -8.21};
    TGraph *g= new TGraph(1);
    int j=0;
    for(int i=0; i<24; i++){
      if(mean[i]>0) {g->SetPoint(j,(mean[i]-6.0)*27,t2[i]); j++;}
    }
    TVirtualPad* pad5=pad2->cd(2);
    g->SetMarkerStyle(20+i/6); g->SetMarkerSize(1);
    g->Draw("ap");
    for(int i=0; i<24; i++){
      TGraph *g2= new TGraph(1);
      if(mean[i]>0) {g2->SetPoint(j,(mean[i]-6.0)*27,t2[i]); j++;}
      g2->SetMarkerStyle(20+i/6); g2->SetMarkerSize(2); g2->SetMarkerColor(i%6+1);
      g2->Draw("p");
    }
    
    TText *tt5= new TText(0.05,0.1,"(VPHASE_ADC-1.2V)/0.95V*27nsec/2"); tt5->SetTextAngle(90); tt5->SetNDC(); tt5->Draw();
    TText *tt6= new TText(0.5,0,"(Tbin-6)*27nsec"); tt6->SetNDC(); tt6->Draw(); 
  }else{  // special case for timing per APVboard
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit(0);
    c1->Divide(4,6);
    char txt[100];
    //int disc=3; char name[100]="MaxAdc";
    int disc=4; char name[100]="LandauMPV";
    //int disc=5; char name[100]="LandauMPV-3Sing";
    sprintf(c,"Disc%1d%s",disc,c2dHist[2]);
    TH2F *h = hist2[disc][2] = (TH2F*)file->Get(c);
    TH1D *h1[24];
    float mean[24];
    for(int rdo=1; rdo<=2; rdo++){
      for(int arm=0; arm<6; arm++){
	for(int grp=0; grp<2; grp++){   
	  int i=(rdo-1)*12+arm*2+grp;
	  TVirtualPad *pad2 = c1->cd(i+1);
	  pad2->SetTopMargin(0.01); pad2->SetBottomMargin(0.1);
	  char ccc[10]; sprintf(ccc,"_%d_%d",disc,i);
	  h1[i]=h->ProjectionX(ccc,i+1,i+1);       
	  h1[i]->GetXaxis()->SetRangeUser(2,12); h1[i]->SetFillColor(4);
	  h1[i]->GetXaxis()->SetLabelSize(0.1); h1[i]->GetYaxis()->SetLabelSize(0.1);
	  h1[i]->Draw(); 
	  int res = h1[i]->Fit("gaus","Q");
	  TF1* f=h1[i]->GetFunction("gaus"); f->SetLineColor(2); f->SetLineWidth(2);
	  if(res==0){
	    mean[i] = f->GetParameter(1);
	  }else{mean[i]=0;};
	  char name[100]; 
	  sprintf(name,"Rdo%1dArm%1d-%1d",rdo,arm,grp);
	  TText *tx = new TText(0.5,0.85,name); tx->SetTextSize(0.1); tx->SetNDC();
	  tx->Draw();
	  if(mean[i]>0){
	    sprintf(name,"peak=%4.1f",mean[i]);
	    TText *tx2 = new TText(0.55,0.75,name); tx2->SetTextSize(0.12); tx2->SetNDC();
	    tx2->Draw();
	  }
	}
      }
    }
  }
  c1->Update();
  save(c2dHist[hid]);
}