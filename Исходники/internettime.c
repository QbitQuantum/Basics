static VOID
CreateNTPServerList(HWND hwnd)
{
    HWND hList;
    WCHAR szValName[MAX_VALUE_NAME];
    WCHAR szData[256];
    DWORD dwIndex = 0;
    DWORD dwValSize;
    DWORD dwNameSize;
    DWORD dwDefault = 1;
    LONG lRet;
    HKEY hKey;

    hList = GetDlgItem(hwnd,
                       IDC_SERVERLIST);

    lRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DateTime\\Servers",
                        0,
                        KEY_QUERY_VALUE,
                        &hKey);
    if (lRet != ERROR_SUCCESS)
        return;

    while (TRUE)
    {
        dwValSize = MAX_VALUE_NAME * sizeof(WCHAR);
        szValName[0] = L'\0';
        lRet = RegEnumValueW(hKey,
                             dwIndex,
                             szValName,
                             &dwValSize,
                             NULL,
                             NULL,
                             (LPBYTE)szData,
                             &dwNameSize);
        if (lRet == ERROR_SUCCESS)
        {
            /* Get date from default reg value */
            if (wcscmp(szValName, L"") == 0) // if (Index == 0)
            {
                dwDefault = _wtoi(szData);
                dwIndex++;
            }
            else
            {
                SendMessageW(hList,
                             CB_ADDSTRING,
                             0,
                             (LPARAM)szData);
                dwIndex++;
            }
        }
        else if (lRet != ERROR_MORE_DATA)
        {
            break;
        }
    }

    if (dwDefault < 1 || dwDefault > dwIndex)
        dwDefault = 1;

    /* Server reg entries count from 1,
     * Combo boxes count from 0 */
    dwDefault--;

    SendMessageW(hList,
                 CB_SETCURSEL,
                 dwDefault,
                 0);

    RegCloseKey(hKey);
}