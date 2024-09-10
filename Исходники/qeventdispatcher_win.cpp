void QEventDispatcherWin32Private::doWsaAsyncSelect(int socket)
{
    Q_ASSERT(internalHwnd);
    int sn_event = 0;
    if (sn_read.contains(socket))
        sn_event |= FD_READ | FD_CLOSE | FD_ACCEPT;
    if (sn_write.contains(socket))
        sn_event |= FD_WRITE | FD_CONNECT;
    if (sn_except.contains(socket))
        sn_event |= FD_OOB;
    // BoundsChecker may emit a warning for WSAAsyncSelect when sn_event == 0
    // This is a BoundsChecker bug and not a Qt bug
    WSAAsyncSelect(socket, internalHwnd, sn_event ? WM_QT_SOCKETNOTIFIER : 0, sn_event);
}