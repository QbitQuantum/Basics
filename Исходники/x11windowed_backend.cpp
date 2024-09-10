void X11WindowedBackend::init()
{
    int screen = 0;
    xcb_connection_t *c = nullptr;
    Display *xDisplay = XOpenDisplay(deviceIdentifier().constData());
    if (xDisplay) {
        c = XGetXCBConnection(xDisplay);
        XSetEventQueueOwner(xDisplay, XCBOwnsEventQueue);
        screen = XDefaultScreen(xDisplay);
    }
    if (c && !xcb_connection_has_error(c)) {
        m_connection = c;
        m_screenNumber = screen;
        m_display = xDisplay;
        for (xcb_screen_iterator_t it = xcb_setup_roots_iterator(xcb_get_setup(m_connection));
            it.rem;
            --screen, xcb_screen_next(&it)) {
            if (screen == m_screenNumber) {
                m_screen = it.data;
            }
        }
        XRenderUtils::init(m_connection, m_screen->root);
        createWindow();
        startEventReading();
        connect(this, &X11WindowedBackend::cursorChanged, this,
            [this] {
                createCursor(softwareCursor(), softwareCursorHotspot());
            }
        );
        setReady(true);
        waylandServer()->seat()->setHasPointer(true);
        waylandServer()->seat()->setHasKeyboard(true);
        emit screensQueried();
    } else {
        emit initFailed();
    }
}