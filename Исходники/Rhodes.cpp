// This method is called immediately before entering the message loop.
// It contains initialization code for the application.
// Returns:
// S_OK => Success. Continue with RunMessageLoop() and PostMessageLoop().
// S_FALSE => Skip RunMessageLoop(), call PostMessageLoop().
// error code => Failure. Skip both RunMessageLoop() and PostMessageLoop().
HRESULT CRhodesModule::PreMessageLoop(int nShowCmd) throw()
{
    HRESULT hr;
	/*HRESULT hr = __super::PreMessageLoop(nShowCmd);
    if (FAILED(hr))
    {
        return hr;
    }*/
    // Note: In this sample, we don't respond differently to different hr success codes.

    //SetLastError(0);
//    HANDLE hEvent = CreateEvent( NULL, false, false, CMainWindow::GetWndClassInfo().m_wc.lpszClassName );

  //  if ( !m_bRestarting && hEvent != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
    //{
        // Rho Running so could bring to foreground
      //  HWND hWnd = FindWindow(CMainWindow::GetWndClassInfo().m_wc.lpszClassName, NULL);

        //if (hWnd)
        //{
          //  ShowWindow(hWnd, SW_SHOW);
            //SendMessage( hWnd, PB_WINDOW_RESTORE, NULL, TRUE);
            //SetForegroundWindow( hWnd );

            //COPYDATASTRUCT cds = {0};
            //cds.cbData = m_strTabName.length()+1;
            //cds.lpData = (char*)m_strTabName.c_str();
            //SendMessage( hWnd, WM_COPYDATA, (WPARAM)WM_WINDOW_SWITCHTAB, (LPARAM)(LPVOID)&cds);
        //}

        //return S_FALSE;
    //}

    if ( !rho_sys_check_rollback_bundle(rho_native_rhopath()) )
    {
        rho_sys_impl_exit_with_errormessage( "Bundle update", "Application is corrupted. Reinstall it, please.");
        return S_FALSE;
    }

#if defined(APP_BUILD_CAPABILITY_SHARED_RUNTIME)
    rho_logconf_Init((rho_wmimpl_get_logpath()[0]==0 ? m_strRootPath.c_str() : rho_wmimpl_get_logpath()), m_strRootPath.c_str(), m_logPort.c_str());
    if (rho_wmimpl_get_logurl()[0]!=0)
	{
        LOGCONF().setLogURL(rho_wmimpl_get_logurl());
		LOGCONF().setLogToSocket(true);
	}
    if (rho_wmimpl_get_logmaxsize())
        LOGCONF().setMaxLogFileSize(*rho_wmimpl_get_logmaxsize());
    if (rho_wmimpl_get_loglevel())
        LOGCONF().setMinSeverity(*rho_wmimpl_get_loglevel());
    if (rho_wmimpl_get_fullscreen())
        RHOCONF().setBool("full_screen", true, false);
    if (rho_wmimpl_get_logmemperiod())
        LOGCONF().setCollectMemoryInfoInterval(*rho_wmimpl_get_logmemperiod());
    //SR EMBPD00121468
    //Network api via proxy is not working with proxy enable using config.xml 
    //Sabir: The values were getting set from rhoconfig.txt from function rho_logconf_Init
    //fix: we have to override http_proxy_host using config.xml value
    rho::String szHttpProxy =  rho_wmimpl_get_httpproxy();
    parseHttpProxyURI(szHttpProxy);
#else
    rho_logconf_Init(m_strRootPath.c_str(), m_strRootPath.c_str(), m_logPort.c_str());
#endif // APP_BUILD_CAPABILITY_SHARED_RUNTIME

 SetLastError(0);
 HANDLE hEvent = CreateEvent( NULL, false, false, CMainWindow::GetWndClassInfo().m_wc.lpszClassName );

    if ( !m_bRestarting && hEvent != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
    {
        // Rho Running so could bring to foreground
        HWND hWnd = FindWindow(CMainWindow::GetWndClassInfo().m_wc.lpszClassName, NULL);

        if (hWnd)
        {
            ShowWindow(hWnd, SW_SHOW);
            SendMessage( hWnd, PB_WINDOW_RESTORE, NULL, TRUE);
            SetForegroundWindow( hWnd );

            COPYDATASTRUCT cds = {0};
            cds.cbData = m_strTabName.length()+1;
            cds.lpData = (char*)m_strTabName.c_str();
            SendMessage( hWnd, WM_COPYDATA, (WPARAM)WM_WINDOW_SWITCHTAB, (LPARAM)(LPVOID)&cds);
        }

        return S_FALSE;
    }



    LOGCONF().setMemoryInfoCollector(CLogMemory::getInstance());

    if ( !rho_rhodesapp_canstartapp(g_strCmdLine.c_str(), " /-,") )
    {
		LOG(INFO) + "This is hidden app and can be started only with security key.";
		if (RHOCONF().getString("invalid_security_token_start_path").length() <= 0)
        {
			return S_FALSE;
        }
    }

	LOG(INFO) + "Rhodes started";
	if (RHOCONF().isExist("http_proxy_url")) {
		parseHttpProxyURI(RHOCONF().getString("http_proxy_url"));
	} else if (RHOCONF().isExist("http_proxy_uri")) {
		parseHttpProxyURI(RHOCONF().getString("http_proxy_uri"));
	}


	//Check for bundle directory is exists.
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	
	// rootpath + "rho/"
	if (m_strRootPath.at(m_strRootPath.length()-1) == '/') 
    {
		hFind = FindFirstFile(convertToStringW(m_strRootPath.substr(0, m_strRootPath.find_last_of('/'))).c_str(), &wfd);
	} 
    else if (m_strRootPath.at(m_strRootPath.length()-1) == '\\') 
    {
		//delete all '\' from the end of the pathname
		int i = m_strRootPath.length();
		for ( ; i != 1; i--) {
			if (m_strRootPath.at(i-1) != '\\')
				break;
		}

		hFind = FindFirstFile(convertToStringW(m_strRootPath.substr(0, i)).c_str(), &wfd);
	}

	if (INVALID_HANDLE_VALUE == hFind || !(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
    {
		int last = 0, pre_last = 0;
		last = getRhoRootPath().find_last_of('\\');
		pre_last = getRhoRootPath().substr(0, last).find_last_of('\\');
		String appName = getRhoRootPath().substr(pre_last + 1, last - pre_last - 1);

		String messageText = "Bundle directory \"" + 
								m_strRootPath.substr(0, m_strRootPath.find_last_of('/')) + 
								"\" is  missing\n";

		LOG(INFO) + messageText;
		int msgboxID = MessageBox(NULL,
									convertToStringW(messageText).c_str(),
									convertToStringW(appName).c_str(),
									MB_ICONERROR | MB_OK);


		return S_FALSE;
    }

    createPowerManagementThread();

    if (RHOCONF().getBool("Application.autoStart"))
        createAutoStartShortcut();

#if defined(APP_BUILD_CAPABILITY_SHARED_RUNTIME)
    if ((!rho_wmimpl_get_is_version2()) && (rho_wmimpl_get_startpage()[0] != 0)) {
        String spath = convertToStringA(rho_wmimpl_get_startpage());
        RHOCONF().setString("start_path", spath, false);
    }
#endif // APP_BUILD_CAPABILITY_SHARED_RUNTIME

    rho::common::CRhodesApp::Create(m_strRootPath, m_strRootPath, m_strRuntimePath);

    set_bridge_direct_callback();

    bool bRE1App = false;

#if defined(APP_BUILD_CAPABILITY_SHARED_RUNTIME)
    if (!rho_wmimpl_get_is_version2())
        bRE1App = true;
#endif

    RHODESAPP().setJSApplication(bRE1App || _AtlModule.isJSApplication());

    DWORD dwStyle = m_bMinimized ? 0 : WS_VISIBLE;

#ifdef OS_WINCE
    m_appWindow.getTabbar().SetStartTabName(m_strTabName);
#else
    m_appWindow.setStartTabName(m_strTabName);
#endif

#if !defined(_WIN32_WCE)
    dwStyle |= WS_OVERLAPPEDWINDOW;
#endif
    // Create the main application window
    String strTitle = RHODESAPP().getAppTitle();
    m_appWindow.Create(NULL, CWindow::rcDefault, convertToStringW(strTitle).c_str(), dwStyle);

    if (NULL == m_appWindow.m_hWnd)
    {
        return S_FALSE;
    }

    m_appWindow.InvalidateRect(NULL, TRUE);
	m_appWindow.SetActiveWindow();	//  Enterprise Browser was failing to launch maximimized through a shortcut, this line ensures it launches maximised
    m_appWindow.UpdateWindow();
#if defined(APP_BUILD_CAPABILITY_SYMBOL)
	initialiseRhoElementsExt();
#endif
    m_appWindow.initBrowserWindow();

    if (m_bMinimized)
        m_appWindow.ShowWindow(SW_MINIMIZE);

/*
    if (bRE1App)
    {
#if defined(APP_BUILD_CAPABILITY_SYMBOL)
        registerRhoExtension();
#endif

#if !defined( APP_BUILD_CAPABILITY_WEBKIT_BROWSER ) && defined(OS_WINCE)
	    m_appWindow.Navigate2(_T("about:blank"), -1 );
#endif //!APP_BUILD_CAPABILITY_WEBKIT_BROWSER

        rho_webview_navigate(RHOCONF().getString("start_path").c_str(), 0 );
    }
    else
    { */
        RHODESAPP().startApp();

#if !defined( APP_BUILD_CAPABILITY_WEBKIT_BROWSER ) && defined(OS_WINCE)
        // Navigate to the "loading..." page
	    m_appWindow.Navigate2(_T("about:blank"), -1 );
#endif //APP_BUILD_CAPABILITY_WEBKIT_BROWSER
    //}

#if defined(_WIN32_WCE)
    if(RHO_IS_WMDEVICE)
    {

        DWORD dwConnCount = 0;
        hr = lpfn_Registry_GetDWORD( SN_CONNECTIONSNETWORKCOUNT_ROOT,
		    SN_CONNECTIONSNETWORKCOUNT_PATH, 
		    SN_CONNECTIONSNETWORKCOUNT_VALUE, 
            &dwConnCount
        );
        rho_sysimpl_sethas_network((dwConnCount > 1) ? 1 : 0);

        DWORD dwCellConnected = 0;
        hr = lpfn_Registry_GetDWORD( SN_CONNECTIONSNETWORKCOUNT_ROOT,
		    SN_CELLSYSTEMCONNECTED_PATH, 
		    SN_CELLSYSTEMCONNECTED_VALUE, 
            &dwCellConnected
        );
        rho_sysimpl_sethas_cellnetwork(dwCellConnected);

	    // Register for changes in the number of network connections
	    hr = lpfn_Registry_NotifyWindow(SN_CONNECTIONSNETWORKCOUNT_ROOT,
		    SN_CONNECTIONSNETWORKCOUNT_PATH, 
		    SN_CONNECTIONSNETWORKCOUNT_VALUE, 
		    m_appWindow.m_hWnd, 
		    WM_CONNECTIONSNETWORKCOUNT, 
		    0, 
		    NULL, 
		    &g_hNotify);

	    hr = lpfn_Registry_NotifyWindow(SN_CONNECTIONSNETWORKCOUNT_ROOT,
		    SN_CELLSYSTEMCONNECTED_PATH, 
		    SN_CELLSYSTEMCONNECTED_VALUE, 
		    m_appWindow.m_hWnd, 
		    WM_CONNECTIONSNETWORKCELL, 
		    0, 
		    NULL, 
		    &g_hNotifyCell);
    }
#endif

    return S_OK;
}