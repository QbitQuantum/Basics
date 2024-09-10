VOID CGameProcedure::CreateMainWnd(VOID)
{
	//------------------------------------------------------
	//计算窗口大小
	m_bMinimized		= FALSE;
	m_bFullScreen		= TRUE;
	fVector2 fResoution;
	if (CGameProcedure::s_pVariableSystem->GetAs_Int("View_FullScreen"))
	{
		fResoution.x  = (float)::GetSystemMetrics(SM_CXSCREEN);
		fResoution.y  = (float)::GetSystemMetrics(SM_CYSCREEN);	
	}
	else
	{
		fResoution = s_pVariableSystem->GetAs_Vector2("View_Resoution");
	}
	CGameProcedure::m_fWindowFOV = fResoution.x / fResoution.y;
	SetRect(&m_rectWindow, 0, 0, (int)fResoution.x, (int)fResoution.y);
	AdjustWindowRect(&m_rectWindow, DEFWINDOW_STYLE, FALSE);

	SetRect(&m_rectFCOffset, m_rectWindow.left, m_rectWindow.top, 
		m_rectWindow.right-(int)fResoution.x, m_rectWindow.bottom-(int)fResoution.y);

	UINT dwX = (::GetSystemMetrics(SM_CXFULLSCREEN)-(m_rectWindow.right-m_rectWindow.left))/2;
	UINT dwY = (::GetSystemMetrics(SM_CYFULLSCREEN)-(m_rectWindow.bottom-m_rectWindow.top))/2;
	OffsetRect(&m_rectWindow, -m_rectFCOffset.left, -m_rectFCOffset.top);
	OffsetRect(&m_rectWindow, dwX, dwY);

	m_bActive			= true;
	m_bRenderingPaused	= FALSE;

	//------------------------------------------------------
	//注册窗口类
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= (WNDPROC)_MainWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= g_hInstance;
	wcex.hIcon			= LoadIcon(g_hInstance, (LPCTSTR)IDD_GAME_DIALOG);
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground	= (HBRUSH)NULL; //GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= (LPCTSTR)NULL;
	wcex.lpszClassName	= MAINWINDOW_CLASS;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	RegisterClassEx(&wcex);

	//------------------------------------------------------
	//创建窗口
	CHAR szTitle[MAX_PATH];
	_snprintf(szTitle, MAX_PATH, "%s %s (%s %s)", GAME_TITLE, VERSION_INFO, __DATE__, __TIME__);

	HWND hWnd = CreateWindowEx(NULL, MAINWINDOW_CLASS, szTitle, 
		DEFWINDOW_STYLE,
		m_rectWindow.left, m_rectWindow.top, 
		m_rectWindow.right-m_rectWindow.left, 
		m_rectWindow.bottom-m_rectWindow.top,
		NULL, NULL, g_hInstance, NULL);

	if (!hWnd)
	{
		TDThrow(_T("Can't create main window!"));
	}

	if (CGameProcedure::s_pVariableSystem->GetAs_Int("View_FullScreen"))
	{
		s_pEventSystem->PushEvent(GE_VARIABLE_CHANGED, "View_FullScreen", "1");
		s_pEventSystem->PushEvent(GE_CHAT_ADJUST_MOVE_CTL, (INT)fResoution.x, (INT)fResoution.y);
	}else
	{
		const STRING& strVariable = CGameProcedure::s_pVariableSystem->GetAs_String("View_Resoution");
		s_pEventSystem->PushEvent(GE_VARIABLE_CHANGED,"View_Resoution", strVariable.c_str());
		s_pEventSystem->PushEvent(GE_CHAT_ADJUST_MOVE_CTL, (INT)fResoution.x, (INT)fResoution.y);
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	g_hMainWnd = hWnd;
}