int api_loop_run_internal(api_loop_t* loop)
{
    BOOL status;
    DWORD transfered;
    ULONG_PTR key;
    OVERLAPPED* overlapped;
    DWORD error;
    BOOL failed;
    os_win_t* win;

    api_scheduler_init(&loop->base.scheduler);
    loop->base.scheduler.pool = &loop->base.pool;
	
    loop->base.now = api_time_current();
    loop->base.last_activity = loop->base.now;

    api_loop_ref(loop);

    do
    {
        if (0 < api_timer_process(&loop->base.sleeps, TIMER_Sleep, loop->base.now))
        {
            loop->base.now = api_time_current();
            loop->base.last_activity = loop->base.now;
        }

        failed = 0;
        error = 0;
        status = GetQueuedCompletionStatus(loop->iocp, &transfered, &key,
            &overlapped, (DWORD)api_loop_calculate_wait_timeout(&loop->base));

        loop->base.now = api_time_current();

        if (status == FALSE)
        {
            failed = 1;
            error = GetLastError();

            if (overlapped == NULL)
            {
                /*
                 * Completion port closed, propably by api_loop_stop
                 */
                if (error == ERROR_ABANDONED_WAIT_0)
                {
                    loop->iocp = NULL;
                    failed = 1;
                    break;
                }

                if (error == WAIT_TIMEOUT)
                {
                    failed = 0;
                    key = 0;

                    if (0 < api_timer_process(&loop->base.idles, TIMER_Idle,
                                        loop->base.now - loop->base.last_activity))
                    {
                        loop->base.now = api_time_current();
                        loop->base.last_activity = loop->base.now;
                    }
                }
            }

            if (overlapped != NULL)
            {
                /*
                 * Eof or Connection was closed
                 */
                if (transfered == 0)
                {
                    failed = 0;
                }
            }
        }

        if (!failed && key != 0)
        {
            win = (os_win_t*)key;
            win->processor(win, transfered, overlapped, loop, error);
            loop->base.now = api_time_current();
            loop->base.last_activity = loop->base.now;
        }

        api_timer_process(&loop->base.timeouts, TIMER_Timeout,
                loop->base.now - loop->base.last_activity);

        loop->base.now = api_time_current();
    }
    while (!failed);

    if (API__OK != api_loop_cleanup(loop))
    {
        /* handle error */
    }

    if (loop->iocp != NULL)
    {
        if (!CloseHandle(loop->iocp))
        {
            /* handle error when eopll not closed already */
        }
    }

    return API__OK;
}