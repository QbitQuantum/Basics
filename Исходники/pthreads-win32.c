int pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex) {
    DWORD res = 0;
    int last_waiter = 0;
    PThreadCond * p = (PThreadCond *)*cond;

    EnterCriticalSection(&p->waiters_count_lock);
    p->waiters_count++;
    LeaveCriticalSection(&p->waiters_count_lock);

    /* This call atomically releases the mutex and waits on the */
    /* semaphore until <pthread_cond_signal> or <pthread_cond_broadcast> */
    /* are called by another thread. */
    res = SignalObjectAndWait(*mutex, p->sema, INFINITE, FALSE);
    if (res == WAIT_FAILED) return set_win32_errno(GetLastError());

    /* Re-acquire lock to avoid race conditions. */
    EnterCriticalSection(&p->waiters_count_lock);

    /* We're no longer waiting... */
    p->waiters_count--;

    /* Check to see if we're the last waiter after <pthread_cond_broadcast>. */
    last_waiter = p->was_broadcast && p->waiters_count == 0;

    LeaveCriticalSection(&p->waiters_count_lock);

    /* If we're the last waiter thread during this particular broadcast */
    /* then let all the other threads proceed. */
    if (last_waiter) {
        /* This call atomically signals the <waiters_done_> event and waits until */
        /* it can acquire the <mutex>.  This is required to ensure fairness.  */
        DWORD err = SignalObjectAndWait(p->waiters_done, *mutex, INFINITE, FALSE);
        if (err == WAIT_FAILED) return set_win32_errno(GetLastError());
    }
    else {
        /* Always regain the external mutex since that's the guarantee we */
        /* give to our callers.  */
        DWORD err = WaitForSingleObject(*mutex, INFINITE);
        if (err == WAIT_FAILED) return set_win32_errno(GetLastError());
    }
    assert(res == WAIT_OBJECT_0);
    return 0;
}