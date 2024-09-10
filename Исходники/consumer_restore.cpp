bool
BackupRestore::table(const TableS & table){
  if (!m_restore && !m_restore_meta)
    return true;

  const char * name = table.getTableName();
  
  /**
   * Ignore blob tables
   */
  if(match_blob(name) >= 0)
    return true;
  
  const NdbTableImpl & tmptab = NdbTableImpl::getImpl(* table.m_dictTable);
  if(tmptab.m_indexType != NdbDictionary::Index::Undefined){
    m_indexes.push_back(table.m_dictTable);
    return true;
  }
  
  BaseString tmp(name);
  Vector<BaseString> split;
  if(tmp.split(split, "/") != 3){
    err << "Invalid table name format `" << name << "`" << endl;
    return false;
  }

  m_ndb->setDatabaseName(split[0].c_str());
  m_ndb->setSchemaName(split[1].c_str());
  
  NdbDictionary::Dictionary* dict = m_ndb->getDictionary();
  if(m_restore_meta){
    NdbDictionary::Table copy(*table.m_dictTable);

    copy.setName(split[2].c_str());

    /*
      update min and max rows to reflect the table, this to
      ensure that memory is allocated properly in the ndb kernel
    */
    copy.setMinRows(table.getNoOfRecords());
    if (table.getNoOfRecords() > copy.getMaxRows())
    {
      copy.setMaxRows(table.getNoOfRecords());
    }

    if (dict->createTable(copy) == -1) 
    {
      err << "Create table `" << table.getTableName() << "` failed: "
	  << dict->getNdbError() << endl;
      return false;
    }
    info << "Successfully restored table `"
         << table.getTableName() << "`" << endl;
  }  
  
  const NdbDictionary::Table* tab = dict->getTable(split[2].c_str());
  if(tab == 0){
    err << "Unable to find table: `" << split[2].c_str() << "`" << endl;
    return false;
  }
  const NdbDictionary::Table* null = 0;
  m_new_tables.fill(table.m_dictTable->getTableId(), null);
  m_new_tables[table.m_dictTable->getTableId()] = tab;
  return true;
}