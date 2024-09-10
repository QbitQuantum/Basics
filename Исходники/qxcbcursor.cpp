void QXcbCursor::changeCursor(QCursor *cursor, QWindow *widget)
{
    QXcbWindow *w = 0;
    if (widget && widget->handle())
        w = static_cast<QXcbWindow *>(widget->handle());
    else
        // No X11 cursor control when there is no widget under the cursor
        return;

    xcb_cursor_t c = XCB_CURSOR_NONE;
    if (cursor) {
        const QXcbCursorCacheKey key(*cursor);
        CursorHash::iterator it = m_cursorHash.find(key);
        if (it == m_cursorHash.end()) {
            const Qt::CursorShape shape = cursor->shape();
            it = m_cursorHash.insert(key, shape == Qt::BitmapCursor ? createBitmapCursor(cursor) : createFontCursor(shape));
        }
        c = it.value();
    }

    w->setCursor(c);
}