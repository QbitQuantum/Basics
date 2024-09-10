TString get_sample_name(TString name)
{
  TObjArray* arr = name.Tokenize(".");
  
  TString out = ((TObjString*)arr->At(arr->GetEntries()-2))->GetString();
  out.ReplaceAll("_JER_up", "");
  out.ReplaceAll("_JER_down", "");
  out.ReplaceAll("_JEC_up", "");
  out.ReplaceAll("_JEC_down", "");

  out.ReplaceAll("_PU_down", "");
  out.ReplaceAll("_PU_up", "");
  out.ReplaceAll("_LJets_up", "");
  out.ReplaceAll("_LJets_down", "");
  out.ReplaceAll("_BJets_up", "");
  out.ReplaceAll("_BJets_down", "");
  out.ReplaceAll("_MuonSF_down", "");
  out.ReplaceAll("_MuonSF_up", "");
  out.ReplaceAll("_BJets_down", "");
  out.ReplaceAll("_BJets_down", "");
  out.ReplaceAll("_matching_down", "");
  out.ReplaceAll("_matching_up", "");
  out.ReplaceAll("_scale_down", "");
  out.ReplaceAll("_scale_up", "");

  out.ToLower();

  out.ReplaceAll("dyjets_50toinf", "zlight");
  out.ReplaceAll("dyjets", "zlight");
  out.ReplaceAll("dy", "zlight");
  out.ReplaceAll("wjets_bflavor", "wb");
  out.ReplaceAll("wjets_cflavor", "wc");
  out.ReplaceAll("wjets_lflavor", "wlight");
  //out.ReplaceAll("tt", "ttbar");

  
  if (out.Contains("zp")){
    TString temp = out;
    temp.ReplaceAll("zp","");
    temp.ReplaceAll("p", ".");
    TObjArray* arr2 = temp.Tokenize("w");
    TString nom = ((TObjString*)arr2->At(1))->GetString();
    TString denom = ((TObjString*)arr2->At(0))->GetString();
    cout << "nom = " << nom << " denom = " << denom << endl;
    Int_t p = (100*nom.Atof())/denom.Atof();
    cout << "p = " << p << endl;
    out = TString::Format("zp %d w %d p",denom.Atoi(), p);
    out.ReplaceAll(" ", "");
  }
  
  return out;
}