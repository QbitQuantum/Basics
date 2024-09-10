void mergePlotResponse(const string& canvasName, TMultiGraph *mgResponse, TGraph *gResponseMC_MJB, TGraph *gResponseData_MJB, TGraph *gratio_MJB, TGraph *gResponseMC_MPF, TGraph *gResponseData_MPF, TGraph *gratio_MPF, double y_min, double y_max, const string& label_MJB, const string& label_MPF, const string& path) { // Mikko's tdrstyle_mod14
  TCanvas *c3 = tdrDiCanvas(canvasName.c_str(),mgResponse,gratio_MJB,2,0);
  c3->cd(1);

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  mgResponse->SetMaximum(y_max);
  mgResponse->SetMinimum(y_min);
  mgResponse->Draw("P");
  gPad->RedrawAxis();
  //c3->SetLogx(1);

  //TLegend* legend = new TLegend(0.55, 0.15, 0.92, 0.38);
  TLegend* legend = new TLegend(0.63, 0.15, 0.93, 0.30);
  legend->SetFillColor(kWhite);
  legend->SetFillStyle(kNone);
  legend->SetTextFont(43);
  legend->SetBorderSize(0);
  //legend->SetTextSize(0.045);
  string toLeg = label_MJB + ", MC";
  legend->AddEntry(gResponseMC_MJB, toLeg.c_str(),"p");
  toLeg = label_MJB + ", data";
  legend->AddEntry(gResponseData_MJB,toLeg.c_str(),"p");
  toLeg = label_MPF + ", MC";
  legend->AddEntry(gResponseMC_MPF,toLeg.c_str(),"p");
  toLeg = label_MPF + ", data";
  legend->AddEntry(gResponseData_MPF,toLeg.c_str(),"p");
  legend->Draw("same");


  c3->cd(2);
  TF1* ratioFit_MJB = new TF1("ratioFit_MJB", "[0]", mgResponse->GetXaxis()->GetXmin(),mgResponse->GetXaxis()->GetXmax());
  ratioFit_MJB->SetParameter(0, 0.);
  ratioFit_MJB->SetLineColor(gratio_MJB->GetLineColor());
  ratioFit_MJB->SetLineWidth(0);

  gratio_MJB->Draw("APE1");
  gratio_MJB->GetYaxis()->SetTitle("Data / MC");
  gratio_MJB->SetMarkerSize(1.0);
  gratio_MJB->SetMaximum(1.05);
  gratio_MJB->SetMinimum(0.95);
  gratio_MJB->GetXaxis()->SetLimits(mgResponse->GetXaxis()->GetXmin(),mgResponse->GetXaxis()->GetXmax());

  gratio_MPF->Draw("PE1same");

  c3->Update();
  gratio_MJB->Fit(ratioFit_MJB, "RQ");
  //gratio_MJB->GetYaxis()->SetRangeUser(-1,3);
  double fitValue_MJB = ratioFit_MJB->GetParameter(0);
  double fitError_MJB = ratioFit_MJB->GetParError(0);

  TF1* ratioFit_MPF = new TF1("ratioFit_MPF", "[0]", mgResponse->GetXaxis()->GetXmin(),mgResponse->GetXaxis()->GetXmax());
  ratioFit_MPF->SetParameter(0, 0.);
  ratioFit_MPF->SetLineColor(gratio_MPF->GetLineColor());
  ratioFit_MPF->SetLineWidth(0);
  gratio_MPF->Fit(ratioFit_MPF, "RQ");
  //gratio_MPF->GetYaxis()->SetRangeUser(-1,3);
  double fitValue_MPF = ratioFit_MPF->GetParameter(0);
  double fitError_MPF = ratioFit_MPF->GetParError(0);

  TPaveText* fitlabel = new TPaveText(0.57, 0.82, 0.85, 0.84, "brNDC");
  fitlabel->SetTextSize(0.08);
  fitlabel->SetFillColor(0);
  fitlabel->SetTextFont(42);
  fitlabel->SetTextColor(gratio_MJB->GetLineColor());
  TString fitLabelTextMJB = TString::Format("Fit %s: %.4f #pm %.4f", label_MJB.c_str(), fitValue_MJB, fitError_MJB);
  fitlabel->AddText(fitLabelTextMJB);
  fitlabel->Draw("same");

  TPaveText* fitlabel_MPF = new TPaveText(0.57, 0.72, 0.85, 0.74, "brNDC");
  fitlabel_MPF->SetTextSize(0.08);
  fitlabel_MPF->SetFillColor(0);
  fitlabel_MPF->SetTextFont(42);
  fitlabel_MPF->SetTextColor(gratio_MPF->GetLineColor());
  TString fitLabelTextMPF = TString::Format("Fit %s: %.4f #pm %.4f", label_MPF.c_str(), fitValue_MPF, fitError_MPF);
  fitlabel_MPF->AddText(fitLabelTextMPF);
  fitlabel_MPF->Draw("same");

  gPad->RedrawAxis();
  c3->SaveAs(path.c_str());
}