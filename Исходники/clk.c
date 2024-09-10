LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hDC, hGenDC;
    HBRUSH hBrush;
    BOOL bNeedsMovement;
    const long SROLLUP = 120;
    const long SROLLDOWN = 65416;
    COLORREF crRandom;

    switch(nMsg)
    {
    case WM_CTLCOLORSTATIC:
        hGenDC = (HDC) wParam;
        SetTextColor(hGenDC, RGB(0, 0xFF, 0xFF));
        SetBkColor(hGenDC, crWndColor);
        hBrush = CreateSolidBrush(crWndColor);
        return (INT_PTR)hBrush;

    case WM_CLOSE:
        ReleaseDC(hLblHelp, hGenDC);
        DeleteObject(hBrush);
        KillTimer(hWnd, nIDTmr);
        DestroyWindow(hWnd);
        PostQuitMessage(0);
        return TRUE;

    case WM_SETCURSOR:
        if(wParam == (WPARAM)hLblHelp)
            SetCursor(LoadCursor(NULL, IDC_HAND));
        else
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        return TRUE;

    case WM_COMMAND:
    {
        if((HWND)lParam == hLblHelp)
            DialogBox(NULL, MAKEINTRESOURCE(IDD_DLG), hWnd, DlgProc);
        return TRUE;
    }
    case WM_KEYDOWN:
    {
        bNeedsMovement = FALSE;
        if(wParam == VK_X && (GetKeyState(VK_CONTROL ) & 8000))
        {
            ReleaseDC(hLblHelp, hGenDC);
            DeleteObject(hBrush);
            //KillTimer(hWnd, nIDTmr);
            DestroyWindow(hWnd);
            PostQuitMessage(0);
            return TRUE;
        }
        if(wParam == VK_UP && (GetKeyState(VK_CONTROL ) & 8000))
        {
            POSY = POSY > -1 ? POSY - 1 : POSY;
            bNeedsMovement = TRUE;
        }
        if(wParam == VK_DOWN && (GetKeyState(VK_CONTROL ) & 8000))
        {
            POSY = POSY < 1 ? POSY + 1 : POSY;
            bNeedsMovement = TRUE;
        }
        if(wParam == VK_LEFT && (GetKeyState(VK_CONTROL ) & 8000))
        {
            POSX = POSX > -1 ? POSX - 1 : POSX;
            bNeedsMovement = TRUE;
        }
        if(wParam == VK_RIGHT && (GetKeyState(VK_CONTROL ) & 8000))
        {
            POSX = POSX < 1 ? POSX + 1 : POSX;
            bNeedsMovement = TRUE;
        }
        if(GetKeyState(VK_LCONTROL ) & 8000 && (wParam > 48 && wParam < 58))
        {
            crDigitColor = PRESETS[(long)wParam - 49];
            crColonColor = PRESETS[(long)wParam - 49];
            fnParseTime(hWnd);
        }
        if(GetKeyState(VK_RCONTROL ) & 8000 && (wParam > 48 && wParam < 58))
        {
            crColonColor = PRESETS[(long)wParam - 49];
            fnParseTime(hWnd);
        }

        if(GetKeyState(VK_LCONTROL ) & 8000 && wParam == VK_0)
        {
            crRandom = RGB(fnRandom(255), fnRandom(255), fnRandom(255));
            crDigitColor = crRandom;
            crColonColor = crRandom;
            fnParseTime(hWnd);
        }
        if(GetKeyState(VK_RCONTROL ) & 8000 && wParam == VK_0)
        {
            crColonColor = RGB(fnRandom(255), fnRandom(255), fnRandom(255));
            fnParseTime(hWnd);
        }
        if(GetKeyState(VK_CONTROL ) & 8000 && wParam == VK_H)
        {
            HELP = !HELP;
            if(HELP)
                ShowWindow(hLblHelp, SW_SHOWNORMAL);
            else
                ShowWindow(hLblHelp, SW_HIDE);
        }
        if(bNeedsMovement) fnMoveWnd(hWnd);
        return TRUE;
    }
    case WM_MOUSEWHEEL:
    {
        if((long)HIWORD(wParam) == SROLLUP && (GetKeyState(VK_CONTROL ) & 8000))
            if(lOpacity < 255)
            {
                lOpacity += 5;
                SetLayeredWindowAttributes(hWnd, crWndColor, lOpacity, LWA_ALPHA);
            }
        if((long)HIWORD(wParam) == SROLLDOWN && (GetKeyState(VK_CONTROL ) & 8000))
            if(lOpacity > 20)
            {
                lOpacity -= 5;
                SetLayeredWindowAttributes(hWnd, crWndColor, lOpacity, LWA_ALPHA);
            }
        return TRUE;
    }
    case WM_MBUTTONDOWN:
    {
        if(GetKeyState(VK_CONTROL ) & 8000)
        {
            lOpacity = 255;
            MASKED = !MASKED;
            if(MASKED)
                SetLayeredWindowAttributes(hWnd, crWndColor, lOpacity, LWA_COLORKEY);
            else
                SetLayeredWindowAttributes(hWnd, crWndColor, lOpacity, LWA_ALPHA);
        }
        return TRUE;
    }
    case WM_TIMER:
    {
        return TRUE;
    }

    }
    return DefWindowProc(hWnd, nMsg, wParam, lParam);
}