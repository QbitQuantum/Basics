LRESULT CALLBACK CRoboMXApp::NewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
{
	HDC hdc = (HDC)wParam;
	CRect rect;

	switch (uMsg)	{
	case WM_SIZE :
		SendMessage(hwnd, WM_ERASEBKGND, (WPARAM)GetDC(hwnd), 0);
        return CallWindowProc(theApp.m_pOldWndProc, hwnd, uMsg, wParam, lParam);
	case WM_ERASEBKGND :

		SetStretchBltMode(hdc, HALFTONE);
		GetClientRect(hwnd, &rect);
		if(rect.Width() && rect.Height())
			theApp.m_iBgImage.Draw(hdc, rect);

		return 1;
	default :
		return CallWindowProc(theApp.m_pOldWndProc, hwnd, uMsg, wParam, lParam);
	}
}