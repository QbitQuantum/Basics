void drawHistos(TCanvas * C, TString filename, TString category, TTree* Tmine, TTree* Tother,TString var, int nbins, float xmin, float xmax, TString selection, TString myGroup, TString myRootFile, TString group, TString groupRootFile,TString mySel="1",TString groupSel="1"){
  TH1F* Hmine = new TH1F(TString("Hmine")+var,"",nbins,xmin,xmax); 
  Hmine->GetYaxis()->SetTitle(category);
  Hmine->GetXaxis()->SetTitle(var);
  Hmine->SetLineColor(1);
  Hmine->SetStats(0);
  TH1F* Hother = new TH1F(TString("Hother")+var,"",nbins,xmin,xmax); 
  Hother->GetYaxis()->SetTitle(category);
  Hother->GetXaxis()->SetTitle(var);
  Hother->SetLineColor(2);
  Hother->SetStats(0);

  TText TXmine;
  TXmine.SetTextColor(1);
  TXmine.SetTextSize(.04);
  TText TXother;
  TXother.SetTextColor(2);
  TXother.SetTextSize(.04);

  Tmine->Draw(var+">>"+Hmine->GetName(),selection+"*("+mySel+")");
  Tother->Draw(var+">>"+Hother->GetName(),selection+"*("+groupSel+")");

  ////Draw one histogram on top of the other
  C->Clear();
  //Hmine->Scale(1./Hmine->Integral());
  //Hother->Scale(1./Hother->Integral()); 
  //Hother->Scale(968134./688134.); //GGH e-tau
  if(Hmine->GetMaximum()>Hother->GetMaximum())
    Hmine->GetYaxis()->SetRangeUser(0,Hmine->GetMaximum()*1.1);
  else Hmine->GetYaxis()->SetRangeUser(0,Hother->GetMaximum()*1.1);
  Hmine->Draw("hist");
  Hother->Draw("histsame");

//   ///Draw the difference of the historgrams
//   TH1F*HDiff=(TH1F*)Hmine->Clone("HDiff");
//   HDiff->Add(Hother,-1);
//   int max= abs(HDiff->GetMaximum())>abs( HDiff->GetMinimum()) ?   abs(HDiff->GetMaximum()): abs( HDiff->GetMinimum());
//   HDiff->GetYaxis()->SetRangeUser(-2*(max>0?max:1),2*(max>0?max:1));
//   HDiff->Draw("hist");
//   TLine line;
//   line.DrawLine(HDiff->GetXaxis()->GetXmin(),0,HDiff->GetXaxis()->GetXmax(),0);

  //Print the integrals of the histograms a the top
  //TXmine.DrawTextNDC(.2,.965,myGroup+"_"+myRootFile+": "+(long)(Hmine->Integral(0,Hmine->GetNbinsX()+1)));
  //TXother.DrawTextNDC(.2,.93,group+"_"+groupRootFile+": "+(long)(Hother->Integral(0,Hother->GetNbinsX()+1)));
  TXmine.DrawTextNDC(.2,.965,myGroup+" : "+(long)(Hmine->Integral(0,Hmine->GetNbinsX()+1)));
  TXother.DrawTextNDC(.2,.93,group+": "+(long)(Hother->Integral(0,Hother->GetNbinsX()+1)));
  C->Print(filename);

  delete Hmine;
  delete Hother;
}