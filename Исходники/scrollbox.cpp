LRESULT CALLBACK
ScrollboxWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_SIZE:
            if (hwnd == hScrollbox)
            {
                UpdateScrollbox();
            }
            break;
        case WM_HSCROLL:
            if (hwnd == hScrollbox)
            {
                SCROLLINFO si;
                si.cbSize = sizeof(SCROLLINFO);
                si.fMask = SIF_ALL;
                GetScrollInfo(hScrollbox, SB_HORZ, &si);
                switch (LOWORD(wParam))
                {
                    case SB_THUMBTRACK:
                    case SB_THUMBPOSITION:
                        si.nPos = HIWORD(wParam);
                        break;
                    case SB_LINELEFT:
                        si.nPos -= 5;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 5;
                        break;
                    case SB_PAGELEFT:
                        si.nPos -= si.nPage;
                        break;
                    case SB_PAGERIGHT:
                        si.nPos += si.nPage;
                        break;
                }
                SetScrollInfo(hScrollbox, SB_HORZ, &si, TRUE);
                MoveWindow(hScrlClient, -GetScrollPos(hScrollbox, SB_HORZ),
                           -GetScrollPos(hScrollbox, SB_VERT), imgXRes * zoom / 1000 + 6,
                           imgYRes * zoom / 1000 + 6, TRUE);
            }
            break;

        case WM_VSCROLL:
            if (hwnd == hScrollbox)
            {
                SCROLLINFO si;
                si.cbSize = sizeof(SCROLLINFO);
                si.fMask = SIF_ALL;
                GetScrollInfo(hScrollbox, SB_VERT, &si);
                switch (LOWORD(wParam))
                {
                    case SB_THUMBTRACK:
                    case SB_THUMBPOSITION:
                        si.nPos = HIWORD(wParam);
                        break;
                    case SB_LINEUP:
                        si.nPos -= 5;
                        break;
                    case SB_LINEDOWN:
                        si.nPos += 5;
                        break;
                    case SB_PAGEUP:
                        si.nPos -= si.nPage;
                        break;
                    case SB_PAGEDOWN:
                        si.nPos += si.nPage;
                        break;
                }
                SetScrollInfo(hScrollbox, SB_VERT, &si, TRUE);
                MoveWindow(hScrlClient, -GetScrollPos(hScrollbox, SB_HORZ),
                           -GetScrollPos(hScrollbox, SB_VERT), imgXRes * zoom / 1000 + 6,
                           imgYRes * zoom / 1000 + 6, TRUE);
            }
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}