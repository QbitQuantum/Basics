void drawOneComparison(vector<TH1F*> histos, vector<TString> descr, TString xaxislabel, const char *filename, TPaveText *t=0) {
  
  if(histos.size()!=descr.size()) {
    cout << "description not complete!" << endl;
    return;
  }

  vector<int> colors;
  colors.push_back(kRed+1);
  colors.push_back(kAzure-6);
  colors.push_back(kTeal+3);
  colors.push_back(kBlue+3);

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
  c1->SetGridx();
  c1->SetGridy();  
  TLegend* legend = new TLegend(0.20, 0.20, 0.43, 0.36);
  legend->SetBorderSize(   0);
  legend->SetFillColor (   0);
  legend->SetTextAlign (  12);
  legend->SetTextFont  (  42);
  legend->SetTextSize  (0.05);

  for(int i=0;i<(int)histos.size();++i) {
    
    histos[i]->SetMinimum(0.5);
    histos[i]->SetMaximum(1.1);
    histos[i]->SetMarkerSize(2);
    histos[i]->SetMarkerStyle(20);
    histos[i]->SetMarkerColor(colors[i]);
    histos[i]->SetLineColor(colors[i]);
    histos[i]->SetTitle("");
    if(TString(histos[i]->GetName()).Contains("PU")) {
      histos[i]->SetMaximum(1.1);
      histos[i]->Fit("pol1","","same",1,35);
      histos[i]->GetFunction("pol1")->SetLineColor(colors[i]);
    }
    histos[i]->GetXaxis()->SetTitle(xaxislabel);
    histos[i]->GetYaxis()->SetTitle("efficiency");
    histos[i]->GetYaxis()->SetTitleOffset(1.5);

    legend->AddEntry(histos[i],descr[i]);

    if(i==0) { 
      histos[i]->Draw("pe1");
      for(int bin=1;bin<=histos[i]->GetNbinsX();bin++) {
	//cout << "bin i = " << bin << ": " <<  histos[i]->GetBinContent(bin) << " +/- " << histos[i]->GetBinError(bin) << endl;
	//	cout << "m35_fakeRate[" << bin << "] = " << histos[i]->GetBinContent(bin) << ";" << endl;
      }
      for(int bin=1;bin<=histos[i]->GetNbinsX();bin++) {
	//	cout << "m35_fakeRate_err[" << bin << "] = " << histos[i]->GetBinError(bin) << ";" << endl;
      }
    }
    else histos[i]->Draw("same pe1");
  }
  legend->Draw();
  if(t) t->Draw();

  TString basename(filename);
  c1->SaveAs(basename+TString(".png"));
  c1->SaveAs(basename+TString(".pdf"));

}