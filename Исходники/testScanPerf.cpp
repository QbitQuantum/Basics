int
create_table(){
  NdbDictionary::Dictionary* dict = g_ndb->getDictionary();
  assert(dict);
  if(g_paramters[P_CREATE].value){
    g_ndb->getDictionary()->dropTable(g_tablename);
    const NdbDictionary::Table * pTab = NDBT_Tables::getTable(g_tablename);
    assert(pTab);
    NdbDictionary::Table copy = * pTab;
    copy.setLogging(false);
    if(dict->createTable(copy) != 0){
      g_err << "Failed to create table: " << g_tablename << endl;
      return -1;
    }

    NdbDictionary::Index x(g_indexname);
    x.setTable(g_tablename);
    x.setType(NdbDictionary::Index::OrderedIndex);
    x.setLogging(false);
    for (unsigned k = 0; k < copy.getNoOfColumns(); k++){
      if(copy.getColumn(k)->getPrimaryKey()){
	x.addColumnName(copy.getColumn(k)->getName());
      }
    }

    if(dict->createIndex(x) != 0){
      g_err << "Failed to create index: " << endl;
      return -1;
    }
  }
  g_table = dict->getTable(g_tablename);
  g_index = dict->getIndex(g_indexname, g_tablename);
  assert(g_table);
  assert(g_index);

  if(g_paramters[P_CREATE].value)
  {
    int rows = g_paramters[P_ROWS].value;
    HugoTransactions hugoTrans(* g_table);
    if (hugoTrans.loadTable(g_ndb, rows)){
      g_err.println("Failed to load %s with %d rows", 
		    g_table->getName(), rows);
      return -1;
    }
  }
  
  return 0;
}