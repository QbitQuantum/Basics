DWORD CALLBACK AboutBoxProc(HWND hWnd, DWORD uMsg, DWORD wParam, DWORD lParam)
{
    static HBITMAP hbmpBackgroundTop = NULL;
    static HFONT   hPageHeadingFont = NULL;
    static HFONT   hTextFont = NULL;
    static HFONT   hAuthorFont = NULL;

    switch (uMsg) {
    case WM_INITDIALOG:
    {
        //Title
        SetWindowTextW(hWnd, wGS(PLUG_ABOUT).c_str());

        // Use the size of the image
        hbmpBackgroundTop = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ABOUT_LOGO));

        BITMAP bmTL;
        GetObject(hbmpBackgroundTop, sizeof(BITMAP), &bmTL);

        hTextFont = ::CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
        hAuthorFont = ::CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");

        hPageHeadingFont = ::CreateFont(24, 0, 0, 0, FW_BOLD, 0, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Bold");

        SendDlgItemMessage(hWnd, IDC_VERSION, WM_SETFONT, (WPARAM)hTextFont, TRUE);
        SendDlgItemMessage(hWnd, IDC_TEAM, WM_SETFONT, (WPARAM)hPageHeadingFont, TRUE);
        SendDlgItemMessage(hWnd, IDC_THANKS, WM_SETFONT, (WPARAM)hPageHeadingFont, TRUE);

        SendDlgItemMessage(hWnd, IDC_ZILMAR, WM_SETFONT, (WPARAM)hAuthorFont, TRUE);
        SendDlgItemMessage(hWnd, IDC_JABO, WM_SETFONT, (WPARAM)hAuthorFont, TRUE);
        SendDlgItemMessage(hWnd, IDC_SMIFF, WM_SETFONT, (WPARAM)hAuthorFont, TRUE);
        SendDlgItemMessage(hWnd, IDC_GENT, WM_SETFONT, (WPARAM)hAuthorFont, TRUE);

        SendDlgItemMessage(hWnd, IDC_ZILMAR_DETAILS, WM_SETFONT, (WPARAM)hTextFont, TRUE);
        SendDlgItemMessage(hWnd, IDC_JABO_DETAILS, WM_SETFONT, (WPARAM)hTextFont, TRUE);
        SendDlgItemMessage(hWnd, IDC_SMIFF_DETAILS, WM_SETFONT, (WPARAM)hTextFont, TRUE);
        SendDlgItemMessage(hWnd, IDC_GENT_DETAILS, WM_SETFONT, (WPARAM)hTextFont, TRUE);

        SendDlgItemMessage(hWnd, IDC_THANK_LIST, WM_SETFONT, (WPARAM)hTextFont, TRUE);

        stdstr_f VersionDisplay("Version: %s", VER_FILE_VERSION_STR);
        SetWindowText(GetDlgItem(hWnd, IDC_VERSION), VersionDisplay.c_str());
    }
    break;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LONG)(LRESULT)((HBRUSH)GetStockObject(NULL_BRUSH));
    }
    break;
    case WM_ERASEBKGND:
    {
        HPEN outline;
        HBRUSH fill;
        RECT rect;

        outline = CreatePen(PS_SOLID, 1, 0x00FFFFFF);
        fill = CreateSolidBrush(0x00FFFFFF);
        SelectObject((HDC)wParam, outline);
        SelectObject((HDC)wParam, fill);

        GetClientRect(hWnd, &rect);

        Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        if (BeginPaint(hWnd, &ps))
        {
            RECT rcClient;
            GetClientRect(hWnd, &rcClient);

            BITMAP bmTL_top;
            GetObject(hbmpBackgroundTop, sizeof(BITMAP), &bmTL_top);

            HDC     memdc = CreateCompatibleDC(ps.hdc);
            HGDIOBJ save = SelectObject(memdc, hbmpBackgroundTop);
            BitBlt(ps.hdc, 0, 0, bmTL_top.bmWidth, bmTL_top.bmHeight, memdc, 0, 0, SRCCOPY);
            SelectObject(memdc, save);
            DeleteDC(memdc);

            EndPaint(hWnd, &ps);
        }
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
            if (hbmpBackgroundTop)
            {
                DeleteObject(hbmpBackgroundTop);
            }
            if (hTextFont)
            {
                ::DeleteObject(hTextFont);
            }
            if (hPageHeadingFont)
            {
                ::DeleteObject(hPageHeadingFont);
            }
            if (hAuthorFont)
            {
                ::DeleteObject(hAuthorFont);
            }
            //ReleaseCapture();
            EndDialog(hWnd, 0);
            break;
        }
    default:
        return FALSE;
    }
    return TRUE;
}