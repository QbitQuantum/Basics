int DlgDirSelectComboBoxExA(
    HWND hwndDlg,
    LPSTR pszOut,
    int cchOut,
    int idComboBox)
{
    LPWSTR lpwsz;
    BOOL fRet;

    lpwsz = (LPWSTR)UserLocalAlloc(HEAP_ZERO_MEMORY, cchOut * sizeof(WCHAR));
    if (!lpwsz) {
        return FALSE;
    }

    fRet = DlgDirSelectComboBoxExW(hwndDlg, lpwsz, cchOut, idComboBox);

    WCSToMB(lpwsz, -1, &pszOut, cchOut, FALSE);

    UserLocalFree(lpwsz);

    return fRet;
}