Double_t strangeRight(Double_t *x, Double_t *par) {
  Double_t n0=par[0];  //1.35
  Double_t m=par[1];  //(1.78-1.35)/140
  Double_t z0=par[2]; //antenna position
  Double_t x1=par[3]; // pulser position
  Double_t z1=par[4]; // pulser position
  Double_t D=x[0];
  Double_t C=getC(par,D);
  
  Double_t val=TMath::CosH(m*(x1+C)/D);
  //  std::cout << D << "\t" << C << "\t" << val <<"\n";
  return val;
}