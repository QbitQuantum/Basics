void tpcdraw(Int_t sec, Int_t row, Int_t pad)
{
   gStyle->SetOptStat(0); 
  //calculate occupancy for selected sector and pad row 
  //for selected pad is obtained signal shape 
  Double_t par[3];
  gtpc.SetSecRowTime(sec,row);
  gtpc.SetHisto(pad);
  gtpc.Draw("box");  
  //plot histograms with specified options
  //move pads to another position be possible add text
  gtpc.GetPad1().SetPad(0.05,0.72,0.95,0.95);
  gtpc.GetPad2().SetPad(0.05,0.47,0.95,0.70); 
  gtpc.GetPad3().SetPad(0.05,0.22,0.95,0.45);  
  //fit histogram of occupancy on specified range <150,500> 
  gtpc.GetPad2().cd();
  g1 = new TF1("pol0_r","pol0",150,500); 
  gtpc.GetHis3()->Fit("pol0_r","R0Q");    
  g1->GetParameters(&par[0]);
  Float_t error = g1->GetParError(0);
  fitText = new TPaveText(0.15,0.7,0.3,0.9,"NDC");
  fitText->AddText("p0 fit on interval <150-500>");
  char s[100];
  sprintf(s,"%0.3f+- %0.3f",par[0],error);
  fitText->AddText(s);
  fitText->Draw();
  gtpc.GetPad2().Update();     
  //set logarithmic 
  gtpc.GetPad3().cd();
  gtpc.GetPad3().SetLogy();  
   gtpc.GetPad3().Draw();    
  //add comments to the histograms 
  gtpc.GetCanvas().cd();
  TPaveText * comment = new TPaveText(0.05,0.03,0.95,0.2,"NDC");
  comment->SetTextAlign(12);
  comment->SetFillColor(42);
  comment->ReadFile("comment.txt");
  comment->Draw();
  gtpc.GetCanvas().Update();
  

}