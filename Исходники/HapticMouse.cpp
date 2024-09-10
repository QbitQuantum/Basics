BOOL CHapticMouse::CancelLeaveNotify()
{
    TRACKMOUSEEVENT tmev;
    tmev.cbSize = sizeof tmev;
    tmev.dwFlags = TME_CANCEL | TME_LEAVE;
    tmev.hwndTrack = GetSafeHwnd();
    tmev.dwHoverTime = HOVER_DEFAULT;

    return _TrackMouseEvent(&tmev);
}