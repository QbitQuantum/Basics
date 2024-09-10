static LRESULT WINAPI MCIAVI_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    TRACE("hwnd=%p msg=%x wparam=%lx lparam=%lx\n", hWnd, uMsg, wParam, lParam);

    switch (uMsg) {
    case WM_CREATE:
        SetWindowLongW(hWnd, 0, (LPARAM)((CREATESTRUCTW *)lParam)->lpCreateParams);
        return DefWindowProcW(hWnd, uMsg, wParam, lParam);

    case WM_DESTROY:
        MCIAVI_mciClose(GetWindowLongW(hWnd, 0), MCI_WAIT, NULL);
        SetWindowLongW(hWnd, 0, 0);
        return DefWindowProcW(hWnd, uMsg, wParam, lParam);

    case WM_ERASEBKGND:
	{
	    RECT	rect;
	    GetClientRect(hWnd, &rect);
	    FillRect((HDC)wParam, &rect, GetStockObject(BLACK_BRUSH));
	}
       return 1;

    case WM_PAINT:
        {
            WINE_MCIAVI *wma = (WINE_MCIAVI *)mciGetDriverData(GetWindowLongW(hWnd, 0));

            if (!wma)
                return DefWindowProcW(hWnd, uMsg, wParam, lParam);
            
            EnterCriticalSection(&wma->cs);

            /* the animation isn't playing, don't paint */
	    if (wma->dwStatus == MCI_MODE_NOT_READY)
            {
                LeaveCriticalSection(&wma->cs);
		/* default paint handling */
                return DefWindowProcW(hWnd, uMsg, wParam, lParam);
            }

            if (wParam)
                MCIAVI_PaintFrame(wma, (HDC)wParam);
            else
            {
	        PAINTSTRUCT ps;
                BeginPaint(hWnd, &ps);
                MCIAVI_PaintFrame(wma, ps.hdc);
	        EndPaint(hWnd, &ps);
	    }

            LeaveCriticalSection(&wma->cs);
        }
       return 1;

    default:
        return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }
}