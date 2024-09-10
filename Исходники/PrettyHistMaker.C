void makeScaleFactorHist(TCanvas* canvas, const std::string& name, const std::string& tag)
{
  TMultiGraph* multigraph = NULL;
  std::stringstream graphName;
  graphName << name << "ScaleFactorMultigraph";
  multigraph = (TMultiGraph*)canvas->GetPrimitive(graphName.str().c_str());
  if (multigraph == NULL) {
    std::cerr << "Error: no object of TCanvas " << canvas->GetName() << " with name ";
    std::cerr << graphName.str() << std::endl;
    return;
  }
  multigraph->GetYaxis()->SetRangeUser(0.3, 1.7);
  multigraph->GetYaxis()->SetLabelSize(0.03);
  canvas->Draw();
  canvas->SetCanvasSize(600,600);
  canvas->SetWindowSize(610,630);
  TPaveText* label = new TPaveText(0.25, 0.8, 0.55, 0.9, "NDC");
  label->SetTextFont(62);
  label->SetTextSize(0.03);
  label->SetBorderSize(0);
  label->SetFillColor(0);
  label->AddText("CMS 2011");
  label->AddText("");
  label->AddText("#int L dt = 204 pb^{-1}");
  label->SetTextAlign(11);
  label->Draw();
  std::stringstream file;
  file << "/data2/yohay/scaleFactor_" << tag << "_" << name << ".pdf";
  canvas->SaveAs(file.str().c_str());
}