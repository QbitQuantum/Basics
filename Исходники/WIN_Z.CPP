/*
============
WZ_WndProc
============
*/
LONG WINAPI WZ_WndProc (
    HWND    hWnd,
    UINT    uMsg,
    WPARAM  wParam,
    LPARAM  lParam)
{
	int		fwKeys, xPos, yPos;
    RECT	rect;

    GetClientRect(hWnd, &rect);

    switch (uMsg)
    {

	case WM_DESTROY:
		QEW_StopGL( hWnd, s_hglrcZ, s_hdcZ );
		return 0;

	case WM_CREATE:
        s_hdcZ = GetDC(hWnd);
	    QEW_SetupPixelFormat( s_hdcZ, false);
		if ( ( s_hglrcZ = wglCreateContext( s_hdcZ ) ) == 0 )
			Error( "wglCreateContext in WZ_WndProc failed" );

        if (!wglMakeCurrent( s_hdcZ, s_hglrcZ ))
			Error ("wglMakeCurrent in WZ_WndProc failed");

		if (!wglShareLists( g_qeglobals.d_hglrcBase, s_hglrcZ ) )
			Error( "wglShareLists in WZ_WndProc failed" );
		return 0;

	case WM_PAINT:
        { 
		    PAINTSTRUCT	ps;

		    BeginPaint(hWnd, &ps);

            if ( !wglMakeCurrent( s_hdcZ, s_hglrcZ ) )
				Error ("wglMakeCurrent failed");
			QE_CheckOpenGLForErrors();

			Z_Draw ();
		    SwapBuffers(s_hdcZ);

			EndPaint(hWnd, &ps);
        }
		return 0;


	case WM_KEYDOWN:
		QE_KeyDown (wParam);
		return 0;

	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		if (GetTopWindow(g_qeglobals.d_hwndMain) != hWnd)
			BringWindowToTop(hWnd);

		SetFocus( g_qeglobals.d_hwndZ );
		SetCapture( g_qeglobals.d_hwndZ );
		fwKeys = wParam;        // key flags 
		xPos = (short)LOWORD(lParam);  // horizontal position of cursor 
		yPos = (short)HIWORD(lParam);  // vertical position of cursor 
		yPos = (int)rect.bottom - 1 - yPos;
		Z_MouseDown (xPos, yPos, fwKeys);
		return 0;

	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
		fwKeys = wParam;        // key flags 
		xPos = (short)LOWORD(lParam);  // horizontal position of cursor 
		yPos = (short)HIWORD(lParam);  // vertical position of cursor 
		yPos = (int)rect.bottom - 1 - yPos;
		Z_MouseUp (xPos, yPos, fwKeys);
		if (! (fwKeys & (MK_LBUTTON|MK_RBUTTON|MK_MBUTTON)))
			ReleaseCapture ();
		return 0;

	case WM_GETMINMAXINFO:
	{
		MINMAXINFO *pmmi = (LPMINMAXINFO) lParam;

		pmmi->ptMinTrackSize.x = ZWIN_WIDTH;
		return 0;
	}

	case WM_MOUSEMOVE:
		fwKeys = wParam;        // key flags 
		xPos = (short)LOWORD(lParam);  // horizontal position of cursor 
		yPos = (short)HIWORD(lParam);  // vertical position of cursor 
		yPos = (int)rect.bottom - 1 - yPos;
		Z_MouseMoved (xPos, yPos, fwKeys);
		return 0;

    case WM_SIZE:
		z.width = rect.right;
		z.height = rect.bottom;
		InvalidateRect( g_qeglobals.d_hwndZ, NULL, false);
		return 0;

	case WM_NCCALCSIZE:// don't let windows copy pixels
		DefWindowProc (hWnd, uMsg, wParam, lParam);
		return WVR_REDRAW;

	case WM_KILLFOCUS:
	case WM_SETFOCUS:
		SendMessage( hWnd, WM_NCACTIVATE, uMsg == WM_SETFOCUS, 0 );
		return 0;

   	case WM_CLOSE:
        /* call destroy window to cleanup and go away */
        DestroyWindow (hWnd);
		return 0;
    }

	return DefWindowProc (hWnd, uMsg, wParam, lParam);
}