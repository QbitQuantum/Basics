BOOL CColorsApp::InitInstance()
{
	// Standard initialization

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	//
	// Convert the items in the Color menu to owner-draw.
	//
	CMenu* pMenu = pFrame->GetMenu ();
	ASSERT (pMenu != NULL);

	for (int i=0; i<5; i++)
		pMenu->ModifyMenu (ID_COLOR_RED + i, MF_OWNERDRAW, 
                    ID_COLOR_RED + i);

	return TRUE;
}