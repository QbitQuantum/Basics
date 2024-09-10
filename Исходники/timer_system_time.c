int create_time_thread(lm_res_param_t *pm)
{

    TIMECAPS tc;

    pm->tm_param.count = 0;

    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR)
    {
        DWORD err = GetLastError();
        lmice_critical_print("Create time thread failed[%u]\n", err);
        return 1;
    }

    pm->tm_param.wTimerRes = min(max(tc.wPeriodMin, MMTIME_RESOLUTION), tc.wPeriodMax);
    pm->tm_param.wTimerDelay = pm->tm_param.wTimerRes;

    timeBeginPeriod(pm->tm_param.wTimerRes);

    pm->tm_param.wTimerID = timeSetEvent(
                pm->tm_param.wTimerDelay,                // delay
                pm->tm_param.wTimerRes,                  // resolution (global variable)
                time_thread_proc,               // callback function
                (DWORD_PTR)pm,                  // user data
                TIME_PERIODIC );                // single timer event
    if(! pm->tm_param.wTimerID)
        return 1;
    else
        return 0;
}