BOOL CWinHTTrackApp::InitInstance()
{
  /* See <https://msdn.microsoft.com/library/ff919712> */
#if (defined(_WIN32) && (!defined(_DEBUG)))
  {
    /* See KB 2389418
    "If this parameter is an empty string (""), the call removes the 
    current directory from the default DLL search order" */
    BOOL (WINAPI*const k32_SetDllDirectoryA)(LPCSTR) = 
      (BOOL (WINAPI *)(LPCSTR))
      GetProcAddress(GetModuleHandle("kernel32.dll"), "SetDllDirectoryA");
    if (k32_SetDllDirectoryA != NULL && !k32_SetDllDirectoryA("")) {
      /* Do no choke on NT or 98SE with KernelEx NT API (James Blough) */
      const DWORD dwVersion = GetVersion();
      const DWORD dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
      const DWORD dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
      if (dwMajorVersion >= 5) {
        assertf(!"SetDllDirectory failed");
      }
    }
  }
#endif

  /* No error messageboxes */
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX);

  /* Inits */
  CrashReportInit();
  hts_set_error_callback(httrackErrorCallback);
  hts_init();

  WhttMutex = CreateMutex(NULL,FALSE,NULL);

  // Change the registry key under which our settings are stored.
  // TODO: You should modify this string to be something appropriate
  // such as the name of your company or organization.
  SetRegistryKey("WinHTTrack Website Copier");
  LANG_INIT();    // petite init langue
  
  /* INDISPENSABLE pour le drag&drop! */
  InitCommonControls();
  if (!AfxOleInit())
  {
	  AfxMessageBox(LANG(LANG_F1));
	  return FALSE;
  }
  AfxEnableControlContainer();
  
  // Pointeur sur CShellApp
  CShellApp_app=&app;
  this_app=this;
  _Cinprogress_inst=NULL;
  LibRasUse=0;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

  httrack_icon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

  // DOC //
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWinHTTrackDoc),
		RUNTIME_CLASS(CSplitterFrame),       // main SDI frame window
		RUNTIME_CLASS(CView)); 
	AddDocTemplate(pDocTemplate);

  /*
	CMDIFrameWnd* pMainFrame = new CMDIFrameWnd;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
  */

	// create main window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	int nCmdShow = m_nCmdShow;


  // Also in this example, there is only one menubar shared between
	//  all the views.  The automatic menu enabling support of MFC
	//  will disable the menu items that don't apply based on the
	//  currently active view.  The one MenuBar is used for all
	//  document types, including when there are no open documents.

  // enable file manager drag/drop and DDE Execute open
	pMainFrame->DragAcceptFiles();

  // Now finally show the main menu
	//pMainFrame->ShowWindow(m_nCmdShow);
	//pMainFrame->UpdateWindow();
	m_pMainWnd = pMainFrame;

  // command line arguments are ignored, create a new (empty) document
	//OnFileNew();
  // DOC //

  // Parse command line for standard shell commands, DDE, file open
  CCommandLineInfo cmdInfo;
  ParseCommandLine(cmdInfo);

  TCHAR ModulePath[MAX_PATH + 1];
  ModulePath[0] = '\0';
  ::GetModuleFileName(NULL, ModulePath, sizeof(ModulePath)/sizeof(TCHAR) - 1);
  hts_rootdir(ModulePath);

  // Restore position
	((CMainFrame*)m_pMainWnd)->InitialShowWindow(nCmdShow);
	pMainFrame->UpdateWindow();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

  // Init Winsock
  WSockInit();

	// The one and only window has been initialized, so show and update it.
	//m_pMainWnd->ShowWindow(SW_SHOW);
	//m_pMainWnd->UpdateWindow();

  /*CWinApp* app=AfxGetApp();
  POSITION pos;
  pos=app->GetFirstDocTemplatePosition();
  CDocTemplate* templ = app->GetNextDocTemplate(pos);
  pos=templ->GetFirstDocPosition();
  CDocument* doc  = templ->GetNextDoc(pos);

  CRuntimeClass* pRuntimeClass = RUNTIME_CLASS( CTest );
  CObject* pObject = pRuntimeClass->CreateObject();
  ASSERT( pObject->IsKindOf( RUNTIME_CLASS( CTest ) ) );
  
  doc->AddView((CView*) pObject);
  */

  {
    // enable file manager drag/drop and DDE Execute open
    EnableShellOpen();
    RegisterShellFileTypes();

    CWinApp* pApp = AfxGetApp();

    // register "New File" handler
    if (pApp->GetProfileInt("Interface","SetupRun",0) != 1
      || pApp->GetProfileInt("Interface","SetupHasRegistered",0) == 1) {
        HKEY phkResult;
        DWORD creResult;
      if (RegCreateKeyEx(HKEY_CLASSES_ROOT,".whtt",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&phkResult,&creResult)==ERROR_SUCCESS) {
        RegCloseKey(phkResult);
        if (RegCreateKeyEx(HKEY_CLASSES_ROOT,".whtt\\ShellNew",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&phkResult,&creResult)==ERROR_SUCCESS) {
          char voidbuff='\0';
          RegSetValueEx(phkResult,"NullFile",0,REG_SZ,(LPBYTE)&voidbuff,1);
          RegCloseKey(phkResult);
        }
      }   
    }

    // Infos la 1ere fois!
    if (pApp->GetProfileInt("Interface","FirstRun",0) != 3) {
      pApp->WriteProfileInt("Interface","FirstRun",3);

      Cabout about;
      about.DoModal();
      
      // Default proxy? Check is the current IP looks local or not.
      BOOL isPublic = FALSE;
      char hostname[256];
      if (gethostname(hostname, sizeof(hostname) - 1) == 0) {
        struct addrinfo* res = NULL;
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = PF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        if (getaddrinfo(hostname, NULL, &hints, &res) == 0) {
          if (res->ai_addr != NULL && res->ai_addrlen > 0) {
            if (res->ai_family == AF_INET) {
              sockaddr_in *const si = (sockaddr_in*) res->ai_addr;
              const unsigned char *const ipv4 = (unsigned char*) &si->sin_addr;
              isPublic = ! (
                ipv4[0] == 10  /* 10/8 */
                || (ipv4[0] == 192 && ipv4[1] == 168)  /* 192.168/16 */
                || (ipv4[0] == 172 && ipv4[1] >= 16 && ipv4[1] <= 31)  /* 172.16/12 */
                );
            } else if (res->ai_family == AF_INET6) {  /* assume no more proxy */
              isPublic = TRUE;
            }
          }
        }
        if (res) {
          freeaddrinfo(res);
        }
      }
      if (!isPublic && maintab) {
        maintab->DefineDefaultProxy();
        if (maintab->DoModal()!=IDCANCEL) {
          // Default proxy values
          CString strSection       = "OptionsValues";
          MyWriteProfileString("",strSection, "Proxy",maintab->m_option10.m_proxy);
          MyWriteProfileString("",strSection, "Port",maintab->m_option10.m_port);
        }
        maintab->UnDefineDefaultProxy();
      }
    }
  }
  

#ifdef HTTRACK_AFF_WARNING
#ifndef _DEBUG
  AfxMessageBox("--WARNING--\r\n"HTTRACK_AFF_WARNING);
#endif
#endif

  return TRUE;
}