UINT ExecutionLogWindow::GetTrackPos(HWND hwnd, int fnBar)
{
    SCROLLINFO si;
    si.cbSize = sizeof(si);
    si.fMask = SIF_TRACKPOS;
    if (GetScrollInfo(hwnd, fnBar, &si)) {
        return si.nTrackPos;
    }
    return 0;
}