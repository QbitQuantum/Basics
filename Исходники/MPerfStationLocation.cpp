MPerfStationLocation::MPerfStationLocation(
           MString& s,
           const MString& workitemkey
           ) :
  mWorkitemkey(workitemkey)
{
  MString emptyString;

  tableName("perfstationlocation");
  mCodeValue = s.getToken('^', 0);
  insert("codval", mCodeValue);
  if( s.tokenExists('^', 1)) mCodeSchemeDesignator = s.getToken('^',1);
  insert("codschdes", mCodeSchemeDesignator);
  if( s.tokenExists('^', 2)) mCodeMeaning = s.getToken('^',2);
  insert("codmea", mCodeMeaning);
  insert("workitemkey",mWorkitemkey);
}