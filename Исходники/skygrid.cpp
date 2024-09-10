void TSkyGridBinDoc::LoadBinDocV(const TStr& InBinFNm){
  printf("Processing SkyGrid News-Binary file '%s'...\n", InBinFNm.CStr());
  TFIn SIn(InBinFNm); int Docs=0;
  while (!SIn.Eof()){
    TSkyGridBinDoc Doc(SIn);
    Docs++; printf("%d\r", Docs);
  }
  printf("\nDone.\n");
}