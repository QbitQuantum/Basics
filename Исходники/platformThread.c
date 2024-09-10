int loom_mutex_trylock_real(const char *file, int line, MutexHandle m)
{
#ifndef NTELEMETRY
    TmU64 matchId;
#endif

    lmAssert(m != 0, "loom_mutex_lock_real - tried to lock NULL");

    tmTryLockEx(gTelemetryContext, &matchId, 1000, file, line, m, "mutex_trylock");

    if (TryEnterCriticalSection((CRITICAL_SECTION *)m))
    {
        tmEndTryLockEx(gTelemetryContext, matchId, file, line, m, TMLR_SUCCESS);
        tmSetLockState(gTelemetryContext, m, TMLS_LOCKED, "mutex_trylock");
        return 1;
    }
    else
    {
        tmEndTryLockEx(gTelemetryContext, matchId, file, line, m, TMLR_FAILED);
        return 0;
    }
}