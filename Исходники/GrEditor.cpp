/*func*------------------------------------------------------------------------
  description:
  in :
  out:
-----------------------------------------------------------------------------*/
BOOL CGrEditorApp::InitInstance()
{
	HRESULT hr;
	HFONT hFont;
	LOGFONT logFont;
	CGdiObject *pGdiObject;
	USES_CONVERSION;

   // Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_GR_OLE_INIT_FAILED);
		return FALSE;
	}
	hr = ::CoInitializeSecurity (NULL, -1, NULL, NULL,
	                             RPC_C_AUTHN_LEVEL_NONE, 
	                             RPC_C_IMP_LEVEL_IMPERSONATE, 
	                             NULL, EOAC_NONE, NULL);
	assert (SUCCEEDED (hr));    

   // prevent the Server-Busy dialog
   COleMessageFilter *pFilter = AfxOleGetMessageFilter();
   assert (pFilter);
   if (pFilter != NULL)
   {
      pFilter->EnableNotRespondingDialog(FALSE);
      pFilter->EnableBusyDialog(FALSE);
   }

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	_Module.Init (ObjectMap, m_hInstance);

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.

	SetRegistryKey (_T ("Softing\\4CONTROLV2\\4CONTROL Engineering"));

   int     iValue;
   CString strKey, strSec;
   strSec.LoadString(IDS_GR_REG_SECTION);

   strKey.LoadString(IDS_GR_REG_RUBBLINE);
	iValue = GetProfileInt ((LPCTSTR)strSec, (LPCTSTR)strKey, 0);
          WriteProfileInt ((LPCTSTR)strSec, (LPCTSTR)strKey, iValue );   // set Line draw mode to rubberlines

   strKey.LoadString(IDS_GR_REG_RUBB_RECON);
	iValue = GetProfileInt ((LPCTSTR)strSec, (LPCTSTR)strKey, 1);
          WriteProfileInt ((LPCTSTR)strSec, (LPCTSTR)strKey, iValue );   // set Line draw mode to rubberlines

   strKey.LoadString(IDS_GR_REG_ZOOMVALUE);
	iValue = GetProfileInt ((LPCTSTR)strSec, (LPCTSTR)strKey, 100);
          WriteProfileInt ((LPCTSTR)strSec, (LPCTSTR)strKey, iValue );   // set zoom factor for 4gr

   // default sizes for element insertion
   strKey.LoadString(IDS_GR_REG_STEPSIZE);
	iValue = GetProfileInt ((LPCTSTR)strSec, (LPCTSTR)strKey, (4<<16)+4); // <0: AutoSize:on; HiWord:X; LoWord:Y
          WriteProfileInt ((LPCTSTR)strSec, (LPCTSTR)strKey, iValue );

    // ST actions we yes the STEditor settings ..
	WriteProfileInt    (_T ("ST"), _T ("Case"           ), 0                    );   // keywords are case insensitive
	WriteProfileInt    (_T ("ST"), _T ("Chroma"         ), 1                    );   // coloring enabled
	WriteProfileString (_T ("ST"), _T ("Background"     ), _T ("255,255,255"   ));   // background color white
	WriteProfileString (_T ("ST"), _T ("Default Text"   ), _T ("0,0,0"         ));   // text color black
	WriteProfileString (_T ("ST"), _T ("Quote"          ), _T ("128,128,128"   ));   // string color grey
	WriteProfileString (_T ("ST"), _T ("Comment"        ), _T ("0,128,0"       ));   // comment color red
	WriteProfileString (_T ("ST"), _T ("Comment Start 1"), _T ("(*"            ));   // comments start with (*
	WriteProfileString (_T ("ST"), _T ("Comment End 1"  ), _T ("*)"            ));   // comments end with *)
	WriteProfileInt    (_T ("ST"), _T ("Keep Tabs"      ), 0                    );   // tabs are not converted to spaces
	WriteProfileInt    (_T ("ST"), _T ("Show Tabs"      ), 0                    );   // tabs are not visualized
	WriteProfileInt    (_T ("ST"), _T ("Tab Size"       ), 4                    );   // tab is as wide as 4 spaces
	WriteProfileString (_T ("ST"), _T ("Keywords"       ), _T ("stkeywords.ini"));   //

	// sizeof (LOGFONT) gives you the maximum size of a LOGFONT structure.
	// CGdiObject::GetObject possibly returns less because the font name
	// at the end of the LOGFONT structure may not take the whole space
	// reserved for it.
	hFont = (HFONT)GetStockObject (ANSI_FIXED_FONT);
	pGdiObject = CGdiObject::FromHandle (hFont);
	if (pGdiObject != NULL && pGdiObject->GetObject (sizeof (LOGFONT), &logFont) != 0)
	{
		int iFontSize;
		CWindowDC dc (m_pMainWnd);

		WriteProfileString (_T ("ST"), _T ("Font Name"), A2T (logFont.lfFaceName));
		iFontSize = MulDiv (logFont.lfHeight, 72, dc.GetDeviceCaps (LOGPIXELSY));
		WriteProfileInt (_T ("ST"), _T ("Font Size"), iFontSize);
		WriteProfileInt (_T ("ST"), _T ("Font Weight"), logFont.lfWeight);
		WriteProfileInt (_T ("ST"), _T ("Font Italic"), logFont.lfItalic);
		WriteProfileInt (_T ("ST"), _T ("CharSet"), logFont.lfCharSet);
	};

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplate = new CMultiDocTemplate(
		IDR_GR_TYPE,
		RUNTIME_CLASS(CGrEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGrEditorView));
	m_pDocTemplate->SetServerInfo(
		IDR_GR_TYPE_SRVR_EMB, IDR_GR_TYPE_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(m_pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, m_pDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_GR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

   // create a dummy image .. to solve the problem with DeleteTempMap in OnIdle
   m_pDummyImage = new CImageList();
   VERIFY (m_pDummyImage->Create (16, 15, TRUE, 0, 1));      
   CBitmap bm;
   bm.LoadBitmap (IDR_GR_MAINFRAME);
   m_pDummyImage->Add (&bm, RGB (192, 192, 192));

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CSTCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_DOC_OBJECT_SERVER);
	COleObjectFactory::UpdateRegistryAll();

	if (cmdInfo.m_bRegServer)
	{
		TCHAR szModule[_MAX_PATH+10];
		LPOLESTR pszModule;
		HRESULT hr;
		LPTYPELIB pTypeLib;
		USES_CONVERSION;

		::GetModuleFileName (m_hInstance, szModule, _MAX_PATH);
		pszModule = T2OLE (szModule);
		hr = LoadTypeLib (pszModule, &pTypeLib);
		if (SUCCEEDED (hr))
		{
			hr = RegisterTypeLib (pTypeLib, pszModule, NULL);
			pTypeLib->Release ();
		};

		return (FALSE);
	};

   // Prevents ProcessShellCommand from displaying
   // a message box when unregistering.
   if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
   {
      cmdInfo.m_bRunEmbedded = true;
   };
	
   // Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}