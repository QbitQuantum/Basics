uint32 HeroChart::onMessage(uint32 message, uint32 wParam, uint32 lParam)
{
    switch (message)
    {
    case WM_ERASEBKGND:
    {
        HDC hDC = (HDC) wParam;
        SetBkColor(hDC, 0x000000);
        RECT rc;
        GetClientRect(hWnd, &rc);
        ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
    }
    return TRUE;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint(hWnd, &ps);

        HDC hBitmapDC = CreateCompatibleDC(hDC);

        SetBkColor(hDC, 0x000000);
        SetBkMode(hDC, OPAQUE);
        for (int i = 0; i < numTags; i++)
        {
            SelectObject(hDC, textTags[i].hFont);
            SetTextColor(hDC, textTags[i].color);
            RECT rc = textTags[i].rc;
            rc.top -= scrollPos;
            rc.bottom -= scrollPos;
            DrawText(hDC, textTags[i].text, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }

        ImageLibrary* ilib = getApp()->getImageLibrary();
        SelectObject(hDC, counterFont);
        SetTextColor(hDC, 0xFFFFFF);
        for (int i = 0; i < numTaverns; i++)
        {
            if (i == curTavern)
            {
                RECT rc = taverns[i].rc;
                rc.top -= scrollPos + 3;
                rc.bottom -= scrollPos - 3;
                rc.left -= 3;
                rc.right += 3;
                SetBkColor(hDC, taverns[i].color);
                ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
                SetBkColor(hDC, 0x000000);
                rc = taverns[i].rc;
                rc.top -= scrollPos;
                rc.bottom -= scrollPos;
                ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
            }
            for (int h = 0; h < 12; h++)
            {
                Dota::Hero* hero = taverns[i].heroes[h];
                if (hero)
                {
                    int x = taverns[i].rc.left + (32 + 2) * (h % 4);
                    int y = taverns[i].rc.top + (32 + 2) * (h / 4);
                    HBITMAP hBitmap = ilib->getBitmap(String::format("big%s", hero->icon));
                    if (hBitmap)
                    {
                        SelectObject(hBitmapDC, hBitmap);
                        BitBlt(hDC, x, y - scrollPos, 32, 32, hBitmapDC, 0, 0, SRCCOPY);
                        RECT tipRc = {x, y - scrollPos, x + 32, y + 32 - scrollPos};
                        DrawText(hDC, String::format(" %d ", heroCounter[hero->point]),
                                 -1, &tipRc, DT_SINGLELINE | DT_RIGHT | DT_BOTTOM);
                    }
                }
            }
        }

        DeleteDC(hBitmapDC);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_SIZE:
    {
        SCROLLINFO si;
        memset(&si, 0, sizeof si);
        si.cbSize = sizeof si;
        si.fMask = SIF_PAGE | SIF_RANGE | SIF_DISABLENOSCROLL;
        si.nPage = height();
        si.nMin = 0;
        si.nMax = contentHeight;
        SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        SetFocus(hWnd);
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam) + scrollPos;
        for (int i = 0; i < numTaverns; i++)
        {
            if (x >= taverns[i].rc.left && y >= taverns[i].rc.top &&
                    x < taverns[i].rc.right && y < taverns[i].rc.bottom)
            {
                if (curTavern >= 0)
                {
                    RECT rc = taverns[curTavern].rc;
                    rc.left -= 3;
                    rc.top -= scrollPos + 3;
                    rc.right += 3;
                    rc.bottom -= scrollPos - 3;
                    curTavern = i;
                    InvalidateRect(hWnd, &rc, TRUE);
                }
                curTavern = i;
                RECT rc = taverns[i].rc;
                rc.left -= 3;
                rc.top -= scrollPos + 3;
                rc.right += 3;
                rc.bottom -= scrollPos - 3;
                InvalidateRect(hWnd, &rc, TRUE);

                notify(WM_SETTAVERN, i, 0);

                int hx = (x - taverns[i].rc.left) / (32 + 2);
                int hy = (y - taverns[i].rc.top) / (32 + 2);
                int h = hx + hy * 4;
                if (h >= 0 && h < 12 && taverns[i].heroes[h])
                    notify(WM_SETHERO, taverns[i].heroes[h]->point, 0);

                break;
            }
        }
    }
    return 0;
    case WM_MOUSEWHEEL:
        doScroll(scrollPos - GET_WHEEL_DELTA_WPARAM(wParam) * 30 / WHEEL_DELTA);
        break;
    case WM_VSCROLL:
    {
        SCROLLINFO si;
        memset(&si, 0, sizeof si);
        si.cbSize = sizeof si;
        si.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_VERT, &si);
        switch (LOWORD(wParam))
        {
        case SB_TOP:
            si.nPos = si.nMin;
            break;
        case SB_BOTTOM:
            si.nPos = si.nMax;
            break;
        case SB_LINEUP:
            si.nPos--;
            break;
        case SB_LINEDOWN:
            si.nPos++;
            break;
        case SB_PAGEUP:
            si.nPos -= si.nPage;
            break;
        case SB_PAGEDOWN:
            si.nPos += si.nPage;
            break;
        case SB_THUMBTRACK:
            si.nPos = si.nTrackPos;
            break;
        }
        doScroll(si.nPos);
    }
    break;
    default:
        return M_UNHANDLED;
    }
    return 0;
}