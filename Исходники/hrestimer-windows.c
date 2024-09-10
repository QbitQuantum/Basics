//------------------------------------------------------------------------------
tOplkError hrestimer_deleteTimer(tTimerHdl* pTimerHdl_p)
{
    tOplkError          ret = kErrorOk;
    UINT                index;
    tHresTimerInfo*     pTimerInfo;
    HANDLE              hTimer;

    DEBUG_LVL_TIMERH_TRACE("%s() Deleting timer: %lx\n", __func__, *pTimerHdl_p);

    if (pTimerHdl_p == NULL)
        return kErrorTimerInvalidHandle;

    if (*pTimerHdl_p == 0)
    {   // no timer created yet
        return ret;
    }
    else
    {
        index = (UINT)HDL_TO_IDX(*pTimerHdl_p);
        if (index >= TIMER_COUNT)
        {   // invalid handle
            return kErrorTimerInvalidHandle;
        }
        pTimerInfo = &hresTimerInstance_l.aTimerInfo[index];
        if (pTimerInfo->eventArg.timerHdl.handle != *pTimerHdl_p)
        {   // invalid handle
            return ret;
        }
    }

    pTimerInfo->pfnCallback = NULL;
    *pTimerHdl_p = 0;

    // Cancel timer
    hTimer = hresTimerInstance_l.aHandle[index + HRTIMER_HDL_TIMER0];
    CancelWaitableTimer(hTimer);
    return ret;
}