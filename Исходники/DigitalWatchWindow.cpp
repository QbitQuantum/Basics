int DigitalWatchWindow::Create(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char szWindowClass[100];
	char szTitle[100];

	sprintf((char *)&szWindowClass, "DIGITALWATCH_BDA");
	sprintf((char *)&szTitle, "DigitalWatch");

	g_pData->hWnd = FindWindowW(CA2W(szWindowClass), NULL);

	//LATER: Option for multiple instances
	if (g_pData->hWnd != NULL && !g_pData->settings.application.multiple)
	{
		(log << "An instance of Digital Watch is already running.\n  Bringing the existing instance to the foreground.\n").Write();
		SetForegroundWindow(g_pData->hWnd);
		return FALSE;
	}

//	if (g_pData->hWnd != NULL && g_pData->settings.application.multiple)
//		g_pData->values.application.multiple = g_pData->settings.application.multiple;

	HBRUSH br = CreateSolidBrush(0x00000000);

	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEXA);

	wcex.style			= CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;// | CS_NOCLOSE | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)MainWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= 0;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DIGITALWATCH);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= br;
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	ATOM ar = RegisterClassExA(&wcex);

	USES_CONVERSION;
	g_pData->hWnd = CreateWindowA(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW/*WS_THICKFRAME*/, CW_USEDEFAULT, 0, 726, 435, NULL, NULL, NULL, NULL);
	if (!g_pData->hWnd)
	{
		__int64 err = GetLastError();
		//return_FALSE_SHOWMSG("Error creating window: " << err)
		return (log << "Error creating window: " << err << "\n").Show();
	}

	SetWindowLong(g_pData->hWnd, GWL_STYLE, GetWindowLong(g_pData->hWnd, GWL_STYLE) & (~(WS_CAPTION/* | WS_BORDER*/))); 

	if (g_pData->settings.window.startAtLastWindowPosition && g_pData->settings.loadedFromFile)
	{
		(log << "Restoring last window position. x=" << g_pData->values.window.position.x << " y=" << g_pData->values.window.position.y << " width=" <<g_pData->values.window.size.width << " height=" << g_pData->values.window.size.height << "\n").Write();
	}
	
	BOOL bFullscreen = g_pData->values.window.bFullScreen;
	g_pData->values.window.bFullScreen = FALSE;
	g_pTv->SetWindowPos(g_pData->values.window.position.x, g_pData->values.window.position.y, g_pData->values.window.size.width, g_pData->values.window.size.height, g_pData->settings.window.startAtLastWindowPosition && g_pData->settings.loadedFromFile, TRUE);
	g_pData->values.window.bFullScreen = bFullscreen;

	ShowWindow(g_pData->hWnd, nCmdShow);
	UpdateWindow(g_pData->hWnd);

	if (g_pData->settings.window.startFullscreen != 0)
	{
		(log << "Restoring fullscreen state\n").Write();
		g_pTv->Fullscreen();
	}
	if (g_pData->settings.window.startAlwaysOnTop != 0)
	{
		(log << "Restoring always on top\n").Write();
		g_pTv->AlwaysOnTop();
	}

	return TRUE;
}