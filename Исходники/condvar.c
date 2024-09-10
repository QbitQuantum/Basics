int nn_condvar_wait (nn_condvar_t *cond, nn_mutex_t *lock, int timeout)
{
    BOOL brc;
    DWORD expire;

    /*  Likely this is redundant, but for API correctness be explicit. */
    expire = (timeout < 0) ? INFINITE : (DWORD) timeout;
    brc = SleepConditionVariableCS (&cond->cv, &lock->mutex, expire);
    if (!brc && GetLastError () == ERROR_TIMEOUT) {
        return (-ETIMEDOUT);
    }
    return (0);
}