int ReadSolutionData(const std::string fngdxfile)
{
  int                status, VarNr, NrRecs, FDim, dim, vartype;
  std::string        msg, VarName;
  std::string        sp[GMS_MAX_INDEX_DIM];
  double             v[GMS_MAX_INDEX_DIM];

  gdx.OpenRead(fngdxfile, status);
  if (status) 
    gdxerror(status, "gdxOpenRead");

  VarName = "result";
  if (0==gdx.FindSymbol(VarName, VarNr)) {
    cout << "Could not find variable >" << VarName << "<" << endl;
    return 1;
  }

  gdx.SymbolInfo(VarNr, VarName, dim, vartype);
  if (2 != dim || GMS_DT_VAR != vartype) {
    cout << VarName << " is not a two dimensional variable" << endl;
    return 1;
  }

  if (0==gdx.DataReadStrStart(VarNr, NrRecs)) 
    gdxerror(gdx.GetLastError(), "gdxDataReadStrStart");

  while (gdx.DataReadStr(sp, v, FDim)) {
    int i;

    if (0.0==v[GMS_VAL_LEVEL]) continue; /* skip level = 0.0 is default */
    for (i=0; i<dim; i++)
      cout << sp[i] << ((i<dim-1)? ".":"");
    cout << " = " << v[GMS_VAL_LEVEL] << endl;
  }
  cout <<  "All solution values shown" << endl;

  gdx.DataReadDone();

  if ((status=gdx.GetLastError())) 
    gdxerror(status, "GDX");
    
  if (gdx.Close()) 
    gdxerror(gdx.GetLastError(), "gdxClose");
  
  return 0;
}