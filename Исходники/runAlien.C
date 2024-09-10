//___________________________________________________________
Int_t GetYear(TString &sample){
  TString yearstring = sample(3,4); 
  Int_t year = yearstring.Atoi();
  return 2000 + year;
}