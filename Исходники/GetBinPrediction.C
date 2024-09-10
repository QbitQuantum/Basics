int GetBinPrediction()
{

    cout << "Loading Ra2bBin.C" << endl;
    gROOT->ProcessLine(".L RA2bBin.C+");
    cout << "Loading Prediction.C" << endl;
    gROOT->ProcessLine(".L Prediction.C+");
    cout << "Loading Expectation.C" << endl;
    gROOT->ProcessLine(".L Expectation.C+");

    // ------------------------------------------------------------------- //


    Expectation* expec = new Expectation();
    TChain* expectation = new TChain("PredictionTree");
    Prediction* predic = new Prediction();
    TChain* prediction = new TChain("PredictionTree");

    // ------------------------------------------------------------------- //

    ifstream myfile1 ("filelist.txt");

    string root_file;
    if (myfile1.is_open()) {
        while( myfile1.good() ) {
            getline (myfile1,root_file);
            cout << root_file << endl;
            if (root_file.length() > 0) {
                TString path = root_file;
                expectation->Add(path);
                prediction->Add(path);
            }
        }
        myfile1.close();
    }

    // ------------------------------------------------------------------- //

    expectation->Process(expec);
    prediction->Process(predic);

    // ------------------------------------------------------------------- //

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(51, 0);

    // For the canvas:
    gStyle->SetCanvasColor(0);
    gStyle->SetCanvasBorderMode(0);

    // For the Pad:
    gStyle->SetPadColor(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPadBorderSize(2);
    gStyle->SetPadBorderMode(0);

    // For the frame:
    gStyle->SetFrameBorderMode(0);

    // For the histo:
    gStyle->SetMarkerSize(0.7);
    gStyle->SetMarkerStyle(20);
    gStyle->SetMarkerColor(1);

    // For the statistics box:
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(1011);

    // Margins:
    gStyle->SetPadBottomMargin(0.25);
    gStyle->SetPadTopMargin(0.15);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadRightMargin(0.1);

    // For the Global title:
    gStyle->SetOptTitle(0);
    gStyle->SetTitleColor(1);
    gStyle->SetTitleFillColor(10);
    gStyle->SetTitleTextColor(1);
    gStyle->SetTitleFont(42);
    gStyle->SetTitleFontSize(0.05);
    gStyle->SetTitleBorderSize(0);

    // For the axis
    gStyle->SetNdivisions(510, "X");
    gStyle->SetNdivisions(510, "Y");
    gStyle->SetTickLength(0.03);

    // For the axis titles:
    gStyle->SetTitleOffset(1.4, "X");
    gStyle->SetTitleOffset(1.25, "Y");
    gStyle->SetTitleOffset(1.2, "Y");
    gStyle->SetTitleOffset(0.5, "Z");
    gStyle->SetTitleSize(0.05, "XYZ");
    gStyle->SetTitleSize(0.061, "XYZ");
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetTitleX(0.15);
    gStyle->SetTitleY(0.99);

    // For the axis labels:
    gStyle->SetLabelSize(0.04, "XYZ");
    gStyle->SetLabelOffset(0.01, "XYZ");
    gStyle->SetLabelFont(42, "XYZ");

    // For the legend
    gStyle->SetLegendBorderSize(0);

    gROOT->ForceStyle();

    enum {cqcd=kRed+3, cltau=kYellow, cllep=kRed+1, czinv=kGreen+1, cdata=kBlack, cpred=kBlue+2};

    TH1F* h_pred = predic->CalcPrediction(predic->yields_2D);
    TH1F* h_exp = expec->yields;

    int NBins = h_pred->GetNbinsX();

    h_pred->SetTitle("");
    h_exp->SetTitle("");

    h_pred->SetLineColor(cqcd );
    h_exp->SetLineColor(cdata);

    h_pred->SetFillColor(cqcd );
    h_exp->SetFillColor(cdata);

    h_pred->SetMarkerColor(cqcd );
    h_exp->SetMarkerColor(cdata);

    h_exp->SetMarkerStyle(20);
    h_exp->SetMarkerSize (1.2);
    h_exp->SetLineWidth(2);

    h_exp->GetYaxis()->SetTitleSize(0.08);
    h_exp->GetYaxis()->SetLabelSize(0.06);

    h_pred->GetYaxis()->SetTitleSize(0.08);
    h_pred->GetYaxis()->SetLabelSize(0.06);

    gStyle->SetHatchesSpacing(0.5);
    gStyle->SetHatchesLineWidth(1);

    TCanvas *c = new TCanvas("c", "c", 1200, 800);
    c->cd();
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.45, 1, 1);
    pad1->SetFillStyle(4000);
    pad1->Draw();
    pad1->SetLogy();
    pad1->SetTopMargin(0.1);
    pad1->SetBottomMargin(0);
    pad1->SetRightMargin(0.05);
    pad1->SetLeftMargin(0.15);
    pad1->cd();

    TH1F *vFrame1 = pad1->DrawFrame(0.0, 0.1, (double) NBins, 20000.0);
    vFrame1->GetYaxis()->SetTitle("Events");
    vFrame1->GetYaxis()->SetTitleOffset(-1.3);
    vFrame1->GetYaxis()->SetTitleSize(0.15);
    vFrame1->GetYaxis()->SetTitleFont(42);
    vFrame1->GetYaxis()->SetLabelOffset(-0.04);
    vFrame1->GetYaxis()->SetLabelSize(0.05);
    vFrame1->GetYaxis()->SetLabelFont(42);
    vFrame1->GetXaxis()->SetLabelOffset(1.0);
    vFrame1->GetYaxis()->SetTickLength(0.02);
    vFrame1->GetYaxis()->SetTicks("+");
    vFrame1->SetFillStyle(4000);
    h_pred->Draw("same histe");
    h_exp->Draw("same pe");

    TLatex *title = new TLatex(0., 30000, "Simulation, L = 10 fb^{ -1}, #sqrt{s} = 13 TeV");
    title->SetNDC(0);
    title->SetTextFont(42);
    title->SetTextSize(0.06);
    title->Draw("same");

    pad1->cd();
    c->cd();
    TLegend *leg1 = new TLegend(0.7,0.85,0.95,0.93,NULL,"NDC");
    leg1->SetLineColor(0);
    leg1->SetLineStyle(1);
    leg1->SetLineWidth(1);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(4000);
    leg1->SetTextSize(0.025);
    leg1->SetTextFont(42);
    leg1->AddEntry(h_exp, "MC Expectation", "lp");
    leg1->AddEntry(h_pred,  "R+S Prediction", "lf");
    leg1->Draw("same");

    double pred[NBins];
    double pred_err[NBins];
    double exp[NBins];
    double exp_err[NBins];
    double x[NBins];
    double y[NBins];
    double ey_UP[NBins];
    double ey_DN[NBins];
    double r[NBins];
    double r_e[NBins];
    double bins_e[NBins];
    for(int ii=0; ii<NBins; ii++) {
        pred[ii] = h_pred->GetBinContent(ii+1);
        pred_err[ii] = h_pred->GetBinError(ii+1);
        exp[ii] = h_exp->GetBinContent(ii+1);
        exp_err[ii] = h_exp->GetBinError(ii+1);
        bins_e[ii] = 0.5;
        x[ii] = 0.5+ii;
        y[ii] = 0.;
        ey_UP[ii] = pred_err[ii]/pred[ii];
        ey_DN[ii] = pred_err[ii]/pred[ii];
        r[ii] = (pred[ii]-exp[ii])/exp[ii];
        r_e[ii] = sqrt((pred_err[ii]/exp[ii])*(pred_err[ii]/exp[ii])+(exp_err[ii]*pred[ii]/exp[ii]/exp[ii])*(exp_err[ii]*pred[ii]/exp[ii]/exp[ii]));
    }

    TGraphAsymmErrors *ratio = new TGraphAsymmErrors(NBins, x, r, bins_e, bins_e, r_e, r_e);

    ratio->SetMarkerColor(cdata);
    ratio->SetMarkerStyle(20);
    ratio->SetMarkerSize (1.2);
    ratio->SetLineColor(cdata);
    ratio->SetLineWidth(2);

    TH1F *h_ratio = new TH1F("h_ratio_mc", "h_ratio_mc", NBins, 0, NBins);

    h_ratio->SetMarkerColor(cdata);

    h_ratio->SetMarkerStyle(20);
    h_ratio->SetMarkerSize (1.2);
    h_ratio->SetLineWidth(1);
    h_ratio->SetMinimum(-1.2);
    h_ratio->SetMaximum(2.2);

    for (int ibin=1; ibin<=h_exp->GetNbinsX(); ibin++) {
        h_ratio->SetBinContent(ibin, 0);
        h_ratio->SetBinError(ibin, 0);
        h_ratio->GetXaxis()->SetBinLabel(ibin, h_pred->GetXaxis()->GetBinLabel(ibin));
    }

    c->cd();
    TPad *pad2 = new TPad("pad2", "pad2", 0., 0., 1, 0.5);
    pad2->SetTopMargin(0.0);
    pad2->SetRightMargin(0.05);
    pad2->SetLeftMargin(0.15);
    pad2->SetBottomMargin(0.4);
    pad2->Draw("same");
    pad2->cd();

    TH1F *vFrame2 = pad2->DrawFrame(0.0, 0.45, (double) NBins, 1.5);
    vFrame2->GetYaxis()->SetTitle("(Pred.-Exp.)/Exp.");
    vFrame2->GetYaxis()->SetTitleOffset(2.6);
    vFrame2->GetYaxis()->SetTitleSize(0.08);
    vFrame2->GetYaxis()->SetTitleFont(42);
    vFrame2->GetYaxis()->SetLabelOffset(0.08);
    vFrame2->GetYaxis()->SetLabelSize(0.06);
    vFrame2->GetYaxis()->SetLabelFont(42);
    vFrame2->GetXaxis()->SetLabelOffset(1.0);
    vFrame2->GetYaxis()->SetTickLength(-0.02);
    vFrame2->GetYaxis()->SetTicks("+");


    h_ratio->SetTitle("");
    h_ratio->GetYaxis()->SetTitle("(Pred.-Exp.)/Exp.");
    h_ratio->GetYaxis()->SetTitleOffset(0.6);
    h_ratio->GetYaxis()->SetLabelOffset(0.02);
    h_ratio->GetYaxis()->SetTickLength(0.02);
    h_ratio->GetYaxis()->SetTitleSize(0.08);
    h_ratio->GetYaxis()->SetLabelSize(0.06);
    h_ratio->GetXaxis()->SetLabelOffset(0.01);
    h_ratio->Draw("e5");
    ratio->Draw("P0Z");

    c->SaveAs("BinByBinClosure_test.pdf");

    return 1;

}