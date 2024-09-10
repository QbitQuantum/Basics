DWORD
WINAPI
PlayLogonSoundThread(
    IN LPVOID lpParameter)
{
    BYTE TokenUserBuffer[256];
    PTOKEN_USER pTokenUser = (TOKEN_USER*)TokenUserBuffer;
    ULONG Length;
    HKEY hKey;
    WCHAR wszBuffer[MAX_PATH] = {0};
    WCHAR wszDest[MAX_PATH];
    DWORD dwSize = sizeof(wszBuffer), dwType;
    SERVICE_STATUS_PROCESS Info;
    UNICODE_STRING SidString;
    NTSTATUS Status;
    ULONG Index = 0;
    SC_HANDLE hSCManager, hService;

    //
    // FIXME: Isn't it possible to *JUST* impersonate the current user
    // *AND* open its HKCU??
    //

    /* Get SID of current user */
    Status = NtQueryInformationToken((HANDLE)lpParameter,
                                     TokenUser,
                                     TokenUserBuffer,
                                     sizeof(TokenUserBuffer),
                                     &Length);
    if (!NT_SUCCESS(Status))
    {
        ERR("NtQueryInformationToken failed: %x!\n", Status);
        return 0;
    }

    /* Convert SID to string */
    RtlInitEmptyUnicodeString(&SidString, wszBuffer, sizeof(wszBuffer));
    Status = RtlConvertSidToUnicodeString(&SidString, pTokenUser->User.Sid, FALSE);
    if (!NT_SUCCESS(Status))
    {
        ERR("RtlConvertSidToUnicodeString failed: %x!\n", Status);
        return 0;
    }

    /* Build path to logon sound registry key.
       Note: We can't use HKCU here, because Winlogon is owned by SYSTEM user */
    if (FAILED(StringCbCopyW(wszBuffer + SidString.Length/sizeof(WCHAR),
                             sizeof(wszBuffer) - SidString.Length,
                             L"\\AppEvents\\Schemes\\Apps\\.Default\\WindowsLogon\\.Current")))
    {
        /* SID is too long. Should not happen. */
        ERR("StringCbCopyW failed!\n");
        return 0;
    }

    /* Open registry key and query sound path */
    if (RegOpenKeyExW(HKEY_USERS, wszBuffer, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        ERR("RegOpenKeyExW(%ls) failed!\n", wszBuffer);
        return 0;
    }

    if (RegQueryValueExW(hKey, NULL, NULL, &dwType,
                      (LPBYTE)wszBuffer, &dwSize) != ERROR_SUCCESS ||
        (dwType != REG_SZ && dwType != REG_EXPAND_SZ))
    {
        ERR("RegQueryValueExW failed!\n");
        RegCloseKey(hKey);
        return 0;
    }

    RegCloseKey(hKey);

    if (!wszBuffer[0])
    {
        /* No sound has been set */
        ERR("No sound has been set\n");
        return 0;
    }

    /* Expand environment variables */
    if (!ExpandEnvironmentStringsW(wszBuffer, wszDest, MAX_PATH))
    {
        ERR("ExpandEnvironmentStringsW failed!\n");
        return 0;
    }

    /* Open the service manager */
    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager)
    {
        ERR("OpenSCManager failed (%x)\n", GetLastError());
        return 0;
    }

    /* Open the wdmaud service */
    hService = OpenServiceW(hSCManager, L"wdmaud", GENERIC_READ);
    if (!hService)
    {
        /* The service is not installed */
        TRACE("Failed to open wdmaud service (%x)\n", GetLastError());
        CloseServiceHandle(hSCManager);
        return 0;
    }

    /* Wait for wdmaud to start */
    do
    {
        if (!QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&Info, sizeof(SERVICE_STATUS_PROCESS), &dwSize))
        {
            TRACE("QueryServiceStatusEx failed (%x)\n", GetLastError());
            break;
        }

        if (Info.dwCurrentState == SERVICE_RUNNING)
            break;

        Sleep(1000);

    } while (Index++ < 20);

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    /* If wdmaud is not running exit */
    if (Info.dwCurrentState != SERVICE_RUNNING)
    {
        WARN("wdmaud has not started!\n");
        return 0;
    }

    /* Sound subsystem is running. Play logon sound. */
    TRACE("Playing logon sound: %ls\n", wszDest);
    PlaySoundRoutine(wszDest, TRUE, SND_FILENAME);
    return 0;
}