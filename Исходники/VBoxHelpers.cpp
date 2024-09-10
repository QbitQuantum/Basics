/**
 * Attempt to force Windows to reload the cursor image by attaching to the
 * thread of the window currently under the mouse, hiding the cursor and
 * showing it again.  This could fail to work in any number of ways (no
 * window under the cursor, the cursor has moved to a different window while
 * we are processing), but we just accept this, as the cursor will be reloaded
 * at some point anyway.
 */
void hlpReloadCursor(void)
{
    POINT mousePos;
    HWND hWin;
    DWORD hThread, hCurrentThread;

    GetCursorPos(&mousePos);
    hWin = WindowFromPoint(mousePos);
    if (hWin)
    {
        hThread = GetWindowThreadProcessId(hWin, NULL);
        hCurrentThread = GetCurrentThreadId();
        if (hCurrentThread != hThread)
            AttachThreadInput(hCurrentThread, hThread, TRUE);
    }
    ShowCursor(false);
    ShowCursor(true);
    if (hWin && (hCurrentThread != hThread))
        AttachThreadInput(hCurrentThread, hThread, FALSE);
}