lm_error lm_wait(lm_monitor monitor, int ms)
{
    DWORD timeout = (ms >= 0) ? ((DWORD)ms) : INFINITE;
    
    if (!monitor || !monitor->ready)
        return lm_pointer;

    if (SleepConditionVariableCS(&monitor->cv, &monitor->cs, timeout))
        return lm_ok;
    return (GetLastError() == ERROR_TIMEOUT) ? lm_timeout : lm_pointer;
}