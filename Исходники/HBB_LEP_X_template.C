void 
HBB_LEP_X(bool scaled=true, bool log=true, float min=0.1, float max=-1., const char* inputfile="root/$HISTFILE", const char* directory="bb_$CATEGORY")
{
  // define common canvas, axes pad styles
  SetStyle(); gStyle->SetLineStyleString(11,"20 10");

  // determine category tag
  const char* category_extra = "";
  if(std::string(directory) == std::string("bb_had0"  )){ category_extra = "all-had_{0}";  }
  if(std::string(directory) == std::string("bb_had1"  )){ category_extra = "all-had_{1}";  }
  if(std::string(directory) == std::string("bb_had2"  )){ category_extra = "all-had_{2}";  }
  if(std::string(directory) == std::string("bb_had3"  )){ category_extra = "all-had_{3}";  }
  if(std::string(directory) == std::string("bb_had4"  )){ category_extra = "all-had_{4}";  }
  if(std::string(directory) == std::string("bb_had5"  )){ category_extra = "all-had_{5}";  }
  if(std::string(directory) == std::string("bb_lep"   )){ category_extra = "semi-lep";  }

  const char* dataset;
  if(std::string(inputfile).find("7TeV")!=std::string::npos){dataset = "Preliminary, #sqrt{s} = 7 TeV, L = 4.8 fb^{-1}";}
  if(std::string(inputfile).find("8TeV")!=std::string::npos){dataset = "Preliminary, #sqrt{s} = 8 TeV, L = 19.4 fb^{-1}";}
  
  TFile* input = new TFile(inputfile);
  TH1F* bkgBBB  = refill((TH1F*)input->Get(TString::Format("%s/bkgBBB"   , directory)), "bkgBBB"); InitHist(bkgBBB, "", "", kMagenta-10, 1001);;
#ifdef MSSM
  float bbHScale = 1.; // scenario for MSSM, mhmax, mA=160, tanb=20, A+H for the time being
  if(std::string(inputfile).find("7TeV")!=std::string::npos){ bbHScale = (23314.3*0.879 + 21999.3*0.877)/1000.; }
  if(std::string(inputfile).find("8TeV")!=std::string::npos){ bbHScale = (31087.9*0.879 + 29317.8*0.877)/1000.; }
 //  float bbHScale = 1.; // scenario for MSSM, mhmax, mA=160, tanb=10, A+H for the time being
//   if(std::string(inputfile).find("7TeV")!=std::string::npos){ bbHScale = (6211.6*0.89 + 5145.0*0.85)/1000.; }
//   if(std::string(inputfile).find("8TeV")!=std::string::npos){ bbHScale = (8282.7*0.89 + 6867.8*0.85)/1000.; }
  TH1F* bbH  = refill((TH1F*)input->Get(TString::Format("%s/bbH160"  , directory)), "bbH"  ); InitSignal(bbH); bbH->Scale(bbHScale);
#endif
  TH1F* data   = refill((TH1F*)input->Get(TString::Format("%s/data_obs", directory)), "data", true);
  InitHist(data, "#bf{m_{b#bar{b}} [GeV]}", "#bf{dN/dm_{b#bar{b}} [1/GeV]}"); InitData(data);

  TH1F* ref=(TH1F*)bkgBBB->Clone("ref");

  double unscaled[7];
  unscaled[0] = bkgBBB ->Integral();
#ifdef MSSM
  unscaled[1] = bbH ->Integral();
  unscaled[2] = 0;
#endif

  if(scaled){
    rescale(bkgBBB,   1);
#ifdef MSSM 
    rescale(bbH,   2);
#endif
  }

  TH1F* scales[7];
  scales[0] = new TH1F("scales-bkgBBB", "", 3, 0, 3);
  scales[0]->SetBinContent(1, unscaled[0]>0 ? (bkgBBB  ->Integral()/unscaled[0]-1.) : 0.);
#ifdef MSSM
  scales[1] = new TH1F("scales-bbH"  , "", 3, 0, 3);
  scales[1]->SetBinContent(2, unscaled[1]>0 ? (bbH  ->Integral()/unscaled[1]-1.) : 0.);
  scales[2] = new TH1F("scales-NONE" , "", 3, 0, 3);
  scales[2]->SetBinContent(3, 0.);
#endif

  if(!log){
#ifdef MSSM
    bbH  ->Add(bkgBBB);
#endif
  }

  /*
    mass plot before and after fit
  */
  TCanvas* canv = MakeCanvas("canv", "histograms", 600, 600);
  canv->cd();
  if(log){ canv->SetLogy(1); }
#if defined MSSM
  if(!log){ data->GetXaxis()->SetRange(0, data->FindBin(350)); } else{ data->GetXaxis()->SetRange(0, data->FindBin(1000)); };
#endif

  data->SetNdivisions(505);
  data->SetMinimum(min);
  data->SetMaximum(max>0 ? max : std::max(maximum(data, log), maximum(bkgBBB, log)));
  data->Draw("e");

  TH1F* errorBand = (TH1F*)bkgBBB ->Clone();
  errorBand  ->SetMarkerSize(0);
  errorBand  ->SetFillColor(1);
  errorBand  ->SetFillStyle(3013);
  errorBand  ->SetLineWidth(1);

  if(log){
    bkgBBB  ->Draw("histsame");
    $DRAW_ERROR
#ifndef DROP_SIGNAL
    bbH     ->Draw("histsame");
#endif
  }
  else{  
#ifndef DROP_SIGNAL
    bbH     ->Draw("histsame");
#endif  
    bkgBBB  ->Draw("histsame");
    $DRAW_ERROR
  }
  data->Draw("esame");
  canv->RedrawAxis();

  //CMSPrelim(dataset, "b#bar{b}", 0.17, 0.835);
  CMSPrelim(dataset, "", 0.17, 0.835);  
  TPaveText* chan     = new TPaveText(0.20, 0.74+0.061, 0.32, 0.74+0.161, "NDC");
  chan->SetBorderSize(   0 );
  chan->SetFillStyle(    0 );
  chan->SetTextAlign(   12 );
  chan->SetTextSize ( 0.05 );
  chan->SetTextColor(    1 );
  chan->SetTextFont (   62 );
  chan->AddText("b#bar{b}");
  chan->Draw();

  TPaveText* cat      = new TPaveText(0.20, 0.68+0.061, 0.32, 0.68+0.161, "NDC");
  cat->SetBorderSize(   0 );
  cat->SetFillStyle(    0 );
  cat->SetTextAlign(   12 );
  cat->SetTextSize ( 0.05 );
  cat->SetTextColor(    1 );
  cat->SetTextFont (   62 );
  cat->AddText(category_extra);
  cat->Draw();
 
#ifdef MSSM
  TPaveText* massA      = new TPaveText(0.75, 0.48+0.061, 0.85, 0.48+0.161, "NDC");
  massA->SetBorderSize(   0 );
  massA->SetFillStyle(    0 );
  massA->SetTextAlign(   12 );
  massA->SetTextSize ( 0.03 );
  massA->SetTextColor(    1 );
  massA->SetTextFont (   62 );
  massA->AddText("m_{A}=160GeV");
  massA->Draw();

  TPaveText* tanb      = new TPaveText(0.75, 0.44+0.061, 0.85, 0.44+0.161, "NDC");
  tanb->SetBorderSize(   0 );
  tanb->SetFillStyle(    0 );
  tanb->SetTextAlign(   12 );
  tanb->SetTextSize ( 0.03 );
  tanb->SetTextColor(    1 );
  tanb->SetTextFont (   62 );
  tanb->AddText("tan#beta=20");
  tanb->Draw();

  TPaveText* scen      = new TPaveText(0.75, 0.40+0.061, 0.85, 0.40+0.161, "NDC");
  scen->SetBorderSize(   0 );
  scen->SetFillStyle(    0 );
  scen->SetTextAlign(   12 );
  scen->SetTextSize ( 0.03 );
  scen->SetTextColor(    1 );
  scen->SetTextFont (   62 );
  scen->AddText("mhmax");
  scen->Draw();
#endif


#ifdef MSSM  
  TLegend* leg = new TLegend(0.55, 0.65, 0.94, 0.90);
  SetLegendStyle(leg);
  leg->AddEntry(bbH  , "#phi#rightarrowb#bar{b}" , "L" );
#endif
  leg->AddEntry(data,   "observed"                       , "LP");
  leg->AddEntry(bkgBBB, "bkgBBB"                      , "F" );
  $ERROR_LEGEND
  leg->Draw();

//#ifdef MSSM
//  TPaveText* mssm  = new TPaveText(0.69, 0.85, 0.90, 0.90, "NDC");
//  mssm->SetBorderSize(   0 );
//  mssm->SetFillStyle(    0 );
//  mssm->SetTextAlign(   12 );
//  mssm->SetTextSize ( 0.03 );
//  mssm->SetTextColor(    1 );
//  mssm->SetTextFont (   62 );
//  mssm->AddText("(m_{A}=250, tan#beta=5)");
//  mssm->Draw();
//#else
//  TPaveText* mssm  = new TPaveText(0.83, 0.85, 0.95, 0.90, "NDC");
//  mssm->SetBorderSize(   0 );
//  mssm->SetFillStyle(    0 );
//  mssm->SetTextAlign(   12 );
//  mssm->SetTextSize ( 0.03 );
//  mssm->SetTextColor(    1 );
//  mssm->SetTextFont (   62 );
//  mssm->AddText("m_{H}=125");
//  mssm->Draw();
//#endif

  /*
    Ratio Data over MC
  */
  TCanvas *canv0 = MakeCanvas("canv0", "histograms", 600, 400);
  canv0->SetGridx();
  canv0->SetGridy();
  canv0->cd();

  TH1F* zero = (TH1F*)ref ->Clone("zero"); zero->Clear();
  TH1F* rat1 = (TH1F*)data->Clone("rat"); 
  rat1->Divide(bkgBBB);
  for(int ibin=0; ibin<rat1->GetNbinsX(); ++ibin){
    if(rat1->GetBinContent(ibin+1)>0){
      // catch cases of 0 bins, which would lead to 0-alpha*0-1
      rat1->SetBinContent(ibin+1, rat1->GetBinContent(ibin+1)-1.);
    }
    zero->SetBinContent(ibin+1, 0.);
  }
  rat1->SetLineColor(kBlack);
  rat1->SetFillColor(kGray );
  rat1->SetMaximum(+1.5);
  rat1->SetMinimum(-1.5);
  rat1->GetYaxis()->CenterTitle();
  rat1->GetYaxis()->SetTitle("#bf{Data/MC-1}");
  rat1->GetXaxis()->SetTitle("#bf{m_{b#bar{b}} [GeV]}");
  rat1->Draw();
  zero->SetLineColor(kBlack);
  zero->Draw("same");
  canv0->RedrawAxis();

  /*
    Ratio After fit over Prefit
  */
  TCanvas *canv1 = MakeCanvas("canv1", "histograms", 600, 400);
  canv1->SetGridx();
  canv1->SetGridy();
  canv1->cd();

  TH1F* rat2 = (TH1F*) bkgBBB->Clone("rat2");
  rat2->Divide(ref);
  for(int ibin=0; ibin<rat2->GetNbinsX(); ++ibin){
    if(rat2->GetBinContent(ibin+1)>0){
      // catch cases of 0 bins, which would lead to 0-alpha*0-1
      rat2 ->SetBinContent(ibin+1, rat2->GetBinContent(ibin+1)-1.);
    }
  }
  rat2->SetLineColor(kRed+ 3);
  rat2->SetFillColor(kRed-10);
  rat2->SetMaximum(+0.3);
  rat2->SetMinimum(-0.3);
  rat2->GetYaxis()->SetTitle("#bf{Fit/Prefit-1}");
  rat2->GetYaxis()->CenterTitle();
  rat2->GetXaxis()->SetTitle("#bf{m_{b#bar{b}} [GeV]}");
  rat2->GetXaxis()->SetRange(0, 28);
  rat2->Draw();
  zero->SetLineColor(kBlack);
  zero->Draw("same");
  canv1->RedrawAxis();

  /*
    Relative shift per sample
  */
  TCanvas *canv2 = MakeCanvas("canv2", "histograms", 600, 400);
  canv2->SetGridx();
  canv2->SetGridy();
  canv2->cd();

  InitHist  (scales[0], "", "", kMagenta-10, 1001);
  scales[0]->Draw();
  scales[0]->GetXaxis()->SetBinLabel(1, "#bf{bkgBBB}");
#ifdef MSSM
  scales[0]->GetXaxis()->SetBinLabel(2, "#bf{bbH}"  );
  scales[0]->GetXaxis()->SetBinLabel(3, "#bf{NONE}" );
#endif
  scales[0]->SetMaximum(+1.0);
  scales[0]->SetMinimum(-1.0);
  scales[0]->GetYaxis()->CenterTitle();
  scales[0]->GetYaxis()->SetTitle("#bf{Fit/Prefit-1}");
  zero->Draw("same");
  canv2->RedrawAxis();

  /*
    prepare output
  */
  bool isSevenTeV = std::string(inputfile).find("7TeV")!=std::string::npos;
  canv ->Print(TString::Format("%s_%sscaled_%s_%s.png"       , directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
  canv ->Print(TString::Format("%s_%sscaled_%s_%s.pdf"       , directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
  canv ->Print(TString::Format("%s_%sscaled_%s_%s.eps"       , directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
  canv0->Print(TString::Format("%s_datamc_%sscaled_%s_%s.png", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
  canv0->Print(TString::Format("%s_datamc_%sscaled_%s_%s.pdf", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
  canv0->Print(TString::Format("%s_datamc_%sscaled_%s_%s.eps", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
  canv1->Print(TString::Format("%s_prefit_%sscaled_%s_%s.png", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
  canv1->Print(TString::Format("%s_prefit_%sscaled_%s_%s.pdf", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
  canv1->Print(TString::Format("%s_prefit_%sscaled_%s_%s.eps", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
  canv2->Print(TString::Format("%s_sample_%sscaled_%s_%s.png", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
  canv2->Print(TString::Format("%s_sample_%sscaled_%s_%s.pdf", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
  canv2->Print(TString::Format("%s_sample_%sscaled_%s_%s.eps", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
  TFile* output = new TFile(TString::Format("%s_%sscaled_%s_%s.root", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""), "update");
  output->cd();
  data ->Write("data_obs");
  bkgBBB  ->Write("bkgBBB"  );
#ifdef MSSM
  bbH  ->Write("bbH"     );
#endif
  if(errorBand){
    errorBand->Write("errorBand");
  }
  output->Close();
}