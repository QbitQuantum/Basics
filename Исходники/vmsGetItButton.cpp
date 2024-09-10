void vmsGetItButton::Create(HWND hwndParent, const RECT* prcFlash)
{
	if (m_hWnd)
		return;

	m_hWnd = CreateWindowEx (0, _T ("{E93F4E35-5841-41e7-AFF6-F456BBAE488B}"), NULL, 
		WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwndParent, NULL, 
		_Module.GetModuleInstance (), NULL);

	m_hwndTB = CreateWindow (TOOLBARCLASSNAME, 
		NULL, WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT |
		TBSTYLE_TRANSPARENT | TBSTYLE_LIST | 
		CCS_NODIVIDER | CCS_NORESIZE | CCS_NOPARENTALIGN, 0, 0, 16+70, 16+7, 
		m_hWnd, NULL, _Module.GetModuleInstance (), NULL);
	SendMessage (m_hwndTB, TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_DRAWDDARROWS);

	SetWindowLongPtr (m_hwndTB, GWL_USERDATA, (LONG_PTR)this);
	SetWindowLongPtr (m_hWnd, GWL_USERDATA, (LONG_PTR)this);

	SendMessage (m_hwndTB, TB_BUTTONSTRUCTSIZE, sizeof (TBBUTTON), 0);

	tstring str = vmsFdmTranslations::o ().GetString (L_DLBYFDM);
	if (str.empty ())
		str = _T("Download with FDM");
	USES_CONVERSION;
	SendMessage (m_hwndTB, TB_ADDSTRING, 0, (LPARAM)str.c_str ());

	SendMessage (m_hwndTB, TB_SETBITMAPSIZE, 0, MAKELONG (16, 16));
	SendMessage (m_hwndTB, TB_SETIMAGELIST, 0, (LPARAM)m_hImgs);
	
	TBBUTTON btn = {0};
	btn.iBitmap = 0;
	btn.idCommand = ID_DOWNLOAD_IT;
	btn.fsState = TBSTATE_ENABLED;
	btn.fsStyle = TBSTYLE_BUTTON | TBSTYLE_DROPDOWN;
	btn.dwData = 0;
	btn.iString = 0;
	SendMessage (m_hwndTB, TB_ADDBUTTONS, 1, (LPARAM)&btn);

	RECT rc;
	SendMessage (m_hwndTB, TB_GETRECT, btn.idCommand, (LPARAM)&rc);

	int x, y;

	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;

	if (prcFlash == NULL)
	{
		POINT pt; GetCursorPos (&pt);
		ScreenToClient (hwndParent, &pt);
		x = pt.x += 10, y = pt.y -= 50;
		RECT rc0; GetClientRect (hwndParent, &rc0);
		if (x + cx >= rc0.right)
			x = rc0.right - cx - 1;
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;
	}
	else
	{
		RECT rc;
		GetWindowRect (hwndParent, &rc);
		POINT pt;
		if (prcFlash->top - rc.top >= cy)
			pt.y = prcFlash->top - cy;
		else
			pt.y = prcFlash->bottom;
		if (prcFlash->left >= rc.left)
			pt.x = prcFlash->left;
		else
			pt.x = rc.left;
		ScreenToClient (hwndParent, &pt);
		x = pt.x; y = pt.y;
	}

	SetWindowPos (m_hWnd, NULL, x, y, cx, cy, SWP_NOZORDER);
	SetWindowPos (m_hwndTB, NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);

	HRGN hRgn = CreateRoundRectRgn (0, 0, cx + 1, cy + 1, 3, 3);
	SetWindowRgn (m_hWnd, hRgn, TRUE);
}