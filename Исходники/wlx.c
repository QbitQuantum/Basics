static
BOOL
GetGinaPath(
    OUT LPWSTR Path,
    IN DWORD Len)
{
    LONG Status;
    DWORD Type, Size;
    HKEY hKey;

    Status = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon",
        0,
        KEY_QUERY_VALUE,
        &hKey);
    if (Status != ERROR_SUCCESS)
    {
        /* Default value */
        wcsncpy(Path, L"msgina.dll", Len);
        return TRUE;
    }

    Size = Len * sizeof(WCHAR);
    Status = RegQueryValueExW(
        hKey,
        L"GinaDLL",
        NULL,
        &Type,
        (LPBYTE)Path,
        &Size);
    if (Status != ERROR_SUCCESS || Type != REG_SZ || Size == 0)
        wcsncpy(Path, L"msgina.dll", Len);
    RegCloseKey(hKey);
    return TRUE;
}