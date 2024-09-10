BOOL CReClass2015App::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_STANDARD_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	SetRegistryKey(_T("ReClass 2015"));
	EnableTaskbarInteraction(FALSE);
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	crBackground		= GetProfileInt("Colors", "crBackground", crBackground);
	crSelect			= GetProfileInt("Colors", "crSelect", crSelect);
	crHidden			= GetProfileInt("Colors", "crHidden", crHidden);
	crOffset			= GetProfileInt("Colors", "crOffset", crOffset);
	crAddress			= GetProfileInt("Colors", "crAddress", crAddress);
	crType				= GetProfileInt("Colors", "crType", crType);
	crName				= GetProfileInt("Colors", "crName", crName);
	crIndex				= GetProfileInt("Colors", "crIndex", crIndex);
	crValue				= GetProfileInt("Colors", "crValue", crValue);
	crComment			= GetProfileInt("Colors", "crComment", crComment);	  
	crVTable			= GetProfileInt("Colors", "crVTable", crVTable);
	crFunction			= GetProfileInt("Colors", "crFunction", crFunction);
	crChar				= GetProfileInt("Colors", "crChar", crChar);
	crCustom			= GetProfileInt("Colors", "crCustom", crCustom);
	crHex				= GetProfileInt("Colors", "crHex", crHex);
	gbOffset			= GetProfileInt("Display", "gbOffset", gbOffset) > 0 ? true : false;
	gbAddress			= GetProfileInt("Display", "gbAddress", gbAddress) > 0 ? true : false;
	gbText				= GetProfileInt("Display", "gbText", gbText) > 0 ? true : false;
	gbFloat				= GetProfileInt("Display", "gbFloat", gbFloat) > 0 ? true : false;
	gbInt				= GetProfileInt("Display", "gbInt", gbInt) > 0 ? true : false;
	gbString			= GetProfileInt("Display", "gbString", gbString) > 0 ? true : false;
	gbPointers			= GetProfileInt("Display", "gbPointers", gbPointers) > 0 ? true : false;
	gbClassBrowser		= GetProfileInt("Display", "gbClassBrowser", gbClassBrowser) > 0 ? true : false;
	gbFilterProcesses	= GetProfileInt("Display", "gbFilterProcesses", gbFilterProcesses) > 0 ? true : false;


	// make toggle
	gbTop = false; //GetProfileInt("Display","gbTop",gbTop) > 0 ? true : false;

	CMDIFrameWnd* pFrame = new CMainFrame();
	m_pMainWnd = pFrame;
	if(!pFrame) 
		return FALSE;
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_ReClass2015TYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ReClass2015TYPE));

	HICON icon;
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_OPEN));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_CLOSED));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_CLASS));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_METHOD));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_VTABLE));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_DELETE));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_ADD));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_RANDOM));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_DROPARROW));	Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_POINTER));	Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_ARRAY));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_CUSTOM));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_ENUM));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_FLOAT));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_LEFT));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_RIGHT));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_MATRIX));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_INTEGER));	Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_TEXT));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_UNSIGNED));	Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_VECTOR));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_CHANGE));		Icons.push_back(icon);
	icon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_CAMERA));		Icons.push_back(icon);

	//Font.CreatePointFont(80,"Terminal");
	////Font.CreateFont(16, 8, 0, 0, FW_NORMAL,FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY, FIXED_PITCH, "Terminal");
	//FontWidth = 16;
	//FontHeight = 16;
	//FontWidth = 8;
	//FontHeight = 8;

	Font.CreateFont(16, 8, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, "Terminal");
	FontWidth = 8;
	FontHeight = 14;

	//FontWidth = 8;
	//FontHeight = 16;
	//Font.CreateFont(FontHeight, FontWidth, 0, 0, FW_NORMAL,FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY, FIXED_PITCH, "Fixedsys");
	//FontHeight = 14;

	//SmallFont.CreateFont(12, 8, 0, 0, FW_NORMAL,FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY, FIXED_PITCH, "Terminal");

	//UpdateMemoryMap();
	//UpdateExports();

	// Initialize the editor
	if (!Scintilla_RegisterClasses(AfxGetApp()->m_hInstance))
	{	
		AfxMessageBox("Scintilla failed to initiailze");
		return FALSE;
	}

	pFrame->ShowWindow(m_nCmdShow);
	pFrame->UpdateWindow();

	getDebugPriv();

	return TRUE;
}