BOOL CMyApp::InitInstance()     {
	
	if (!DComOk()) {
		AfxMessageBox(_T("DCOM OLE Not supported"),MB_SYSTEMMODAL+MB_OK);
		return FALSE;       
	}      

	
	// Initialize OLE libraries       
	if (!AfxOleInit2())        {
		AfxMessageBox(_T("OLE Initialization Failed!"),MB_SYSTEMMODAL+MB_OK);
		return FALSE;       
	}        // Initialize the ATL Module

	_Module.Init(ObjectMap,m_hInstance); 
    _Module.dwThreadID = GetCurrentThreadId();

#ifdef _AFXDLL
		Enable3dControls(); // Call this when using MFC in a shared DLL
#else      
		Enable3dControlsStatic(); // Call this when linking
	// to MFC statically     
#endif

    //Reg UnregSever 
    TCHAR szTokens[] = _T("-/");
	int nRet = 0;
	BOOL bRun = TRUE;
	LPCTSTR lpszToken = FindOneOf(m_lpCmdLine, szTokens);

	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_ModbusServer, FALSE);
			nRet = _Module.UnregisterServer();
			nRet = UnRegisterTypeLib(
			   LIBID_MODBUSSERVERLib, 1, 0,
               LOCALE_NEUTRAL, SYS_WIN32);
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_ModbusServer, TRUE);
			nRet = _Module.RegisterServer(TRUE);
			bRun = FALSE;
			// Update the System Registry
			COleObjectFactory::UpdateRegistryAll(); // MFC Classes
			if(!(SUCCEEDED(nRet))){
				AfxMessageBox("Register server Failed",MB_SYSTEMMODAL+MB_OK);
			}
			bRun=FALSE;
			break;
		}
		lpszToken = FindOneOf(lpszToken, szTokens);
	}
		
	// ATL Classes
	// Create the dialog box or other stuff here
	// Register OLE Class Factories
	// MFC ones are for multiple as specified
	// by the IMPLEMENT_OLECREATE() macro
	//COleObjectFactory::RegisterAll();
	// ATL ones specifically register with REGCLS_MULTIPLEUSE
	if (bRun) {
		if(!(SUCCEEDED(_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER,
			REGCLS_MULTIPLEUSE)))){
				AfxMessageBox("RegisterClassObjects Failed",MB_SYSTEMMODAL+MB_OK);
		}
	}

	VERIFY(CTcpServer::StartWinsock());

	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())        {
		// Application was run with /Embedding or /Automation.
		// Don't show the main window in this case. 
		//Test();
		return TRUE;
	}   
	
	return FALSE; // Nothing to do, so exit.    
	
}