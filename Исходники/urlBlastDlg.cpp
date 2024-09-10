/*-----------------------------------------------------------------------------
	Kill any Dr. Watson windows that are open (we already killed the browser process)
-----------------------------------------------------------------------------*/
void CurlBlastDlg::KillProcs(void)
{
#ifndef _DEBUG

    WTS_PROCESS_INFO * proc = NULL;
    DWORD count = 0;
    if( WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, 0, 1, &proc, &count) )
    {
        for( DWORD i = 0; i < count; i++ )
        {
            bool terminate = false;

            // check for Dr. Watson
            if( !lstrcmpi(PathFindFileName(proc[i].pProcessName), _T("dwwin.exe")) )
            {
                if( !bDrWatson )
                {
                    log.LogEvent(event_KilledDrWatson);
                    bDrWatson = true;
                }
                terminate = true;
            }
            else if(lstrcmpi(PathFindFileName(proc[i].pProcessName), _T("iexplore.exe")))
            {
                if (worker) {
                    EnterCriticalSection( &(worker->cs) );
                    // make sure it's not the browser we launched
                    if( proc[i].ProcessId != worker->browserPID
                            && worker->userSID && proc[i].pUserSid
                            && IsValidSid(worker->userSID) && IsValidSid(proc[i].pUserSid) )
                    {
                        // see if the SID matches
                        if( EqualSid(proc[i].pUserSid, worker->userSID ) )
                            terminate = true;
                    }
                    LeaveCriticalSection( &(worker->cs) );
                }
            }

            if( terminate )
            {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, proc[i].ProcessId);
                if( hProc )
                {
                    TerminateProcess(hProc, 0);
                    CloseHandle(hProc);
                }
            }
        }

        WTSFreeMemory(proc);
    }
#endif
}