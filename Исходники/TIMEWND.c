/*****************************************************************************
*
* TWnd_OnPaint
*
* Handle WM_PAINT message to time window.
*
* HWND hWnd                 - Window handle
*
* Repaint the 3D inset borders around the edge of the client area.
* Repaint the time.
*
*****************************************************************************/
VOID NEAR PASCAL TWnd_OnPaint( HWND hWnd) { PAINTSTRUCT ps; HDC hDC;
HBRUSH hBrOld; int nWidth; int nHeight;

    RECT                    rc;

    GetClientRect(hWnd, &rc);
    nWidth  = rc.right;
    nHeight = rc.bottom;
    
    hDC = BeginPaint(hWnd, &ps);

    hBrOld = (HBRUSH)SelectObject(hDC, GetStockObject(GRAY_BRUSH));
    PatBlt(hDC, 0, 0, 1, nHeight-1, PATCOPY);
    PatBlt(hDC, 1, 0, nWidth-2, 1, PATCOPY);

    SelectObject(hDC, GetStockObject(BLACK_BRUSH));
    PatBlt(hDC, 1, 1, 1, nHeight-3, PATCOPY);
    PatBlt(hDC, 2, 1, nWidth-4, 1, PATCOPY);

    SelectObject(hDC, GetStockObject(WHITE_BRUSH));
    PatBlt(hDC, rc.right-1, 0, 1, nHeight-1, PATCOPY);
    PatBlt(hDC, 0, rc.bottom-1, nWidth, 1, PATCOPY);

    SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
    PatBlt(hDC, rc.right-2, 1, 1, nHeight-2, PATCOPY);
    PatBlt(hDC, 1, rc.bottom-2, nWidth-2, 1, PATCOPY);
    
    SelectObject(hDC, hBrOld);

    gbRepaint = TRUE;
    PaintTime(hDC);

    EndPaint(hWnd, &ps);
}