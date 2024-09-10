BOOL CESFEA2DApp::InitInstance()
{
	Enable3dControls();	
	SetRegistryKey(_T("ESFEA"));
	LoadStdProfileSettings(8);

	CAnimateCtrl animctrl;

	m_sg.create_tree();

	m_i_manip_mode		= 0;
	m_drag_mode			= true;

	m_font.CreateFont(-11, 0, 0, 0, 0, 0, 0, 0,
							DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
							ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Arial"));

	m_font_small.CreateFont(-10, 0, 0, 0, FW_BOLD, 0, 0, 0,
								DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Arial Bold"));

	m_background_color.set_value(0.8f, 0.8f, 0.8f);

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	pFrame->LoadFrame(IDR_MAINFRAME, 
							WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, 
							NULL,
							NULL);

	m_app_icon = LoadIcon(IDI_SEJIKA);
	m_pMainWnd->SetIcon(m_app_icon, TRUE);
	m_pMainWnd->SetIcon(m_app_icon, FALSE);

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	m_last_file = GetProfileString("user", "last_file", "..\\Mesh Files\\P3.xml");
	open_file(m_last_file);

	return TRUE;
}