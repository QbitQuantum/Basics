// If the window was previously visible, the return value is nonzero.
// If the window was previously hidden, the return value is zero.
bool apiShowWindow(HWND ahWnd, int anCmdShow)
{
	#ifdef _DEBUG
	wchar_t szLastFore[1024]; getWindowInfo(GetForegroundWindow(), szLastFore);
	wchar_t szWnd[1024]; getWindowInfo(ahWnd, szWnd);
	#endif

	bool lbRc = ::ShowWindow(ahWnd, anCmdShow) ? true : false;

	return lbRc;
}