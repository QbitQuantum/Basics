BOOL
WINAPI
LoadUserProfileW(IN HANDLE hToken,
                 IN OUT LPPROFILEINFOW lpProfileInfo)
{
    WCHAR szUserHivePath[MAX_PATH];
    LPWSTR UserName = NULL, Domain = NULL;
    DWORD UserNameLength = 0, DomainLength = 0;
    PTOKEN_USER UserSid = NULL;
    SID_NAME_USE AccountType;
    UNICODE_STRING SidString = { 0, 0, NULL };
    LONG Error;
    BOOL ret = FALSE;
    DWORD dwLength = sizeof(szUserHivePath) / sizeof(szUserHivePath[0]);

    DPRINT("LoadUserProfileW() called\n");

    /* Check profile info */
    if (!lpProfileInfo || (lpProfileInfo->dwSize != sizeof(PROFILEINFOW)) ||
        (lpProfileInfo->lpUserName == NULL) || (lpProfileInfo->lpUserName[0] == 0))
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    /* Don't load a profile twice */
    if (CheckForLoadedProfile(hToken))
    {
        DPRINT ("Profile already loaded\n");
        lpProfileInfo->hProfile = NULL;
        return TRUE;
    }

    if (lpProfileInfo->lpProfilePath)
    {
        wcscpy(szUserHivePath, lpProfileInfo->lpProfilePath);
    }
    else
    {
        /* FIXME: check if MS Windows allows lpProfileInfo->lpProfilePath to be NULL */
        if (!GetProfilesDirectoryW(szUserHivePath, &dwLength))
        {
            DPRINT1("GetProfilesDirectoryW() failed (error %ld)\n", GetLastError());
            return FALSE;
        }
    }

    /* Create user hive name */
    wcscat(szUserHivePath, L"\\");
    wcscat(szUserHivePath, lpProfileInfo->lpUserName);
    wcscat(szUserHivePath, L"\\ntuser.dat");
    DPRINT("szUserHivePath: %S\n", szUserHivePath);

    /* Create user profile directory if needed */
    if (GetFileAttributesW(szUserHivePath) == INVALID_FILE_ATTRIBUTES)
    {
        /* Get user sid */
        if (GetTokenInformation(hToken, TokenUser, NULL, 0, &dwLength) ||
            GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
            DPRINT1 ("GetTokenInformation() failed\n");
            return FALSE;
        }

        UserSid = (PTOKEN_USER)HeapAlloc(GetProcessHeap(), 0, dwLength);
        if (!UserSid)
        {
            DPRINT1("HeapAlloc() failed\n");
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            goto cleanup;
        }

        if (!GetTokenInformation(hToken, TokenUser, UserSid, dwLength, &dwLength))
        {
            DPRINT1("GetTokenInformation() failed\n");
            goto cleanup;
        }

        /* Get user name */
        do
        {
            if (UserNameLength > 0)
            {
                HeapFree(GetProcessHeap(), 0, UserName);
                UserName = (LPWSTR)HeapAlloc(GetProcessHeap(), 0, UserNameLength * sizeof(WCHAR));
                if (!UserName)
                {
                    DPRINT1("HeapAlloc() failed\n");
                    SetLastError(ERROR_NOT_ENOUGH_MEMORY);
                    goto cleanup;
                }
            }
            if (DomainLength > 0)
            {
                HeapFree(GetProcessHeap(), 0, Domain);
                Domain = (LPWSTR)HeapAlloc(GetProcessHeap(), 0, DomainLength * sizeof(WCHAR));
                if (!Domain)
                {
                    DPRINT1("HeapAlloc() failed\n");
                    SetLastError(ERROR_NOT_ENOUGH_MEMORY);
                    goto cleanup;
                }
            }
            ret = LookupAccountSidW(NULL,
                                    UserSid->User.Sid,
                                    UserName,
                                    &UserNameLength,
                                    Domain,
                                    &DomainLength,
                                    &AccountType);
        } while (!ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER);

        if (!ret)
        {
            DPRINT1("LookupAccountSidW() failed\n");
            goto cleanup;
        }

        /* Create profile */
        /* FIXME: ignore Domain? */
        DPRINT("UserName %S, Domain %S\n", UserName, Domain);
        ret = CreateUserProfileW(UserSid->User.Sid, UserName);
        if (!ret)
        {
            DPRINT1("CreateUserProfileW() failed\n");
            goto cleanup;
        }
    }

    /* Get user SID string */
    ret = GetUserSidFromToken(hToken, &SidString);
    if (!ret)
    {
        DPRINT1("GetUserSidFromToken() failed\n");
        goto cleanup;
    }
    ret = FALSE;

    /* Acquire restore privilege */
    if (!AcquireRemoveRestorePrivilege(TRUE))
    {
        DPRINT1("AcquireRemoveRestorePrivilege() failed (Error %ld)\n", GetLastError());
        goto cleanup;
    }

    /* Load user registry hive */
    Error = RegLoadKeyW(HKEY_USERS,
                        SidString.Buffer,
                        szUserHivePath);
    AcquireRemoveRestorePrivilege(FALSE);
    if (Error != ERROR_SUCCESS)
    {
        DPRINT1("RegLoadKeyW() failed (Error %ld)\n", Error);
        SetLastError((DWORD)Error);
        goto cleanup;
    }

    /* Open future HKEY_CURRENT_USER */
    Error = RegOpenKeyExW(HKEY_USERS,
                          SidString.Buffer,
                          0,
                          MAXIMUM_ALLOWED,
                          (PHKEY)&lpProfileInfo->hProfile);
    if (Error != ERROR_SUCCESS)
    {
        DPRINT1("RegOpenKeyExW() failed (Error %ld)\n", Error);
        SetLastError((DWORD)Error);
        goto cleanup;
    }

    ret = TRUE;

cleanup:
    HeapFree(GetProcessHeap(), 0, UserSid);
    HeapFree(GetProcessHeap(), 0, UserName);
    HeapFree(GetProcessHeap(), 0, Domain);
    RtlFreeUnicodeString(&SidString);

    DPRINT("LoadUserProfileW() done\n");
    return ret;
}