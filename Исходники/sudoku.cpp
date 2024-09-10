//------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int cmdShow)
{
	int i;
	HDC dc;
	MSG mesg;
	RECT rc;

	inst = hInstance;

	//DPIAware
	typedef BOOL(WINAPI *TGetProcAddress)();
	TGetProcAddress getProcAddress = (TGetProcAddress)GetProcAddress(GetModuleHandle(_T("user32")), "SetProcessDPIAware");
	if(getProcAddress) getProcAddress();

	memset(custom, 200, sizeof(custom));
	_tcscpy(pdfObject.fn, _T("sudoku.pdf"));
	pdfObject.pageWidth=595;
	pdfObject.pageHeight=842;
	pdfObject.count=6;
	pdfObject.countPerPage=6;
	pdfObject.border=40;
	pdfObject.spacing=20;
	readini();
	//load common controls
#if _WIN32_IE >= 0x0300
	INITCOMMONCONTROLSEX iccs;
	iccs.dwSize= sizeof(INITCOMMONCONTROLSEX);
	iccs.dwICC= ICC_BAR_CLASSES;
	InitCommonControlsEx(&iccs);
#else
	InitCommonControls();
#endif
	// create the main window
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.lpfnWndProc = WndMainProc;
	wc.hInstance = inst;
	wc.lpszClassName = CLASSNAME;
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon         = LoadIcon(inst, MAKEINTRESOURCE(IDI_MAINICON));
	if(!RegisterClass(&wc)){
#ifdef UNICODE
		msg("This version cannot run on Windows 95/98/ME.");
#else
		msg("RegisterClass failed");
#endif
		return 2;
	}
	scrW= GetSystemMetrics(SM_CXSCREEN);
	scrH= GetSystemMetrics(SM_CYSCREEN);
	aminmax(mainLeft, 0, scrW-50);
	aminmax(mainTop, 0, scrH-50);
	hWin = CreateWindow(CLASSNAME, title,
		WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN,
		mainLeft, mainTop, mainW, mainH, 0, 0, inst, 0);
	if(!hWin){
		msg("CreateWindow failed");
		return 3;
	}

	haccel= LoadAccelerators(inst, MAKEINTRESOURCE(IDR_ACCELERATOR));
	Naccel= CopyAcceleratorTable(haccel, accel, sizeA(accel));
	initLang();
	//create status bar
	statusbar= CreateStatusWindow(WS_CHILD, 0, hWin, 1);
	static int parts[]={100, 140, 210, 230, -1};
	dc=GetDC(hWin);
	for(i=0; i<sizeA(parts)-1; i++){
		parts[i]=parts[i]*GetDeviceCaps(dc, LOGPIXELSX)/96;
	}
	ReleaseDC(hWin, dc);
	SendMessage(statusbar, SB_SETPARTS, sizeA(parts), (LPARAM)parts);
	ShowWindow(statusbar, SW_SHOW);
	//create tool bar
	i=sizeA(tbb);
	for(TBBUTTON *u=tbb; u<endA(tbb); u++){
		if(u->fsStyle==TBSTYLE_SEP) i--;
	}
	toolbar = CreateToolbarEx(hWin,
		WS_CHILD|TBSTYLE_TOOLTIPS, 2, i,
		inst, IDB_TOOLBAR, tbb, sizeA(tbb),
		16, 16, 16, 15, sizeof(TBBUTTON));
	GetClientRect(toolbar, &rc);
	MapWindowPoints(toolbar, hWin, (POINT*)&rc, 2);
	toolH= rc.bottom;
	if(toolBarVisible) ShowWindow(toolbar, SW_SHOW);

	langChanged();
	ShowWindow(hWin, cmdShow);
	initSquare(false);

	UpdateWindow(hWin);
	toolBitmap();
	numButtons();

	while(GetMessage(&mesg, NULL, 0, 0)==TRUE){
		if(!TranslateAccelerator(hWin, haccel, &mesg)){
			TranslateMessage(&mesg);
			DispatchMessage(&mesg);
		}
	}
	if(delreg) deleteini(HKEY_CURRENT_USER);
	return 0;
}