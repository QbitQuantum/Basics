FeatureFileIOPtr  FeatureFileIO::LookUpDriver (const KKStr&  _driverName)
{
  vector<FeatureFileIOPtr>*  drivers = RegisteredDrivers ();
  KKStr  driverNameLower = _driverName.ToLower ();
  vector<FeatureFileIOPtr>::const_iterator  idx;
  for  (idx = drivers->begin ();  idx != drivers->end ();  idx++)
  {
    if  ((*idx)->driverNameLower == driverNameLower)
      return  *idx;
  }
  return  NULL;
}  /* LookUpDriver */