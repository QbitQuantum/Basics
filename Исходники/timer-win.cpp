RTDECL(int) RTTimerCreate(PRTTIMER *ppTimer, unsigned uMilliesInterval, PFNRTTIMER pfnTimer, void *pvUser)
{
#ifndef USE_WINMM
    /*
     * On windows we'll have to set the timer resolution before
     * we start the timer.
     */
    ULONG ulMax = UINT32_MAX;
    ULONG ulMin = UINT32_MAX;
    ULONG ulCur = UINT32_MAX;
    NtQueryTimerResolution(&ulMax, &ulMin, &ulCur);
    Log(("NtQueryTimerResolution -> ulMax=%lu00ns ulMin=%lu00ns ulCur=%lu00ns\n", ulMax, ulMin, ulCur));
    if (ulCur > ulMin && ulCur > 10000 /* = 1ms */)
    {
        if (NtSetTimerResolution(10000, TRUE, &ulCur) >= 0)
            Log(("Changed timer resolution to 1ms.\n"));
        else if (NtSetTimerResolution(20000, TRUE, &ulCur) >= 0)
            Log(("Changed timer resolution to 2ms.\n"));
        else if (NtSetTimerResolution(40000, TRUE, &ulCur) >= 0)
            Log(("Changed timer resolution to 4ms.\n"));
        else if (ulMin <= 50000 && NtSetTimerResolution(ulMin, TRUE, &ulCur) >= 0)
            Log(("Changed timer resolution to %lu *100ns.\n", ulMin));
        else
        {
            AssertMsgFailed(("Failed to configure timer resolution!\n"));
            return VERR_INTERNAL_ERROR;
        }
    }
#endif /* !USE_WINN */

    /*
     * Create new timer.
     */
    int rc = VERR_IPE_UNINITIALIZED_STATUS;
    PRTTIMER pTimer = (PRTTIMER)RTMemAlloc(sizeof(*pTimer));
    if (pTimer)
    {
        pTimer->u32Magic    = RTTIMER_MAGIC;
        pTimer->pvUser      = pvUser;
        pTimer->pfnTimer    = pfnTimer;
        pTimer->iTick       = 0;
        pTimer->uMilliesInterval = uMilliesInterval;
#ifdef USE_WINMM
        /* sync kill doesn't work. */
        pTimer->TimerId     = timeSetEvent(uMilliesInterval, 0, rttimerCallback, (DWORD_PTR)pTimer, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
        if (pTimer->TimerId)
        {
            ULONG ulMax = UINT32_MAX;
            ULONG ulMin = UINT32_MAX;
            ULONG ulCur = UINT32_MAX;
            NtQueryTimerResolution(&ulMax, &ulMin, &ulCur);
            Log(("NtQueryTimerResolution -> ulMax=%lu00ns ulMin=%lu00ns ulCur=%lu00ns\n", ulMax, ulMin, ulCur));

            *ppTimer = pTimer;
            return VINF_SUCCESS;
        }
        rc = VERR_INVALID_PARAMETER;

#else /* !USE_WINMM */

        /*
         * Create Win32 event semaphore.
         */
        pTimer->iError = 0;
        pTimer->hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
        if (pTimer->hTimer)
        {
#ifdef USE_APC
            /*
             * Create wait semaphore.
             */
            pTimer->hevWait = CreateEvent(NULL, FALSE, FALSE, NULL);
            if (pTimer->hevWait)
#endif
            {
                /*
                 * Kick off the timer thread.
                 */
                rc = RTThreadCreate(&pTimer->Thread, rttimerCallback, pTimer, 0, RTTHREADTYPE_TIMER, RTTHREADFLAGS_WAITABLE, "Timer");
                if (RT_SUCCESS(rc))
                {
                    /*
                     * Wait for the timer to successfully create the timer
                     * If we don't get a response in 10 secs, then we assume we're screwed.
                     */
                    rc = RTThreadUserWait(pTimer->Thread, 10000);
                    if (RT_SUCCESS(rc))
                    {
                        rc = pTimer->iError;
                        if (RT_SUCCESS(rc))
                        {
                            *ppTimer = pTimer;
                            return VINF_SUCCESS;
                        }
                    }
                    ASMAtomicXchgU32(&pTimer->u32Magic, RTTIMER_MAGIC + 1);
                    RTThreadWait(pTimer->Thread, 250, NULL);
                    CancelWaitableTimer(pTimer->hTimer);
                }
#ifdef USE_APC
                CloseHandle(pTimer->hevWait);
#endif
            }
            CloseHandle(pTimer->hTimer);
        }
#endif /* !USE_WINMM */

        AssertMsgFailed(("Failed to create timer uMilliesInterval=%d. rc=%d\n", uMilliesInterval, rc));
        RTMemFree(pTimer);
    }
    else
        rc = VERR_NO_MEMORY;
    return rc;
}