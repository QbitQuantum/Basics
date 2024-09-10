QWindowsCursor::CursorState QWindowsCursor::cursorState()
{
#ifndef Q_OS_WINCE
    enum { cursorShowing = 0x1, cursorSuppressed = 0x2 }; // Windows 8: CURSOR_SUPPRESSED
    CURSORINFO cursorInfo;
    cursorInfo.cbSize = sizeof(CURSORINFO);
    if (GetCursorInfo(&cursorInfo)) {
        if (cursorInfo.flags & CursorShowing)
            return CursorShowing;
        if (cursorInfo.flags & cursorSuppressed)
            return CursorSuppressed;
    }
#endif // !Q_OS_WINCE
    return CursorHidden;
}