NABoolean QualifiedName::isHive(const NAString &catName) 
{
  NAString hiveDefCatName = "";
  CmpCommon::getDefault(HIVE_CATALOG, hiveDefCatName, FALSE);
  hiveDefCatName.toUpper();
  
  if (CmpCommon::getDefault(MODE_SEAHIVE) == DF_ON &&
      ((NOT catName.isNull()) &&
       ((catName == HIVE_SYSTEM_CATALOG) ||
	(catName == hiveDefCatName))))
    return TRUE;

  return FALSE;
}