/*----------------------------------------------------------------------------*\
|   AppWndProc( hwnd, uiMessage, wParam, lParam )                              |
|                                                                              |
|   Description:                                                               |
|       The window proc for the app's main (tiled) window.  This processes all |
|       of the parent window's messages.                                       |
|                                                                              |
\*----------------------------------------------------------------------------*/
LONG FAR PASCAL _export AppWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    BOOL f;
  
    switch (msg)
    {
        case WM_CREATE:
            hwndA = CreateWindowEx(WS_EX_CLIENTEDGE,ANIMATE_CLASS, NULL,
//              ACS_CENTER |
                ACS_TRANSPARENT |
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                10, 10, 500, 200, hwnd, (HMENU)42, hInstApp, NULL);
	    break;

	case WM_SIZE:
            //if (hwndC = GetWindow(hwnd, GW_CHILD))
            //    MoveWindow(hwndC, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
	    break;

        case WM_ACTIVATEAPP:
	    fAppActive = (BOOL)wParam;
            break;

        case WM_TIMER:
            break;

        case WM_ERASEBKGND:
            break;

        case WM_INITMENU:
	    EnableMenuSz((HMENU)wParam, TEXT("Edit.Paste"), IsClipboardFormatAvailable(CF_TEXT));
            break;

        case WM_COMMAND:
            //
            //  the animate control will notify us when play start or stops.
            //
            if (LOWORD(wParam) == 42)
            {
                if (GET_WM_COMMAND_CMD(wParam, lParam) == ACN_STOP)
                    AppSetText(TEXT("(stopped)"));
                else if (GET_WM_COMMAND_CMD(wParam, lParam) == ACN_START)
                    AppSetText(TEXT("(playing)"));
                else
                    AppSetText(NULL);
            }
            return HandleCommand(hwnd,msg,wParam,lParam);

	case WM_DESTROY:
	    hAccelApp = NULL;
            PostQuitMessage(0);
	    break;

        case WM_CLOSE:
	    break;

        case WM_PALETTECHANGED:
	    if ((HWND)wParam == hwnd)
		break;

	    // fall through to WM_QUERYNEWPALETTE

	case WM_QUERYNEWPALETTE:
	    hdc = GetDC(hwnd);

	    if (hpalApp)
		SelectPalette(hdc, hpalApp, FALSE);

	    f = RealizePalette(hdc);
	    ReleaseDC(hwnd,hdc);

	    if (f)
		InvalidateRect(hwnd,NULL,TRUE);

	    return f;

        case WM_PAINT:
	    hdc = BeginPaint(hwnd,&ps);
	    AppPaint (hwnd,hdc);
            EndPaint(hwnd,&ps);
            return 0L;
    }
    return DefWindowProc(hwnd,msg,wParam,lParam);
}