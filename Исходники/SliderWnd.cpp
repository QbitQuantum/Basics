void SliderWnd::PositionWindow() {
    POINT p;
    GetCursorPos(&p);

    HMONITOR monitor = MonitorFromPoint(p, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mInfo = {};
    mInfo.cbSize = sizeof(mInfo);
    GetMonitorInfo(monitor, &mInfo);
    RECT mRect = mInfo.rcWork;

    /* Default location is the bottom of the window centered above cursor. */
    POINT loc;
    loc.x = p.x - _size.cx / 2;
    loc.y = p.y - _size.cy;

    /* Reposition the window if it's falling off the monitor somewhere. */
    if (loc.y < mRect.top) {
        loc.y = mRect.top;
    }

    if (loc.x < mRect.left) {
        loc.x = mRect.left;
    }

    if (p.y > mRect.bottom) {
        loc.y = mRect.bottom - _size.cy;
    }

    if (p.x > mRect.right - _size.cx) {
        loc.x = mRect.right - _size.cx;
    }

    Position(loc.x, loc.y);
}