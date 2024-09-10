void *
writer_thread(void *args)
{
	DB *dbp;
	DB_ENV *dbenv;
	DBT key, data;
	DB_TXN *txn;

	char *key_strings[] = {"001", "002", "003", "004", "005",
	    "006", "007", "008", "009", "010"};
	int i, j, payload, ret, thread_num;
	int retry_count, max_retries = 20;

	dbp = (DB *)args;
	dbenv = dbp->dbenv;

	/* Get the thread number */
	(void)mutex_lock(&thread_num_lock);
	global_thread_num++;
	thread_num = global_thread_num;
	(void)mutex_unlock(&thread_num_lock);

	/* Initialize the random number generator */
	srand(thread_num);

	/* Write 50 times and then quit */
	for (i = 0; i < 50; i++) {
		retry_count = 0; /* Used for deadlock retries */
retry:
		ret = dbenv->txn_begin(dbenv, NULL, &txn, 0);
		if (ret != 0) {
			dbenv->err(dbenv, ret, "txn_begin failed");
			return ((void *)EXIT_FAILURE);
		}

		memset(&key, 0, sizeof(DBT));
		memset(&data, 0, sizeof(DBT));
		for (j = 0; j < 10; j++) {
			/* Set up our key and data DBTs. */
			data.data = key_strings[j];
			data.size = (u_int32_t)strlen(key_strings[j]) + 1;

			payload = rand() + i;
			key.data = &payload;
			key.size = sizeof(int);

			switch (ret = dbp->put(dbp, txn, &key, &data,
			    DB_NOOVERWRITE)) {
			case 0:
				break;
			case DB_KEYEXIST:
				break;
			case DB_LOCK_DEADLOCK:
				(void)txn->abort(txn);
				if (retry_count < max_retries) {
					retry_count++;
					goto retry;
				}
				return ((void *)EXIT_FAILURE);
			default:
				dbenv->err(dbenv, ret, "db put failed");
				ret = txn->abort(txn);

				if (ret != 0)
					dbenv->err(dbenv, ret,
					    "txn abort failed");
				return ((void *)EXIT_FAILURE);
			}
		}

		if ((ret = txn->commit(txn, 0)) != 0) {
			dbenv->err(dbenv, ret, "txn commit failed");
			return ((void *)EXIT_FAILURE);
		}
	}
	return ((void *)EXIT_SUCCESS);
}