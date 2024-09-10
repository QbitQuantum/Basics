BOOL InitInstance(HANDLE hInstance, int nCmdShow)
{
	g_hInst = (HINSTANCE)hInstance;
	
	OleInitialize(NULL);

	INITCOMMONCONTROLSEX	icex;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES | ICC_INTERNET_CLASSES;

	InitCommonControlsEx(&icex);

    g_hMainWnd = CreateWindowEx(0, _GAME_SERVER_CLASS, _GAME_SERVER_TITLE, 
							WS_OVERLAPPEDWINDOW|WS_VISIBLE,
							CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,                 
							NULL, NULL, (HINSTANCE)hInstance, NULL);

	g_hToolBar = CreateToolbarEx(g_hMainWnd, WS_CHILD|CCS_TOP|WS_VISIBLE|WS_BORDER,
									_IDW_TOOLBAR, sizeof(tbButtons) / sizeof(TBBUTTON), (HINSTANCE)hInstance, IDB_TOOLBAR,
									(LPCTBBUTTON)&tbButtons, sizeof(tbButtons) / sizeof(TBBUTTON),
									_BMP_CX, _BMP_CY, _BMP_CX, _BMP_CY, sizeof(TBBUTTON));

	RECT rcMainWnd, rcToolBar, rcStatusBar;

	GetClientRect(g_hMainWnd, &rcMainWnd);
	GetWindowRect(g_hToolBar, &rcToolBar);

	g_hStatusBar = CreateWindowEx(0L, STATUSCLASSNAME, _TEXT(""), WS_CHILD|WS_BORDER|WS_VISIBLE|SBS_SIZEGRIP,
									0, rcMainWnd.bottom - _STATUS_HEIGHT, (rcMainWnd.right - rcMainWnd.left), _STATUS_HEIGHT, g_hMainWnd, (HMENU)_IDW_STATUSBAR, g_hInst, NULL);

	int	nStatusPartsWidths[_NUMOFMAX_STATUS_PARTS];
	int nCnt = 0;
	
	for (int i = _NUMOFMAX_STATUS_PARTS - 1; i >= 0; i--)
		nStatusPartsWidths[nCnt++] = (rcMainWnd.right - rcMainWnd.left) - (90 * i);

	SendMessage(g_hStatusBar, SB_SETPARTS, _NUMOFMAX_STATUS_PARTS, (LPARAM)nStatusPartsWidths);

	GetWindowRect(g_hStatusBar, &rcStatusBar);

    g_hLogMsgWnd = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, _TEXT(""), 
							WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_EDITLABELS,
							0, (rcToolBar.bottom - rcToolBar.top), (rcMainWnd.right - rcMainWnd.left), 
							(rcMainWnd.bottom - rcMainWnd.top) - (rcToolBar.bottom - rcToolBar.top) - (rcStatusBar.bottom - rcStatusBar.top),
							g_hMainWnd, NULL, (HINSTANCE)hInstance, NULL);

	ListView_SetExtendedListViewStyleEx(g_hLogMsgWnd, 0, LVS_EX_FULLROWSELECT);

	LV_COLUMN	lvc;
	TCHAR		szText[64];

	lvc.mask	= LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt		= LVCFMT_LEFT;
	lvc.cx		= 150;
	lvc.pszText	= szText;

	for (i = 0; i < 3; i++)
	{
		lvc.iSubItem = i;
		LoadString((HINSTANCE)hInstance, IDS_LVS_LABEL1 + i, szText, sizeof(szText)/sizeof(TCHAR));
		
		ListView_InsertColumn(g_hLogMsgWnd, i, &lvc);
	}

	OrgLogMsgWndProc = (WNDPROC)SetWindowLong(g_hLogMsgWnd, GWL_WNDPROC, (LONG)LogMsgWndProc);

	SendMessage(g_hToolBar, TB_SETSTATE, (WPARAM)IDM_STOPSERVICE, (LPARAM)MAKELONG(TBSTATE_INDETERMINATE, 0));

	ShowWindow(g_hMainWnd, SW_SHOW);
	UpdateWindow(g_hMainWnd);

	if (WSAStartup(MAKEWORD(2, 2), &g_wsd) != 0)
		return (FALSE);

	srand((unsigned)time(NULL));

	BYTE	btInstalled;

	if (!jRegGetKey(_GAME_SERVER_REGISTRY, _TEXT("Installed"), (LPBYTE)&btInstalled))
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_CONFIGDLG), NULL, (DLGPROC)ConfigDlgFunc);

	TCHAR	wszDatabase[256];
	char	szDatabase[256];

	jRegGetKey(_GAME_SERVER_REGISTRY, _TEXT("Device"), (LPBYTE)wszDatabase);
	WideCharToMultiByte(CP_ACP, 0, wszDatabase, -1, szDatabase, sizeof(szDatabase), NULL, NULL);

	g_MirDB.SetDiagRec( __cbDBMsg );
	g_MirDB.Init();

	g_pConnCommon	= g_MirDB.CreateConnection( "Mir2_Common", "sa", "prg" );
	g_pConnGame		= g_MirDB.CreateConnection( szDatabase, "sa", "prg" );

	return TRUE;
}