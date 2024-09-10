BOOL
IsInstalledApplication(LPWSTR lpRegName, BOOL IsUserKey)
{
    DWORD dwSize = MAX_PATH, dwType;
    WCHAR szName[MAX_PATH];
    WCHAR szDisplayName[MAX_PATH];
    HKEY hKey, hSubKey;
    INT ItemIndex = 0;

    if (RegOpenKeyW(IsUserKey ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE,
                    L"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
                    &hKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    while (RegEnumKeyExW(hKey, ItemIndex, szName, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        if (RegOpenKeyW(hKey, szName, &hSubKey) == ERROR_SUCCESS)
        {
            dwType = REG_SZ;
            dwSize = MAX_PATH;
            if (RegQueryValueExW(hSubKey,
                                 L"DisplayName",
                                 NULL,
                                 &dwType,
                                 (LPBYTE)szDisplayName,
                                 &dwSize) == ERROR_SUCCESS)
            {
                if (wcscmp(szDisplayName, lpRegName) == 0)
                {
                    RegCloseKey(hSubKey);
                    RegCloseKey(hKey);
                    return TRUE;
                }
            }
        }

        RegCloseKey(hSubKey);
        dwSize = MAX_PATH;
        ItemIndex++;
    }

    RegCloseKey(hKey);
    return FALSE;
}