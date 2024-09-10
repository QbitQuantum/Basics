bool Win32CursorController::isCursorVisible()
{
    CURSORINFO rCursorInfo;
    rCursorInfo.cbSize = sizeof(CURSORINFO);
    if( !GetCursorInfo( &rCursorInfo ) )
    {
        //DWORD error = GetLastError();
        return false;
    }

    // rCursorInfo.flags values :
    // 0 == Cursor is hidden
    // CURSOR_SHOWING == cursor is visible
    return (bool)(rCursorInfo.flags == CURSOR_SHOWING);
}