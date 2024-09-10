float *getwq(TH1 *h) {
  TString delim = "_";
  TString hn = h->GetName();
  TObjArray *tokens = hn.Tokenize(delim);
  TObjString *wstro = (TObjString*)tokens->At(1);
  TObjString *qstro = (TObjString*)tokens->At(2);
  TString wstr = wstro->GetString();
  TString qstr = qstro->GetString();
  double wval = wstr.Atof();
  double qval = qstr.Atof();
  float *ret = new float[2];
  ret[0] = wval;
  ret[1] = qval;
  delete tokens;
  return ret;
}