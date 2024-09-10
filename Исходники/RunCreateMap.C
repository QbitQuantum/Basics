void RunCreateMap() {

  cout << "RunCreateMap" << endl; 

  TString DataRangeString = gSystem->Getenv("DATARANGE");
  int DataRange = DataRangeString.Atoi() - 1; 

  CreateMap(false, DataRange);

}