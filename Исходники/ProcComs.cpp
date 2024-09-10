void wmain(int argc, WCHAR *argv[])
{
    DWORD     dwSize;
    HANDLE    hToken;
    LPVOID    lpvEnv;
    PROCESS_INFORMATION pi = {0};
    STARTUPINFO         si = {0};
    WCHAR               szUserProfile[256] = L"";

    si.cb = sizeof(STARTUPINFO);

    if (argc != 4)
    {
        /*    wprintf(L"Usage: %s [user@domain] [password] [cmd]", argv[0]);
            wprintf(L"\n\n"); */
        //   return;
    }

    dwSize = sizeof(szUserProfile)/sizeof(WCHAR);


    OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken);
    //ShowLastError(L"OpenProcessToken");
    //SetPrivilege(&hToken, SE_SYSTEMTIME_NAME,TRUE);
    // if(!SetPrivilege(hToken, SE_TCB_NAME , TRUE)) printf("Set Privilege Failed");// DisplayError(L"SetPrivilege");
    //if (!LogonUser(argv[1], NULL , argv[2], LOGON32_LOGON_INTERACTIVE,    LOGON32_PROVIDER_DEFAULT, &hToken))       DisplayError(L"LogonUser");

    if (!CreateEnvironmentBlock(&lpvEnv, hToken, TRUE))    ShowLastError(L"CreateEnvironmentBlock");

    dwSize = sizeof(szUserProfile)/sizeof(WCHAR);

    if (!GetUserProfileDirectory(hToken, szUserProfile, &dwSize))        ShowLastError(L"GetUserProfileDirectory");
    //
    // TO DO: change NULL to '.' to use local account database
    //
    if (!CreateProcessWithLogonW(argv[1], NULL, argv[2],             LOGON_WITH_PROFILE, NULL, argv[3],             CREATE_UNICODE_ENVIRONMENT, lpvEnv, szUserProfile,             &si, &pi))

        ShowLastError(L"CreateProcessWithLogonW");

    if (!DestroyEnvironmentBlock(lpvEnv))        ShowLastError(L"DestroyEnvironmentBlock");


    CloseHandle(hToken);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}