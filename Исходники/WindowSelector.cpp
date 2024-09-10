void WindowSelector::start(std::function<void(KWin::Toplevel*)> callback, const QByteArray &cursorName)
{
    xcb_cursor_t cursor = createCursor(cursorName);
    if (m_active) {
        callback(nullptr);
        return;
    }

    xcb_connection_t *c = connection();
    ScopedCPointer<xcb_grab_pointer_reply_t> grabPointer(xcb_grab_pointer_reply(c, xcb_grab_pointer_unchecked(c, false, rootWindow(),
        XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
        XCB_EVENT_MASK_POINTER_MOTION |
        XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW,
        XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, XCB_WINDOW_NONE,
        cursor, XCB_TIME_CURRENT_TIME), NULL));
    if (grabPointer.isNull() || grabPointer->status != XCB_GRAB_STATUS_SUCCESS) {
        callback(nullptr);
        return;
    }
    m_active = grabXKeyboard();
    if (!m_active) {
        xcb_ungrab_pointer(connection(), XCB_TIME_CURRENT_TIME);
        callback(nullptr);
        return;
    }
    grabXServer();
    m_callback = callback;
}