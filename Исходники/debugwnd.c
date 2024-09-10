/*-----------------------------------------------------------------------------
    Name        : dbwWindowProc
    Description : Window Procedure for debug window
    Inputs      : see Windows docs
    Outputs     : "   "       "
    Return      : "   "       "
----------------------------------------------------------------------------*/
long FAR PASCAL dbwWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    RECT rect;
    switch (message)
    {
        case WM_SETFOCUS:
            SetFocus(ghMainWindow);
            break;
        case WM_MOVE:
            GetWindowRect(hWnd, &rect);
            dbwWindowX = rect.left;
            dbwWindowY = rect.top;
            return 0;
        case WM_PAINT:
            dbwAllPanesRepaint((HDC)wParam);
            ValidateRect(hDebugWindow, NULL);
            return 0;
        case WM_DESTROY:
            return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}