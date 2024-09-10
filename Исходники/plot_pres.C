TF1* fit_xy_res(double &x, double &xe, double &max, bool do_fit, int idel, int ipad, TCanvas *tc,
		TH1F* h, const char *meth, const char *var_tag, const char *det_tag, const char *var, const char *det_desc) {

  tc->cd(1+ipad);

  //cout << "var_tag = " << var_tag << endl;
  TLatex *tt = new TLatex();
  tt->SetTextSize(0.08);
  tt->SetTextColor(4);
  tt->SetNDC(true);

  double fmx = 2.2;
  double fit_min= h->GetMean()-fmx*h->GetRMS();
  double fit_max= h->GetMean()+fmx*h->GetRMS();
  TF1* f = new TF1(Form("fxres_%s_%d_%s",det_tag,idel,meth), "gaus",fit_min,fit_max);

  if (do_fit) {

    h->Fit(f,"R+Q");
    x = f->GetParameter(2);
    xe = f->GetParError(2);

    if (f->GetParameter(1) < f->GetParError(1))
      cout << "   OK: ";
    else
      cout << " OOPS: ";
    cout << var_tag << " " << meth << " " << det_tag << idel;
    cout << " mean= " << f->GetParameter(1) << " pm " << f->GetParError(1);
    cout << " sigma= " << f->GetParameter(2) << " pm " << f->GetParError(2) << endl;

  } else {

    max = TMath::Max(max, x);
    h->Draw();
    //tt->DrawLatex(0.12,0.15, h->GetTitle());
  }

  tt->DrawLatex(0.65,0.8, meth);
  tt->DrawLatex(0.65,0.7, var);
  tt->DrawLatex(0.65,0.6, det_desc);
  tt->DrawLatex(0.65,0.5, Form("#delta = %d%%",idel-5 ));

  max = TMath::Max(max, x);
  gPad->SetGridx();
  return f;
}