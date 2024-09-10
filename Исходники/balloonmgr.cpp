void BalloonMgr::post()
{
    if (_pending.empty())
        return;  // No active balloon!?

    // Post balloon tip
    Balloon &balloon = _pending.front();
    NOTIFYICONDATA nid;
    nid.hWnd = balloon.hwnd;
    nid.cbSize = sizeof(nid);
    nid.uID = IDI_APCUPSD;
    nid.uFlags = NIF_INFO;
    astrncpy(nid.szInfo, balloon.text.c_str(), sizeof(nid.szInfo));
    astrncpy(nid.szInfoTitle, balloon.title.c_str(), sizeof(nid.szInfoTitle));
    nid.uTimeout = MAX_TIMEOUT;
    nid.dwInfoFlags = NIIF_INFO;
    Shell_NotifyIcon(NIM_MODIFY, &nid);

    // Set a timeout to clear the balloon
    LARGE_INTEGER timeout;
    if (_pending.size() > 1)  // More balloons pending: use minimum timeout
        timeout.QuadPart = -(MIN_TIMEOUT * 10000);
    else  // No other balloons pending: Use maximum timeout
        timeout.QuadPart = -(MAX_TIMEOUT * 10000);
    SetWaitableTimer(_timer, &timeout, 0, NULL, NULL, false);

    // Remember the time at which we started the timer
    gettimeofday(&_time, NULL);
}