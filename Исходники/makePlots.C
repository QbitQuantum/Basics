void overlay_plots(const string& fFile0, const string& fFile1, const double fYmax, const string& fPlot, const string& fLegendEnt1, const string& fLegendEnt2, const string& fName) {
  
   TProfile *p[2];
 
   TFile file0(fFile0.c_str());
   TDirectoryFile *subDir = (TDirectoryFile*)file0.Get("offsetAnalysis");
   p[0] = (TProfile*)subDir->Get(fPlot.c_str());

   TFile file1(fFile1.c_str());
   subDir = (TDirectoryFile*)file1.Get("offsetAnalysis");
   p[1] = (TProfile*)subDir->Get(fPlot.c_str()); 

   p[0]->SetTitleOffset(1.5,"Y");
   p[0]->GetXaxis()->SetTitleSize(0.04);
   p[0]->GetYaxis()->SetTitleSize(0.04);
   
   double ymax = ((p[0]->GetMaximum())>(p[1]->GetMaximum())) ? p[0]->GetMaximum() : p[1]->GetMaximum();
   
   p[0]->GetYaxis()->SetRangeUser(0.,fYmax);
   
   TCanvas *c = new TCanvas("c","",800,800);
   c->cd();
  
   p[0]->SetLineWidth(3);
   p[0]->SetLineColor(kRed);
   p[0]->SetFillColor(kRed);
   p[0]->Draw("hist");
   p[1]->SetLineWidth(3);
   p[1]->SetLineColor(kBlack);
   p[1]->SetMarkerStyle(20);
   p[1]->SetMarkerColor(kBlack);
   p[1]->Draw("sames");
   
   TLegend *legend = new TLegend(.57,.77,.9,.87);
   legend->SetBorderSize(1);
   legend->SetFillColor(0);
//    legend->SetFillStyle(0);
   legend->SetMargin(0.12);
   legend->AddEntry(p[0],fLegendEnt1.c_str(),"l");
   legend->AddEntry(p[1],fLegendEnt2.c_str(),"l");
   legend->Draw();
   
   TLatex l;
   l.SetTextAlign(12);
   l.SetTextSize(0.04);
   l.SetTextFont(62);
   l.SetNDC();
   l.DrawLatex(0.15,0.85,"CMS 2009 Preliminary");
   
   string fileName = fName;
   c->SetGridy();
   c->SaveAs(fileName.c_str());
   
   delete legend;
   delete c;
}