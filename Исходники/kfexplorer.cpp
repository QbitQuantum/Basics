void AddRegisteredFolderToHistory(KNOWNFOLDERID kfid)
{
    HKEY hKey;
    DWORD dwDisp = 0;
    if (ERROR_SUCCESS == RegCreateKeyExW(HKEY_LOCAL_MACHINE, SZ_REG_PATH_HISTORY, 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp))
    {
        WCHAR szGuid[GUID_SIZE];
        StringFromGUID2(kfid, szGuid, ARRAYSIZE(szGuid));
        SHSetValueW(hKey, NULL, szGuid, REG_SZ, NULL, NULL);
        RegCloseKey(hKey);
    }
}