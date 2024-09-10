PDH_STATUS
ConnectMachine (
    PPERF_MACHINE   pThisMachine
)
{
    LONGLONG    llCurrentTime;
    PDH_STATUS  pdhStatus;
    LONG        lStatus;

    // only one thread at a time can try to connect to a machine.

    WAIT_FOR_AND_LOCK_MUTEX(pThisMachine->hMutex);

    // get the current time
    GetLocalFileTime (&llCurrentTime);

    if (pThisMachine->llRetryTime < llCurrentTime) {
        if (pThisMachine->llRetryTime != 0) {
            // connect to system's performance registry
            if (lstrcmpiW(pThisMachine->szName, szStaticLocalMachineName) == 0) {
                // this is the local machine so use the local reg key
                pThisMachine->hKeyPerformanceData = HKEY_PERFORMANCE_DATA;
            } else {
                __try {
                    // close any open keys
                    if (pThisMachine->hKeyPerformanceData != NULL) {
                        RegCloseKey (pThisMachine->hKeyPerformanceData);
                        pThisMachine->hKeyPerformanceData = NULL;
                    }
                } __except (EXCEPTION_EXECUTE_HANDLER) {
                    lStatus = GetExceptionCode();
                }

                // now try to connect

                __try {
                    // this can generate exceptions in some error cases
                    // so trap them here and continue
                    // remote machine so try to connect to it.
                    lStatus = RegConnectRegistryW (
                        pThisMachine->szName,
                        HKEY_PERFORMANCE_DATA,
                        &pThisMachine->hKeyPerformanceData);
                } __except (EXCEPTION_EXECUTE_HANDLER) {
                    lStatus = GetExceptionCode();
                }
                if (lStatus != ERROR_SUCCESS) {
                    pThisMachine->hKeyPerformanceData = NULL;
                }
            }

            if (pThisMachine->hKeyPerformanceData != NULL) {
                // successfully connected to computer's registry, so
                // get the performance names from that computer and cache them

                if (pThisMachine->szPerfStrings != NULL) {
                    // reload the perf strings, incase new ones have been
                    // installed
                    G_FREE (pThisMachine->szPerfStrings);
                    pThisMachine->szPerfStrings = NULL;
                }

                pThisMachine->szPerfStrings = BuildNameTable (
                    (pThisMachine->hKeyPerformanceData == HKEY_PERFORMANCE_DATA ?
                        NULL : pThisMachine->szName),
                    NULL,
                    &pThisMachine->dwLastPerfString);

                if (pThisMachine->szPerfStrings != NULL) {
                    pdhStatus = ERROR_SUCCESS;
                    pThisMachine->dwStatus = ERROR_SUCCESS;
                } else {
                    // unable to read system counter name strings
                    pdhStatus = PDH_CANNOT_READ_NAME_STRINGS;
                    pThisMachine->dwStatus = PDH_CSTATUS_NO_MACHINE;
                }
            } else {
                // unable to connect to remote machine
                pdhStatus = PDH_CANNOT_CONNECT_MACHINE;
                pThisMachine->dwStatus = PDH_CSTATUS_NO_MACHINE;
            }
        } else {
            // already connected
            // (note: is there a way to test this?)
            pdhStatus = ERROR_SUCCESS;
            pThisMachine->dwStatus = ERROR_SUCCESS;
        }

        if (pdhStatus != ERROR_SUCCESS) {
            // this attempt didn't work so reset retry counter  to
            // wait some more for the machine to come back up.
            pThisMachine->llRetryTime = llCurrentTime + RETRY_TIME_INTERVAL;
        } else {
            // clear the retry counter to allow function calls
            pThisMachine->llRetryTime = 0;
        }
    } else {