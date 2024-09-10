void
run_xact(DB_ENV *dbenv, DB *db, int offset, int count)
{
  //	va_list ap;
	DBC *dbc;
	DBT key, data;
	DB_TXN *tid;
	int ret;
	char *s;

	/* Initialization. */
	memset(&key, 0, sizeof(key));
	memset(&data, 0, sizeof(data));
	int keyPtr;
	int valPtr;
	key.data = &keyPtr;
	key.size = sizeof(int);/*strlen(name);*/
	data.data = &valPtr;
	data.size = sizeof(int);

retry:	/* Begin the transaction. */
	if ((ret = dbenv->txn_begin(dbenv, NULL, &tid, 0)) != 0) {
		dbenv->err(dbenv, ret, "DB_ENV->txn_begin");
		exit (1);
	}

	/* Delete any previously existing item. */
	/*	switch (ret = db->del(db, tid, &key, 0)) {
	case 0:
	case DB_NOTFOUND:
	  break;
	case DB_LOCK_DEADLOCK:
	  abort();
	  / * Deadlock: retry the operation. * /
			  if ((ret = tid->abort(tid)) != 0) {
			    dbenv->err(dbenv, ret, "DB_TXN->abort");
			    exit (1);
			  }
			  goto retry;
	default:
	  //	  dbenv->err(dbenv, ret, "db->del: %s", name);
	  abort();
	  exit (1);
	} */
 

	/* Create a cursor. */
	/*	if ((ret = db->cursor(db, tid, &dbc, 0)) != 0) {
		dbenv->err(dbenv, ret, "db->cursor");
		exit (1);
		} */

	int q;
	/* Count is one for this test */
	//	assert(count == 1);

	for(q = offset; q < offset + count; q++) {
	  keyPtr = q+1;
	  valPtr = q;
	  /*	  switch (ret = db->del(db, tid, &key, 0)) {
	  case 0:
	  case DB_NOTFOUND:
	    break;
	  case DB_LOCK_DEADLOCK:
	    abort();
	    // Deadlock: retry the operation. 
	    if ((ret = tid->abort(tid)) != 0) {
	      dbenv->err(dbenv, ret, "DB_TXN->abort");
	      exit (1);
	    }
	    goto retry;
	  default:
	    //	  dbenv->err(dbenv, ret, "db->del: %s", name);
	    abort();
	    exit (1);
	    } */
	  		
	  //	  pthread_mutex_lock(&hack);
	  switch (ret = db->put(db, tid, &key, &data, 0)) {
	  case 0:
	    break;
	  case DB_LOCK_DEADLOCK:
	    //		  va_end(ap);
	    abort();  // Locking should be disabled!
	    /* Deadlock: retry the operation. */
	    if ((ret = dbc->c_close(dbc)) != 0) {
	      dbenv->err(
			 dbenv, ret, "dbc->c_close");
	      exit (1);
	    }
	    if ((ret = tid->abort(tid)) != 0) {
	      dbenv->err(dbenv, ret, "DB_TXN->abort");
	      exit (1);
		  }
	    goto retry;
	  default:
	    /* Error: run recovery. */
	    dbenv->err(dbenv, ret, "dbc->put: %d/%d", q, q);
	    abort();  // Error invalidates benchmark!
	    exit (1);
	  }
	  //	  pthread_mutex_unlock(&hack);
	  putCount++;
	}
	

	if ((ret = tid->commit(tid, 0)) != 0) {
		dbenv->err(dbenv, ret, "DB_TXN->commit");
		exit (1);
	}
	commitCount++;
#ifdef DEBUG_BDB
	printf("Called commit\n");
#endif
}