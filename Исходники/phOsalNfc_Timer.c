void phOsalNfc_Timer_Delete(uint32_t TimerId)
{
    uint32_t uIndex;

    //
    // In various places in the code, timers are initialized only
    // after they are first needed.  Despite this fact, they are
    // deleted unconditionally when their context is being deleted
    // Intead of adding an if statement in all places where
    // timers are being deleted, this check is added to prevent 
    // a NULL deref.
    //
    if (NULL == gpphOsalNfc_Context ||
        PH_OSALNFC_TIMER_ID_INVALID == TimerId)
    {
        return;
    }

    uIndex = TimerId - PH_OSAL_TIMER_BASE_ADDRESS;

    EnterCriticalSection(&gpphOsalNfc_Context->TimerLock);

    if(gpphOsalNfc_Context->TimerList[uIndex].pTimer != NULL) 
    {
        SetThreadpoolTimer(gpphOsalNfc_Context->TimerList[uIndex].pTimer, NULL, 0, 0);
        LeaveCriticalSection(&gpphOsalNfc_Context->TimerLock);
        
        WaitForThreadpoolTimerCallbacks(gpphOsalNfc_Context->TimerList[uIndex].pTimer, TRUE);

        EnterCriticalSection(&gpphOsalNfc_Context->TimerLock);

        CloseThreadpoolTimer(gpphOsalNfc_Context->TimerList[uIndex].pTimer);
        gpphOsalNfc_Context->TimerList[uIndex].pTimer    = NULL;
        gpphOsalNfc_Context->TimerList[uIndex].pCallback = NULL;
        gpphOsalNfc_Context->TimerList[uIndex].pContext  = NULL;
        gpphOsalNfc_Context->TimerList[uIndex].bFired    = FALSE;

        uIndex = 0;
        while (uIndex < PH_MAX_OSAL_NUM_TIMERS) 
        {
            if (gpphOsalNfc_Context->TimerList[uIndex].pTimer != NULL)
            {
                break;
            }
            uIndex++;
        }
    }

    LeaveCriticalSection(&gpphOsalNfc_Context->TimerLock);
}