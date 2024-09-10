void startPeriodicThreadToAbortExpiredTransactions(ServiceContext* serviceContext) {
    // Enforce calling this function once, and only once.
    static bool firstCall = true;
    invariant(firstCall);
    firstCall = false;

    auto periodicRunner = serviceContext->getPeriodicRunner();
    invariant(periodicRunner);

    // We want this job period to be dynamic, to run every (transactionLifetimeLimitSeconds/2)
    // seconds, where transactionLifetimeLimitSeconds is an adjustable server parameter, or within
    // the 1 second to 1 minute range.
    //
    // PeriodicRunner does not currently support altering the period of a job. So we are giving this
    // job a 1 second period on PeriodicRunner and incrementing a static variable 'seconds' on each
    // run until we reach transactionLifetimeLimitSeconds/2, at which point we run the code and
    // reset 'seconds'. Etc.
    PeriodicRunner::PeriodicJob job("startPeriodicThreadToAbortExpiredTransactions",
                                    [](Client* client) {
                                        static int seconds = 0;
                                        int lifetime = gTransactionLifetimeLimitSeconds.load();

                                        invariant(lifetime >= 1);
                                        int period = lifetime / 2;

                                        // Ensure: 1 <= period <= 60 seconds
                                        period = (period < 1) ? 1 : period;
                                        period = (period > 60) ? 60 : period;

                                        if (++seconds <= period) {
                                            return;
                                        }

                                        seconds = 0;

                                        // The opCtx destructor handles unsetting itself from the
                                        // Client. (The PeriodicRunner's Client must be reset before
                                        // returning.)
                                        auto opCtx = client->makeOperationContext();

                                        // Set the Locker such that all lock requests' timeouts will
                                        // be overridden and set to 0. This prevents the expired
                                        // transaction aborter thread from stalling behind any
                                        // non-transaction, exclusive lock taking operation blocked
                                        // behind an active transaction's intent lock.
                                        opCtx->lockState()->setMaxLockTimeout(Milliseconds(0));

                                        killAllExpiredTransactions(opCtx.get());
                                    },
                                    Seconds(1));

    periodicRunner->scheduleJob(std::move(job));
}