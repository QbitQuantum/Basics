bool CProcess::Kill(unsigned long timeout) const
{
#if   defined(NCBI_OS_UNIX)

    TPid pid = (TPid)m_Process;

    // Try to kill the process with SIGTERM first
    if (kill(pid, SIGTERM) < 0  &&  errno == EPERM) {
        return false;
    }

    // Check process termination within the timeout
    unsigned long x_timeout = timeout;
    for (;;) {
        TPid reap = waitpid(pid, static_cast<int*>(NULL), WNOHANG);
        if (reap) {
            if (reap != (TPid)(-1)) {
                _ASSERT(reap == pid);
                return true;
            }
            if (errno != ECHILD)
                return false;
            if (kill(pid, 0) < 0)
                return true;
        }
        unsigned long x_sleep = kWaitPrecision;
        if (x_sleep > x_timeout) {
            x_sleep = x_timeout;
        }
        if ( !x_sleep ) {
             break;
        }
        SleepMilliSec(x_sleep);
        x_timeout  -= x_sleep;
    }
    _ASSERT(!x_timeout);

    // Try harder to kill the stubborn process -- SIGKILL may not be caught!
    int res = kill(pid, SIGKILL);
    if ( !timeout ) {
        return res <= 0;
    }
    SleepMilliSec(kWaitPrecision);
    // Reap the zombie (if child) up from the system
    waitpid(pid, static_cast<int*>(NULL), WNOHANG);
    // Check whether the process cannot be killed
    // (most likely due to a kernel problem)
    return kill(pid, 0) < 0;

#elif defined(NCBI_OS_MSWIN)

    // Safe process termination
    bool safe = (timeout > 0);

    // Try to kill current process?
    if ( m_Type == ePid  &&  (TPid)m_Process == GetCurrentPid() ) {
        ExitProcess(-1);
        // NOTREACHED
        return false;
    }

    HANDLE hProcess    = NULL;
    HANDLE hThread     = NULL;
    bool   enable_sync = true;

    // Get process handle
    if (m_Type == eHandle) {
        hProcess = (TProcessHandle)m_Process;

    } else {  // m_Type == ePid
        hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_TERMINATE |
                               SYNCHRONIZE, FALSE, (TPid)m_Process);
        if ( !hProcess ) {
            // Try to open with minimal access right needed
            // to terminate process.
            enable_sync = false;
            hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, (TPid)m_Process);
            if (!hProcess) {
                if (GetLastError() != ERROR_ACCESS_DENIED) {
                    return false;
                }
                // If we have an administrative rights, that we can try
                // to terminate the process using SE_DEBUG_NAME privilege,
                // which system administrators normally have, but it might
                // be disabled by default. When this privilege is enabled,
                // the calling thread can open processes with any access
                // rights regardless of the security descriptor assigned
                // to the process.

                // Determine OS version
                OSVERSIONINFO vi;
                vi.dwOSVersionInfoSize = sizeof(vi);
                GetVersionEx(&vi);
                if (vi.dwPlatformId != VER_PLATFORM_WIN32_NT) {
                    return false;
                }

                // Get current thread token 
                HANDLE hToken;
                if (!OpenThreadToken(GetCurrentThread(), 
                                     TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES,
                                     FALSE, &hToken)) {
                    if (GetLastError() != ERROR_NO_TOKEN) {
                        return false;
                    }
                    // Rrevert to the process token, if not impersonating
                    if (!OpenProcessToken(GetCurrentProcess(),
                                          TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES,
                                          &hToken)) {
                        return false;
                    }
                }

                // Try to enable the SE_DEBUG_NAME privilege

                TOKEN_PRIVILEGES tp, tp_prev;
                DWORD            tp_prev_size = sizeof(tp_prev);

                tp.PrivilegeCount = 1;
                tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);

                if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp),
                                           &tp_prev, &tp_prev_size)) {
                    CloseHandle(hToken);
                    return false;
                }
                if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
                    // The AdjustTokenPrivileges function cannot add new
                    // privileges to the access token. It can only enable or
                    // disable the token's existing privileges.
                    CloseHandle(hToken);
                    return false;
                }

                // Try to open process handle again
                hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, (TPid)m_Process);
                
                // Restore original privilege state
                AdjustTokenPrivileges(hToken, FALSE, &tp_prev, sizeof(tp_prev),
                                      NULL, NULL);
                CloseHandle(hToken);
            }
        }
    }

    // Check process handle
    if ( !hProcess  ||  hProcess == INVALID_HANDLE_VALUE ) {
        return true;
    }
    // Terminate process
    bool terminated = false;

    CStopWatch timer;
    if ( safe ) {
        timer.Start();
    }
    // Safe process termination
    if ( safe  &&  enable_sync ) {
        // (kernel32.dll loaded at same address in each process)
        FARPROC exitproc = GetProcAddress(GetModuleHandleA("KERNEL32.DLL"),
                                          "ExitProcess");
        if ( exitproc ) {
            hThread = CreateRemoteThread(hProcess, NULL, 0,
                                        (LPTHREAD_START_ROUTINE)exitproc,
                                        0, 0, 0);
            // Wait until process terminated, or timeout expired
            if (hThread   &&
                (WaitForSingleObject(hProcess, timeout) == WAIT_OBJECT_0)){
                terminated = true;
            }
        }
    }
    // Try harder to kill stubborn process
    if ( !terminated ) {
        if ( TerminateProcess(hProcess, -1) != 0  ||
            GetLastError() == ERROR_INVALID_HANDLE ) {
            // If process "terminated" succesfuly or error occur but
            // process handle became invalid -- process has terminated
            terminated = true;
        }
    }
    if (safe  &&  terminated) {
        // The process terminating now.
        // Reset flag, and wait for real process termination.

        terminated = false;
        double elapsed = timer.Elapsed() * kMilliSecondsPerSecond;
        unsigned long linger_timeout = (elapsed < timeout) ? 
            (unsigned long)((double)timeout - elapsed) : 0;

        for (;;) {
            if ( !IsAlive() ) {
                terminated = true;
                break;
            }
            unsigned long x_sleep = kWaitPrecision;
            if (x_sleep > linger_timeout) {
                x_sleep = linger_timeout;
            }
            if ( !x_sleep ) {
                break;
            }
            SleepMilliSec(x_sleep);
            linger_timeout -= x_sleep;
        }
    }
    // Close temporary process handle
    if ( hThread ) {
        CloseHandle(hThread);
    }
    if (m_Type == ePid) {
        CloseHandle(hProcess);
    }
    return terminated;

#endif
}