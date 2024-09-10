static void
ngx_worker_process_cycle(ngx_cycle_t *cycle, char *mevn)
{
    char        wtevn[NGX_PROCESS_SYNC_NAME];
    char        wqevn[NGX_PROCESS_SYNC_NAME];
    char        wroevn[NGX_PROCESS_SYNC_NAME];
    HANDLE      mev, events[3];
    u_long      nev, ev;
    ngx_err_t   err;
    ngx_tid_t   wtid, cmtid, cltid;
    ngx_log_t  *log;

    log = cycle->log;

    ngx_log_debug0(NGX_LOG_DEBUG_CORE, log, 0, "worker started");

    ngx_sprintf((u_char *) wtevn, "ngx_worker_term_%ul%Z", ngx_pid);
    events[0] = CreateEvent(NULL, 1, 0, wtevn);
    if (events[0] == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "CreateEvent(\"%s\") failed", wtevn);
        goto failed;
    }

    ngx_sprintf((u_char *) wqevn, "ngx_worker_quit_%ul%Z", ngx_pid);
    events[1] = CreateEvent(NULL, 1, 0, wqevn);
    if (events[1] == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "CreateEvent(\"%s\") failed", wqevn);
        goto failed;
    }

    ngx_sprintf((u_char *) wroevn, "ngx_worker_reopen_%ul%Z", ngx_pid);
    events[2] = CreateEvent(NULL, 1, 0, wroevn);
    if (events[2] == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "CreateEvent(\"%s\") failed", wroevn);
        goto failed;
    }

    mev = OpenEvent(EVENT_MODIFY_STATE, 0, mevn);
    if (mev == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "OpenEvent(\"%s\") failed", mevn);
        goto failed;
    }

    if (SetEvent(mev) == 0) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "SetEvent(\"%s\") failed", mevn);
        goto failed;
    }


    ngx_sprintf((u_char *) ngx_cache_manager_mutex_name,
                "ngx_cache_manager_mutex_%s%Z", ngx_unique);

    ngx_cache_manager_mutex = OpenMutex(SYNCHRONIZE, 0,
                                        ngx_cache_manager_mutex_name);
    if (ngx_cache_manager_mutex == NULL) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "OpenMutex(\"%s\") failed", ngx_cache_manager_mutex_name);
        goto failed;
    }

    ngx_cache_manager_event = CreateEvent(NULL, 1, 0, NULL);
    if (ngx_cache_manager_event == NULL) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "CreateEvent(\"ngx_cache_manager_event\") failed");
        goto failed;
    }


    if (ngx_create_thread(&wtid, ngx_worker_thread, NULL, log) != 0) {
        goto failed;
    }

    if (ngx_create_thread(&cmtid, ngx_cache_manager_thread, NULL, log) != 0) {
        goto failed;
    }

    if (ngx_create_thread(&cltid, ngx_cache_loader_thread, NULL, log) != 0) {
        goto failed;
    }

    for ( ;; ) {
        ev = WaitForMultipleObjects(3, events, 0, INFINITE);

        err = ngx_errno;
        ngx_time_update();

        ngx_log_debug1(NGX_LOG_DEBUG_CORE, log, 0,
                       "worker WaitForMultipleObjects: %ul", ev);

        if (ev == WAIT_OBJECT_0) {
            ngx_terminate = 1;
            ngx_log_error(NGX_LOG_NOTICE, log, 0, "exiting");

            if (ResetEvent(events[0]) == 0) {
                ngx_log_error(NGX_LOG_ALERT, log, 0,
                              "ResetEvent(\"%s\") failed", wtevn);
            }

            break;
        }

        if (ev == WAIT_OBJECT_0 + 1) {
            ngx_quit = 1;
            ngx_log_error(NGX_LOG_NOTICE, log, 0, "gracefully shutting down");
            break;
        }

        if (ev == WAIT_OBJECT_0 + 2) {
            ngx_reopen = 1;
            ngx_log_error(NGX_LOG_NOTICE, log, 0, "reopening logs");

            if (ResetEvent(events[2]) == 0) {
                ngx_log_error(NGX_LOG_ALERT, log, 0,
                              "ResetEvent(\"%s\") failed", wroevn);
            }

            continue;
        }

        if (ev == WAIT_FAILED) {
            ngx_log_error(NGX_LOG_ALERT, log, err,
                          "WaitForMultipleObjects() failed");

            goto failed;
        }
    }

    /* wait threads */

    if (SetEvent(ngx_cache_manager_event) == 0) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                      "SetEvent(\"ngx_cache_manager_event\") failed");
    }

    events[1] = wtid;
    events[2] = cmtid;

    nev = 3;

    for ( ;; ) {
        ev = WaitForMultipleObjects(nev, events, 0, INFINITE);

        err = ngx_errno;
        ngx_time_update();

        ngx_log_debug1(NGX_LOG_DEBUG_CORE, log, 0,
                       "worker exit WaitForMultipleObjects: %ul", ev);

        if (ev == WAIT_OBJECT_0) {
            break;
        }

        if (ev == WAIT_OBJECT_0 + 1) {
            if (nev == 2) {
                break;
            }

            events[1] = events[2];
            nev = 2;
            continue;
        }

        if (ev == WAIT_OBJECT_0 + 2) {
            nev = 2;
            continue;
        }

        if (ev == WAIT_FAILED) {
            ngx_log_error(NGX_LOG_ALERT, log, err,
                          "WaitForMultipleObjects() failed");
            break;
        }
    }

    ngx_close_handle(ngx_cache_manager_event);
    ngx_close_handle(events[0]);
    ngx_close_handle(events[1]);
    ngx_close_handle(events[2]);
    ngx_close_handle(mev);

    ngx_worker_process_exit(cycle);

failed:

    exit(2);
}