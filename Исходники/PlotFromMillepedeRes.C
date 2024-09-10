void PlotFromMillepedeRes(TString strMillepedeRes, TString strOutdir, TString strVars, int plotType)
{
  // strPar = "u", "v", "w", "alpha", "beta", "gamma", "def1", "def2", "def3"
  TFile* f = new TFile(strOutdir+TString("fOut.root"),"recreate");
  TTree* tr = new TTree("tr","tr");
  tr->ReadFile(strMillepedeRes,strVars);

  if (plotType==PARSwithERRvsLABEL)
    PlotParValVsLabelWithErr(f, tr, strMillepedeRes, strOutdir);

  if (plotType==NHITS)
    PlotHistsNhitsPerModule(f, tr, strMillepedeRes, strOutdir);

  if (plotType==PULLS)
    PlotPullsDistr(f, tr, strMillepedeRes, strOutdir);

  if (plotType==PARS)
    PlotParsDistr(f, tr, strMillepedeRes, strOutdir);

}// end of PlotPars