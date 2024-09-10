bool UpdateLayeredWindowT(HWND hWnd, HDC hdcDst, POINT *pptDst, SIZE* psize, HDC hdcSrc, POINT* pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags)
{
	typedef BOOL(WINAPI * lpfnUpdateLayeredWindow)(HWND hWnd, HDC hdcDst, POINT *pptDst, SIZE* psize, HDC hdcSrc, POINT* pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
	lpfnUpdateLayeredWindow UpdateLayeredWindow;
	HMODULE hUser32 = GetModuleHandle(_T("user32.dll"));
	UpdateLayeredWindow = (lpfnUpdateLayeredWindow)GetProcAddress(hUser32, "UpdateLayeredWindow");
	UpdateLayeredWindow(hWnd, hdcDst, pptDst, psize, hdcSrc, pptSrc, crKey, pblend, dwFlags);
	FreeLibrary(hUser32);
	return true;
}