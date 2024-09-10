void IWindow::selectWindow()
{
    hWndDC = GetWindowDC(hWnd);
	hBufferDC = CreateCompatibleDC(hWndDC);
	hWndBitmap = CreateCompatibleBitmap(hWndDC, wndWidth, wndHeight);
	hWndBitmap = (HBITMAP)SelectObject(hBufferDC, hWndBitmap);

	if(!BitBlt(hBufferDC, 0, 0, wndWidth, wndHeight, hWndDC, 0, 0, SRCCOPY)){
		DWORD dwError = GetLastError();
		_tprintf(_T("BitBlt: dwError = %i \n"), dwError);
	}

	if(hWndDC != NULL)
	{
		HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		hPen = (HPEN)SelectObject(hWndDC, hPen);

		MoveToEx(hWndDC, 1, 1, NULL);
		LineTo(hWndDC, wndWidth - 1, 1);
		LineTo(hWndDC, wndWidth - 1, wndHeight - 1);
		LineTo(hWndDC, 1, wndHeight - 1);
		LineTo(hWndDC, 1, 1);

		DeleteObject(SelectObject(hWndDC, hPen));
	}
}