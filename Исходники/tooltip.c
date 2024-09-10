static LRESULT CALLBACK MyWindowWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_ACTIVATE:
			if ( wParam == WA_INACTIVE && bEmbedBrowserObject )
			{
				ShowWindow(hwndHTMLParent, SW_HIDE);
				UnEmbedBrowserObject(hwndHTMLParent);
				bEmbedBrowserObject = FALSE;
				bTooltipShow = FALSE;
			}
			break;
		default:
			return DefWindowProcA(hwnd, message, wParam, lParam);
	}
	return DefWindowProcA(hwnd, message, wParam, lParam);
}