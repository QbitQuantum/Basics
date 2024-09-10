bool
BackupRestore::table(const TableS & table){
  if (!m_restore_meta) 
  {
    return true;
  }
  NdbDictionary::Dictionary* dict = m_ndb->getDictionary();
  if (dict->createTable(*table.m_dictTable) == -1) 
  {
    err << "Create table " << table.getTableName() << " failed: "
	<< dict->getNdbError() << endl;
    return false;
  }
  info << "Successfully restored table " << table.getTableName()<< endl ;
  return true;
}