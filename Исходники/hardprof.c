static
BOOL
GetProfileCount(LPDWORD lpProfileCount)
{
    HKEY hKey;
    LONG lError;

    *lpProfileCount = 0;

    lError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                           L"System\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles",
                           0,
                           KEY_READ,
                           &hKey);
    if (lError != ERROR_SUCCESS)
        return FALSE;

    lError = RegQueryInfoKeyW(hKey, NULL, NULL, NULL, lpProfileCount,
                              NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    RegCloseKey(hKey);

    if (lError != ERROR_SUCCESS)
        return FALSE;

    return TRUE;
}