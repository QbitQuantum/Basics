int
main()
{
    int round;
    int b, t;
    int res;

    INIT();

#ifdef USE_DYNAMO
    dynamorio_app_init();
    dynamorio_app_start();
#endif


    /* this doesn't do much in fact */
    res = SetProcessWorkingSetSize(GetCurrentProcess(),
                                   MINSIZE_KB*1024,
                                   MAXSIZE_KB*1024);
    // on Win2003 there is a SetProcessWorkingSetSizeEx that sets QUOTA_LIMITS_HARDWS_ENABLE


    if (res == 0)
        print("SetProcessWorkingSetSize failed GLE: %d\n", GetLastError());

    for (round = 0; round < ROUNDS; round++) {
#ifdef VERBOSE
        print("round %d\n", round);
#endif
        global_started = 0;
        global_finished = 0;

        /* do in a batch */
        for (b = 0; b < TOTAL_THREADS / BATCH_SIZE; b++) {
            for (t = 0; t < BATCH_SIZE; t++) {
                thread[t] = create_thread(executor);
                if (thread[t] == NULL)
                    print("GLE: %d\n", GetLastError());
                assert(thread[t] != NULL);
            }
            /* now synchronize with all of them - or maybe some? */

#ifdef VERBOSE
            print("started %d threads\n", TOTAL_THREADS);
#else
#ifndef SILENT
            print("started some threads\n");
#endif
#endif
            for (t = 0; t < BATCH_SIZE; t++) {
                assert(thread[t] != NULL);
                join_thread(thread[t]);
                CloseHandle((HANDLE)thread[t]);
                thread[t] = NULL; /* in case want to synch with some in a batch, but with all at the end */

                if (SWAP_OUT_AFTER_THREAD) {
                    res = SetProcessWorkingSetSize(GetCurrentProcess(),
                                                   -1, -1);
                }
            }
#ifdef VERBOSE
            print("some %d work, done %d\n", global_started, global_finished);
#endif
            if (SWAP_OUT_AFTER_BATCH) {
                res = SetProcessWorkingSetSize(GetCurrentProcess(),
                                               -1, -1);
            }
        }
    }

#ifdef USE_DYNAMO
    dynamorio_app_stop();
    dynamorio_app_exit();
#endif

    print("done\n");
    return 0;
}