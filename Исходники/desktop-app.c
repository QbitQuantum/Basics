static LPARAM
on_WM_PAINT(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC dc;
	PAINTSTRUCT ps;

	// WM_PAINT message
	// http://msdn.microsoft.com/en-us/library/windows/desktop/dd145213(v=vs.85).aspx
	// > A window may receive internal paint messages as a result
	// > of calling RedrawWindow with the RDW_INTERNALPAINT flag
	// > set. In this case, the window may not have an update
	// > region. An application should call the GetUpdateRect
	// > function to determine whether the window has an
	// > update region. If GetUpdateRect returns zero, the
	// > application should not call the BeginPaint and EndPaint
	// > functions.
	if (GetUpdateRect(hwnd, NULL, FALSE) == 0) {
		return 0;
	}

	dc = BeginPaint(hwnd, &ps);
	TextOut(dc, 0, 0, _T("hello"), 5);
	EndPaint(hwnd, &ps);

	return 0;
}