static
HFONT
SetLrgFont(PMAP infoPtr)
{
    LOGFONTW lf;
    HFONT hFont = NULL;
    HDC hdc;
    HWND hCombo;
    LPWSTR lpFontName;
    INT Len;

    hCombo = GetDlgItem(infoPtr->hParent,
                        IDC_FONTCOMBO);

    Len = GetWindowTextLengthW(hCombo);

    if (Len != 0)
    {
        lpFontName = HeapAlloc(GetProcessHeap(),
                               0,
                               (Len + 1) * sizeof(WCHAR));

        if (lpFontName)
        {
            SendMessageW(hCombo,
                         WM_GETTEXT,
                         Len + 1,
                         (LPARAM)lpFontName);

            ZeroMemory(&lf,
                       sizeof(lf));

            hdc = GetDC(infoPtr->hLrgWnd);
            lf.lfHeight = GetDeviceCaps(hdc,
                                        LOGPIXELSY) / 2;
            ReleaseDC(infoPtr->hLrgWnd,
                      hdc);

            lf.lfCharSet =  DEFAULT_CHARSET;
            wcsncpy(lf.lfFaceName,
                    lpFontName,
                    sizeof(lf.lfFaceName) / sizeof(lf.lfFaceName[0]));

            hFont = CreateFontIndirectW(&lf);

            HeapFree(GetProcessHeap(),
                     0,
                     lpFontName);
        }
    }

    return hFont;
}