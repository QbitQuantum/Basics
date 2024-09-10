BOOL CFdmApp::InitInstance()
{
	g_crashReporter.reset (new vmsAppCrashReporter (
		g_appVersion.getVersion ()->m_tstrProductName,
		L"",
		g_appVersion.getVersion ()->m_tstrFileVersion,
		L"freedownloadmanager.org", L"/dump.php"));

	bool bContinue = true;
	if (g_crashReporter->CheckIfSubmitDumpIsRequestedByCommandLine (bContinue))
	{
		if (!bContinue)
			return FALSE;
	}

	g_crashReporter->InitializeCrashCatcher ();

	AfxEnableControlContainer ();

	{
		_configthreadlocale (_DISABLE_PER_THREAD_LOCALE);
		tstringstream tss;
		tss << _T (".") << GetACP ();
		_tsetlocale(LC_ALL, tss.str ().c_str ());
		_configthreadlocale (_ENABLE_PER_THREAD_LOCALE);
	}

	
	SetRegistryKey (IDS_COMPANY);

	CheckRegistry ();

	fsIECatchMgr::CleanIEPluginKey ();

	
	CString strPath = GetProfileString (_T(""), _T("Path"), _T(""));
	BOOL bNeedLocalRegister = FALSE;
	if (strPath == _T(""))
	{
		CRegKey key;
		if (ERROR_SUCCESS == key.Open (HKEY_CURRENT_USER, _T("Software\\FreeDownloadManager.ORG\\Free Download Manager"), KEY_WRITE))
			vmsSHCopyKey (HKEY_LOCAL_MACHINE, _T("Software\\FreeDownloadManager.ORG\\Free Download Manager"), key);
		strPath = GetProfileString (_T(""), _T("Path"), _T(""));
		bNeedLocalRegister = strPath != "";
	}

	if (GetFileAttributes (strPath + _T("\\fdm.exe")) == DWORD (-1))
	{
		strPath = _T("");
		bNeedLocalRegister = false;
	}

	
	
	if (strPath == _T("") || FALSE == SetCurrentDirectory (strPath))
		_dwAppState |= APPSTATE_PORTABLE_MODE;

	TCHAR tszExeDir [MY_MAX_PATH], tszExeFile [MY_MAX_PATH];
	GetModuleFileName (NULL, tszExeFile, sizeof (tszExeFile));
	fsGetPath (tszExeFile, tszExeDir);

	if (IS_PORTABLE_MODE)
	{
		strPath = tszExeDir;
		SetCurrentDirectory (strPath);
	}

	m_strAppPath = strPath;
	if (m_strAppPath.IsEmpty () == FALSE)
	{
		if (m_strAppPath [m_strAppPath.GetLength ()-1] != '\\' &&
				m_strAppPath [m_strAppPath.GetLength ()-1] != '/')
			m_strAppPath += '\\';
	}

	if (IS_PORTABLE_MODE == false)
	{
		CString strDataFldr = tszExeDir; strDataFldr += _T("Data");
		
		
		
		if (m_strAppPath.CompareNoCase (tszExeDir) &&
			 DWORD (-1) != GetFileAttributes (strDataFldr))
		{
			
			_dwAppState |= APPSTATE_PORTABLE_MODE;
			_dwAppState |= APPSTATE_PORTABLE_MODE_NOREG;
			m_strAppPath = tszExeDir;
		}
	}

	if (IS_PORTABLE_MODE)
	{
		
		vmsAppSettingsStore* pStgs = _App.get_SettingsStore ();
		CString strStgsFile = m_strAppPath + "Data\\settings.dat";
		fsBuildPathToFile (strStgsFile);
		pStgs->LoadSettingsFromFile (strStgsFile);
		_App.ApplySettingsToMutexes ();
	}

	BOOL bNoLng = FALSE;

	if (FALSE == InitLanguage ())
		bNoLng = TRUE;

	if (_tcscmp (m_lpCmdLine, _T("-suis")) == 0 || 
			_tcscmp (m_lpCmdLine, _T("-euis")) == 0 ||
			_tcscmp (m_lpCmdLine, _T("-duis")) == 0)
	{
		IntegrationSettings ();
		return FALSE;
	}

	if (IS_PORTABLE_MODE)
	{
		
		
		
		TCHAR szTmpFile [MY_MAX_PATH];
		CString str = m_strAppPath; str += _T("Data");
		CreateDirectory (str, NULL);
		if (0 == GetTempFileName (str, _T("fdm"), 0, szTmpFile))
			MessageBox (NULL, LS (L_NOWRITEACCESSTODATAFOLDER), vmsFdmAppMgr::getAppName (), MB_ICONWARNING);
		else
			DeleteFile (szTmpFile);
	}

	_SkinMgr.Initialize ();

	_IECatchMgr.ReadSettings ();
	_NOMgr.Initialize ();
	_IECMM.ReadState ();

	
	HRESULT hRes = OleInitialize (NULL);
	
	if (FAILED(hRes))
		return FALSE;
	
	m_bCOMInited = TRUE;

	const tstring currentVersion = vmsFdmAppMgr::getVersion ()->m_fileVersion.ToString ();
	bool currentVersionFirstRun = currentVersion != _App.RecentVersionRun ();
	if (currentVersionFirstRun)
		_App.RecentVersionRun (currentVersion);

	vmsAppGlobalObjects::Create2 (currentVersionFirstRun);

	fsFDMCmdLineParser cmdline;

	cmdline.Parse (fsFDMCmdLineParser::Elevated);

	if (cmdline.isRunAsElevatedTasksProcessor ())
	{
		RunAsElevatedTasksProcessor (cmdline);
		return FALSE;
	}

	if (cmdline.isNeedExit ())
		return FALSE;

	m_bForceSilentSpecified = cmdline.is_ForceSilentSpecified ();

	if (cmdline.isNeedRegisterServer ())
	{
		onNeedRegisterServer ( false );
		return FALSE;
	}
	else if (cmdline.isNeedRegisterServerUserOnly ())
	{
		onNeedRegisterServer ( true );
		return FALSE;
	}
	else if (cmdline.isNeedUnregisterServer ())
	{
		onNeedUnregisterServer ();
		return FALSE;
	}

	if (vmsWinSecurity::os_supports_elevation () && 
		_tcsncmp (m_lpCmdLine, _T("-nelvcheck"), 10) && _tcsicmp (m_lpCmdLine, _T("-autorun")))
	{
		if (vmsWinSecurity::IsProcessElevated ())
		{
			WCHAR wsz [MAX_PATH] = L"";
			GetModuleFileNameW (NULL, wsz, MAX_PATH);
			std::wstring wstr = L"\"";
			wstr += wsz;
			wstr += L"\" -nelvcheck ";
			wstr += CT2WEX<> (m_lpCmdLine);
			_appMutex.CloseMutex ();
			STARTUPINFOW si = {0}; PROCESS_INFORMATION pi = {0};
			si.cb = sizeof (si);
			if (vmsWinSecurity::RunAsDesktopUser (wsz, (LPWSTR)wstr.c_str (), NULL, si, pi))
				return FALSE;
			_appMutex.Create ();
		}
	}

	cmdline.Parse (fsFDMCmdLineParser::Normal);

	if (CheckFdmStartedAlready (m_bForceSilentSpecified == FALSE))
		return FALSE;

	if (!InitATL())
		return FALSE;

	_App.StartCount (_App.StartCount () + 1);

	
	
	if (IS_PORTABLE_MODE && (_dwAppState & APPSTATE_PORTABLE_MODE_NOREG) == 0)
		Install_RegisterServer ();

	
	
	
	
	vmsFilesToDelete::Process ();

	if (bNeedLocalRegister)
		RegisterServer (FALSE);

	

#ifdef _AFXDLL
	Enable3dControls();			
#else
	Enable3dControlsStatic();	
#endif

	CheckLocked ();

	_UpdateMgr.ReadSettings ();
	
	if (_UpdateMgr.IsStartUpdaterNeeded ())
	{
		if (_UpdateMgr.StartUpdater ())	
			return FALSE;	
		else
			::MessageBox (NULL, LS (L_CANTFINDUPDATER), LS (L_ERR), MB_ICONERROR);
	}

	vmsFlvSniffInjector::o ().Enable (_App.FlvMonitoring_Enable () != FALSE);

	LoadHistory ();

	_Snds.ReadSettings ();

	if (!vmsBtSupport::isBtDllValid ())
	{
		MessageBox (NULL, LS (L_INVALID_BT_MODULE), _T ("Free Download Manager"), MB_ICONERROR);
		return FALSE;
	}

	auto ytdllmgr = std::make_shared <vmsYouTubeParserDllMgr> (
		std::make_shared <vmsAppDataFolder> (L"FreeDownloadManager.ORG", L"Free Download Manager"),
		currentVersionFirstRun);
	vmsYouTubeParserDllMgr::reset (ytdllmgr);

	auto avMerger = std::make_shared<vmsAVMergerFFMPEG>();
	auto avAfterMergeAction = std::make_shared<vmsYouTubeAfterMergeAction>();
	auto avYouTubeMergingMgr = std::make_shared <vmsAVMergingMgr>( avMerger, avAfterMergeAction, 1 );	
	_YouTubeDldsMgr.setYouTubeAVMergingMgr( avYouTubeMergingMgr );

	CMainFrame* pFrame = NULL;
	fsnew1 (pFrame, CMainFrame);
	m_pMainWnd = pFrame;

	
	if (FALSE == pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, 
		NULL, NULL))
	{
		return FALSE;
	}

	
	BOOL bHidden = _tcscmp (m_lpCmdLine, _T ("-autorun")) == 0;

	_App.View_ReadWndPlacement (pFrame, _T("MainFrm"), 
		bHidden ? fsAppSettings::RWPA_FORCE_SWHIDE_AND_KEEP_MINIMIZED_MAXIMIZED_STATE : fsAppSettings::RWPA_NONE);

	if (!bHidden)
	{
		if (_App.Prg_StartMinimized ())
		{
			if (IsWindowVisible (pFrame->m_hWnd))
				pFrame->ShowWindow (SW_MINIMIZE);
		}
		else
		{
			pFrame->UpdateWindow();
			if (pFrame->IsWindowVisible ())
				pFrame->SetForegroundWindow ();
		}
	}

	m_bStarting = FALSE;

	
	hRes = _Module.RegisterClassObjects (CLSCTX_LOCAL_SERVER, 
				REGCLS_MULTIPLEUSE);
	if (FAILED (hRes))
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				hRes,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				(LPTSTR) &lpMsgBuf,
				0,
				NULL 
				);
			
			
			
			MessageBox( NULL, (LPCTSTR)lpMsgBuf, nullptr, MB_OK | MB_ICONINFORMATION );
			
			LocalFree( lpMsgBuf );
	}
	m_bATLInited2 = SUCCEEDED (hRes);

	return TRUE;
}