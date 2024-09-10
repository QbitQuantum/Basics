//------------------------------------------------------------------------------
tOplkError timeru_setTimer(tTimerHdl* pTimerHdl_p, ULONG timeInMs_p, tTimerArg argument_p)
{
    tTimerEntry*    pNewEntry;
    tTimerEntry**   ppEntry;

    // check pointer to handle
    if (pTimerHdl_p == NULL)
        return kErrorTimerInvalidHandle;

    // fetch entry from free timer list
    enterCriticalSection(TIMERU_FREE_LIST);
    pNewEntry = timeruInstance_l.pFreeListFirst;
    if (pNewEntry != NULL)
    {
        timeruInstance_l.pFreeListFirst = pNewEntry->pNext;
        timeruInstance_l.freeEntries--;
        if (timeruInstance_l.minFreeEntries > timeruInstance_l.freeEntries)
        {
            timeruInstance_l.minFreeEntries = timeruInstance_l.freeEntries;
        }
    }
    leaveCriticalSection(TIMERU_FREE_LIST);

    if (pNewEntry == NULL)
    {   // sorry, no free entry
        return kErrorTimerNoTimerCreated;
    }

    *pTimerHdl_p = (tTimerHdl)pNewEntry;
    OPLK_MEMCPY(&pNewEntry->timerArg, &argument_p, sizeof(tTimerArg));

    // insert timer entry in timer list
    enterCriticalSection(TIMERU_TIMER_LIST);
    // calculate timeout based on start time
    pNewEntry->timeoutInMs = (getTickCount() - timeruInstance_l.startTimeInMs) + timeInMs_p;

    ppEntry = &timeruInstance_l.pTimerListFirst;
    while (*ppEntry != NULL)
    {
        if ((*ppEntry)->timeoutInMs > pNewEntry->timeoutInMs)
        {
            (*ppEntry)->timeoutInMs -= pNewEntry->timeoutInMs;
            break;
        }
        pNewEntry->timeoutInMs -= (*ppEntry)->timeoutInMs;
        ppEntry = &(*ppEntry)->pNext;
    }
    // insert before **ppEntry
    pNewEntry->pNext = *ppEntry;
    *ppEntry = pNewEntry;
    leaveCriticalSection(TIMERU_TIMER_LIST);

#if (TARGET_SYSTEM == _WIN32_ || TARGET_SYSTEM == _WINCE_ )
    if (ppEntry == &timeruInstance_l.pTimerListFirst)
    {
        SetEvent(timeruInstance_l.ahEvents[TIMERU_EVENT_WAKEUP]);
    }
#endif

    return kErrorOk;
}