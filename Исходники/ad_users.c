static
DWORD
UmnSrvUpdateADUser(
    PLW_EVENTLOG_CONNECTION pEventlog,
    HANDLE hReg,
    HKEY hUsers,
    long long PreviousRun,
    long long Now,
    PLSA_SECURITY_OBJECT pUser
    )
{
    DWORD dwError = 0;
    HKEY hKey = NULL;
    USER_MONITOR_PASSWD old = { 0 };
    DWORD dwNow = Now;
    PSTR pEncodedUser = NULL;

    dwError = LwURLEncodeString(
                    pUser->userInfo.pszUnixName,
                    &pEncodedUser);
    BAIL_ON_UMN_ERROR(dwError);

    dwError = RegOpenKeyExA(
                    hReg,
                    hUsers,
                    pEncodedUser,
                    0,
                    KEY_ALL_ACCESS,
                    &hKey);
    if (dwError == LWREG_ERROR_NO_SUCH_KEY_OR_VALUE)
    {
        UMN_LOG_INFO("Adding user '%s' (uid %d)",
                        pUser->userInfo.pszUnixName, pUser->userInfo.uid);

        dwError = RegCreateKeyExA(
                        hReg,
                        hUsers,
                        pEncodedUser,
                        0,
                        NULL,
                        0,
                        KEY_ALL_ACCESS,
                        NULL,
                        &hKey,
                        NULL);
        BAIL_ON_UMN_ERROR(dwError);

        dwError = UmnSrvWriteADUserValues(
                        hReg,
                        hKey,
                        pUser);
        if (dwError == ERROR_NO_UNICODE_TRANSLATION)
        {
            UMN_LOG_ERROR("Ignoring user with URL encoding %s because one of their fields has no UCS-2 representation", pEncodedUser);

            // Delete the key so it does not show up with blank values next
            // time.
            dwError = RegCloseKey(
                    hReg,
                    hKey);
            BAIL_ON_UMN_ERROR(dwError);
            hKey = NULL;

            dwError = RegDeleteKeyA(
                            hReg,
                            hUsers,
                            pEncodedUser);
            BAIL_ON_UMN_ERROR(dwError);

            dwError = ERROR_NO_UNICODE_TRANSLATION;
            BAIL_ON_UMN_ERROR(dwError);
        }
        BAIL_ON_UMN_ERROR(dwError);

        dwError = UmnSrvWriteADUserEvent(
                        pEventlog,
                        PreviousRun,
                        NULL,
                        Now,
                        pUser);
        BAIL_ON_UMN_ERROR(dwError);
    }
    else
    {
        BAIL_ON_UMN_ERROR(dwError);

        dwError = UmnSrvReadUser(
                        "AD Users",
                        pEncodedUser,
                        &old);
        BAIL_ON_UMN_ERROR(dwError);

        if (strcmp((pUser->userInfo.pszPasswd ?
                        pUser->userInfo.pszPasswd : "x"),
                    old.pw_passwd) ||
                pUser->userInfo.uid != old.pw_uid ||
                pUser->userInfo.gid != old.pw_gid ||
                !UmnSrvStringsEqual(pUser->userInfo.pszGecos, old.pw_gecos) ||
                !UmnSrvStringsEqual(pUser->userInfo.pszHomedir, old.pw_dir) ||
                !UmnSrvStringsEqual(pUser->userInfo.pszShell, old.pw_shell) ||
                !UmnSrvStringsEqual(pUser->userInfo.pszDisplayName,
                    old.pDisplayName))
        {
            UMN_LOG_INFO("User '%s' (uid %d) changed",
                            pUser->userInfo.pszUnixName, pUser->userInfo.uid);
            dwError = UmnSrvWriteADUserValues(
                            hReg,
                            hKey,
                            pUser);
            BAIL_ON_UMN_ERROR(dwError);

            dwError = UmnSrvWriteADUserEvent(
                            pEventlog,
                            PreviousRun,
                            &old,
                            Now,
                            pUser);
            BAIL_ON_UMN_ERROR(dwError);
        }
    }

    dwError = RegSetValueExA(
                    hReg,
                    hKey,
                    "LastUpdated",
                    0,
                    REG_DWORD,
                    (PBYTE)&dwNow,
                    sizeof(dwNow));
    BAIL_ON_UMN_ERROR(dwError);

cleanup:
    LW_SAFE_FREE_STRING(pEncodedUser);
    UmnSrvFreeUserContents(&old);
    if (hKey)
    {
        RegCloseKey(
                hReg,
                hKey);
    }
    return dwError;
    
error:
    goto cleanup;
}