void EMCDistribution_PeakSample_Fast(bool full_gain = false)
{
  const TString gain = "RAW";

  TString hname = "EMCDistribution_" + gain + TString(full_gain ? "_FullGain" : "") + cuts;

  TH2 *h2 = NULL;
  {
    if (full_gain)
    {
      h2 = new TH2F(hname,
                    Form(";Calibrated Tower Energy Sum (ADC);Count / bin"), 100,
                    .05 * 100, 25 * 100, 64, -.5, 63.5);
      QAHistManagerDef::useLogBins(h2->GetXaxis());
    }
    else
    {
      h2 = new TH2F(hname,
                    Form(";Calibrated Tower Energy Sum (ADC);Count / bin"), 260,
                    -.2 * 100, 5 * 100, 64, -.5, 63.5);
    }
    T->Draw(
        "TOWER_" + gain + "_CEMC[].get_bineta() + 8* TOWER_" + gain + "_CEMC[].get_binphi():(TOWER_RAW_CEMC[].signal_samples[10] - TOWER_RAW_CEMC[].signal_samples[0])*(-1)>>" + hname, "", "goff");
  }

  TText *t;
  TCanvas *c1 = new TCanvas(
      "EMCDistribution_PeakSample_Fast_" + TString(full_gain ? "_FullGain" : "") + cuts,
      "EMCDistribution_PeakSample_Fast_" + TString(full_gain ? "_FullGain" : "") + cuts, 1800, 950);
  c1->Divide(8, 8, 0., 0.01);
  int idx = 1;
  TPad *p;

  for (int iphi = 8 - 1; iphi >= 0; iphi--)
  {
    for (int ieta = 0; ieta < 8; ieta++)
    {
      p = (TPad *) c1->cd(idx++);
      c1->Update();

      p->SetLogy();
      if (full_gain)
      {
        p->SetLogx();
      }
      p->SetGridx(0);
      p->SetGridy(0);

      TString hname = Form("hEnergy_ieta%d_iphi%d", ieta, iphi) + TString(full_gain ? "_FullGain" : "");

      TH1 *h = h2->ProjectionX(hname, ieta + 8 * iphi + 1,
                               ieta + 8 * iphi + 1);  // axis bin number is encoded as ieta+8*iphi+1

      h->SetLineWidth(0);
      h->SetLineColor(kBlue + 3);
      h->SetFillColor(kBlue + 3);

      h->GetXaxis()->SetTitleSize(.09);
      h->GetXaxis()->SetLabelSize(.08);
      h->GetYaxis()->SetLabelSize(.08);

      h->Draw();

      if (full_gain)
        h->Fit("x*gaus", "M");
      else
        h->Fit("landau", "M");

      double peak = -1;

      TF1 *fit = ((TF1 *) (h->GetListOfFunctions()->At(0)));
      if (fit)
      {
        fit->SetLineColor(kRed);
        peak = fit->GetParameter(1);
      }

      cout << Form("Finished <Col%d Row%d> = %.1f", ieta, iphi, peak)
           << endl;

      TText *t = new TText(.9, .9,
                           Form("<Col%d Row%d> = %.1f", ieta, iphi, peak));
      t->SetTextAlign(33);
      t->SetTextSize(.15);
      t->SetNDC();
      t->Draw();
    }
  }

  SaveCanvas(c1,
             TString(_file0->GetName()) + TString("_DrawPrototype3EMCalTower_") + TString(c1->GetName()), false);
}