void CreatProc(int argc, WCHAR *argv[])
{
    DWORD     dwSize;
    HANDLE    hToken;
    LPVOID    lpvEnv;
    PROCESS_INFORMATION pi = {0};
    STARTUPINFO         si = {0};
    WCHAR               szUserProfile[256] = L"";

    si.cb = sizeof(STARTUPINFO);
    
     //
    // TO DO: change NULL to '.' to use local account database
    //
    if (!LogonUser(argv[1], NULL, argv[2], LOGON32_LOGON_INTERACTIVE, 
            LOGON32_PROVIDER_DEFAULT, &hToken))
        DisplayError(L"LogonUser");

    //if (!CreateEnvironmentBlock(&lpvEnv, hToken, TRUE))        DisplayError(L"CreateEnvironmentBlock");

   // dwSize = sizeof(szUserProfile)/sizeof(WCHAR);

    //if (!GetUserProfileDirectory(hToken, szUserProfile, &dwSize))        DisplayError(L"GetUserProfileDirectory");

    //
    // TO DO: change NULL to '.' to use local account database
    //
    int bResult;
	bResult = CreateProcessWithLogonW(argv[1], NULL, argv[2],     
        LOGON_WITH_PROFILE, NULL, argv[3],             
		CREATE_UNICODE_ENVIRONMENT, /*lpvEnv*/ NULL, szUserProfile,             &si, &pi);
    DWORD dwError;
	dwError = ::GetLastError();
		DisplayError(L"CreateProcessWithLogonW");

//    if (!DestroyEnvironmentBlock(lpvEnv))        DisplayError(L"DestroyEnvironmentBlock");

    CloseHandle(hToken);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}