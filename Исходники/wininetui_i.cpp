BOOL SetCertDlgItem(HWND hDlg,
                    DWORD dwIconCtl,
                    DWORD dwTextCtl,
                    DWORD dwString,
                    BOOL  fError)
{
    ASSERT(hDlg);

    // Load small icon and set it
    HICON hicon = (HICON)LoadImageW(HINST_RESDLL,
                        MAKEINTRESOURCEW(fError ? IDI_WARN : IDI_SUCCESS),
                        IMAGE_ICON, AM_SM_CXSMICON, AM_SM_CYSMICON, 0);

    if(hicon)
    {
        HICON hiconOld = (HICON)SendDlgItemMessageW(hDlg,dwIconCtl,
                                STM_SETIMAGE,(WPARAM)IMAGE_ICON,
                                (LPARAM)hicon);

        if(hiconOld)
            DestroyIcon(hiconOld);
    }

    // The dialog displays the error string by default.  Replace this with the
    // success string if an error didn't occur.
    if(!fError)
    {
        WCHAR sz[512];
        if(LoadStringW(HINST_RESDLL,dwString,sz,ARRAYSIZE(sz)))
            SetDlgItemTextW(hDlg,dwTextCtl,sz);
    }
    return TRUE;
}