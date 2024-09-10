void RecoQA(const char* inFile) {
  gROOT->LoadMacro("bfcread_hist_prefixes_add_to_ps.C");

  TString baseName = inFile;
  if (baseName.EndsWith(".daq"))
    baseName.ReplaceAll(".daq",".hist.root");
  else if (baseName.EndsWith(".event.root"))
    baseName.ReplaceAll(".event.root",".hist.root");
  else if (baseName.EndsWith(".MuDst.root"))
    baseName.ReplaceAll(".MuDst.root",".hist.root");

  TString histFile = baseName;

  baseName.Remove(0,baseName.Last('/')+1);

  TString outputName = baseName;
  outputName.ReplaceAll(".root",".CC");

  TString histList = "StRoot/St_QA_Maker/QAhlist_Reco.h";
  if (! gSystem->Which(".",histList.Data()))
    histList.Prepend(gSystem->ExpandPathName("$STAR/"));
  
  bfcread_hist_prefixes_add_to_ps(histFile.Data(),"EventQA",
    "bfcTree",outputName.Data(),baseName.Data(),histList.Data());
}