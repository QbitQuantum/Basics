void DockWnd::setIcon(const char *icon)
{
#ifndef WIN32
#if !defined(QT_MACOSX_VERSION) && !defined(QT_MAC)
    if (wharfIcon){
        wharfIcon->set(m_state, bBlink ?  m_unread : NULL);
	repaint();
	return;
    }
#endif
#endif
    drawIcon = Pict(icon);
#ifndef WIN32
#if !defined(QT_MACOSX_VERSION) && !defined(QT_MAC)
    if (!inTray){
        repaint();
        return;
    }
#endif
#endif
#ifdef WIN32
    QWidget::setIcon(drawIcon);
    if (IsWindowUnicode(winId())){
        __NOTIFYICONDATAW notifyIconData;
        memset(&notifyIconData, 0, sizeof(notifyIconData));
        notifyIconData.cbSize = sizeof(notifyIconData);
        notifyIconData.hIcon = topData()->winIcon;
        notifyIconData.hWnd = winId();
        notifyIconData.uFlags = NIF_ICON;
        Shell_NotifyIconW(NIM_MODIFY, (NOTIFYICONDATAW*)&notifyIconData);
    }else{
        __NOTIFYICONDATAA notifyIconData;
        memset(&notifyIconData, 0, sizeof(notifyIconData));
        notifyIconData.cbSize = sizeof(notifyIconData);
        notifyIconData.hIcon = topData()->winIcon;
        notifyIconData.hWnd = winId();
        notifyIconData.uFlags = NIF_ICON;
        Shell_NotifyIconA(NIM_MODIFY, (NOTIFYICONDATAA*)&notifyIconData);
    }
#else
#if !defined(QT_MACOSX_VERSION) && !defined(QT_MAC)
    if (wharfIcon)
        return;
#endif
    // from PSI:
    // thanks to Robert Spier for this:
    // for some reason the repaint() isn't being honored, or isn't for
    // the icon.  So force one on the widget behind the icon
    erase();
    QPaintEvent pe( rect() );
    paintEvent(&pe);
#endif
}