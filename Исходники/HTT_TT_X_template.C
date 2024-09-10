void 
HTT_TT_X(bool scaled=true, bool log=false, float min=0., float max=-1., const char* inputfile="root/$HISTFILE", const char* directory="$CATEGORY")
{
  // define common canvas, axes pad styles
  SetStyle(); gStyle->SetLineStyleString(11,"20 10");

  // determine category tag
  const char* category_extra = "";
  if(std::string(directory) == std::string("emu_0jet_low"  )){ category_extra = "0 jet, low p_{T}";  }
  if(std::string(directory) == std::string("emu_0jet_high" )){ category_extra = "0 jet, high p_{T}"; }
  if(std::string(directory) == std::string("emu_boost_low" )){ category_extra = "1 jet, low p_{T}";  }
  if(std::string(directory) == std::string("emu_boost_high")){ category_extra = "1 jet, high p_{T}"; }
  if(std::string(directory) == std::string("emu_vbf"       )){ category_extra = "2 jet (VBF)";       }
  if(std::string(directory) == std::string("emu_nobtag"    )){ category_extra = "No B-Tag";          }
  if(std::string(directory) == std::string("emu_btag"      )){ category_extra = "B-Tag";             }

  const char* dataset;
  if(std::string(inputfile).find("7TeV")!=std::string::npos){dataset = "CMS Preliminary,  ZH#rightarrow#lltau#tau, 4.9 fb^{-1} at 7 TeV";}
  if(std::string(inputfile).find("8TeV")!=std::string::npos){dataset = "CMS Preliminary,  ZH#rightarrowll#tau#tau, 19.4 fb^{-1} at 8 TeV";}
#ifdef MSSM
  if(std::string(inputfile).find("8TeV")!=std::string::npos){dataset = "CMS Preliminary,  H#rightarrow#tau#tau, 19.4 fb^{-1} at 8 TeV";}
#endif
  
  TFile* input = new TFile(inputfile);
  TH1F* ZZ  = refill((TH1F*)input->Get(TString::Format("%s/ZZ"   , directory)), "ZZ"); InitHist(ZZ, "", "", kMagenta-10, 1001);
  TH1F* GGToZZ2L2L  = refill((TH1F*)input->Get(TString::Format("%s/GGToZZ2L2L"   , directory)), "GGToZZ2L2L"); InitHist(GGToZZ2L2L, "", "", kMagenta-10, 1001);
  TH1F* Zjets    = refill((TH1F*)input->Get(TString::Format("%s/Zjets"     , directory)), "Zjets"  ); InitHist(Zjets  , "", "", kRed    + 2, 1001);
#ifndef DROP_SIGNAL
  TH1F* ZH_htt    = refill((TH1F*)input->Get(TString::Format("%s/ZH_htt"  , directory)+"125"), "ZH_htt"  ); InitSignal(ZH_htt); ZH_htt->Scale(SIGNAL_SCALE);
  TH1F* ZH_hww    = refill((TH1F*)input->Get(TString::Format("%s/ZH_hww"  , directory)+"125"), "ZH_hww"  ); InitSignal(ZH_hww); ZH_hww->Scale(SIGNAL_SCALE);
#endif
  TH1F* data   = refill((TH1F*)input->Get(TString::Format("%s/data_obs", directory)), "data", true);
  InitHist(data, "#bf{m_{#tau#tau} [GeV]}", "#bf{dN/dm_{#tau#tau} [1/GeV]}"); InitData(data);

  TH1F* ref=(TH1F*)ZZ->Clone("ref");
  ref->Add(GGToZZ2L2L);
  ref->Add(Zjets  );

  double unscaled[5];
  unscaled[0] = ZZ->Integral();
  unscaled[1] = GGToZZ2L2L->Integral();
  unscaled[2] = Zjets  ->Integral();
#ifndef DROP_SIGNAL
  unscaled[3] = ZH_htt  ->Integral();
  unscaled[4] = ZH_hww  ->Integral();
#endif

  if(scaled){
    rescale(ZZ, 1);
    rescale(GGToZZ2L2L, 2);
    rescale(Zjets,   3);
#ifndef DROP_SIGNAL
    rescale(ZH_htt,   4);
    rescale(ZH_hww,   5);
#endif
  }

  TH1F* scales[5];
  scales[0] = new TH1F("scales-ZZ", "", 5, 0, 5);
  scales[0]->SetBinContent(1, unscaled[0]>0 ? (ZZ->Integral()/unscaled[0]-1.) : 0.);
  scales[1] = new TH1F("scales-GGToZZ2L2L", "", 5, 0, 5);
  scales[1]->SetBinContent(2, unscaled[1]>0 ? (GGToZZ2L2L->Integral()/unscaled[1]-1.) : 0.);
  scales[2] = new TH1F("scales-Zjets"  , "", 5, 0, 5);
  scales[2]->SetBinContent(3, unscaled[2]>0 ? (Zjets  ->Integral()/unscaled[2]-1.) : 0.);
#ifndef DROP_SIGNAL
  scales[3] = new TH1F("scales-ZH_htt"  , "", 5, 0, 5);
  scales[3]->SetBinContent(4, unscaled[3]>0 ? (ZH_htt  ->Integral()/unscaled[3]-1.) : 0.);
  scales[4] = new TH1F("scales-ZH_hww"  , "", 5, 0, 5);
  scales[4]->SetBinContent(5, unscaled[4]>0 ? (ZH_hww  ->Integral()/unscaled[4]-1.) : 0.);
#endif

  GGToZZ2L2L->Add(Zjets);
  ZZ  ->Add(GGToZZ2L2L);
  if(log){
#ifndef DROP_SIGNAL
    ZH_htt  ->Add(ZH_hww );
#endif
  }
  else{
#ifndef DROP_SIGNAL
    ZH_htt   ->Add(ZH_hww);
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
#else
  data->GetXaxis()->SetRange(0, data->FindBin(350));
#endif

  data->SetNdivisions(505);
  data->SetMinimum(min);
  float maxZZ=ZZ->GetBinContent(ZZ->GetMaximumBin()); float maxdata=data->GetBinContent(data->GetMaximumBin());
  if (maxdata>maxZZ)
     data->SetMaximum(1.8*maxdata);
  else
     data->SetMaximum(1.8*maxZZ);
  data->Draw("e");

//  TH1F* errorBand = (TH1F*)ZZ ->Clone();
  TH1F* errorBand = (TH1F*)Zjets ->Clone();
  errorBand  ->SetMarkerSize(0);
  errorBand  ->SetFillColor(1);
  errorBand  ->SetFillStyle(3013);
  errorBand  ->SetLineWidth(1);
  errorBand  ->Scale(0.15);
  for(int idx=0; idx<errorBand->GetNbinsX(); ++idx){
    if(errorBand->GetBinContent(idx)>0){
      std::cout << "Uncertainties on summed background samples: " << errorBand->GetBinError(idx)/errorBand->GetBinContent(idx) << std::endl;
      break;
    }
  }
  //if(log){
    ZZ  ->Draw("histsame");
    Zjets->Draw("histsame");
    $DRAW_ERROR
#ifndef DROP_SIGNAL
    ZH_htt  ->Draw("histsame");
#endif
  //}
  //else{
//#ifndef DROP_SIGNAL
//    ggH  ->Draw("histsame");
//#endif
//    Ztt  ->Draw("histsame");
//    ttbar->Draw("histsame");
//    EWK  ->Draw("histsame");
//    Fakes->Draw("histsame");
//    $DRAW_ERROR
//  }
  data->Draw("esame");
  canv->RedrawAxis();

//  //CMSPrelim(dataset, "#tau_{e}#tau_{#mu}", 0.17, 0.835);  
  CMSPrelim(dataset, "", 0.16, 0.835);  
  TPaveText* chan     = new TPaveText(0.20, 0.74+0.061, 0.32, 0.74+0.161, "NDC");
  chan->SetBorderSize(   0 );
  chan->SetFillStyle(    0 );
  chan->SetTextAlign(   12 );
  chan->SetTextSize ( 0.05 );
  chan->SetTextColor(    1 );
  chan->SetTextFont (   62 );
  if (directory=="eett_zh") 
    chan->AddText("#tau#tau");
  else
    chan->AddText("#mu#mu#tau#tau");
  chan->Draw();
//
//  TPaveText* cat      = new TPaveText(0.20, 0.68+0.061, 0.32, 0.68+0.161, "NDC");
//  cat->SetBorderSize(   0 );
//  cat->SetFillStyle(    0 );
//  cat->SetTextAlign(   12 );
//  cat->SetTextSize ( 0.05 );
//  cat->SetTextColor(    1 );
//  cat->SetTextFont (   62 );
//  cat->AddText(category_extra);
//  cat->Draw();
//
//#ifdef MSSM
//  TPaveText* massA      = new TPaveText(0.75, 0.48+0.061, 0.85, 0.48+0.161, "NDC");
//  massA->SetBorderSize(   0 );
//  massA->SetFillStyle(    0 );
//  massA->SetTextAlign(   12 );
//  massA->SetTextSize ( 0.03 );
//  massA->SetTextColor(    1 );
//  massA->SetTextFont (   62 );
//  massA->AddText("m_{A}=$MAGeV");
//  massA->Draw();
//
//  TPaveText* tanb      = new TPaveText(0.75, 0.44+0.061, 0.85, 0.44+0.161, "NDC");
//  tanb->SetBorderSize(   0 );
//  tanb->SetFillStyle(    0 );
//  tanb->SetTextAlign(   12 );
//  tanb->SetTextSize ( 0.03 );
//  tanb->SetTextColor(    1 );
//  tanb->SetTextFont (   62 );
//  tanb->AddText("tan#beta=$TANB");
//  tanb->Draw();
// 
//  TPaveText* scen      = new TPaveText(0.75, 0.40+0.061, 0.85, 0.40+0.161, "NDC");
//  scen->SetBorderSize(   0 );
//  scen->SetFillStyle(    0 );
//  scen->SetTextAlign(   12 );
//  scen->SetTextSize ( 0.03 );
//  scen->SetTextColor(    1 );
//  scen->SetTextFont (   62 );
//  scen->AddText("mhmax");
//  scen->Draw();
//#endif
//
//#ifdef MSSM  
//  TLegend* leg = new TLegend(0.45, 0.65, 0.95, 0.90);
//  SetLegendStyle(leg);
//  leg->AddEntry(ggH  , "#phi#rightarrow#tau#tau" , "L" );
//#else
  TLegend* leg = new TLegend(0.50, 0.65, 0.95, 0.90);
  SetLegendStyle(leg);
//#ifndef DROP_SIGNAL
//  if(SIGNAL_SCALE!=1){
    leg->AddEntry(ZH_htt  , TString::Format("%.0f#timesZH(125 GeV)#rightarrowll#tau#tau", SIGNAL_SCALE) , "L" );
//  }
//  else{
//    leg->AddEntry(ggH  , "H(125 GeV)#rightarrow#tau#tau" , "L" );
//  }
//#endif
//#endif
  leg->AddEntry(data , "observed"                       , "LP");
  leg->AddEntry(ZZ  , "ZZ"           , "F" );
  leg->AddEntry(Zjets, "Reducible"                       , "F" );
//  leg->AddEntry(EWK  , "electroweak"                    , "F" );
//  leg->AddEntry(Fakes, "QCD"                            , "F" );
  $ERROR_LEGEND
  leg->Draw();
//
////#ifdef MSSM
////  TPaveText* mssm  = new TPaveText(0.69, 0.85, 0.90, 0.90, "NDC");
////  mssm->SetBorderSize(   0 );
////  mssm->SetFillStyle(    0 );
////  mssm->SetTextAlign(   12 );
////  mssm->SetTextSize ( 0.03 );
////  mssm->SetTextColor(    1 );
////  mssm->SetTextFont (   62 );
////  mssm->AddText("(m_{A}=250, tan#beta=5)");
////  mssm->Draw();
////#else
////  TPaveText* mssm  = new TPaveText(0.83, 0.85, 0.95, 0.90, "NDC");
////  mssm->SetBorderSize(   0 );
////  mssm->SetFillStyle(    0 );
////  mssm->SetTextAlign(   12 );
////  mssm->SetTextSize ( 0.03 );
////  mssm->SetTextColor(    1 );
////  mssm->SetTextFont (   62 );
////  mssm->AddText("m_{H}=125");
////  mssm->Draw();
////#endif
//
//  /*
//    Ratio Data over MC
//  */
//  TCanvas *canv0 = MakeCanvas("canv0", "histograms", 600, 400);
//  canv0->SetGridx();
//  canv0->SetGridy();
//  canv0->cd();
//
//  TH1F* zero = (TH1F*)ref ->Clone("zero"); zero->Clear();
//  TH1F* rat1 = (TH1F*)data->Clone("rat"); 
//  rat1->Divide(Ztt);
//  for(int ibin=0; ibin<rat1->GetNbinsX(); ++ibin){
//    if(rat1->GetBinContent(ibin+1)>0){
//      // catch cases of 0 bins, which would lead to 0-alpha*0-1
//      rat1->SetBinContent(ibin+1, rat1->GetBinContent(ibin+1)-1.);
//    }
//    zero->SetBinContent(ibin+1, 0.);
//  }
//  rat1->SetLineColor(kBlack);
//  rat1->SetFillColor(kGray );
//  rat1->SetMaximum(+0.5);
//  rat1->SetMinimum(-0.5);
//  rat1->GetYaxis()->CenterTitle();
//  rat1->GetYaxis()->SetTitle("#bf{Data/MC-1}");
//  rat1->GetXaxis()->SetTitle("#bf{m_{#tau#tau} [GeV]}");
//  rat1->Draw();
//  zero->SetLineColor(kBlack);
//  zero->Draw("same");
//  canv0->RedrawAxis();
//
//  /*
//    Ratio After fit over Prefit
//  */
//  TCanvas *canv1 = MakeCanvas("canv1", "histograms", 600, 400);
//  canv1->SetGridx();
//  canv1->SetGridy();
//  canv1->cd();
//
//  TH1F* rat2 = (TH1F*) Ztt->Clone("rat2");
//  rat2->Divide(ref);
//  for(int ibin=0; ibin<rat2->GetNbinsX(); ++ibin){
//    if(rat2->GetBinContent(ibin+1)>0){
//      // catch cases of 0 bins, which would lead to 0-alpha*0-1
//      rat2 ->SetBinContent(ibin+1, rat2->GetBinContent(ibin+1)-1.);
//    }
//  }
//  rat2->SetLineColor(kRed+ 3);
//  rat2->SetFillColor(kRed-10);
//  rat2->SetMaximum(+0.3);
//  rat2->SetMinimum(-0.3);
//  rat2->GetYaxis()->SetTitle("#bf{Fit/Prefit-1}");
//  rat2->GetYaxis()->CenterTitle();
//  rat2->GetXaxis()->SetTitle("#bf{m_{#tau#tau} [GeV]}");
//  rat2->GetXaxis()->SetRange(0, 28);
//  rat2->Draw();
//  zero->SetLineColor(kBlack);
//  zero->Draw("same");
//  canv1->RedrawAxis();
//
//  /*
//    Relative shift per sample
//  */
//  TCanvas *canv2 = MakeCanvas("canv2", "histograms", 600, 400);
//  canv2->SetGridx();
//  canv2->SetGridy();
//  canv2->cd();
//
//  InitHist  (scales[0], "", "", kMagenta-10, 1001);
//  InitHist  (scales[1], "", "", kRed    + 2, 1001);
//  InitHist  (scales[2], "", "", kBlue   - 8, 1001);
//  InitHist  (scales[3], "", "", kOrange - 4, 1001);
//#ifndef DROP_SIGNAL
//  InitSignal(scales[4]);
//  InitSignal(scales[5]);
//  InitSignal(scales[6]);
//#endif
//  scales[0]->Draw();
//  scales[0]->GetXaxis()->SetBinLabel(1, "#bf{Fakes}");
//  scales[0]->GetXaxis()->SetBinLabel(2, "#bf{EWK}"  );
//  scales[0]->GetXaxis()->SetBinLabel(3, "#bf{ttbar}");
//  scales[0]->GetXaxis()->SetBinLabel(4, "#bf{Ztt}"  );
//#ifdef MSSM
//  scales[0]->GetXaxis()->SetBinLabel(5, "#bf{ggH}"  );
//  scales[0]->GetXaxis()->SetBinLabel(6, "#bf{bbH}"  );
//  scales[0]->GetXaxis()->SetBinLabel(7, "#bf{NONE}" );
//#else
//  scales[0]->GetXaxis()->SetBinLabel(5, "#bf{ggH}"  );
//  scales[0]->GetXaxis()->SetBinLabel(6, "#bf{qqH}"  );
//  scales[0]->GetXaxis()->SetBinLabel(7, "#bf{VH}"   );
//#endif
//  scales[0]->SetMaximum(+1.0);
//  scales[0]->SetMinimum(-1.0);
//  scales[0]->GetYaxis()->CenterTitle();
//  scales[0]->GetYaxis()->SetTitle("#bf{Fit/Prefit-1}");
//  scales[1]->Draw("same");
//  scales[2]->Draw("same");
//  scales[3]->Draw("same");
//#ifndef DROP_SIGNAL
//  scales[4]->Draw("same");
//  scales[5]->Draw("same");
//  scales[6]->Draw("same");
//#endif
//  zero->Draw("same");
//  canv2->RedrawAxis();
//
//  /*
//    prepare output
//  */
  bool isSevenTeV = std::string(inputfile).find("7TeV")!=std::string::npos;
  canv ->Print(TString::Format("%s_%sscaled_%s_%s.png"       , directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
  canv ->Print(TString::Format("%s_%sscaled_%s_%s.pdf"       , directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
  canv ->Print(TString::Format("%s_%sscaled_%s_%s.eps"       , directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
//  canv0->Print(TString::Format("%s_datamc_%sscaled_%s_%s.png", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
//  canv0->Print(TString::Format("%s_datamc_%sscaled_%s_%s.pdf", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
//  canv0->Print(TString::Format("%s_datamc_%sscaled_%s_%s.eps", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
//  canv1->Print(TString::Format("%s_prefit_%sscaled_%s_%s.png", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
//  canv1->Print(TString::Format("%s_prefit_%sscaled_%s_%s.pdf", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
//  canv1->Print(TString::Format("%s_prefit_%sscaled_%s_%s.eps", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
//  canv2->Print(TString::Format("%s_sample_%sscaled_%s_%s.png", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : "")); 
//  canv2->Print(TString::Format("%s_sample_%sscaled_%s_%s.pdf", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
//  canv2->Print(TString::Format("%s_sample_%sscaled_%s_%s.eps", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""));
  TFile* output = new TFile(TString::Format("%s_%sscaled_%s_%s.root", directory, scaled ? "re" : "un", isSevenTeV ? "7TeV" : "8TeV", log ? "LOG" : ""), "update");
  output->cd(); 
  data ->Write("data_obs");
  ZZ->Write("ZZ"   );
  Zjets  ->Write("Zjets"     );
  ZH_htt->Write("ZH_htt"   );
  ZH_hww  ->Write("ZH_hww"     );
//#ifdef MSSM
//  ggH  ->Write("ggH"     );
//  bbH  ->Write("bbH"     );
//#else
//#ifndef DROP_SIGNAL
//  ggH  ->Write("ggH"     );
//  qqH  ->Write("qqH"     );
//  VH   ->Write("VH"      );
//#endif
//#endif
  if(errorBand){
    errorBand->Write("errorBand");
  }
  output->Close();
}