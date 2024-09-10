void
bringToFront()
{
#if defined(Q_WS_X11)
    {
        qDebug() << Q_FUNC_INFO;

        QWidget* widget = tomahawkWindow();
        if ( !widget )
            return;

        widget->show();
        widget->activateWindow();
        widget->raise();

        WId wid = widget->winId();
        NETWM::init();

        XEvent e;
        e.xclient.type = ClientMessage;
        e.xclient.message_type = NETWM::NET_ACTIVE_WINDOW;
        e.xclient.display = QX11Info::display();
        e.xclient.window = wid;
        e.xclient.format = 32;
        e.xclient.data.l[0] = 2;
        e.xclient.data.l[1] = QX11Info::appTime();
        e.xclient.data.l[2] = 0;
        e.xclient.data.l[3] = 0l;
        e.xclient.data.l[4] = 0l;

        XSendEvent( QX11Info::display(), RootWindow( QX11Info::display(), DefaultScreen( QX11Info::display() ) ), False, SubstructureRedirectMask | SubstructureNotifyMask, &e );
    }
#elif defined(Q_WS_WIN)
    {
        qDebug() << Q_FUNC_INFO;

        QWidget* widget = tomahawkWindow();
        if ( !widget )
            return;

        widget->show();
        widget->activateWindow();
        widget->raise();

        WId wid = widget->winId();

        HWND hwndActiveWin = GetForegroundWindow();
        int  idActive      = GetWindowThreadProcessId(hwndActiveWin, NULL);
        if ( AttachThreadInput(GetCurrentThreadId(), idActive, TRUE) )
        {
            SetForegroundWindow( wid );
            SetFocus( wid );
            AttachThreadInput(GetCurrentThreadId(), idActive, FALSE);
        }
    }
#endif
}