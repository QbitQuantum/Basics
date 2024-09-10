//*------------------------------------------------------------------------
//| WctFleditWndProc
//|
//| PURPOSE:    Window procedure for the Fledit window.
//|
//| ENTRY/EXIT: Per Windows convention
//*------------------------------------------------------------------------
LONG  APIENTRY WctFleditWndProc(HWND hWnd, UINT wMsgID,
                                 WPARAM wParam, LPARAM lParam )
{
        HANDLE  hBuffer;
        LPSTR   lpBuffer, lpFNameTemp;
        RECT    rect;
        HDC     hdc;
        static  HWND  hWndEdit;
        static  TEXTMETRIC tm;
        static  CHAR szFileName[80];
        HFONT   hFont;

        switch( wMsgID ) {
            case WM_CREATE:
                GetClientRect (hWnd, &rect);

                hdc = GetDC(hWnd);
                GetTextMetrics(hdc, (LPTEXTMETRIC)&tm);

                hWndEdit = CreateWindow("EDIT", "",
                   WS_CHILD | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL |
                   ES_AUTOHSCROLL | WS_BORDER | WS_VISIBLE | ES_MULTILINE,
                   0, tm.tmHeight,rect.right, rect.bottom - tm.tmHeight,
                   hWnd, NULL, hgInstWct, 0L);

                ReleaseDC(hWnd, hdc);

                lpFNameTemp = (LPSTR)(((LPCREATESTRUCT)lParam)->lpszName);

                // Use lParam as LPSTR to file to load.
                //--------------------------------------------------------
                if ( lpFNameTemp != NULL)
                        if ((hBuffer = WctReadFile(lpFNameTemp, sp)) != NULL)
                            {
                                lpBuffer = (LPSTR)GlobalLock(hBuffer);
                                if (lpBuffer != NULL)
                                {
                                    SetWindowText(hWndEdit, lpBuffer);
                                    GlobalUnlock(hBuffer);
                                }
                                GlobalFree(hBuffer);
                           }

                // After reading in file NULL terminate text if too Long.
                //--------------------------------------------------------
                if ( lstrlen(lpFNameTemp) > 72)
                        *(lpFNameTemp+72) = '\0';

                wsprintf(szFileName, "FILE: %s", (LPSTR)lpFNameTemp);

                hdc = GetDC(hWnd);
                GetTextMetrics(hdc, (LPTEXTMETRIC)&tm);
                hFont = GetStockObject(ANSI_VAR_FONT);
                SelectObject(hdc, hFont);
                DeleteObject(SelectObject(hdc, GetStockObject(BLACK_PEN)));
                TextOut(hdc, 0, 0, (LPSTR)szFileName,
                        lstrlen((LPSTR)szFileName));
                DeleteObject(SelectObject(hdc, hFont));
                ReleaseDC(hWnd, hdc);

                SetWindowText(hWnd, "Compare Results");
                break;

           case WM_SIZE:
                GetClientRect (hWnd, (LPRECT)&rect);
                SetWindowPos (hWndEdit, NULL, 0, 0, rect.right,
                            rect.bottom - tm.tmHeight, SWP_NOMOVE);
                break;

           case WM_SETFOCUS:
                SetFocus(hWndEdit);
                break;

           case WM_PAINT:
                ValidateRect (hWnd, (LPRECT)NULL);
                hdc = GetDC(hWnd);
                DeleteObject(SelectObject(hdc, GetStockObject(BLACK_PEN)));
                hFont = GetStockObject(ANSI_VAR_FONT);
                SelectObject(hdc, hFont);
                TextOut(hdc, 0, 0, (LPSTR)szFileName,
                        lstrlen((LPSTR)szFileName));
                DeleteObject(SelectObject(hdc, hFont));
                ReleaseDC(hWnd, hdc);
                break;

           case WM_CHAR:
                if (wParam == VK_ESCAPE)
                    {
                        DestroyWindow (hWndEdit);
                        DestroyWindow (hWnd);
                    }
                break;

           default:
                return ( DefWindowProc(hWnd, wMsgID, wParam, lParam));
           }

        return (0L);
}