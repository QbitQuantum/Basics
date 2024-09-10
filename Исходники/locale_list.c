LOCALE_LIST_NODE*
LocaleList_Create(VOID)
{
    WCHAR szValue[MAX_PATH];
    DWORD dwIndex;
    DWORD dwSize;
    HKEY hKey;

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                      L"SYSTEM\\CurrentControlSet\\Control\\Nls\\Language",
                      0,
                      KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE,
                      &hKey) != ERROR_SUCCESS)
    {
        return NULL;
    }

    dwSize = sizeof(szValue);
    dwIndex = 0;

    while (RegEnumValueW(hKey, dwIndex, szValue, &dwSize,
                         NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        WCHAR szName[MAX_STR_LEN];
        DWORD dwId;

        dwId = DWORDfromString(szValue);

        if (GetLocaleInfoW(LOWORD(dwId),
                           LOCALE_SLANGUAGE,
                           szName, ARRAYSIZE(szName)))
        {
            LocaleList_Append(dwId, szName);
        }

        dwSize = sizeof(szValue);
        ++dwIndex;
    }

    return _LocaleList;
}