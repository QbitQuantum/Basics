void Plots::Legend(TString histoname1,TString histoname2,TString histoname3, TString histoname4, TH1F *histo1, TH1F *histo2, TH1F *histo3, TH1F *histo4)
{

TLegend *leg = new TLegend(0.45,0.88,1.,1.0); 
leg->SetTextAlign(32);
leg->SetTextColor(1);
leg->SetTextSize(0.020);

char  label[128];
sprintf(label,"perfect alignment;      mean = %1.3f, RMS = %1.3f",convert(histo1->GetMean()),convert(histo1->GetRMS()));
leg->AddEntry(histoname1, label, "l");
sprintf(label,"SurveyLASCosmics alignment; mean = %1.3f, RMS = %1.3f",convert(histo2->GetMean()),convert(histo2->GetRMS()));
leg->AddEntry(histoname2, label, "l");
sprintf(label,"10 pb-1 alignment;  mean = %1.3f, RMS = %1.3f",convert(histo3->GetMean()),convert(histo3->GetRMS()));
leg->AddEntry(histoname3, label, "l");
sprintf(label,"100 pb-1 alignment;  mean = %1.3f, RMS = %1.3f",convert(histo4->GetMean()),convert(histo4->GetRMS()));
leg->AddEntry(histoname4, label, "l");
leg->Draw();

}