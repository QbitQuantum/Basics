//-----------------------------------------------------------------------------
// Name: HighlightWindow (from MSDN Spy Sample)
// Object: highlight or unhightlight a window
// Parameters : 
//     in : HWND hwnd : target window handle
//          BOOL fDraw : TRUE to draw, FALSE to clear
// Return : TRUE on success
//-----------------------------------------------------------------------------
void CSelectWindow::HighlightWindow( HWND hwnd, BOOL fDraw )
{
    #define DINV                3
    HDC hdc;
    RECT rc;
    BOOL bBorderOn;
    bBorderOn = fDraw;

    if (hwnd == NULL || !IsWindow(hwnd))
        return;

    hdc = GetWindowDC(hwnd);
    GetWindowRect(hwnd, &rc);
    OffsetRect(&rc, -rc.left, -rc.top);

    if (!IsRectEmpty(&rc))
    {
        PatBlt(hdc, rc.left, rc.top, rc.right - rc.left, DINV,  DSTINVERT);
        PatBlt(hdc, rc.left, rc.bottom - DINV, DINV,
            -(rc.bottom - rc.top - 2 * DINV), DSTINVERT);
        PatBlt(hdc, rc.right - DINV, rc.top + DINV, DINV,
            rc.bottom - rc.top - 2 * DINV, DSTINVERT);
        PatBlt(hdc, rc.right, rc.bottom - DINV, -(rc.right - rc.left),
            DINV, DSTINVERT);
    }

    ReleaseDC(hwnd, hdc);
}