BOOL CHookSrvApp::InitInstance()
{
	BOOL bIsAnotherInstanceRunning = 
		g_SingleInstanceObj.IsAnotherInstanceRunning();

	if (!bIsAnotherInstanceRunning)
	{
		#ifdef _AFXDLL
			Enable3dControls();			// Call this when using MFC in a shared DLL
		#else
			Enable3dControlsStatic();	// Call this when linking to MFC statically
		#endif
		// To create the main window, this code creates a new frame window
		// object and then sets it as the application's main window object.
		CMainFrame* pFrame = new CMainFrame;
		m_pMainWnd = pFrame;
		// create and load the frame with its resources
		pFrame->LoadFrame(
			IDR_MAINFRAME,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, 
			NULL,
			NULL
			);

		// The one and only window has been initialized, so show and update it.
		pFrame->ShowWindow(SW_HIDE);
		pFrame->UpdateWindow();
	} // if

	return (!bIsAnotherInstanceRunning);
}