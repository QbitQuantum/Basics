void MakeHyperlink(HWND hwnd, UINT staticid, COLORREF crLink)
{
	URLCtrl *url;
	HWND hwndCtrl = GetDlgItem(hwnd, staticid);

	// If already a hyperlink
	if((UINT_PTR)GetWindowLongPtr(hwndCtrl, GWLP_WNDPROC) == (UINT_PTR)URLCtrlProc)
		return;
	
	url = (URLCtrl *)HeapAlloc(GetProcessHeap(), 0, sizeof(URLCtrl));
	
	// Create font and cursor resources if this is
	// the first control being created
	if(InterlockedIncrement(&lRefCount) == 1)
	{
		LOGFONT lf;
		HFONT hf = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

		GetObject(hf, sizeof lf, &lf);
		lf.lfUnderline = TRUE;
		hfUnderlined = CreateFontIndirect(&lf);

		hCursor = CreateCursor(GetModuleHandle(0), 5, 2, 32, 32, XORMask, ANDMask);
	}
		
	//turn on notify style
    SetWindowLong(hwndCtrl, GWL_STYLE, GetWindowLong(hwndCtrl, GWL_STYLE) | SS_NOTIFY);
	SetWindowLong(hwndCtrl, GWL_EXSTYLE, GetWindowLong(hwndCtrl, GWL_EXSTYLE) | WS_EX_TRANSPARENT);


	// setup colours
	if(crLink != -1) url->crLink = crLink;
	else url->crLink = RGB(0,0,255);
	url->crVisited   = RGB(128,0,128);

	SendMessage(hwndCtrl, WM_SETFONT, (WPARAM)hfUnderlined, 0);

	// subclass
	url->oldproc = (WNDPROC)SetWindowLongPtr(hwndCtrl, GWLP_WNDPROC, (LONG_PTR)URLCtrlProc);
	SetWindowLongPtr(hwndCtrl, GWLP_USERDATA, (LONG_PTR)url);
	
	return;
}