int initRadacct_db(int *num_current, int *num_backlog)
{

	int i, ret;
	pthread_t tid;
	DB *dbp;
	DB_QUEUE_STAT *stat;

	/* Initialize the current database environment. */
	if((ret = db_init_env(&radacct_dbenv[CURRENT], "RADACCT/current")) == 0)
	{
		if((ret = db_init(radacct_dbenv[CURRENT], &radacct_dbp[CURRENT])) != 0)
		{
			return -1;
		}

		dbp = radacct_dbp[CURRENT];

		if((ret = dbp->stat(dbp, &stat, 0)) == 0)
		{
			*num_current = stat->qs_ndata;

			free(stat);
		}
	}
	else
	{
		return -1;
	}

	/* Initialize the backlog database environment. */
	if((ret = db_init_env(&radacct_dbenv[BACKLOG], "RADACCT/backlog")) == 0)
	{
		if((ret = db_init(radacct_dbenv[BACKLOG], &radacct_dbp[BACKLOG])) != 0)
		{
			return -1;
		}

		dbp = radacct_dbp[BACKLOG];

		if((ret = dbp->stat(dbp, &stat, 0)) == 0)
		{
			*num_backlog = stat->qs_ndata;

			free(stat);
		}
	}
	else
	{
		return -1;
	}

	#if USE_TXN
	for(i = 0; i < NUM_DB; ++i)
	{
		if((ret = pthread_create(&tid, NULL, db_maint, radacct_dbenv[i])) != 0)
		{
			NETERROR(MRADC, ("failed to create db_maint [%d] thread: %s\n", i, strerror(ret)));
			return -1;
		}
	}
	#endif

	return 0;
}