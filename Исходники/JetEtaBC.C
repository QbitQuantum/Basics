void JetEtaBC(void){
    std::cout << "Hellowww!!" << std::endl;
    
    TFile *file1;
    file1 = TFile::Open("PF_second.root");
    TH1F* f1 = (TH1F*)file1->FindObjectAny("JetEtaBC");

    TFile *file2;
    file2 = TFile::Open("PAT_second.root");
    TH1F* f2 = (TH1F*)file2->FindObjectAny("JetEtaBC");

    TFile *file3;
    file3 = TFile::Open("PF_IC5_Jets_Corrected.root");
    TH1F* f3 = (TH1F*)file3->FindObjectAny("JetEtaBC");

    TFile *file4;
    file4 = TFile::Open("PF_ak5_tot.root");
    TH1F* f4 = (TH1F*)file4->FindObjectAny("JetEtaBC");

    TCanvas *c1 = new TCanvas("canvas","Plotting Canvas",150,10,990,660);
    c1->Range(-0.1486535,-622.7141,1.350808,5500.641);
    c1->SetFillColor(0);
    c1->SetBorderSize(2);
    c1->SetLogy();
    c1->SetTickx(1);
    c1->SetTicky(1);

    f1->SetStats(kFALSE);
    f4->GetXaxis()->SetTitle("#eta");
    f4->GetXaxis()->SetLabelFont(42);
    f4->GetXaxis()->SetTitleFont(42);
    f4->GetYaxis()->SetTitle("Events");
    f4->GetYaxis()->SetLabelFont(42);
    f4->GetYaxis()->SetTitleOffset(1.19);
    f4->GetYaxis()->SetTitleFont(42);
    f4->SetLineWidth(4);
    f1->SetLineColor(1);

    f2->SetStats(kFALSE);
    f2->SetLineColor(2);
    f2->SetLineWidth(3);

    f3->SetStats(kFALSE);
    f3->SetLineColor(3);
    f3->SetLineWidth(2);

    f4->SetStats(kFALSE);
    f4->SetLineColor(4);
    f1->SetLineWidth(1);
    
    int entries = f1->GetEntries();
    double mean =  f1->GetMean();
    double RMS =  f1->GetRMS();

    int entries1 = f2->GetEntries();
    double mean1 =  f2->GetMean();
    double RMS1 =  f2->GetRMS();

    int entries2 = f3->GetEntries();
    double mean2 =  f3->GetMean();
    double RMS2 =  f3->GetRMS();

    int entries3 = f4->GetEntries();
    double mean3 =  f4->GetMean();
    double RMS3 =  f4->GetRMS();

    TPaveStats *ptstats = new TPaveStats(0.8314943,0.7488136,0.9926437,0.8877119,"brNDC");
    ptstats->SetName("stats");
    ptstats->SetBorderSize(1);
    ptstats->SetFillColor(0);
    ptstats->SetTextAlign(12);
    ptstats->SetTextFont(42);
    ptstats->SetTextColor(1);

    TPaveStats *ptstats1 = new TPaveStats(0.8314943,0.5988136,0.9926437,0.7377119,"brNDC");
    ptstats1->SetName("stats");
    ptstats1->SetBorderSize(1);
    ptstats1->SetFillColor(0);
    ptstats1->SetTextAlign(12);
    ptstats1->SetTextFont(42);
    ptstats1->SetTextColor(2);

    TPaveStats *ptstats2 = new TPaveStats(0.8314943,0.4488136,0.9926437,0.5877119,"brNDC");
    ptstats2->SetName("stats");
    ptstats2->SetBorderSize(1);
    ptstats2->SetFillColor(0);
    ptstats2->SetTextAlign(12);
    ptstats2->SetTextFont(42);
    ptstats2->SetTextColor(3);

    TPaveStats *ptstats3 = new TPaveStats(0.8314943,0.2988136,0.9926437,0.4377119,"brNDC");
    ptstats3->SetName("stats");
    ptstats3->SetBorderSize(1);
    ptstats3->SetFillColor(0);
    ptstats3->SetTextAlign(12);
    ptstats3->SetTextFont(42);
    ptstats3->SetTextColor(4);

    #include <sstream>
    std::string s,s1,s2;
    std::stringstream out,out1,out2;
    out << "Entries = " << entries << " ";
    out1 << "Mean = " << mean << " ";
    out2 << "RMS = " << RMS << " ";
    s = out.str();
    s1 = out1.str();
    s2 = out2.str();

    std::string s_1,s1_1,s2_1;
    std::stringstream out_1,out1_1,out2_1;
    out_1 << "Entries = " << entries1 << " ";
    out1_1 << "Mean = " << mean1 << " ";
    out2_1 << "RMS = " << RMS1 << " ";
    s_1 = out_1.str();
    s1_1 = out1_1.str();
    s2_1 = out2_1.str();

    std::string s_2,s1_2,s2_2;
    std::stringstream out_2,out1_2,out2_2;
    out_2 << "Entries = " << entries2 << " ";
    out1_2 << "Mean = " << mean2 << " ";
    out2_2 << "RMS = " << RMS2 << " ";
    s_2 = out_2.str();
    s1_2 = out1_2.str();
    s2_2 = out2_2.str();

    std::string s_3,s1_3,s2_3;
    std::stringstream out_3,out1_3,out2_3;
    out_3 << "Entries = " << entries3 << " ";
    out1_3 << "Mean = " << mean3 << " ";
    out2_3 << "RMS = " << RMS3 << " ";
    s_3 = out_3.str();
    s1_3 = out1_3.str();
    s2_3 = out2_3.str();

    TText *text = ptstats->AddText(s.c_str());
    text = ptstats->AddText(s1.c_str());
    text = ptstats->AddText(s2.c_str());
    ptstats->SetOptStat(1110);
    ptstats->SetOptFit(0);

    TText *text1 = ptstats1->AddText(s_1.c_str());
    text1 = ptstats1->AddText(s1_1.c_str());
    text1 = ptstats1->AddText(s2_1.c_str());
    ptstats1->SetOptStat(1110);
    ptstats1->SetOptFit(0);

    TText *text2 = ptstats2->AddText(s_2.c_str());
    text2 = ptstats2->AddText(s1_2.c_str());
    text2 = ptstats2->AddText(s2_2.c_str());
    ptstats2->SetOptStat(1110);
    ptstats2->SetOptFit(0);

    TText *text3 = ptstats3->AddText(s_3.c_str());
    text3 = ptstats3->AddText(s1_3.c_str());
    text3 = ptstats3->AddText(s2_3.c_str());
    ptstats3->SetOptStat(1110);
    ptstats3->SetOptFit(0);

    TPaveText *pt = new TPaveText(0.3066092,0.8061864,0.7255747,0.87055085,"blNDC");
    pt->SetName("title");
    pt->SetBorderSize(0);
    pt->SetTextFont(42);
    pt->SetFillColor(0);
    pt->SetTextColor(1);
    text = pt->AddText("PF Number of Jets before cuts");
    text = pt->AddText("PF Jets Pt > 10 GeV  Before Cuts");
  
    TPaveText *pt1 = new TPaveText(0.3066092,0.7261864,0.7055747,0.77055085,"blNDC");
    pt1->SetName("title");
    pt1->SetBorderSize(0);
    pt1->SetTextFont(42);
    pt1->SetFillColor(0);
    pt1->SetTextColor(2);
    text1 = pt1->AddText("PAT Jets Eta Before Cuts");

    TPaveText *pt2 = new TPaveText(0.3066092,0.6561864,0.7055747,0.70055085,"blNDC");
    pt2->SetName("title");
    pt2->SetBorderSize(0);
    pt2->SetTextFont(42);
    pt2->SetFillColor(0);
    pt2->SetTextColor(3);
    text2 = pt2->AddText("PF IC5 Pt > 0 GeV Jets Eta Before Cuts");

    TPaveText *pt3 = new TPaveText(0.3266092,0.5861864,0.7055747,0.63055085,"blNDC");
    pt3->SetName("title");
    pt3->SetBorderSize(0);
    pt3->SetTextFont(42);
    pt3->SetFillColor(0);
    pt3->SetTextColor(4);
    text3 = pt3->AddText("PF ak5 Eta Before Cuts");

    c1->Modified();

    f4->Draw();
    f2->Draw("SAME");
    f3->Draw("SAME");
    f1->Draw("SAME");
    pt->Draw("SAME");
    ptstats->Draw("SAME");
    pt1->Draw("SAME");
    ptstats1->Draw("SAME");
    pt2->Draw("SAME");
    ptstats2->Draw("SAME");
    pt3->Draw("SAME");
    ptstats3->Draw("SAME");
    c1->SaveAs("JetEtaBeforeCutsComparisonAllIhaverightnow.gif");

    return 0;
};