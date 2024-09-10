LRESULT CWindow::OnVScroll(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SCROLLINFO si;

    si.cbSize = sizeof(si);
    si.fMask  = SIF_ALL;
    GetScrollInfo(hWnd, SB_VERT, &si);

    switch (LOWORD(wParam))
    {
    case SB_THUMBTRACK:
    case SB_THUMBPOSITION:
        si.nPos = HIWORD(wParam);
        break;

    case SB_PAGEDOWN:
        si.nPos += si.nPage;
        break;

    case SB_PAGEUP:
        si.nPos -= si.nPage;
        break;

    case SB_LINEUP:
        --si.nPos;
        break;

    case SB_LINEDOWN:
        ++si.nPos;
        break;
    }

    si.fMask = SIF_POS;
    SetScrollInfo(hWnd, SB_VERT, &si, True);
    GetScrollInfo(hWnd, SB_VERT, &si);
    if (iVScrollPos != si.nPos)
    {
        ScrollWindow(hWnd, 0, cyChar * (iVScrollPos - si.nPos), NULL, NULL);
        iVScrollPos = si.nPos;
        UpdateWindow(hWnd);
    }

    return ERROR_SUCCESS;
}