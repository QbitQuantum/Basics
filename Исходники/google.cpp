void TGgSchRSet::LoadRSetsBin(const TStr& FNm, TGgSchRSetV& RSetV){
  TFIn SIn(FNm); RSetV.Clr(); int RSets=0;
  while (!SIn.Eof()){
    RSets++; if (RSets%100==0){printf("%d\r", RSets);}
    PGgSchRSet RSet(SIn);
    RSetV.Add(RSet);
  }
}