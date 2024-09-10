void WindowsMouse::GetMouseCapture(HWND hWnd)
{
    SetCapture(hWnd);
    ShowCursor(0);

    GetCursorPos(&origCursorPos);

    RECT r;
    GetWindowRect(hWnd, &r);
    ClipCursor(&r);
    center.x = (r.left + r.right) / 2;
    center.y = (r.top + r.bottom) / 2;
    SetCursorPos(center.x, center.y);
}