static BOOL
InputList_PrepareUserRegistry(VOID)
{
    BOOL bResult = FALSE;
    HKEY hTempKey = NULL;
    HKEY hKey = NULL;

    if (RegOpenKeyExW(HKEY_CURRENT_USER,
                      L"Keyboard Layout",
                      0,
                      KEY_ALL_ACCESS,
                      &hKey) == ERROR_SUCCESS)
    {
        RegDeleteKeyW(hKey, L"Preload");
        RegDeleteKeyW(hKey, L"Substitutes");

        RegCloseKey(hKey);
    }

    if (RegCreateKeyW(HKEY_CURRENT_USER, L"Keyboard Layout", &hKey) != ERROR_SUCCESS)
    {
        goto Cleanup;
    }

    if (RegCreateKeyW(hKey, L"Preload", &hTempKey) != ERROR_SUCCESS)
    {
        goto Cleanup;
    }

    RegCloseKey(hTempKey);

    if (RegCreateKeyW(hKey, L"Substitutes", &hTempKey) != ERROR_SUCCESS)
    {
        goto Cleanup;
    }

    RegCloseKey(hTempKey);

    bResult = TRUE;

Cleanup:
    if (hTempKey != NULL)
        RegCloseKey(hTempKey);
    if (hKey != NULL)
        RegCloseKey(hKey);

    return bResult;
}