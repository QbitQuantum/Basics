static void OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	RECT rc;
	GetClientRect(hWnd, &rc);

	HBRUSH brHilight = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
	HBRUSH brBkgnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	HPEN penBkgnd = CreatePen(PS_NULL, 0, 0);

	int maxTasks = (TaskCount > MAX_TASKS) ? MAX_TASKS : TaskCount;
	int half = maxTasks / 2;
	int firstTask = (AltTabPrgIdx + TaskCount - half) % TaskCount;

	for (int i = 0; i < maxTasks; i++) {
		int act = (firstTask + i) % TaskCount;
		CProgramItem *pi = TaskList[act];

		RECT rcItem;
		rcItem.left = rc.left;
		rcItem.top = rc.top + (i * SCALEY(20));
		rcItem.right = rc.right;
		rcItem.bottom = rc.top + ((i + 1) * SCALEY(20));

		HGDIOBJ hOrigBrush;
		if (act == AltTabPrgIdx) hOrigBrush = SelectObject(hDC, brHilight);
		else hOrigBrush = SelectObject(hDC, brBkgnd);
		HGDIOBJ hOrigPen = SelectObject(hDC, penBkgnd);

		Rectangle(hDC, rcItem.left, rcItem.top, rcItem.right, rcItem.bottom);

		SelectObject(hDC, hOrigPen);
		SelectObject(hDC, hOrigBrush);

		// icon for progs
		TCHAR pathFileName[MAX_PATH];
		GetProcessPathFileName(pi, pathFileName);

		SHFILEINFO sfi = { 0 };
		DWORD imageList;
		imageList = SHGetFileInfo(pathFileName, 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

		if (imageList != 0) {
			ImageList_DrawEx((HIMAGELIST) imageList, sfi.iIcon, hDC,
				rcItem.left + SCALEX(7), rcItem.top + SCALEY(1), SCALEX(16), SCALEY(16), CLR_NONE, CLR_NONE, ILD_NORMAL);
		}

		// font
		HGDIOBJ hOrigFont = SelectObject(hDC, HBoldFont);
		RECT rcText = rcItem;
		rcText.left += SCALEX(25);
		rcText.right -= SCALEX(25);
		if (act == AltTabPrgIdx) SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
		else SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
		int oldMode = SetBkMode(hDC, TRANSPARENT);

		UINT uFmt = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
		if (pi->ProcessId != 0) uFmt |= DT_NOPREFIX;		// we don not want to interpret & as mark of hot key

		DrawTextEndEllipsis(hDC, pi->Name, lstrlen(pi->Name), &rcText, uFmt);
		SetBkMode(hDC, oldMode);
		SelectObject(hDC, hOrigFont);

	}

	DeleteObject(brBkgnd);
	DeleteObject(penBkgnd);

	EndPaint(hWnd, &ps);
}