static void Test_LockUnlockServiceDatabaseWithServiceStart(void)
{
    BOOL bError = FALSE;

    SC_HANDLE hScm  = NULL;
    SC_HANDLE hSvc  = NULL;
    SC_LOCK   hLock = NULL;

    LPQUERY_SERVICE_CONFIGW lpConfig = NULL;
    DWORD dwRequiredSize = 0;
    SERVICE_STATUS status;
    BOOL bWasRunning = FALSE;
    DWORD dwOldStartType = 0;

    /* Open the services database */
    SetLastError(0xdeadbeef);
    hScm = OpenSCManagerW(NULL, NULL, SC_MANAGER_LOCK);
    ok(hScm != NULL, "Failed to open service manager, error=0x%08lx\n", GetLastError());
    if (!hScm)
    {
        skip("No service control manager; cannot proceed with LockUnlockServiceDatabaseWithServiceStart test\n");
        goto cleanup;
    }
    ok_err(ERROR_SUCCESS);

    /* Grab a handle to the testing service */
    SetLastError(0xdeadbeef);
    hSvc = OpenServiceW(hScm, TESTING_SERVICE, SERVICE_START | SERVICE_STOP | SERVICE_CHANGE_CONFIG | SERVICE_QUERY_CONFIG | SERVICE_QUERY_STATUS);
    ok(hSvc != NULL, "hSvc = 0x%p, expected non-null, error=0x%08lx\n", hSvc, GetLastError());
    if (!hSvc)
    {
        skip("Cannot open a handle to service %S; cannot proceed with LockUnlockServiceDatabaseWithServiceStart test\n", TESTING_SERVICE);
        goto cleanup;
    }
    ok_err(ERROR_SUCCESS);

    /* Lock the services database */
    SetLastError(0xdeadbeef);
    hLock = LockServiceDatabase(hScm);
    ok(hLock != NULL, "hLock = 0x%p, expected non-zero, error=0x%08lx\n", hLock, GetLastError());
    if (!hLock)
    {
        skip("Cannot lock the services database; cannot proceed with LockUnlockServiceDatabaseWithServiceStart test\n");
        goto cleanup;
    }
    ok_err(ERROR_SUCCESS);

    /* To proceed further, firstly attempt to stop the testing service */
    QueryServiceConfigW(hSvc, NULL, 0, &dwRequiredSize);
    lpConfig = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwRequiredSize);
    QueryServiceConfigW(hSvc, lpConfig, dwRequiredSize, &dwRequiredSize);
    dwOldStartType = lpConfig->dwStartType;
    HeapFree(GetProcessHeap(), 0, lpConfig);
    if (dwOldStartType == SERVICE_DISABLED)
    {
        ChangeServiceConfigW(hSvc,
                             SERVICE_NO_CHANGE,
                             SERVICE_DEMAND_START,
                             SERVICE_NO_CHANGE,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL);
    }
    QueryServiceStatus(hSvc, &status);
    bWasRunning = (status.dwCurrentState != SERVICE_STOPPED);
    if (bWasRunning)
    {
        ControlService(hSvc, SERVICE_CONTROL_STOP, &status);
        Sleep(1000); /* Wait 1 second for the service to stop */
    }

    /* Now try to start it (this test won't work under Windows Vista / 7 / 8) */
    SetLastError(0xdeadbeef);
    bError = StartServiceW(hSvc, 0, NULL);
    ok(bError == FALSE, "bError = %u, expected FALSE\n", bError);
    ok_err(ERROR_SERVICE_DATABASE_LOCKED);
    Sleep(1000); /* Wait 1 second for the service to start */

    /* Stop the testing service */
    ControlService(hSvc, SERVICE_CONTROL_STOP, &status);
    Sleep(1000); /* Wait 1 second for the service to stop */

    /* Now unlock the services database */
    SetLastError(0xdeadbeef);
    bError = UnlockServiceDatabase(hLock);
    ok(bError == TRUE, "bError = %u, expected TRUE\n", bError);
    ok_err(ERROR_SUCCESS);

    /* Try to start again the service, this time the database unlocked */
    SetLastError(0xdeadbeef);
    bError = StartServiceW(hSvc, 0, NULL);
    ok(bError == TRUE, "bError = %u, expected TRUE\n", bError);
    ok_err(ERROR_SUCCESS);
    Sleep(1000); /* Wait 1 second for the service to start */

    /* Stop the testing service */
    ControlService(hSvc, SERVICE_CONTROL_STOP, &status);
    Sleep(1000); /* Wait 1 second for the service to stop */

    /* Restore its original state */
    if (bWasRunning)
    {
        StartServiceW(hSvc, 0, NULL);
    }

    if (dwOldStartType == SERVICE_DISABLED)
    {
        ChangeServiceConfigW(hSvc,
                             SERVICE_NO_CHANGE,
                             SERVICE_DISABLED,
                             SERVICE_NO_CHANGE,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL);
    }


cleanup:
    if (hSvc)
        CloseServiceHandle(hSvc);

    if (hScm)
        CloseServiceHandle(hScm);

    return;
}