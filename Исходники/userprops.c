static BOOL
SetUserGeneralData(HWND hwndDlg,
                   PGENERAL_USER_DATA pUserData)
{
    PUSER_INFO_3 pUserInfo = NULL;
    LPTSTR pszFullName = NULL;
    LPTSTR pszComment = NULL;
    NET_API_STATUS status;
    DWORD dwIndex;
    INT nLength;

    NetUserGetInfo(NULL, pUserData->szUserName, 3, (LPBYTE*)&pUserInfo);

    pUserInfo->usri3_flags =
        (pUserData->dwFlags & VALID_GENERAL_FLAGS) |
        (pUserInfo->usri3_flags & ~VALID_GENERAL_FLAGS);

    pUserInfo->usri3_password_expired = pUserData->dwPasswordExpired;

    nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_USER_GENERAL_FULL_NAME));
    if (nLength == 0)
    {
        pUserInfo->usri3_full_name = NULL;
    }
    else
    {
        pszFullName = HeapAlloc(GetProcessHeap(), 0, (nLength + 1) * sizeof(TCHAR));
        GetDlgItemText(hwndDlg, IDC_USER_GENERAL_FULL_NAME, pszFullName, nLength + 1);
        pUserInfo->usri3_full_name = pszFullName;
    }

    nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_USER_GENERAL_DESCRIPTION));
    if (nLength == 0)
    {
        pUserInfo->usri3_full_name = NULL;
    }
    else
    {
        pszComment = HeapAlloc(GetProcessHeap(), 0, (nLength + 1) * sizeof(TCHAR));
        GetDlgItemText(hwndDlg, IDC_USER_GENERAL_DESCRIPTION, pszComment, nLength + 1);
        pUserInfo->usri3_comment = pszComment;
    }

    status = NetUserSetInfo(NULL, pUserData->szUserName, 3, (LPBYTE)pUserInfo, &dwIndex);
    if (status != NERR_Success)
    {
        DebugPrintf(_T("Status: %lu  Index: %lu"), status, dwIndex);
    }

    if (pszFullName)
        HeapFree(GetProcessHeap(), 0, pszFullName);

    if (pszComment)
        HeapFree(GetProcessHeap(), 0, pszComment);

    NetApiBufferFree(pUserInfo);

    return (status == NERR_Success);
}