// A function that performs a series of writes to a
// Berkeley DB database. The information written
// to the database is largely nonsensical, but the
// mechanism of transactional commit/abort and
// deadlock detection is illustrated here.
void *
writerThread(void *args)
{
    int j, thread_num;
    int max_retries = 20;   // Max retry on a deadlock
    const char *key_strings[] = {"key 1", "key 2", "key 3", "key 4",
                           "key 5", "key 6", "key 7", "key 8",
                           "key 9", "key 10"};

    Db *dbp = (Db *)args;
    DbEnv *envp = dbp->get_env();

    // Get the thread number
    (void)mutex_lock(&thread_num_lock);
    global_thread_num++;
    thread_num = global_thread_num;
    (void)mutex_unlock(&thread_num_lock);

    // Initialize the random number generator
    srand(thread_num);

    // Perform 50 transactions
    for (int i=0; i<50; i++) {
        DbTxn *txn;
        bool retry = true;
        int retry_count = 0;
        // while loop is used for deadlock retries
        while (retry) {
            // try block used for deadlock detection and
            // general db exception handling
            try {

                // Begin our transaction. We group multiple writes in
                // this thread under a single transaction so as to
                // (1) show that you can atomically perform multiple
                // writes at a time, and (2) to increase the chances
                // of a deadlock occurring so that we can observe our
                // deadlock detection at work.

                // Normally we would want to avoid the potential for
                // deadlocks, so for this workload the correct thing
                // would be to perform our puts with autocommit. But
                // that would excessively simplify our example, so we
                // do the "wrong" thing here instead.
                txn = NULL;
                envp->txn_begin(NULL, &txn, 0);

                // Perform the database write for this transaction.
                for (j = 0; j < 10; j++) {
                    Dbt key, value;
                    key.set_data((void *)key_strings[j]);
                    key.set_size((u_int32_t)strlen(key_strings[j]) + 1);

                    int payload = rand() + i;
                    value.set_data(&payload);
                    value.set_size(sizeof(int));

                    // Perform the database put
                    dbp->put(txn, &key, &value, 0);
                }

                // countRecords runs a cursor over the entire database.
                // We do this to illustrate issues of deadlocking
                std::cout << thread_num <<  " : Found "
                          <<  countRecords(dbp, txn)
                          << " records in the database." << std::endl;

                std::cout << thread_num <<  " : committing txn : " << i
                          << std::endl;

                // commit
                try {
                    txn->commit(0);
                    retry = false;
                    txn = NULL;
                } catch (DbException &e) {
                    std::cout << "Error on txn commit: "
                              << e.what() << std::endl;
                }
            } catch (DbDeadlockException &) {
                // First thing that we MUST do is abort the transaction.
                if (txn != NULL)
                    (void)txn->abort();

                // Now we decide if we want to retry the operation.
                // If we have retried less than max_retries,
                // increment the retry count and goto retry.
                if (retry_count < max_retries) {
                    std::cerr << "############### Writer " << thread_num
                              << ": Got DB_LOCK_DEADLOCK.\n"
                              << "Retrying write operation." << std::endl;
                    retry_count++;
                    retry = true;
                 } else {
                    // Otherwise, just give up.
                    std::cerr << "Writer " << thread_num
                              << ": Got DeadLockException and out of "
                              << "retries. Giving up." << std::endl;
                    retry = false;
                 }
           } catch (DbException &e) {
                std::cerr << "db put failed" << std::endl;
                std::cerr << e.what() << std::endl;
                if (txn != NULL)
                    txn->abort();
                retry = false;
           } catch (std::exception &ee) {
            std::cerr << "Unknown exception: " << ee.what() << std::endl;
            return (0);
          }
        }
    }
    return (0);
}