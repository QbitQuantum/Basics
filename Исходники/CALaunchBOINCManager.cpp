UINT CALaunchBOINCManager::OnExecution()
{
    static HMODULE advapi32lib = NULL;
    static tSCREATEL pSCREATEL = NULL;
    static tSCTFL pSCTFL = NULL;
    static tSCLOSEL pSCLOSEL = NULL;
    PROCESS_INFORMATION process_info;
    STARTUPINFO startup_info;
    SAFER_LEVEL_HANDLE hSaferHandle;
    HANDLE hRestrictedToken;
    SID_IDENTIFIER_AUTHORITY siaMLA = SECURITY_MANDATORY_LABEL_AUTHORITY;
    PSID  pSidMedium = NULL;
    TOKEN_MANDATORY_LABEL TIL = {0};
    DWORD dwEnableVirtualization = 1;
    tstring strInstallDirectory;
    tstring strBuffer;
    UINT uiReturnValue = -1;
    FILE* f;

    memset(&process_info, 0, sizeof(process_info));
    memset(&startup_info, 0, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    startup_info.dwFlags = STARTF_USESHOWWINDOW;
    startup_info.wShowWindow = SW_SHOW;

    f = fopen("LaunchManager.txt", "w");

    if (!advapi32lib) {
        advapi32lib = LoadLibraryA("advapi32.dll");
        if (advapi32lib) {
            pSCREATEL = (tSCREATEL)GetProcAddress(advapi32lib, "SaferCreateLevel");
            pSCTFL = (tSCTFL)GetProcAddress(advapi32lib, "SaferComputeTokenFromLevel");
            pSCLOSEL = (tSCLOSEL)GetProcAddress(advapi32lib, "SaferCloseLevel");
        }
    }

    if (!pSCREATEL || !pSCTFL || !pSCLOSEL) {
        return ERROR_FILE_NOT_FOUND;
    }

    uiReturnValue = GetProperty( _T("INSTALLDIR"), strInstallDirectory );
    if ( uiReturnValue ) return uiReturnValue;


    // Calculate a restricted token from the current token.
    if (!pSCREATEL( SAFER_SCOPEID_USER, SAFER_LEVELID_NORMALUSER, SAFER_LEVEL_OPEN, &hSaferHandle, NULL ))
    {
        fwprintf(f, _T("SaferCreateLevel retval: '%d'\n"), GetLastError());
    }

    if (!pSCTFL( hSaferHandle, NULL, &hRestrictedToken, NULL, NULL ))
    {
        fwprintf(f, _T("SaferComputeTokenFromLevel retval: '%d'\n"), GetLastError());
    }

    AllocateAndInitializeSid(&siaMLA, 1, SECURITY_MANDATORY_MEDIUM_RID, 0, 0, 0, 0, 0, 0, 0, &pSidMedium);

    TIL.Label.Attributes = SE_GROUP_INTEGRITY;
    TIL.Label.Sid        = pSidMedium;

    if (!SetTokenInformation(hRestrictedToken, (TOKEN_INFORMATION_CLASS)TokenIntegrityLevel, &TIL, sizeof(TOKEN_MANDATORY_LABEL)))
    {
        fwprintf(f, _T("SaferComputeTokenFromLevel (TokenIntegrityLevel) retval: '%d'\n"), GetLastError());
    }

    if (!SetTokenInformation(hRestrictedToken, (TOKEN_INFORMATION_CLASS)TokenVirtualizationEnabled, &dwEnableVirtualization, sizeof(DWORD)))
    {
        fwprintf(f, _T("SaferComputeTokenFromLevel (TokenVirtualizationEnabled) retval: '%d'\n"), GetLastError());
    }


    strBuffer = tstring(_T("\"")) + strInstallDirectory + tstring(_T("boincmgr.exe\""));
    fwprintf(f, _T("Attempting to launch boincmgr.exe\n"));
    fwprintf(f, _T("Launching: '%s'\n"), strBuffer.c_str());
    if (CreateProcessAsUser( hRestrictedToken, NULL, (LPWSTR)strBuffer.c_str(), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup_info, &process_info ))
    {
        fwprintf(f, _T("Success!!!\n"));
        CloseHandle( process_info.hProcess );
        CloseHandle( process_info.hThread );
    }
    else
    {
        fwprintf(f, _T("CreateProcessAsUser retval: '%d'\n"), GetLastError());
    }

    strBuffer = tstring(_T("\"")) + strInstallDirectory + tstring(_T("gridrepublic.exe\""));
    fwprintf(f, _T("Attempting to launch gridrepublic.exe\n"));
    fwprintf(f, _T("Launching: '%s'\n"), strBuffer.c_str());
    if (CreateProcessAsUser( hRestrictedToken, NULL, (LPWSTR)strBuffer.c_str(), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup_info, &process_info ))
    {
        fwprintf(f, _T("Success!!!\n"));
        CloseHandle( process_info.hProcess );
        CloseHandle( process_info.hThread );
    }
    else
    {
        fwprintf(f, _T("CreateProcessAsUser retval: '%d'\n"), GetLastError());
    }

    strBuffer = tstring(_T("\"")) + strInstallDirectory + tstring(_T("charityengine.exe\""));
    fwprintf(f, _T("Attempting to launch charityengine.exe\n"));
    fwprintf(f, _T("Launching: '%s'\n"), strBuffer.c_str());
    if (CreateProcessAsUser( hRestrictedToken, NULL, (LPWSTR)strBuffer.c_str(), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup_info, &process_info ))
    {
        fwprintf(f, _T("Success!!!\n"));
        CloseHandle( process_info.hProcess );
        CloseHandle( process_info.hThread );
    }
    else
    {
        fwprintf(f, _T("CreateProcessAsUser retval: '%d'\n"), GetLastError());
    }

    strBuffer = tstring(_T("\"")) + strInstallDirectory + tstring(_T("progressthruprocessors.exe\""));
    fwprintf(f, _T("Attempting to launch progressthruprocessors.exe\n"));
    fwprintf(f, _T("Launching: '%s'\n"), strBuffer.c_str());
    if (CreateProcessAsUser( hRestrictedToken, NULL, (LPWSTR)strBuffer.c_str(), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup_info, &process_info ))
    {
        fwprintf(f, _T("Success!!!\n"));
        CloseHandle( process_info.hProcess );
        CloseHandle( process_info.hThread );
    }
    else
    {
        fwprintf(f, _T("CreateProcessAsUser retval: '%d'\n"), GetLastError());
    }

    fclose(f);
    CloseHandle( hRestrictedToken );
    pSCLOSEL( hSaferHandle );
 
    return ERROR_SUCCESS;
}