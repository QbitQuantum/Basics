void RunAnalysisAJ(const TString sList="med_JetR05_SjeR01", const TString sPtHard, const TString sPath="data/dataLists/inclAJ")
{
//TChain *chain = CreateChain(Form("%s/%s.txt",sPath.Data(),sList.Data())); if (!chain) return;
//chain->Process("AnalysisTaskUserAJ.C+", Form("%s:DAJ",sList.Data()));
//=============================================================================

  TChain *chain = new TChain("nt"); chain->Add(Form("data/inclAJ/med_JetR05_SjeR01/out_%s.root",sPtHard.Data()));
  chain->Process("AnalysisTaskUserAJ.C+", Form("%s:DAJ",sList.Data()));
//=============================================================================

  return;
}