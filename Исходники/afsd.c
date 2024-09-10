/* called with no locks with translated messages */
LONG APIENTRY MainWndProc(
	HWND hWnd,
	unsigned int message,
	unsigned int wParam,
	long lParam)
{
	HDC hDC;                         /* display-context variable     */
	PAINTSTRUCT ps;                  /* paint structure              */

	main_wnd = hWnd;

	switch (message) {
	    case WM_QUERYOPEN:
		/* block attempts to open the window */
		return 0;

	    case WM_COMMAND:
		/* LOWORD(wParam) is command */
		return (DefWindowProc(hWnd, message, wParam, lParam));

	    case WM_CREATE:
		break;

	    case WM_PAINT:
		hDC = BeginPaint (hWnd, &ps);
		/* nothing to print, but this clears invalidated rectangle flag */
		EndPaint(hWnd, &ps);
		break;

	    case WM_DESTROY:
		RpcMgmtStopServerListening(NULL);
		PostQuitMessage(0);
		break;

	    default:
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}