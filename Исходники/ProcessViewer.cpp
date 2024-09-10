BOOL CProcessViewerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
#if _MSC_VER < 1400
	Enable3dControls();			// Call this when using MFC in a shared DLL
#endif
#else
#if _MSC_VER < 1400
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	if( !IsUserAnAdmin() )
	{
		Utils::ShowWarning( _T( "You are not an administrator, some features won't be accessible!" ));
	}

	ChangeProcessPriority();
	CProcessViewerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}