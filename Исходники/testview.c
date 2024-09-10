//---------------------------------------------------------------------------
// ViewportWndProc
//
// This is the window procedure for the ViewPort window.  It doesn't have to
// do all that much, as is obvious...
//
// RETURNS:     Per Windows convention
//---------------------------------------------------------------------------
LONG  APIENTRY ViewportWndProc (HWND hwnd, WORD msg,
                                 WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch (msg)
        {
        case WM_CREATE:
            {
            RECT    r;
            HMENU   hSysMenu;
            HANDLE  hScreen;

            // Here, we have to allocate memory for the "screen" memory and
            // clear it, and also set the "cursor" location and window size
            // and position monitors.  All this stuff is stored in the extra
            // bytes list of this viewport window.
            //---------------------------------------------------------------
            hScreen = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT,
                                   MAXLINES * (MAXLINELEN+1));
            if (!hScreen)
                return (-1);

            SetWindowLong (hwnd, GWW_MEMHANDLE, (UINT)hScreen);
            SetWindowLong (hwnd, GWW_CURSOR, (UINT)0);
            SetWindowLong (hwnd, GWW_COMECHO, (UINT)0);
            GetClientRect (hwnd, &r);
            SetWindowLong (hwnd, GWW_WINDOWY, (UINT)r.bottom);

            hSysMenu = GetSystemMenu (hwnd, 0);
            AppendMenu (hSysMenu, MF_SEPARATOR, 0, NULL);
            AppendMenu (hSysMenu, MF_STRING, IDM_CLEARVP, "C&lear");

            break;
            }

        case WM_SIZE:
            // Reset the WinY client-area variable to the new size
            //---------------------------------------------------------------
            SetWindowLong (hwnd, GWW_WINDOWY, (DWORD)HIWORD(lParam));
            break;

        case WM_GETMINMAXINFO:
            {
            POINT   FAR *rgpt = (LPPOINT)lParam;
            TEXTMETRIC tm;
            HDC     hDC;
            RECT    r;
            HFONT   hOldFont;
            INT     maxx, maxy, t;

            // This is where we tell windows how large/small the window can
            // be grown/shrunk/maximized, etc.
            //---------------------------------------------------------------
            hDC = GetDC (hwnd);
            hOldFont = SelectObject (hDC, GetStockObject (ANSI_FIXED_FONT));
            GetTextMetrics (hDC, &tm);
            SelectObject (hDC, hOldFont);
            ReleaseDC (hwnd, hDC);

            GetWindowRect (hwnd, &r);
            maxx = MAXLINELEN * (tm.tmMaxCharWidth);
            maxy = MAXLINES * (tm.tmHeight + tm.tmExternalLeading);
            rgpt[1].x = min((GetSystemMetrics(SM_CXFRAME)*2) + maxx,
                            rgpt[1].x);
            rgpt[1].y = min((GetSystemMetrics(SM_CYFRAME)*2) +
                            GetSystemMetrics(SM_CYCAPTION) + maxy,
                            rgpt[1].y);
            rgpt[2].x = min(r.left, GetSystemMetrics(SM_CXSCREEN)-rgpt[1].x);
            t = -GetSystemMetrics(SM_CXFRAME);
            if (rgpt[2].x < t)
                rgpt[2].x = t;
            rgpt[2].y = min(r.top, GetSystemMetrics(SM_CYSCREEN)-rgpt[1].y);
            t = -GetSystemMetrics(SM_CYFRAME);
            if (rgpt[2].y < t)
                rgpt[2].y = t;
            rgpt[4] = rgpt[1];
            break;
            }

        case WM_CLOSE:
            ShowWindow (hwnd, SW_HIDE);
            break;

        case WM_SYSCOMMAND:
            // Closing the viewport by the system menu is actually a "hide"
            //---------------------------------------------------------------
            if (wParam == SC_CLOSE)
                ShowWindow (hwnd, SW_HIDE);
            else if (wParam == IDM_CLEARVP)
                ClearViewport (hwnd);
            else
                return (DefWindowProc (hwnd, msg, wParam, lParam));
            break;

        case WM_DESTROY:
            // Deallocate the screen memory before we die!
            //---------------------------------------------------------------
            GlobalFree ((HANDLE)GetWindowLong (hwnd, GWW_MEMHANDLE));
            break;

        case WM_PAINT:
            {
            HFONT   hOldFont;

            // Refresh the client area ONLY IF not minimized
            //---------------------------------------------------------------
            if (IsIconic(hwnd))
                break;

            BeginPaint (hwnd, &ps);
            hOldFont = SelectObject(ps.hdc, GetStockObject(ANSI_FIXED_FONT));
            if (GetWindowLong (hwnd, GWW_WINDOWY) == CW_USEDEFAULT)
                {
                RECT    r;

                GetClientRect (hwnd, &r);
                SetWindowLong (hwnd, GWW_WINDOWY, (UINT)r.bottom);
                }
            PaintViewport (hwnd, &ps);
            SelectObject (ps.hdc, hOldFont);
            EndPaint (hwnd, &ps);
            break;
            }

        default:
            return (DefWindowProc (hwnd, msg, wParam, lParam));
        }
    return FALSE;
}