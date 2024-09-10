int
main(int argc, char** argv)
{
  NDB_INIT(argv[0]);
  const char *load_default_groups[]= { "mysql_cluster",0 };
  load_defaults("my",load_default_groups,&argc,&argv);

  int ho_error;
#ifndef DBUG_OFF
  opt_debug= "d:t:F:L";
#endif
  if ((ho_error=handle_options(&argc, &argv, my_long_options, 
			       ndb_std_get_one_option)))
    return NDBT_ProgramExit(NDBT_WRONGARGS);

  DBUG_ENTER("main");
  Ndb_cluster_connection con(opt_connect_str);
  if(con.connect(12, 5, 1))
  {
    DBUG_RETURN(NDBT_ProgramExit(NDBT_FAILED));
  }
  

  Ndb ndb(&con,_dbname);
  ndb.init();
  while (ndb.waitUntilReady() != 0);

  NdbDictionary::Dictionary * dict = ndb.getDictionary();
  int no_error= 1;
  int i;

  // create all tables
  Vector<const NdbDictionary::Table*> pTabs;
  if (argc == 0)
  {
    NDBT_Tables::dropAllTables(&ndb);
    NDBT_Tables::createAllTables(&ndb);
    for (i= 0; no_error && i < NDBT_Tables::getNumTables(); i++)
    {
      const NdbDictionary::Table *pTab= dict->getTable(NDBT_Tables::getTable(i)->getName());
      if (pTab == 0)
      {
	ndbout << "Failed to create table" << endl;
	ndbout << dict->getNdbError() << endl;
	no_error= 0;
	break;
      }
      pTabs.push_back(pTab);
    }
  }
  else
  {
    for (i= 0; no_error && argc; argc--, i++)
    {
      dict->dropTable(argv[i]);
      NDBT_Tables::createTable(&ndb, argv[i]);
      const NdbDictionary::Table *pTab= dict->getTable(argv[i]);
      if (pTab == 0)
      {
	ndbout << "Failed to create table" << endl;
	ndbout << dict->getNdbError() << endl;
	no_error= 0;
	break;
      }
      pTabs.push_back(pTab);
    }
  }
  pTabs.push_back(NULL);

  // create an event for each table
  for (i= 0; no_error && pTabs[i]; i++)
  {
    HugoTransactions ht(*pTabs[i]);
    if (ht.createEvent(&ndb)){
      no_error= 0;
      break;
    }
  }

  // create an event operation for each event
  Vector<NdbEventOperation *> pOps;
  for (i= 0; no_error && pTabs[i]; i++)
  {
    char buf[1024];
    sprintf(buf, "%s_EVENT", pTabs[i]->getName());
    NdbEventOperation *pOp= ndb.createEventOperation(buf, 1000);
    if ( pOp == NULL )
    {
      no_error= 0;
      break;
    }
    pOps.push_back(pOp);
  }

  // get storage for each event operation
  for (i= 0; no_error && pTabs[i]; i++)
  {
    int n_columns= pTabs[i]->getNoOfColumns();
    for (int j = 0; j < n_columns; j++) {
      pOps[i]->getValue(pTabs[i]->getColumn(j)->getName());
      pOps[i]->getPreValue(pTabs[i]->getColumn(j)->getName());
    }
  }

  // start receiving events
  for (i= 0; no_error && pTabs[i]; i++)
  {
    if ( pOps[i]->execute() )
    {
      no_error= 0;
      break;
    }
  }

  // create a "shadow" table for each table
  Vector<const NdbDictionary::Table*> pShadowTabs;
  for (i= 0; no_error && pTabs[i]; i++)
  {
    char buf[1024];
    sprintf(buf, "%s_SHADOW", pTabs[i]->getName());

    dict->dropTable(buf);
    if (dict->getTable(buf))
    {
      no_error= 0;
      break;
    }

    NdbDictionary::Table table_shadow(*pTabs[i]);
    table_shadow.setName(buf);
    dict->createTable(table_shadow);
    pShadowTabs.push_back(dict->getTable(buf));
    if (!pShadowTabs[i])
    {
      no_error= 0;
      break;
    }
  }

  // create a hugo operation per table
  Vector<HugoOperations *> hugo_ops;
  for (i= 0; no_error && pTabs[i]; i++)
  {
    hugo_ops.push_back(new HugoOperations(*pTabs[i]));
  }

  int n_records= 3;
  // insert n_records records per table
  do {
    if (start_transaction(&ndb, hugo_ops))
    {
      no_error= 0;
      break;
    }
    for (i= 0; no_error && pTabs[i]; i++)
    {
      hugo_ops[i]->pkInsertRecord(&ndb, 0, n_records);
    }
    if (execute_commit(&ndb, hugo_ops))
    {
      no_error= 0;
      break;
    }
    if(close_transaction(&ndb, hugo_ops))
    {
      no_error= 0;
      break;
    }
  } while(0);

  // copy events and verify
  do {
    if (copy_events(&ndb) < 0)
    {
      no_error= 0;
      break;
    }
    if (verify_copy(&ndb, pTabs, pShadowTabs))
    {
      no_error= 0;
      break;
    }
  } while (0);

  // update n_records-1 records in first table
  do {
    if (start_transaction(&ndb, hugo_ops))
    {
      no_error= 0;
      break;
    }

    hugo_ops[0]->pkUpdateRecord(&ndb, n_records-1);

    if (execute_commit(&ndb, hugo_ops))
    {
      no_error= 0;
      break;
    }
    if(close_transaction(&ndb, hugo_ops))
    {
      no_error= 0;
      break;
    }
  } while(0);

  // copy events and verify
  do {
    if (copy_events(&ndb) < 0)
    {
      no_error= 0;
      break;
    }
    if (verify_copy(&ndb, pTabs, pShadowTabs))
    {
      no_error= 0;
      break;
    }
  } while (0);


  {
    NdbRestarts restarts;
    for (int j= 0; j < 10; j++)
    {
      // restart a node
      if (no_error)
      {
	int timeout = 240;
	if (restarts.executeRestart("RestartRandomNodeAbort", timeout))
	{
	  no_error= 0;
	  break;
	}
      }

      // update all n_records records on all tables
      if (start_transaction(&ndb, hugo_ops))
      {
	no_error= 0;
	break;
      }

      for (int r= 0; r < n_records; r++)
      {
	for (i= 0; pTabs[i]; i++)
	{
	  hugo_ops[i]->pkUpdateRecord(&ndb, r);
	}
      }
      if (execute_commit(&ndb, hugo_ops))
      {
	no_error= 0;
	break;
      }
      if(close_transaction(&ndb, hugo_ops))
      {
	no_error= 0;
	break;
      }

      // copy events and verify
      if (copy_events(&ndb) < 0)
      {
	no_error= 0;
	break;
      }
      if (verify_copy(&ndb, pTabs, pShadowTabs))
      {
	no_error= 0;
	break;
      }
    }
  }

  // drop the event operations
  for (i= 0; i < (int)pOps.size(); i++)
  {
    if (ndb.dropEventOperation(pOps[i]))
    {
      no_error= 0;
    }
  }

  if (no_error)
    DBUG_RETURN(NDBT_ProgramExit(NDBT_OK));
  DBUG_RETURN(NDBT_ProgramExit(NDBT_FAILED));
}