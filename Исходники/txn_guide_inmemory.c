/*
 * A function that performs a series of writes to a
 * Berkeley DB database. The information written
 * to the database is largely nonsensical, but the
 * mechanism of transactional commit/abort and
 * deadlock detection is illustrated here.
 */
void *
writer_thread(void *args)
{
    static char *key_strings[] = {
	"key 1", "key 2", "key 3", "key 4", "key 5",
	"key 6", "key 7", "key 8", "key 9", "key 10"
    };
    DB *dbp;
    DB_ENV *envp;
    DBT key, value;
    DB_TXN *txn;
    int i, j, payload, ret, thread_num;
    int retry_count, max_retries = 20;   /* Max retry on a deadlock */

    dbp = (DB *)args;
    envp = dbp->get_env(dbp);

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

	/*
	 * Some think it is bad form to loop with a goto statement, but
	 * we do it anyway because it is the simplest and clearest way
	 * to achieve our abort/retry operation.
	 */
retry:
	/* Begin our transaction. We group multiple writes in
	 * this thread under a single transaction so as to
	 * (1) show that you can atomically perform multiple writes
	 * at a time, and (2) to increase the chances of a
	 * deadlock occurring so that we can observe our
	 * deadlock detection at work.
	 *
	 * Normally we would want to avoid the potential for deadlocks,
	 * so for this workload the correct thing would be to perform our
	 * puts with autocommit. But that would excessively simplify our
	 * example, so we do the "wrong" thing here instead.
	 */
	ret = envp->txn_begin(envp, NULL, &txn, 0);
	if (ret != 0) {
	    envp->err(envp, ret, "txn_begin failed");
	    return ((void *)EXIT_FAILURE);
	}
	for (j = 0; j < 10; j++) {
	    /* Set up our key and values DBTs */
	    memset(&key, 0, sizeof(DBT));
	    key.data = key_strings[j];
	    key.size = (u_int32_t)strlen(key_strings[j]) + 1;

	    memset(&value, 0, sizeof(DBT));
	    payload = rand() + i;
	    value.data = &payload;
	    value.size = sizeof(int);

	    /* Perform the database put. */
	    switch (ret = dbp->put(dbp, txn, &key, &value, 0)) {
		case 0:
		    break;

		/*
		 * Here's where we perform deadlock detection. If
		 * DB_LOCK_DEADLOCK is returned by the put operation,
		 * then this thread has been chosen to break a deadlock.
		 * It must abort its operation, and optionally retry the
		 * put.
		 */
		case DB_LOCK_DEADLOCK:
		    /*
		     * First thing that we MUST do is abort the
		     * transaction.
		     */
		    (void)txn->abort(txn);
		    /*
		     * Now we decide if we want to retry the operation.
		     * If we have retried less than max_retries,
		     * increment the retry count and goto retry.
		     */
		    if (retry_count < max_retries) {
			printf("Writer %i: Got DB_LOCK_DEADLOCK.\n",
			    thread_num);
			printf("Writer %i: Retrying write operation.\n",
			    thread_num);
			retry_count++;
			goto retry;
		    }
		    /*
		     * Otherwise, just give up.
		     */
		    printf("Writer %i: ", thread_num);
		    printf("Got DB_LOCK_DEADLOCK and out of retries.\n");
		    printf("Writer %i: Giving up.\n", thread_num);
		    return ((void *)EXIT_FAILURE);
		/*
		 * If a generic error occurs, we simply abort the
		 * transaction and exit the thread completely.
		 */
		default:
		    envp->err(envp, ret, "db put failed");
		    ret = txn->abort(txn);
		    if (ret != 0)
			envp->err(envp, ret, "txn abort failed");
		    return ((void *)EXIT_FAILURE);
	     } /** End case statement **/

	}   /** End for loop **/

	/*
	 * print the number of records found in the database.
	 * See count_records() for usage information.
	 */
	printf("Thread %i. Record count: %i\n", thread_num,
	    count_records(dbp, txn));

	/*
	 * If all goes well, we can commit the transaction and
	 * exit the thread.
	 */
	ret = txn->commit(txn, 0);
	if (ret != 0) {
	    envp->err(envp, ret, "txn commit failed");
	    return ((void *)EXIT_FAILURE);
	}
    }
    return ((void *)EXIT_SUCCESS);
}