static void TipOfDay_DoPaint(HWND hwnd, HDC hdc, BOOL bUpdateTextOnly)
{
    RECT rcTip, rcSeperator, rcDidYou, rcBulb, rc = s_rcDraw;
    HBRUSH hBrush;
    HWND hwndStatic;
    HFONT hDidYouFont, hTipFont, hOldFont;
    TCHAR szDidYou[32];
    HANDLE hOldHandle;
    COLORREF crOldBackground;

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

    hwndStatic = GetDlgItem(hwnd, IDC_TXT_TIPSTRING);
    GetWindowRect(hwndStatic, &rcTip);
    Window_ScreenToClientRect(hwnd, &rcTip);

    hwndStatic = GetDlgItem(hwnd, IDC_BMP_BULB);
    GetWindowRect(hwndStatic, &rcBulb);

    crOldBackground = SetBkColor(hdc, GetSysColor(COLOR_WINDOW));

    if (!bUpdateTextOnly)
    {
        HBRUSH hBrushShadow = CreateSolidBrush(GetSysColor(COLOR_BTNSHADOW));
        HBRUSH hOldBrush;
        HDC hdcMem;
        HBITMAP hOldBitmap;
        BITMAP bm;

        Paint_Draw3DRect(hdc, &rc, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNSHADOW), 1);
        InflateRect(&rc, -1, -1);
        Paint_FillRect(hdc, &rc, GetSysColor(COLOR_WINDOW));
        
        rcSeperator = rc;

        rc.right = rcTip.left - 10;
        Paint_FillRect(hdc, &rc, GetSysColor(COLOR_BTNSHADOW));

        GetObject(s_hBulbBitmap, sizeof(BITMAP), &bm);

        Window_ScreenToClientRect(hwnd, &rcBulb);
        hdcMem = CreateCompatibleDC(hdc);
        hOldBitmap      = SelectObject(hdcMem, s_hBulbBitmap);
        rcBulb.bottom   = rcBulb.top + bm.bmHeight;
        rcBulb.right    = rcBulb.left + bm.bmWidth;
        hOldBrush       = SelectObject(hdcMem, hBrushShadow);
        ExtFloodFill(hdcMem, 0, 0, RGB(255, 255, 255), FLOODFILLSURFACE);
        BitBlt(hdc, rcBulb.left, rcBulb.top, Rect_Width(&rcBulb), Rect_Height(&rcBulb),
                hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hOldBitmap);
        DeleteObject(SelectObject(hdcMem, hOldBrush));
        DeleteDC(hdcMem);

        rcSeperator.top     = rcBulb.bottom + 6;
        rcSeperator.bottom  = rcSeperator.top + 1;

        Paint_FillRect(hdc, &rcSeperator, GetSysColor(COLOR_BTNSHADOW));
    }

    hDidYouFont = CreateFont(22, 0, 0, 0, FW_BOLD, 0, 0, 0,
                            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_SWISS, _T("Times"));

    hTipFont    = CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0,
                            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_SWISS, _T("Arial"));

    hOldFont = SelectObject(hdc, hDidYouFont);
    hOldHandle = String_SetResourceHandle(PCPControls_GetHandle());
    _tcsncpy(szDidYou, String_LoadString(IDS_TIP_DIDYOU), sizeof(szDidYou));
    String_SetResourceHandle(hOldHandle);
    rcDidYou        = rcTip;
    rcDidYou.top    = rcBulb.top;
    DrawText(hdc, szDidYou, -1, &rcDidYou, DT_SINGLELINE);

    SelectObject(hdc, hTipFont);
    Paint_FillRect(hdc, &rcTip, GetSysColor(COLOR_WINDOW));
    DrawText(hdc, s_szCurrentTip, -1, &rcTip, DT_WORDBREAK);
    SelectObject(hdc, hOldFont);
    SetBkColor(hdc, crOldBackground);
    DeleteObject(hDidYouFont);
    DeleteObject(hTipFont);
}