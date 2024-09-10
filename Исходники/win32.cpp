DWORD __stdcall CreateThreadActiveX(IN void* pParam)
{
	static TCHAR szAppName[] = TEXT ("HelloWin") ;
	MSG          msg ;
	WNDCLASS     wndclass ;
	HWND         hwnd ;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = g_hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;

	//HWND hq=FindWindow(TEXT("Chrome_WidgetWin_100"),NULL);

	HWND hwndChrome=FindWindow(TEXT("Chrome_WidgetWin_1"),0);
	hwndChrome=GetParent(hwndChrome);   // ¸¸´°¿Ú

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	hwnd = CreateWindow (szAppName,                  // window class name
		TEXT ("The Hello Program"), // window caption
		WS_CHILDWINDOW,//WS_POPUP|WS_EX_TOOLWINDOW,//WS_OVERLAPPEDWINDOW,        // window style
		200,              // initial x position
		200,              // initial y position
		400,              // initial x size
		40,              // initial y size
		//CW_USEDEFAULT,              // initial x position
		//CW_USEDEFAULT,              // initial y position
		hwndChrome,                       // parent window handle
		NULL,                       // window menu handle
		g_hInstance,                  // program instance handle
		NULL) ;                     // creation parameters


	AtlAxWinInit();

	CoInitialize(NULL);

	// The window is attached; act appropriately

	if(hwnd)
	{			

		CAxWindow wnd;
		CLSID clsid;
		LPUNKNOWN pUnkCtrl, pUnkCont;

		IDispatch* pIDsp=NULL;

		HRESULT hr =::CLSIDFromString(L"{ED75F074-4A89-40B3-844C-B28281C3FD8E}",&clsid);

		hr = CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown,
			(void**)&pUnkCtrl);
		CComQIPtr <IPersistStreamInit> spPerStm(pUnkCtrl);
		spPerStm->InitNew();
		wnd.Attach(hwnd);
		wnd.AttachControl(pUnkCtrl, &pUnkCont);

		wnd.QueryControl(IID_IDispatch, (void**)&pIDsp);
	}
			
	ShowWindow (hwnd, SW_SHOW) ;
	UpdateWindow (hwnd) ;

	

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}

	::CoUninitialize();

	return msg.wParam;
}