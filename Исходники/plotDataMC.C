//-------------------------------------------------------------------------------------
void MoveStatsAndDraw (TH1 *data, TH1 *mc, char *dataTitle, char* mcTitle, char* firstline, char* secondline, int log, int col, bool stat, TString cut1, TString cut2, bool movepave){
  c->SetLogy(log);
  mc->Draw();
  data->Draw("pesames");   
  gStyle->SetOptStat(00000000); 
  stat=0;  
  if(stat) gStyle->SetOptStat(1111111111); 

  /*  TPaveText *TITLE = new TPaveText(0.2,0.65,0.55,0.9,"blNDC");
  TITLE->SetFillStyle(4000);
  TITLE->SetFillColor(kWhite);
  TITLE->SetBorderSize(0.1);
  TITLE->SetTextFont(42);
  TITLE->AddText(firstline);
  TITLE->Draw();  */

  if(!movepave) {
  TPaveText *title = new TPaveText(0.2,0.7,0.55,0.93,"blNDC");
  } else {
    //  TPaveText *title = new TPaveText(0.6,0.58,0.95,0.83,"blNDC");
  TPaveText *title = new TPaveText(0.6,0.7,0.95,0.93,"blNDC");
  }
  title->SetFillStyle(4000);
  title->SetFillColor(kWhite);
  title->SetBorderSize(0.1);
  title->SetTextFont(42);
  title->AddText(firstline);
  title->AddText(secondline);
  title->AddText(cut1);
  title->AddText(cut2);
  title->Draw();  
  if(!movepave) {
    TLegend *leg = new TLegend(0.65,0.83,1.,0.93);
  } else {
    TLegend *leg = new TLegend(0.65,0.60,1.,0.7);
  }
  leg->SetFillStyle(4000);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0.1);
  leg->SetTextFont(42);
  leg->AddEntry(data,dataTitle,"p");
  leg->AddEntry(mc,mcTitle,"f");
  leg->Draw();

  c->Modified();
  c->Update();



  if(stat){
  TPaveStats * ps = (TPaveStats *) mc->GetListOfFunctions()->FindObject("stats"); 
  TPaveStats * ps2 = (TPaveStats *) data->GetListOfFunctions()->FindObject("stats");
  Int_t ci; 
  ci = TColor::GetColor(col);
  if( ps ){ 
    ps->SetTextColor(1); 
    ps->SetLineColor(col);   
  }
  else std::cout << "Null pointer to TPaveStats: " << ps << std::endl; 
  ps->SetY1NDC(0.40);
  ps->SetY2NDC(0.68);
  if( ps2 ) ps2->SetTextColor(ci); else std::cout << "Null pointer to TPaveStats: " << ps2 << std::endl;
  }
}