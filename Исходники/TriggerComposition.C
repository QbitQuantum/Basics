void Setoutputfileprefix( TString const& filename ){
  outputfileprefix = filename;
  Int_t pos(0);
  for(Int_t i(0);i<outputfileprefix.Sizeof();i++){
    if(outputfileprefix[i] == '/')
      pos = i;
  }
  outputfileprefix.Remove(0,pos+1);
  outputfileprefix.ReplaceAll(".root","");
}