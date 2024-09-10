void spectra_mw(const char *prefix = "pt/PhiNsigma_KTPCnsig30_STD2010_00_DEFAULT_00")
{
  TGraphErrors *g = ReadMWGraph(Form("%s/mass", prefix), 1);
  g->Draw("ACP");

  TLatex latex;
  latex.SetTextFont(42);
  latex.SetTextAlign(12);
  latex.SetTextSize(0.03);
  latex.SetTextColor(kBlue+1);
  latex.DrawLatex(1.2, 1.01877, "MC generated");
  latex.SetTextColor(kGreen+1);
  latex.DrawLatex(1.2, 1.01877-0.00015, "MC reconstructed");
  latex.SetTextColor(kRed+1);
  latex.DrawLatex(1.2, 1.01877-2*0.000155, "Real data (uncorrected)");
  latex.SetTextColor(kBlack);
  latex.DrawLatex(1.2, 1.01877-3*0.00016, "Real data (corrected)");
  gPad->Print(Form("%s.pdf", g->GetName()));

  gPad->Clear();
  gPad->SetLogy(0);
  TGraphErrors *g = ReadMWGraph(Form("%s/mass", prefix), 3);
  g->Draw("AP");
  latex.SetTextAlign(22);
  latex.SetTextSize(0.04);
  latex.SetTextColor(kBlack);
  latex.DrawLatex(2.0, 1.0207, "pp @ #sqrt{s} = 2.76 TeV");
  latex.DrawLatex(2.0, 1.0205, "TPC 3.0 #sigma");
  latex.DrawLatex(2.0, 1.0202, "#phi #rightarrow K^{ +}  K^{ -}");
  latex.SetTextSize(0.035);
  latex.DrawLatex(1.7, 1.0182, "uncertainties:  stat. (bars) & syst. (boxes)");
  gPad->Print(Form("%s.pdf", g->GetName()));

  gPad->Clear();
  TGraphErrors *g = ReadMWGraph(Form("%s/width", prefix), 2);
  g->Draw("AP");
  TLatex latex;
  latex.SetTextAlign(22);
  latex.SetTextSize(0.04);
  latex.SetTextColor(kBlack);
  latex.DrawLatex(1.7, 0.0090, "pp @ #sqrt{s} = 2.76 TeV");
  latex.DrawLatex(1.7, 0.0085, "TPC 3.0 #sigma");
  latex.DrawLatex(1.7, 0.0077, "#phi #rightarrow K^{ +}  K^{ -}");
  latex.SetTextSize(0.035);
  latex.DrawLatex(1.7, 0.0007, "uncertainties:  stat. (bars) & syst. (boxes)");
  gPad->Print(Form("%s.pdf", g->GetName()));

  //  gPad->Clear();
  //  gPad->SetLogy();
  //  TGraphErrors *g = ReadPtGraphSys("pt/out.txt");
  //  if (!g) return;
  //  g->Draw("AP");
  //  gPad->Print(Form("%s.pdf", g->GetName()));
}