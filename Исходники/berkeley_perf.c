int initRadacct_db(int *num_current)
{

	int i, ret;
	pthread_t tid;
	DB *dbp;
	DB_QUEUE_STAT *stat;

	if((ret = db_init_env(&radacct_dbenv,"database")) == 0)
	{
		if((ret = db_init(radacct_dbenv, &radacct_dbp)) != 0)
		{
			return -1;
		}

		dbp = radacct_dbp;

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

	return 0;
}