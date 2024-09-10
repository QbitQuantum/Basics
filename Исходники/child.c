void child_main(apr_pool_t *pconf)
{
    apr_status_t status;
    apr_hash_t *ht;
    ap_listen_rec *lr;
    HANDLE child_events[2];
    HANDLE *child_handles;
    int listener_started = 0;
    int threads_created = 0;
    int watch_thread;
    int time_remains;
    int cld;
    unsigned tid;
    int rv;
    int i;

    apr_pool_create(&pchild, pconf);
    apr_pool_tag(pchild, "pchild");

    ap_run_child_init(pchild, ap_server_conf);
    ht = apr_hash_make(pchild);

    /* Initialize the child_events */
    max_requests_per_child_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!max_requests_per_child_event) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Child %lu: Failed to create a max_requests event.", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    child_events[0] = exit_event;
    child_events[1] = max_requests_per_child_event;

    allowed_globals.jobsemaphore = CreateSemaphore(NULL, 0, 1000000, NULL);
    apr_thread_mutex_create(&allowed_globals.jobmutex,
                            APR_THREAD_MUTEX_DEFAULT, pchild);

    /*
     * Wait until we have permission to start accepting connections.
     * start_mutex is used to ensure that only one child ever
     * goes into the listen/accept loop at once.
     */
    status = apr_proc_mutex_lock(start_mutex);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_ERR, status, ap_server_conf,
                     "Child %lu: Failed to acquire the start_mutex. Process will exit.", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Child %lu: Acquired the start mutex.", my_pid);

    /*
     * Create the worker thread dispatch IOCompletionPort
     * on Windows NT/2000
     */
    if (use_acceptex) {
        /* Create the worker thread dispatch IOCP */
        ThreadDispatchIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
                                                    NULL,
                                                    0,
                                                    0); /* CONCURRENT ACTIVE THREADS */
        apr_thread_mutex_create(&qlock, APR_THREAD_MUTEX_DEFAULT, pchild);
        qwait_event = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!qwait_event) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Child %lu: Failed to create a qwait event.", my_pid);
            exit(APEXIT_CHILDINIT);
        }
    }

    /*
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Child %lu: Starting %d worker threads.", my_pid, ap_threads_per_child);
    child_handles = (HANDLE) apr_pcalloc(pchild, ap_threads_per_child * sizeof(HANDLE));
    apr_thread_mutex_create(&child_lock, APR_THREAD_MUTEX_DEFAULT, pchild);

    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int *score_idx;
            int status = ap_scoreboard_image->servers[0][i].status;
            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
            }
            ap_update_child_status_from_indexes(0, i, SERVER_STARTING, NULL);
            child_handles[i] = (HANDLE) _beginthreadex(NULL, (unsigned)ap_thread_stacksize,
                                                       worker_main, (void *) i, 0, &tid);
            if (child_handles[i] == 0) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                             "Child %lu: _beginthreadex failed. Unable to create all worker threads. "
                             "Created %d of the %d threads requested with the ThreadsPerChild configuration directive.",
                             my_pid, threads_created, ap_threads_per_child);
                ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
                goto shutdown;
            }
            threads_created++;
            /* Save the score board index in ht keyed to the thread handle. We need this
             * when cleaning up threads down below...
             */
            apr_thread_mutex_lock(child_lock);
            score_idx = apr_pcalloc(pchild, sizeof(int));
            *score_idx = i;
            apr_hash_set(ht, &child_handles[i], sizeof(HANDLE), score_idx);
            apr_thread_mutex_unlock(child_lock);
        }
        /* Start the listener only when workers are available */
        if (!listener_started && threads_created) {
            create_listener_thread();
            listener_started = 1;
            winnt_mpm_state = AP_MPMQ_RUNNING;
        }
        if (threads_created == ap_threads_per_child) {
            break;
        }
        /* Check to see if the child has been told to exit */
        if (WaitForSingleObject(exit_event, 0) != WAIT_TIMEOUT) {
            break;
        }
        /* wait for previous generation to clean up an entry in the scoreboard */
        apr_sleep(1 * APR_USEC_PER_SEC);
    }

    /* Wait for one of three events:
     * exit_event:
     *    The exit_event is signaled by the parent process to notify
     *    the child that it is time to exit.
     *
     * max_requests_per_child_event:
     *    This event is signaled by the worker threads to indicate that
     *    the process has handled MaxRequestsPerChild connections.
     *
     * TIMEOUT:
     *    To do periodic maintenance on the server (check for thread exits,
     *    number of completion contexts, etc.)
     *
     * XXX: thread exits *aren't* being checked.
     *
     * XXX: other_child - we need the process handles to the other children
     *      in order to map them to apr_proc_other_child_read (which is not
     *      named well, it's more like a_p_o_c_died.)
     *
     * XXX: however - if we get a_p_o_c handle inheritance working, and
     *      the parent process creates other children and passes the pipes
     *      to our worker processes, then we have no business doing such
     *      things in the child_main loop, but should happen in master_main.
     */
    while (1) {
#if !APR_HAS_OTHER_CHILD
        rv = WaitForMultipleObjects(2, (HANDLE *) child_events, FALSE, INFINITE);
        cld = rv - WAIT_OBJECT_0;
#else
        rv = WaitForMultipleObjects(2, (HANDLE *) child_events, FALSE, 1000);
        cld = rv - WAIT_OBJECT_0;
        if (rv == WAIT_TIMEOUT) {
            apr_proc_other_child_refresh_all(APR_OC_REASON_RUNNING);
        }
        else
#endif
            if (rv == WAIT_FAILED) {
            /* Something serious is wrong */
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Child %lu: WAIT_FAILED -- shutting down server", my_pid);
            break;
        }
        else if (cld == 0) {
            /* Exit event was signaled */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                         "Child %lu: Exit event signaled. Child process is ending.", my_pid);
            break;
        }
        else {
            /* MaxRequestsPerChild event set by the worker threads.
             * Signal the parent to restart
             */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                         "Child %lu: Process exiting because it reached "
                         "MaxRequestsPerChild. Signaling the parent to "
                         "restart a new child process.", my_pid);
            ap_signal_parent(SIGNAL_PARENT_RESTART);
            break;
        }
    }

    /*
     * Time to shutdown the child process
     */

 shutdown:

    winnt_mpm_state = AP_MPMQ_STOPPING;
    /* Setting is_graceful will cause threads handling keep-alive connections
     * to close the connection after handling the current request.
     */
    is_graceful = 1;

    /* Close the listening sockets. Note, we must close the listeners
     * before closing any accept sockets pending in AcceptEx to prevent
     * memory leaks in the kernel.
     */
    for (lr = ap_listeners; lr ; lr = lr->next) {
        apr_socket_close(lr->sd);
    }

    /* Shutdown listener threads and pending AcceptEx socksts
     * but allow the worker threads to continue consuming from
     * the queue of accepted connections.
     */
    shutdown_in_progress = 1;

    Sleep(1000);

    /* Tell the worker threads to exit */
    workers_may_exit = 1;

    /* Release the start_mutex to let the new process (in the restart
     * scenario) a chance to begin accepting and servicing requests
     */
    rv = apr_proc_mutex_unlock(start_mutex);
    if (rv == APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_NOTICE, rv, ap_server_conf,
                     "Child %lu: Released the start mutex", my_pid);
    }
    else {
        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                     "Child %lu: Failure releasing the start mutex", my_pid);
    }

    /* Shutdown the worker threads */
    if (!use_acceptex) {
        for (i = 0; i < threads_created; i++) {
            add_job(INVALID_SOCKET);
        }
    }
    else { /* Windows NT/2000 */
        /* Post worker threads blocked on the ThreadDispatch IOCompletion port */
        while (g_blocked_threads > 0) {
            ap_log_error(APLOG_MARK,APLOG_INFO, APR_SUCCESS, ap_server_conf,
                         "Child %lu: %d threads blocked on the completion port", my_pid, g_blocked_threads);
            for (i=g_blocked_threads; i > 0; i--) {
                PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, IOCP_SHUTDOWN, NULL);
            }
            Sleep(1000);
        }
        /* Empty the accept queue of completion contexts */
        apr_thread_mutex_lock(qlock);
        while (qhead) {
            CloseHandle(qhead->Overlapped.hEvent);
            closesocket(qhead->accept_socket);
            qhead = qhead->next;
        }
        apr_thread_mutex_unlock(qlock);
    }

    /* Give busy threads a chance to service their connections,
     * (no more than the global server timeout period which 
     * we track in msec remaining).
     */
    watch_thread = 0;
    time_remains = (int)(ap_server_conf->timeout / APR_TIME_C(1000));

    while (threads_created)
    {
        int nFailsafe = MAXIMUM_WAIT_OBJECTS;
        DWORD dwRet;

        /* Every time we roll over to wait on the first group
         * of MAXIMUM_WAIT_OBJECTS threads, take a breather,
         * and infrequently update the error log.
         */
        if (watch_thread >= threads_created) {
            if ((time_remains -= 100) < 0)
                break;

            /* Every 30 seconds give an update */
            if ((time_remains % 30000) == 0) {
                ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, 
                             ap_server_conf,
                             "Child %lu: Waiting %d more seconds "
                             "for %d worker threads to finish.", 
                             my_pid, time_remains / 1000, threads_created);
            }
            /* We'll poll from the top, 10 times per second */
            Sleep(100);
            watch_thread = 0;
        }

        /* Fairness, on each iteration we will pick up with the thread
         * after the one we just removed, even if it's a single thread.
         * We don't block here.
         */
        dwRet = WaitForMultipleObjects(min(threads_created - watch_thread,
                                           MAXIMUM_WAIT_OBJECTS),
                                       child_handles + watch_thread, 0, 0);

        if (dwRet == WAIT_FAILED) {
            break;
        }
        if (dwRet == WAIT_TIMEOUT) {
            /* none ready */
            watch_thread += MAXIMUM_WAIT_OBJECTS;
            continue;
        }
        else if (dwRet >= WAIT_ABANDONED_0) {
            /* We just got the ownership of the object, which
             * should happen at most MAXIMUM_WAIT_OBJECTS times.
             * It does NOT mean that the object is signaled.
             */
            if ((nFailsafe--) < 1)
                break;
        }
        else {
            watch_thread += (dwRet - WAIT_OBJECT_0);
            if (watch_thread >= threads_created)
                break;
            cleanup_thread(child_handles, &threads_created, watch_thread);
        }
    }
 
    /* Kill remaining threads off the hard way */
    if (threads_created) {
        ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                     "Child %lu: Terminating %d threads that failed to exit.",
                     my_pid, threads_created);
    }
    for (i = 0; i < threads_created; i++) {
        int *score_idx;
        TerminateThread(child_handles[i], 1);
        CloseHandle(child_handles[i]);
        /* Reset the scoreboard entry for the thread we just whacked */
        score_idx = apr_hash_get(ht, &child_handles[i], sizeof(HANDLE));
        if (score_idx) {
            ap_update_child_status_from_indexes(0, *score_idx,
                                                SERVER_DEAD, NULL);
        }
    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Child %lu: All worker threads have exited.", my_pid);

    CloseHandle(allowed_globals.jobsemaphore);
    apr_thread_mutex_destroy(allowed_globals.jobmutex);
    apr_thread_mutex_destroy(child_lock);

    if (use_acceptex) {
        apr_thread_mutex_destroy(qlock);
        CloseHandle(qwait_event);
    }

    apr_pool_destroy(pchild);
    CloseHandle(exit_event);
}