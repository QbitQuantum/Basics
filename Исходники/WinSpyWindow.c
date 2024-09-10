//
//  hwnd       - window to calc
//  szDlgUnits - (input)  size in dialog units
//  szClient   - (output) size of client area in pixels
//  szWindow   - (output) total size of based on current settings
//
void CalcDlgWindowSize(HWND hwnd, SIZE *szDlgUnits, SIZE *szClient, SIZE *szWindow)
{
	RECT rect;
	DWORD dwStyle;
	DWORD dwStyleEx;

	// work out the size in pixels of our main window, by converting
	// from dialog units
	SetRect(&rect, 0, 0, szDlgUnits->cx, szDlgUnits->cy);
	MapDialogRect(hwnd, &rect);

	if (szClient)
	{
		szClient->cx = GetRectWidth(&rect);
		szClient->cy = GetRectHeight(&rect);
	}

	dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	dwStyleEx = GetWindowLong(hwnd, GWL_EXSTYLE);

	AdjustWindowRectEx(&rect, dwStyle, FALSE, dwStyleEx);

	if (szWindow)
	{
		szWindow->cx = GetRectWidth(&rect);
		szWindow->cy = GetRectHeight(&rect);
	}
}