void drawHisto(TCanvas* C,TString Group1,TFile* F1,TString Group2,TFile* F2,TString channel,TString category,TString sample,bool PrintDiff){
  C->Clear();
  
  TH1F* H1 = (TH1F*) F1->Get(channel+"_"+category+"/"+sample);
  TH1F* H2 = (TH1F*) F2->Get(channel+"_"+category+"/"+sample);
  
  if(!H1||!H2||H1->Integral()!=H1->Integral()||H2->Integral()!=H2->Integral()){

    if(H1&&H1->Integral()==H1->Integral())H1->Draw("histpe");
    if(H2&&H2->Integral()==H2->Integral())H2->Draw("histpe");

    TText cat;
    cat.DrawTextNDC(.2,.5,channel+"_"+category+"/"+sample);
    if(!H1||H1->Integral()!=H1->Integral()) cat.DrawTextNDC(.2,.4,Group1+" is missing or 0");
    if(!H2||H2->Integral()!=H2->Integral()) cat.DrawTextNDC(.2,.4,Group2+" is missing or 0");

    if(PrintDiff)printf("| %.1f ",100);
    C->Print(TString(C->GetName())+".pdf");
    return;
  }
//   cout<<channel<<" "<<category<<" "<<sample<<endl;
//   cout<<H1->Integral()<<" "<<H2->Integral()<<endl;
//   TText cat;
//   cat.DrawTextNDC(.2,.5,channel+"_"+category+"/"+sample);
//   C->Print(TString(C->GetName())+".pdf");
//   return;


 
  TPad pad1("pad1","",0,0.2,1,1);
  TPad pad2("pad2","",0,0,1,0.2);
    
  ////////////////////////////////////////////
  pad1.cd();


  //H1->SetTitle("");
  H1->SetTitle(channel+"  "+category+"  "+sample);
  H1->GetXaxis()->SetTitle("mass");
  H1->GetYaxis()->SetTitle("");
  H1->GetYaxis()->SetRangeUser(0,(H1->GetMaximum()>H2->GetMaximum() ? H1->GetMaximum() : H2->GetMaximum())*1.2);
  H1->SetLineWidth(3);
  H1->SetLineColor(1);
  H1->SetFillColor(0);
  H1->Draw("histpe");
  H2->SetMarkerSize(0.01);
  H2->SetLineWidth(3);
  H2->SetLineColor(2);
  H2->SetFillColor(0);
  H2->Draw("histesame");
  
  TText TXmine;
  TXmine.SetTextColor(1);
  TXmine.SetTextSize(.04);
  TText TXother;
  TXother.SetTextColor(2);
  TXother.SetTextSize(.04);
  TText TXdiff;
  TXdiff.SetTextColor(4);
  TXdiff.SetTextSize(.03);
  char yield1[100];
  sprintf(yield1,"%.2f",H1->Integral(1,H1->GetNbinsX()));
  char yield2[100];
  sprintf(yield2,"%.2f",H2->Integral(1,H2->GetNbinsX()));
  TXmine.DrawTextNDC(.55,.845,Group1+" : "+yield1);
  TXother.DrawTextNDC(.55,.81,Group2+" : "+yield2);
  char txt[100];
  float diff=100*2*fabs(H1->Integral(1,H1->GetNbinsX())-H2->Integral(1,H2->GetNbinsX()))/(H1->Integral(1,H1->GetNbinsX())+H2->Integral(1,H2->GetNbinsX()));
  sprintf(txt,"Difference = %.1f",diff);
  TXdiff.DrawTextNDC(.25,.85,TString(txt)+"%");

  ////////////////////////////////////////////
  pad2.cd();
  ///Draw the ratio of the historgrams
  TH1F*HDiff=(TH1F*)H2->Clone("HDiff");
  HDiff->Divide(H1);
  HDiff->GetYaxis()->SetRangeUser(0.8,1.2);
  HDiff->GetYaxis()->SetNdivisions(3);
  HDiff->GetYaxis()->SetLabelSize(0.1);
  HDiff->GetYaxis()->SetTitleSize(0.1);
  HDiff->GetYaxis()->SetTitleOffset(0.5);
  //HDiff->GetYaxis()->SetTitle(myGroup + " / " + group);
  HDiff->GetYaxis()->SetTitle("Ratio");
  HDiff->GetXaxis()->SetNdivisions(-1);
  HDiff->GetXaxis()->SetTitle("");
  HDiff->GetXaxis()->SetLabelSize(0.0001);
  HDiff->SetMarkerSize(0.1);
  HDiff->Draw("histpe");
  TLine line;
  line.DrawLine(HDiff->GetXaxis()->GetXmin(),1,HDiff->GetXaxis()->GetXmax(),1);




  C->Clear();
  pad1.Draw();
  pad2.Draw();



  //cout<<setiosflags(ios::fixed)<<precision(2);
  //cout<<"| "<<diff<<" "<<endl;
  //if(PrintDiff)printf("| %.1f ",diff);
  C->Print(TString(C->GetName())+".pdf");

  //delete H1;
  //delete H2;
  delete HDiff;
}