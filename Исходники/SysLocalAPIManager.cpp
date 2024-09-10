/**
 * Reports if the rxapi service is in the running state at the time this
 * function returns.  If the service is in the START PENDING state the function
 * waits untils the service is running or has timed out.
 *
 * @param hService  Opened service handle, must have the SERVICE_QUERY_STATUS
 *                  privilege.
 *
 * @return True the service is not running, otherwise false.
 */
static bool hasServiceStarted(SC_HANDLE hService)
{
    SERVICE_STATUS_PROCESS ssp;
    DWORD                  needed;

    if ( QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &needed) == 0 )
    {
        return false;
    }

    if ( ssp.dwCurrentState == SERVICE_RUNNING || ssp.dwCurrentState == SERVICE_STOPPED ||
         ssp.dwCurrentState == SERVICE_STOP_PENDING )
    {
        return ssp.dwCurrentState == SERVICE_RUNNING;
    }

    // Save the tick count and initial checkpoint.
    uint32_t startTicks = GetTickCount();
    uint32_t oldCheck = ssp.dwCheckPoint;
    uint32_t waitTime;

    // Check the status until the service is no longer start pending.  rxapi is
    // not pausable, so PAUSED or PAUSED_PENDING should not be possible.
    while ( ssp.dwCurrentState == SERVICE_START_PENDING )
    {
        // Do not wait longer than the wait hint, which for rxapi will be 2000
        // milliseconds.
        //
        // Microsoft suggests that a good interval is one tenth the wait hint,
        // but not less than 1 second and no more than 10 seconds. rxapi usually
        // starts in less than 200 milliseconds.
        waitTime = ssp.dwWaitHint / 10;

        if( waitTime < 200 )
        {
            waitTime = 200;
        }
        else if ( waitTime > 10000 )
        {
            waitTime = 10000;
        }

        Sleep(waitTime);

        BOOL success = QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &needed);
        if ( ! success || ssp.dwCurrentState == SERVICE_RUNNING )
        {
            break;
        }

        if ( ssp.dwCheckPoint > oldCheck )
        {
            // The service is making progress, so continue.
            startTicks = GetTickCount();
            oldCheck = ssp.dwCheckPoint;
        }
        else
        {
            if( (GetTickCount() - startTicks) > ssp.dwWaitHint )
            {
                // The wait hint interval has expired and we are still not
                // started, so quit.
                break;
            }
        }
    }

    return ssp.dwCurrentState == SERVICE_RUNNING ? true : false;
}