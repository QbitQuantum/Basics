int
runDDL(NDBT_Context* ctx, NDBT_Step* step){
  Ndb* pNdb= GETNDB(step);
  NdbDictionary::Dictionary* pDict = pNdb->getDictionary();
  
  const int tables = NDBT_Tables::getNumTables();
  while(!ctx->isTestStopped())
  {
    const int tab_no = rand() % (tables);
    NdbDictionary::Table tab = *NDBT_Tables::getTable(tab_no);
    BaseString name= tab.getName();
    name.appfmt("-%d", step->getStepNo());
    tab.setName(name.c_str());
    if(pDict->createTable(tab) == 0)
    {
      HugoTransactions hugoTrans(* pDict->getTable(name.c_str()));
      if (hugoTrans.loadTable(pNdb, 10000) != 0){
	return NDBT_FAILED;
      }
      
      while(pDict->dropTable(tab.getName()) != 0 &&
	    pDict->getNdbError().code != 4009)
	g_err << pDict->getNdbError() << endl;
      
      sleep(1);

    }
  }
  return NDBT_OK;
}