VOID
StartScreenSaver(
    IN PWLSESSION Session)
{
    HKEY hKey = NULL, hCurrentUser = NULL;
    WCHAR szApplicationName[MAX_PATH];
    WCHAR szCommandLine[MAX_PATH + 3];
    DWORD bufferSize = sizeof(szApplicationName) - sizeof(WCHAR);
    DWORD dwType;
    STARTUPINFOW StartupInfo;
    PROCESS_INFORMATION ProcessInformation;
    HANDLE HandleArray[2];
    LONG rc;
    DWORD Status;
    BOOL ret = FALSE;

    if (!ImpersonateLoggedOnUser(Session->UserToken))
    {
        ERR("WL: ImpersonateLoggedOnUser() failed with error %lu\n", GetLastError());
        goto cleanup;
    }

    rc = RegOpenCurrentUser(KEY_READ,
                            &hCurrentUser);
    if (rc != ERROR_SUCCESS)
    {
        ERR("WL: RegOpenCurrentUser Error!\n");
        goto cleanup;
    }

    rc = RegOpenKeyExW(hCurrentUser,
                       L"Control Panel\\Desktop",
                       0,
                       KEY_QUERY_VALUE,
                       &hKey);
    if (rc != ERROR_SUCCESS)
    {
        ERR("WL: RegOpenKeyEx Error!\n");
        goto cleanup;
    }

    rc = RegQueryValueExW(hKey,
                          L"SCRNSAVE.EXE",
                          0,
                          &dwType,
                          (LPBYTE)szApplicationName,
                          &bufferSize);
    if (rc != ERROR_SUCCESS || dwType != REG_SZ)
    {
        ERR("WL: RegQueryValueEx Error!\n");
        goto cleanup;
    }

    if (bufferSize == 0)
    {
        ERR("WL: Buffer size is NULL!\n");
        goto cleanup;
    }

    szApplicationName[bufferSize / sizeof(WCHAR)] = 0; /* Terminate the string */

    if (wcslen(szApplicationName) == 0)
    {
        ERR("WL: Application Name length is zero!\n");
        goto cleanup;
    }

    wsprintfW(szCommandLine, L"%s /s", szApplicationName);
    TRACE("WL: Executing %S\n", szCommandLine);

    ZeroMemory(&StartupInfo, sizeof(STARTUPINFOW));
    ZeroMemory(&ProcessInformation, sizeof(PROCESS_INFORMATION));
    StartupInfo.cb = sizeof(STARTUPINFOW);
    StartupInfo.dwFlags = STARTF_SCRNSAVER;

    /* FIXME: run the screen saver on the screen saver desktop */
    ret = CreateProcessW(szApplicationName,
                         szCommandLine,
                         NULL,
                         NULL,
                         FALSE,
                         0,
                         NULL,
                         NULL,
                         &StartupInfo,
                         &ProcessInformation);
    if (!ret)
    {
        ERR("WL: Unable to start %S, error %lu\n", szApplicationName, GetLastError());
        goto cleanup;
    }

    CloseHandle(ProcessInformation.hThread);

    SystemParametersInfoW(SPI_SETSCREENSAVERRUNNING, TRUE, NULL, 0);

    /* Wait the end of the process or some other activity */
    ResetEvent(Session->hUserActivity);
    HandleArray[0] = ProcessInformation.hProcess;
    HandleArray[1] = Session->hUserActivity;
    Status = WaitForMultipleObjects(2, HandleArray, FALSE, INFINITE);
    if (Status == WAIT_OBJECT_0 + 1)
    {
        /* Kill the screen saver */
        TerminateProcess(ProcessInformation.hProcess, 0);
    }

    SetEvent(Session->hEndOfScreenSaver);

    CloseHandle(ProcessInformation.hProcess);

cleanup:
    RevertToSelf();
    if (hKey)
        RegCloseKey(hKey);

    if (hCurrentUser)
        RegCloseKey(hCurrentUser);

    if (!ret)
    {
        PostMessageW(Session->SASWindow, WLX_WM_SAS, WLX_SAS_TYPE_SCRNSVR_ACTIVITY, 0);
#ifndef USE_GETLASTINPUTINFO
        InterlockedExchange((LONG*)&Session->LastActivity, GetTickCount());
#endif
    }
}