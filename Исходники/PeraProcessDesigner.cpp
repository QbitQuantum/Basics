BOOL CPeraProcessDesignerApp::InitInstance()
{
	ZTools::InitZToolsLog();

	if ( !m_CmdLine.Parse() )
	{
		MessageBox( NULL, "解析命令行失败！", g_lpszAppTitle, MB_OK | MB_TOPMOST );
		return FALSE;
	}

	m_hMetux = CreateMutex(NULL,TRUE,"PeraProcessDesigner.exe");
	if (m_hMetux)
	{
		if (ERROR_ALREADY_EXISTS== GetLastError())
		{
			HWND hwndPeraProcessDesignerCopied = FindPeraProcessDesignerMainWindow();
			//当有互斥，但是没找到窗口时，认为之前的进程还在启动中，简单处理，直接退出
			if ( hwndPeraProcessDesignerCopied)
			{
				if ( !m_CmdLine.GetValue( NULL ).IsEmpty() )
				{
#define WS_OPENWS_SENDMSG
#ifdef WS_OPENWS_SENDMSG
					DWORD dwProcessId = 0;
					GetWindowThreadProcessId(hwndPeraProcessDesignerCopied, &dwProcessId); 
					if ( GetTopModalWindow( dwProcessId ) == NULL )
					{
						CSharedMemory Mem;
						CString sMemData = g_lpszDoubleOpenWsMemStr;
						Mem.Init( g_lpszDoubleOpenWsMemName, sMemData.GetLength()+MAX_PATH );
						SendCopyData( hwndPeraProcessDesignerCopied, CPMSG_WORKSPACE_MAKESUREINFO, (LPVOID)NULL, 0 );
						sMemData.Empty();
						sMemData = (LPCTSTR)Mem.GetData();
						if ( sMemData.CompareNoCase( g_lpszDoubleOpenWsMemStr ) == 0 )
						{
							MessageBox( NULL, "建模环境处于活动状态，请先保存模型后重试！", g_lpszAppTitle, MB_OK | MB_TOPMOST );
						}
						else
						{
							CString sCmdLine = ::GetCommandLine();
							SendCopyData( hwndPeraProcessDesignerCopied, CPMSG_WORKSPACE_OPENWS, (LPVOID)(LPCTSTR)sCmdLine, sCmdLine.GetLength()+1 );
						}
					}
					else
					{
						MessageBox( NULL, "建模环境处于活动状态，请先保存模型后重试！", g_lpszAppTitle, MB_OK | MB_TOPMOST );
					}
#else
					MessageBox( hwndPeraProcessDesignerCopied, "建模环境已打开，请在建模环境中打开本文件！", g_lpszAppTitle, MB_OK | MB_TOPMOST );
#endif
				}
				if (IsIconic(hwndPeraProcessDesignerCopied)) 
					ShowWindow(hwndPeraProcessDesignerCopied,SW_RESTORE);

				SetForegroundWindow(hwndPeraProcessDesignerCopied);
				ZTools::WriteZToolsFormatLog("将已经运行的建模窗口激活,并前端显示...");

			}
			CloseHandle(m_hMetux);
			m_hMetux = NULL;
			ZTools::WriteZToolsFormatLog("已经存在一个建模客户端,本运行实例将退出...");

			return FALSE;
		}
	}

	m_LoginData.m_strRealName = m_CmdLine.GetValue( "realName" );
	m_LoginData.m_strUser = m_CmdLine.GetValue( "userName" );
	m_LoginData.m_strTicket = m_CmdLine.GetValue( "ticket-proxy" );

	WriteShareMemoryLoginInfo();

	CCrashHandler ch;
	ch.SetProcessExceptionHandlers();
	ch.SetThreadExceptionHandlers();

	//如果PeraTaskService进程不存在，自动启动
	StartPeraTaskService();

	//_CrtSetBreakAlloc(1300);
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//hModule = ::LoadLibrary("C:\\Users\\kunmiao-li\\Desktop\\TestBuild\\PeraLicMgr\\Release\\PeraLicMgr.dll");
//#ifndef _DEBUG

	if (!InitLicense("PeraWorkSpace"))
		return FALSE;
// 	if(!m_FlexNetMgr.CheckOutLicense("PeraWorkSpace"))
// 	{
// 		return FALSE;
// 	}



//	hModule = ::LoadLibrary(ZTools::FormatString("%s\\PeraLicMgr.dll", GetFlexwareBinPathMethod()).c_str());
//	if( hModule != NULL ) 
//	{
//		lpFnDLLfunc = (LPFNDLLFUNC) ::GetProcAddress(hModule, "CheckOutLicense");
//		if(lpFnDLLfunc != NULL)
//		{
//			if(!lpFnDLLfunc("PeraProcessDesigner"))
//			{
//				return FALSE;
//			}
//		}
//		else	
//		{
//			return FALSE;
//		}
//	}
//	else
//	{
//		AfxMessageBox("检测到系统安装不完整，请联系管理员重新安装！", MB_OK|MB_ICONINFORMATION);
//		return FALSE;
//	}
//#endif
	
	//if(!m_FlexNetMgr.InitNewJob("PeraProcessDesigner"))
	//{
	//	return FALSE;
	//}
	
	CWinApp::InitInstance();

	InitGDIPlus();
	LoadResLibImageSet();
	//LoadDefaultFont();

	//CBCGPPopupMenuBar::SetPeraPaint( g_crToolbarBg );

	//CXmlBase xml;
	//MSXML2::IXMLDOMDocument2Ptr pdoc = xml.GetXmlDocPtrByFile(GetExecDir() + "\\Manifest.xml");

	//MSXML2::IXMLDOMNodeListPtr pModels;
	//MSXML2::IXMLDOMNodePtr pModel;
	//long lModelCount;
	//HRESULT hr = S_OK;

	//map<CString, CString> mapAttrs;
	//map<CString, CString>::iterator iterAttrs;
	//CString str;

	//pModels = xml.GetNodeListPtr("/Manifest/Component", pdoc);
	//if (pModels != NULL)
	//{
	//	lModelCount = pModels->Getlength();
	//	for (long i=0; i<lModelCount; i++)
	//	{
	//		hr = pModels->get_item(i, &pModel);
	//		if (FAILED(hr) || NULL == pModel)
	//		{
	//			continue;
	//		}
	//		if (0 == xml.GetAttrsOfNode(mapAttrs, pModel))
	//		{
	//			continue;
	//		}

	//		iterAttrs = mapAttrs.find("RobotName");
	//		if (iterAttrs != mapAttrs.end()) str= iterAttrs->second;
	//	}
	//}

	//CCxArray3D a3d(DT_ARRAY3D_INT);
	//CString str3d = "[1,2,3,4,5,](4,3,2)"

	//CString str = "[1e150,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24](2,3,4)";
//	CString str = "[\"\\\\\\\",,1e150\",\"2\"](2)";
	//{
	//	CString str1;
	//	for (int a=0;a<2;a++)
	//	{
	//		for (int b=0;b<3;b++)
	//		{
	//			for (int c=0;c<4;c++)
	//			{

	//			}
	//		}
	//	}
	//}

	//
	//CxArrayND nd( DT_ARRAY1D_STRING );
	//nd.Parse( str );
	//vector<int> vPos;
	//vPos.push_back(0);
	////vPos.push_back(0);
	////vPos.push_back(0);
	//LPARAM lpData = nd.GetDataPtr( vPos );
	//CString * pData = reinterpret_cast< CString * > ( lpData );
	//nd.Clear();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	EnableTaskBarInteraction(FALSE);

	globalData.SetDPIAware ();
	//globalData.bDisableAero = TRUE;

	//Bar挺靠后，Slider宽度，由于Splitter最小宽度为4，所以此值不应小于4，否则与Splitter不协调。
	CBCGPSlider::m_nDefaultWidth = 4;

	// All registry read/write operations will be produced via CBCGPXMLSettings gateway:
	CBCGPRegistrySP::SetRuntimeClass (RUNTIME_CLASS (CBCGPXMLSettings));

	// Read settings:
	CBCGPXMLSettings::ReadXMLFromFile (FALSE, GetExecDir() + _T("\\user.xml"));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("PeraProcessDesigner"));
	//LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	//SetRegistryBase (_T("Settings"));

	RECT rectDesktop;
	SystemParametersInfo(SPI_GETWORKAREA,0,(PVOID)&rectDesktop,0);
	m_rcLastWindowPlacement = rectDesktop;
	CRect rectDesktop2 = rectDesktop;
	int nFlag = 0;
	int nShowCmd = 0;
	LoadWindowPlacement( m_rcLastWindowPlacement, nFlag, nShowCmd );

	StoreWindowPlacement (rectDesktop2, 2, SW_SHOWMAXIMIZED);

	theGlobalConfig.Load();

	m_bAloneVersionWs = IsPeraProcessRunnerInstalled();

	CCxBCGPVisualManager2007::SetStyle (CCxBCGPVisualManager2007::VS2007_Silver);
	CCxBCGPVisualManager2007::SetDefaultManager (RUNTIME_CLASS (CCxBCGPVisualManager2007));

	//globalData.bDisableAero = TRUE;
	//globalData.bIsOSAlphaBlendingSupport = TRUE;

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitMouseManager();
	//InitContextMenuManager();
	InitKeyboardManager();

	// Enable user-defined tools. If you want allow more than 10 tools,
	// add tools entry to resources (ID_USER_TOOL11, ID_USER_TOOL12,...)
	EnableUserTools (ID_TOOLS_ENTRY, ID_USER_TOOL1, ID_USER_TOOL10);

	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAIN,
		RUNTIME_CLASS(CPeraProcessDesignerDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPeraProcessDesignerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAIN))
		return FALSE;
	
	m_bCreate = TRUE;

	m_pMainWnd = pMainFrame;

	//basehtmldialog中，屏蔽快捷键
	g_hwndMainWindow = pMainFrame->GetSafeHwnd();

	g_pLoadingWindow = new CLoadingWindow( TIMER_LOADING_WINDOW, IDD_DIALOG_LOGIN_BK, m_pMainWnd );
	g_pLoadingWindow->Create( IDD_DIALOG_LOGIN_BK, m_pMainWnd );
	g_pLoadingWindow->Init( GetExecDir() + "\\Res\\DlgProgress\\DlgProgress.png" );

	pMainFrame->m_wndMenuBar.LoadData();

	//pMainFrame->OnMenuModuleOpenjianmo();

	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd


	// Parse command line for standard shell commands, DDE, file open
	//CCommandLineInfo cmdInfo;
	//ParseCommandLine(cmdInfo);


	//if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	//{
	//	if (!pMainFrame->LoadMDIState (GetRegSectionPath ()) || 
	//		DYNAMIC_DOWNCAST(CMDIChildWnd, pMainFrame->GetActiveFrame()) == NULL)
	//	{
	//		if (!ProcessShellCommand(cmdInfo))
	//			return FALSE;
	//	}
	//}
	//else
	//{
	//	// Dispatch commands specified on the command line
	//	if (!ProcessShellCommand(cmdInfo))
	//		return FALSE;
	//}
	// The main window has been initialized, so show and update it

	pMainFrame->OnMenuModuleOpenjianmo();

	m_bInitMDI = TRUE;
	m_nCmdShow = SW_SHOWMAXIMIZED;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	//////////////////////////////////////////////////////////////////////////
	//日志输出窗口
#ifdef USE_DLGLOG
	m_dlgLog.Create(CDlgLog::IDD, NULL);
	//m_dlgLog.ShowWindow(SW_SHOW);

// 	int x, y; 
// 	x = GetSystemMetrics(SM_CXFULLSCREEN); //屏幕宽度 
// 	y = GetSystemMetrics(SM_CYFULLSCREEN); //屏幕高度  

	CRect rectFull;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rectFull,0);

	CRect rect;
	m_dlgLog.GetWindowRect(rect);
	rect.MoveToXY(0, rectFull.bottom - rect.Height());
	m_dlgLog.MoveWindow(rect);
#endif // USE_DLGLOG
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//延长票据有效期
	StartKeepTicketThread();
	//////////////////////////////////////////////////////////////////////////
	//在线编辑用到的共享内存初始化
	m_pSharedMemoryOnlineEdit = NULL;
	m_pSharedMemoryOnlineEdit = new SharedMemoryOnlineEdit();
	//////////////////////////////////////////////////////////////////////////
	g_ReadRobotDB.Load();

	pMainFrame->m_wndLoginBar.RedrawWindow();

	CString sParamFile = m_CmdLine.GetValue( NULL );
	if ( !sParamFile.IsEmpty() )
	{
		ZTools::WriteZToolsFormatLog( "--------------********打开文件[%s]**********-------------", sParamFile );
		theApp.m_processMgr.Open( sParamFile );
	}
	else
	{
		ZTools::WriteZToolsLog( "--------------********未打开文件逻辑**********-------------" );
		CDlgStart lgn;
		lgn.DoModal();
	}

#ifdef USE_DLGLOG
	m_dlgLog.ShowWindow(SW_SHOW);
#endif // USE_DLGLOG

	//////////////////////////////////////////////////////////////////////////
	WINDOWPLACEMENT wp;
	memset(&wp, NULL, sizeof(wp));
	wp.length = sizeof (WINDOWPLACEMENT);

	if (pMainFrame->GetWindowPlacement (&wp))
	{
		wp.rcNormalPosition = m_rcLastWindowPlacement;

		RECT rectDesktop;
		SystemParametersInfo(SPI_GETWORKAREA,0,(PVOID)&rectDesktop,0);
		OffsetRect(&wp.rcNormalPosition, -rectDesktop.left, -rectDesktop.top);

		pMainFrame->SetWindowPlacement (&wp);

	}
	return TRUE;
}