static int
evthread_win32_cond_wait(void *_cond, void *_lock, const struct timeval *tv)
{
    struct evthread_win32_cond *cond = _cond;
    CRITICAL_SECTION *lock = _lock;
    int generation_at_start;
    int waiting = 1;
    int result = -1;
    DWORD ms = INFINITE, ms_orig = INFINITE, startTime, endTime;
    if (tv)
        ms_orig = ms = evutil_tv_to_msec(tv);

    EnterCriticalSection(&cond->lock);
    ++cond->n_waiting;
    generation_at_start = cond->generation;
    LeaveCriticalSection(&cond->lock);

    LeaveCriticalSection(lock);

    startTime = GetTickCount();
    do {
        DWORD res;
        res = WaitForSingleObject(cond->event, ms);
        EnterCriticalSection(&cond->lock);
        if (cond->n_to_wake &&
            cond->generation != generation_at_start) {
            --cond->n_to_wake;
            --cond->n_waiting;
            result = 0;
            waiting = 0;
            goto out;
        } else if (res != WAIT_OBJECT_0) {
            result = (res==WAIT_TIMEOUT) ? 1 : -1;
            --cond->n_waiting;
            waiting = 0;
            goto out;
        } else if (ms != INFINITE) {
            endTime = GetTickCount();
            if (startTime + ms_orig <= endTime) {
                result = 1; /* Timeout */
                --cond->n_waiting;
                waiting = 0;
                goto out;
            } else {
                ms = startTime + ms_orig - endTime;
            }
        }
        /* If we make it here, we are still waiting. */
        if (cond->n_to_wake == 0) {
            /* There is nobody else who should wake up; reset
             * the event. */
            ResetEvent(cond->event);
        }
    out:
        LeaveCriticalSection(&cond->lock);
    } while (waiting);

    EnterCriticalSection(lock);

    EnterCriticalSection(&cond->lock);
    if (!cond->n_waiting)
        ResetEvent(cond->event);
    LeaveCriticalSection(&cond->lock);

    return result;
}