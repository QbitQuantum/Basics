INDEX GetIndexFromProfile( CTString strVarName, INDEX iDefault)
{
  CTString strDefault;
  strDefault.PrintF("%d", iDefault);
  CTString strTemp = theApp.GetProfileString( "Modeler prefs", strVarName, strDefault);
  INDEX iValue;
  sscanf( strTemp, "%d", &iValue);
  return iValue;
};