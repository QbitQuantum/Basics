//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

    static RECT rcce = { 0 };
    static RECT rcst = { 0 };
    static RECT rcsd = { 200, 200, 200, 200 };

    switch (message)
	{
	    case WM_COMMAND:
		    wmId    = LOWORD(wParam);
		    wmEvent = HIWORD(wParam);
		    // Parse the menu selections:
		    switch (wmId)
		    {
		    case IDM_ABOUT:
			    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			    break;
		    case IDM_EXIT:
			    DestroyWindow(hWnd);
			    break;
		    default:
			    return DefWindowProc(hWnd, message, wParam, lParam);
		    }
		    break;
	    case WM_PAINT:
		    hdc = BeginPaint(hWnd, &ps);
		    // TODO: Add any drawing code here...
		    EndPaint(hWnd, &ps);
		    break;
	    case WM_DESTROY:
		    PostQuitMessage(0);
		    break;
        case WM_NCLBUTTONDOWN:
            {
                POINT pt = { 0 };
                pt.x = GET_X_LPARAM(lParam);
                pt.y = GET_Y_LPARAM(lParam);

                RECT rc = { 0 };
                ::GetWindowRect(hWnd, &rc);

                // Cursor to edge
                rcce.left = rc.left - pt.x;
                rcce.top = rc.top - pt.y;
                rcce.right = rc.right - pt.x;
                rcce.bottom = rc.bottom - pt.y;

                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_ENTERSIZEMOVE:
            {
                // Snap zone = Work area
                ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcst, 0);
            }
            break;
        case WM_EXITSIZEMOVE:
            break;
        case WM_MOVING:
            {
                LPRECT lprc = (LPRECT)lParam;

                POINT pt = { 0 };
                ::GetCursorPos(&pt);

                ::SnapUnsnapRect(lprc, &pt, &rcce, &rcst, &rcsd);
            }
            break;
        case WM_SIZING:
            {
                PRECT prc = (PRECT)lParam;

                switch (wParam)
                {
                    case WMSZ_LEFT:
                        if (prc->left < rcst.left + rcsd.left)
                            prc->left = rcst.left;

                        break;
                    case WMSZ_RIGHT:
                        if (prc->right > rcst.right - rcsd.right)
                            prc->right = rcst.right;

                        break;
                    case WMSZ_TOP:
                        if (prc->top < rcst.top + rcsd.top)
                            prc->top = rcst.top;

                        break;
                    case WMSZ_TOPLEFT:
                        if (prc->left < rcst.left + rcsd.left)
                            prc->left = rcst.left;

                        if (prc->top < rcst.top + rcsd.top)
                            prc->top = rcst.top;

                        break;
                    case WMSZ_TOPRIGHT:
                        if (prc->right > rcst.right - rcsd.right)
                            prc->right = rcst.right;

                        if (prc->top < rcst.top + rcsd.top)
                            prc->top = rcst.top;

                        break;
                    case WMSZ_BOTTOM:
                        if (prc->bottom > rcst.bottom - rcsd.bottom)
                            prc->bottom = rcst.bottom;

                        break;
                    case WMSZ_BOTTOMLEFT:
                        if (prc->left < rcst.left + rcsd.left)
                            prc->left = rcst.left;

                        if (prc->bottom > rcst.bottom - rcsd.bottom)
                            prc->bottom = rcst.bottom;

                        break;
                    case WMSZ_BOTTOMRIGHT:
                        if (prc->right > rcst.right - rcsd.right)
                            prc->right = rcst.right;

                        if (prc->bottom > rcst.bottom - rcsd.bottom)
                            prc->bottom = rcst.bottom;

                        break;
                }
            }
            break;
	    default:
		    return DefWindowProc(hWnd, message, wParam, lParam);
	}

    return 0;
}