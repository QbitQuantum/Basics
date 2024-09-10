bool QWindowsMouseHandler::translateMouseEvent(QWindow *window, HWND hwnd,
                                               QtWindows::WindowsEventType et,
                                               MSG msg, LRESULT *result)
{
#ifdef Q_COMPILER_CLASS_ENUM
    enum : quint64 { signatureMask = 0xffffff00, miWpSignature = 0xff515700 };
#else
    static const quint64 signatureMask = 0xffffff00;
    static const quint64 miWpSignature = 0xff515700;
#endif // !Q_COMPILER_CLASS_ENUM

    if (et == QtWindows::MouseWheelEvent)
        return translateMouseWheelEvent(window, hwnd, msg, result);

#ifndef Q_OS_WINCE
    // Check for events synthesized from touch. Lower byte is touch index, 0 means pen.
    const quint64 extraInfo = GetMessageExtraInfo();
    const bool fromTouch = (extraInfo & signatureMask) == miWpSignature && (extraInfo & 0xff);
    if (fromTouch)
        return false;
#endif // !Q_OS_WINCE

    const QPoint winEventPosition(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam));
    if (et & QtWindows::NonClientEventFlag) {
        const QPoint globalPosition = winEventPosition;
        const QPoint clientPosition = QWindowsGeometryHint::mapFromGlobal(hwnd, globalPosition);
        const Qt::MouseButtons buttons = QWindowsMouseHandler::queryMouseButtons();
        QWindowSystemInterface::handleFrameStrutMouseEvent(window, clientPosition,
                                                           globalPosition, buttons,
                                                           QWindowsKeyMapper::queryKeyboardModifiers());
        return false; // Allow further event processing (dragging of windows).
    }

    *result = 0;
    if (msg.message == WM_MOUSELEAVE) {
        if (QWindowsContext::verboseEvents)
            qDebug() << "WM_MOUSELEAVE for " << window << " previous window under mouse = " << m_windowUnderMouse << " tracked window =" << m_trackedWindow;

        // When moving out of a window, WM_MOUSEMOVE within the moved-to window is received first,
        // so if m_trackedWindow is not the window here, it means the cursor has left the
        // application.
        if (window == m_trackedWindow) {
            QWindow *leaveTarget = m_windowUnderMouse ? m_windowUnderMouse : m_trackedWindow;
            if (QWindowsContext::verboseEvents)
                qDebug() << "Generating leave event for " << leaveTarget;
            QWindowSystemInterface::handleLeaveEvent(leaveTarget);
            m_trackedWindow = 0;
            m_windowUnderMouse = 0;
        }
        return true;
    }

    QWindowsWindow *platformWindow = static_cast<QWindowsWindow *>(window->handle());
    const Qt::MouseButtons buttons = keyStateToMouseButtons((int)msg.wParam);

    // If the window was recently resized via mouse doubleclick on the frame or title bar,
    // we don't get WM_LBUTTONDOWN or WM_LBUTTONDBLCLK for the second click,
    // but we will get at least one WM_MOUSEMOVE with left button down and the WM_LBUTTONUP,
    // which will result undesired mouse press and release events.
    // To avoid those, we ignore any events with left button down if we didn't
    // get the original WM_LBUTTONDOWN/WM_LBUTTONDBLCLK.
    if (msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONDBLCLK) {
        m_leftButtonDown = true;
    } else {
        const bool actualLeftDown = buttons & Qt::LeftButton;
        if (!m_leftButtonDown && actualLeftDown) {
            // Autocapture the mouse for current window to and ignore further events until release.
            // Capture is necessary so we don't get WM_MOUSELEAVEs to confuse matters.
            // This autocapture is released normally when button is released.
            if (!platformWindow->hasMouseCapture()) {
                QWindowsWindow::baseWindowOf(window)->applyCursor();
                platformWindow->setMouseGrabEnabled(true);
                platformWindow->setFlag(QWindowsWindow::AutoMouseCapture);
                if (QWindowsContext::verboseEvents)
                    qDebug() << "Automatic mouse capture for missing buttondown event" << window;
            }
            m_previousCaptureWindow = window;
            return true;
        } else if (m_leftButtonDown && !actualLeftDown) {
            m_leftButtonDown = false;
        }
    }

    const QPoint globalPosition = QWindowsGeometryHint::mapToGlobal(hwnd, winEventPosition);
    // In this context, neither an invisible nor a transparent window (transparent regarding mouse
    // events, "click-through") can be considered as the window under mouse.
    QWindow *currentWindowUnderMouse = platformWindow->hasMouseCapture() ?
        QWindowsScreen::windowAt(globalPosition, CWP_SKIPINVISIBLE | CWP_SKIPTRANSPARENT) : window;

    compressMouseMove(&msg);
    // Qt expects the platform plugin to capture the mouse on
    // any button press until release.
    if (!platformWindow->hasMouseCapture()
        && (msg.message == WM_LBUTTONDOWN || msg.message == WM_MBUTTONDOWN
            || msg.message == WM_RBUTTONDOWN || msg.message == WM_XBUTTONDOWN
            || msg.message == WM_LBUTTONDBLCLK || msg.message == WM_MBUTTONDBLCLK
            || msg.message == WM_RBUTTONDBLCLK || msg.message == WM_XBUTTONDBLCLK)) {
        platformWindow->setMouseGrabEnabled(true);
        platformWindow->setFlag(QWindowsWindow::AutoMouseCapture);
        if (QWindowsContext::verboseEvents)
            qDebug() << "Automatic mouse capture " << window;
        // Implement "Click to focus" for native child windows (unless it is a native widget window).
        if (!window->isTopLevel() && !window->inherits("QWidgetWindow") && QGuiApplication::focusWindow() != window)
            window->requestActivate();
    } else if (platformWindow->hasMouseCapture()
               && platformWindow->testFlag(QWindowsWindow::AutoMouseCapture)
               && (msg.message == WM_LBUTTONUP || msg.message == WM_MBUTTONUP
                   || msg.message == WM_RBUTTONUP || msg.message == WM_XBUTTONUP)
               && !buttons) {
        platformWindow->setMouseGrabEnabled(false);
        if (QWindowsContext::verboseEvents)
            qDebug() << "Releasing automatic mouse capture " << window;
    }

    const bool hasCapture = platformWindow->hasMouseCapture();
    const bool currentNotCapturing = hasCapture && currentWindowUnderMouse != window;
#ifndef Q_OS_WINCE
    // Enter new window: track to generate leave event.
    // If there is an active capture, only track if the current window is capturing,
    // so we don't get extra leave when cursor leaves the application.
    if (window != m_trackedWindow && !currentNotCapturing) {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = hwnd;
        tme.dwHoverTime = HOVER_DEFAULT; //
        if (!TrackMouseEvent(&tme))
            qWarning("TrackMouseEvent failed.");
        m_trackedWindow =  window;
    }
#endif // !Q_OS_WINCE

    // No enter or leave events are sent as long as there is an autocapturing window.
    if (!hasCapture || !platformWindow->testFlag(QWindowsWindow::AutoMouseCapture)) {
        // Leave is needed if:
        // 1) There is no capture and we move from a window to another window.
        //    Note: Leaving the application entirely is handled in WM_MOUSELEAVE case.
        // 2) There is capture and we move out of the capturing window.
        // 3) There is a new capture and we were over another window.
        if ((m_windowUnderMouse && m_windowUnderMouse != currentWindowUnderMouse
                && (!hasCapture || window == m_windowUnderMouse))
            || (hasCapture && m_previousCaptureWindow != window && m_windowUnderMouse
                && m_windowUnderMouse != window)) {
            if (QWindowsContext::verboseEvents)
                qDebug() << "Synthetic leave for " << m_windowUnderMouse;
            QWindowSystemInterface::handleLeaveEvent(m_windowUnderMouse);
            if (currentNotCapturing) {
                // Clear tracking if capturing and current window is not the capturing window
                // to avoid leave when mouse actually leaves the application.
                m_trackedWindow = 0;
                // We are not officially in any window, but we need to set some cursor to clear
                // whatever cursor the left window had, so apply the cursor of the capture window.
                QWindowsWindow::baseWindowOf(window)->applyCursor();
            }
        }
        // Enter is needed if:
        // 1) There is no capture and we move to a new window.
        // 2) There is capture and we move into the capturing window.
        // 3) The capture just ended and we are over non-capturing window.
        if ((currentWindowUnderMouse && m_windowUnderMouse != currentWindowUnderMouse
                && (!hasCapture || currentWindowUnderMouse == window))
            || (m_previousCaptureWindow && window != m_previousCaptureWindow && currentWindowUnderMouse
                && currentWindowUnderMouse != m_previousCaptureWindow)) {
            if (QWindowsContext::verboseEvents)
                qDebug() << "Entering " << currentWindowUnderMouse;
            QWindowsWindow::baseWindowOf(currentWindowUnderMouse)->applyCursor();
            QWindowSystemInterface::handleEnterEvent(currentWindowUnderMouse,
                                                     currentWindowUnderMouse->mapFromGlobal(globalPosition),
                                                     globalPosition);
        }
        // We need to track m_windowUnderMouse separately from m_trackedWindow, as
        // Windows mouse tracking will not trigger WM_MOUSELEAVE for leaving window when
        // mouse capture is set.
        m_windowUnderMouse = currentWindowUnderMouse;
    }

    QWindowSystemInterface::handleMouseEvent(window, winEventPosition, globalPosition, buttons,
                                             QWindowsKeyMapper::queryKeyboardModifiers());
    m_previousCaptureWindow = hasCapture ? window : 0;
    return true;
}