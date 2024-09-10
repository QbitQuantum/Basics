/* Bulk delete from a database. */
void BulkExample::bulkDelete(
    int num, int dups, int *countp, int *iterp, int verbose)
{
	Dbt key;
	DbTxn *txnp;
	DbMultipleDataBuilder *ptrd;
	DbMultipleKeyDataBuilder *ptrkd;
	u_int32_t flag;
	int count, i, j, iter, ret;

	txnp = NULL;
	count = flag = iter = ret = 0;
	memset(&key, 0, sizeof(Dbt));

	j = rand() % num;

	/*
	 * The buffer must be at least as large as the page size of the
	 * underlying database and aligned for unsigned integer access.
	 * Its size must be a multiple of 1024 bytes.
	 */
	if (klen != (u_int32_t)UPDATES_PER_BULK_PUT *
	    (sizeof(u_int32_t) + DATALEN) * 1024) {
		klen = (u_int32_t)UPDATES_PER_BULK_PUT *
		    (sizeof(u_int32_t) + DATALEN) * 1024;
		kbuf = realloc(kbuf, klen);
	}
	memset(kbuf, 0, klen);
	key.set_ulen(klen);
	key.set_flags(DB_DBT_USERMEM | DB_DBT_BULK);
	key.set_data(kbuf);
	if (data_val == NULL)
		data_val = (data *)malloc(DATALEN);
	memset(data_val, 0, DATALEN);

	/*
	 * Bulk delete all records of a specific set of keys which includes all
	 * non-negative integers smaller than the random key. The random key is
	 * a random non-negative integer smaller than "num".
	 * If DB_MULTIPLE, construct the key Dbt by the DbMultipleDataBuilder
	 * with the specific set of keys. If DB_MULTIPLE_KEY, construct the key
	 * Dbt by the DbMultipleKeyDataBuilder with all key/data pairs of the
	 * specific set of keys.
	 */
	flag |= (dups) ? DB_MULTIPLE_KEY : DB_MULTIPLE;
	if (dups)
		ptrkd = new DbMultipleKeyDataBuilder(key);
	else
		ptrd = new DbMultipleDataBuilder(key);
	try {
		for (i = 0; i < j; i++) {
			if (i % UPDATES_PER_BULK_PUT == 0) {
				if (txnp != NULL) {
					ret = txnp->commit(0);
					txnp = NULL;
					if (ret != 0)
						throwException(dbenv, NULL,
						    ret, "DB_TXN->commit");
				}
				if ((ret = dbenv->txn_begin(NULL,
				    &txnp, 0)) != 0)
					throwException(dbenv, NULL,
					    ret, "DB_ENV->txn_begin");
			}

			if (dups) {
				data_val->id = 0;
				get_string(tstring, data_val->str, i);
				do {
					if(ptrkd->append(&i,sizeof(i),
					    data_val, DATALEN) == false)
						throwException(dbenv,
						    txnp, EXIT_FAILURE,
"DbMultipleKeyDataBuilder->append");
					count++;
					if (verbose)
						printf(
"Delete key: %d, \tdata: (id %d, str %s)\n",
						    i, data_val->id,
						    data_val->str);
				} while (data_val->id++ < dups);
			} else {
				if(ptrd->append(&i,sizeof(i)) == false)
					throwException(dbenv, txnp, ret,
					    "DbMultipleDataBuilder->append");
				count++;
				if (verbose)
					printf("Delete key: %d\n", i);
			}

			if ((i + 1) % UPDATES_PER_BULK_PUT == 0) {
				if ((ret = dbp->del(txnp, &key, flag)) != 0)
					throwException(dbenv,
					    txnp, ret, "Bulk DB->del");
				iter++;
				if (dups)
					ptrkd = new
					    DbMultipleKeyDataBuilder(key);
				else
					ptrd = new DbMultipleDataBuilder(key);
			}
		}
		if ((j % UPDATES_PER_BULK_PUT) != 0) {
			if ((ret = dbp->del(txnp, &key, flag)) != 0)
				throwException(dbenv,
				    txnp, ret, "Bulk DB->del");
			iter++;
		}

		ret = txnp->commit(0);
		txnp = NULL;
		if (ret != 0)
			throwException(dbenv, NULL, ret, "DB_TXN->commit");

		*countp = count;
		*iterp = iter;
	} catch (DbException &dbe) {
		cerr << "bulkDelete " << dbe.what() << endl;
		if (txnp != NULL)
			(void)txnp->abort();
		throw dbe;
	}
}