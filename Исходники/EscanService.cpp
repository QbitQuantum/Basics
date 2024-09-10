BOOL CreateInteractiveProcess(DWORD dwSessionId,
                              PWSTR pszCommandLine, 
                              BOOL fWait, 
                              DWORD dwTimeout, 
                              DWORD *pExitCode)
{
    DWORD dwError = ERROR_SUCCESS;
    HANDLE hToken = NULL;
    LPVOID lpvEnv = NULL;
    wchar_t szUserProfileDir[MAX_PATH];
    DWORD cchUserProfileDir = ARRAYSIZE(szUserProfileDir);
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi = { 0 };
    DWORD dwWaitResult;

    // Obtain the primary access token of the logged-on user specified by the 
    // session ID.
    if (!WTSQueryUserToken(dwSessionId, &hToken))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    // Run the command line in the session that we found by using the default 
    // values for working directory and desktop.

    // This creates the default environment block for the user.
    if (!CreateEnvironmentBlock(&lpvEnv, hToken, TRUE))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    // Retrieve the path to the root directory of the user's profile.
    if (!GetUserProfileDirectory(hToken, szUserProfileDir, 
        &cchUserProfileDir))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    // Specify that the process runs in the interactive desktop.
    si.lpDesktop = L"winsta0\\default";

    // Launch the process.
    if (!CreateProcessAsUser(hToken, NULL, pszCommandLine, NULL, NULL, FALSE, 
        CREATE_UNICODE_ENVIRONMENT, lpvEnv, szUserProfileDir, &si, &pi))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    if (fWait)
    {
        // Wait for the exit of the process.
        dwWaitResult = WaitForSingleObject(pi.hProcess, dwTimeout);
        if (dwWaitResult == WAIT_OBJECT_0)
        {
            // If the process exits before timeout, get the exit code.
            GetExitCodeProcess(pi.hProcess, pExitCode);
        }
        else if (dwWaitResult == WAIT_TIMEOUT)
        {
            // If it times out, terminiate the process.
            TerminateProcess(pi.hProcess, IDTIMEOUT);
            *pExitCode = IDTIMEOUT;
        }
        else
        {
            dwError = GetLastError();
            goto Cleanup;
        }
    }
    else
    {
        *pExitCode = IDASYNC;
    }

Cleanup:

    // Centralized cleanup for all allocated resources.
    if (hToken)
    {
        CloseHandle(hToken);
        hToken = NULL;
    }
    if (lpvEnv)
    {
        DestroyEnvironmentBlock(lpvEnv);
        lpvEnv = NULL;
    }
    if (pi.hProcess)
    {
        CloseHandle(pi.hProcess);
        pi.hProcess = NULL;
    }
    if (pi.hThread)
    {
        CloseHandle(pi.hThread);
        pi.hThread = NULL;
    }

    // Set the last error if something failed in the function.
    if (dwError != ERROR_SUCCESS)
    {
        SetLastError(dwError);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}