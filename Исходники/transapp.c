void
add_color(DB_ENV *dbenv, DB *dbp, char *color, int increment)
{
	DBT key, data;
	DB_TXN *tid;
	int original, ret;
	char buf[64];

	/* Initialization. */
	memset(&key, 0, sizeof(key));
	key.data = color;
	key.size = strlen(color);
	memset(&data, 0, sizeof(data));
	data.flags = DB_DBT_MALLOC;

	for (;;) {
		/* Begin the transaction. */
		if ((ret = dbenv->txn_begin(dbenv, NULL, &tid, 0)) != 0) {
			dbenv->err(dbenv, ret, "DB_ENV->txn_begin");
			exit (1);
		}

		/*
		 * Get the key.  If it exists, we increment the value.  If it
		 * doesn't exist, we create it.
		 */
		switch (ret = dbp->get(dbp, tid, &key, &data, 0)) {
		case 0:
			original = atoi(data.data);
			break;
		case DB_LOCK_DEADLOCK:
			/* Deadlock: retry the operation. */
			if ((ret = tid->abort(tid)) != 0) {
				dbenv->err(dbenv, ret, "DB_TXN->abort");
				exit (1);
			}
			continue;
		case DB_NOTFOUND:
			original = 0;
			break;
		default:
			/* Error: run recovery. */
			dbenv->err(
			    dbenv, ret, "dbc->get: %s/%d", color, increment);
			exit (1);
		}
		if (data.data != NULL)
			free(data.data);

		/* Create the new data item. */
		(void)snprintf(buf, sizeof(buf), "%d", original + increment);
		data.data = buf;
		data.size = strlen(buf) + 1;

		/* Store the new value. */
		switch (ret = dbp->put(dbp, tid, &key, &data, 0)) {
		case 0:
			/* Success: commit the change. */
			if ((ret = tid->commit(tid, 0)) != 0) {
				dbenv->err(dbenv, ret, "DB_TXN->commit");
				exit (1);
			}
			return;
		case DB_LOCK_DEADLOCK:
			/* Deadlock: retry the operation. */
			if ((ret = tid->abort(tid)) != 0) {
				dbenv->err(dbenv, ret, "DB_TXN->abort");
				exit (1);
			}
			break;
		default:
			/* Error: run recovery. */
			dbenv->err(
			    dbenv, ret, "dbc->put: %s/%d", color, increment);
			exit (1);
		}
	}
}