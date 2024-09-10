XT_DECLARE(xt_state_t) xt_proc_wait_all_procs( xt_proc_t *proc, int *exitcode, xt_exit_why_t *exitwhy, xt_wait_how_t waithow )
{
	DWORD  dwId    = GetCurrentProcessId();
    DWORD  i;
    DWORD  nChilds = 0;
    DWORD  nActive = 0;
    HANDLE ps32;
    PROCESSENTRY32W pe32;
    BOOL   bHasMore = FALSE;
    DWORD  dwFlags  = PROCESS_QUERY_INFORMATION;
    xt_state_t rv = XT_EGENERAL;

    if ( waithow == XT_WAIT )
        dwFlags |= SYNCHRONIZE;

	ps32 = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if ( !(ps32) )
	{
        return xt_get_os_error();
    }
    pe32.dwSize = sizeof(PROCESSENTRY32W);
    if ( !Process32FirstW(ps32, &pe32) )
	{
        if (GetLastError() == ERROR_NO_MORE_FILES)
            return XT_EOF;
        else
            return xt_get_os_error();
    }
    do {
        DWORD  dwRetval = 0;
        DWORD  nHandles = 0;
        HANDLE hProcess = NULL;
        HANDLE pHandles[MAXIMUM_WAIT_OBJECTS];
        do {
            if (pe32.th32ParentProcessID == dwId)
			{
                nChilds++;
                if ( (hProcess = OpenProcess(dwFlags, FALSE, pe32.th32ProcessID)) != NULL )
				{
                    if ( GetExitCodeProcess(hProcess, &dwRetval) )
					{
                        if (dwRetval == STILL_ACTIVE)
						{
                            nActive++;
                            if (waithow == XT_WAIT)
                                pHandles[nHandles++] = hProcess;
                            else
                                CloseHandle(hProcess);
                        }
                        else
						{                                
                            /* Process has exited.
                                * No need to wait for its termination.
                                */
                            CloseHandle(hProcess);
                            if (exitcode)
                                *exitcode = dwRetval;
                            if (exitwhy)
                                *exitwhy  = why_from_exit_code(dwRetval);
                            proc->pid = pe32.th32ProcessID;
                        }
                    }
                    else
					{
                        /* Unexpected error code.
                            * Cleanup and return;
                            */
                        rv = xt_get_os_error();
                        CloseHandle(hProcess);
                        for ( i=0; i<nHandles; i++ )
                            CloseHandle(pHandles[i]);
                        return rv;
                    }
                }
                else {
                    /* This is our child, so it shouldn't happen
                        * that we cannot open our child's process handle.
                        * However if the child process increased the
                        * security token it might fail.
                        */
                }
            }
			bHasMore = Process32NextW( ps32, &pe32 );
        } while ( (bHasMore) && nHandles<MAXIMUM_WAIT_OBJECTS );

        if ( nHandles )
		{
            /* Wait for all collected processes to finish */
            DWORD waitStatus = WaitForMultipleObjects(nHandles, pHandles, TRUE, INFINITE);
            for ( i=0; i<nHandles; i++ )
                CloseHandle(pHandles[i]);
            if ( waitStatus == WAIT_OBJECT_0 )
			{
                /* Decrease active count by the number of awaited
                    * processes.
                    */
                nActive -= nHandles;
            }
            else
			{
                /* Broken from the infinite loop */
                break;
            }
        }
    } while (bHasMore);
    CloseHandle(ps32);

    if ( waithow != XT_WAIT )
	{
        if ( nChilds && nChilds == nActive )
		{
            /* All child processes are running */
            rv = XT_CHILD_NOTDONE;
            proc->pid = -1;
        }
        else {
            /* proc->pid contains the pid of the
                * exited processes
                */
            rv = XT_CHILD_DONE;
        }
    }

    if (nActive == 0) {
        rv = XT_CHILD_DONE;
        proc->pid = -1;
    }

    return rv;
}