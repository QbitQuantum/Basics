BOOL
WINAPI
RefreshPolicyEx(IN BOOL bMachine,
                IN DWORD dwOptions)
{
    if (dwOptions & ~RP_FORCE)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    if (dwOptions & RP_FORCE)
    {
        HANDLE hEvent;
        BOOL Ret = TRUE;

        hEvent = OpenEventW(EVENT_MODIFY_STATE,
                            FALSE,
                            (bMachine ? szMachineGPForceRefreshEvent : szLocalGPForceRefreshEvent));
        if (hEvent != NULL)
        {
            Ret = SetEvent(hEvent);
            CloseHandle(hEvent);
        }

        /* return TRUE even if the mutex doesn't exist! */
        return Ret;
    }
    else
    {
        return RefreshPolicy(bMachine);
    }
}