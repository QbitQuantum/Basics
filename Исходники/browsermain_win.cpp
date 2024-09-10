HRESULT CBrowserModule::PreMessageLoop(int nShowCmd) throw()
{
    HRESULT hr = 0;
    RECT rc = {0, 0, 0, 0};
    DWORD dwExStyle = 0;
    DWORD dwStyle = 0;
    char szWindowTitle[256];
    char szWindowInfo[256];
    char szDebuggingInfo[256];
    int iWebServerPort = 0;
    char szWebServerUsername[256];
    char szWebServerPassword[256];


	hr = __super::PreMessageLoop(nShowCmd);
	if (FAILED(hr)) {
        return hr;
	}

    // Initialize ATL Window Classes
    //
    AtlAxWinInit();

    // Prepare environment for web browser control
    //
    RegisterWebControlCompatiblity();

    // Prepare environment for detecting system conditions
    //
    boinc_parse_init_data_file();

    // Initialize Web Server
    //
    _snprintf(szWebServerUsername, sizeof(szWebServerUsername)-1, "%d", GetCurrentThreadId());
    _snprintf(szWebServerPassword, sizeof(szWebServerPassword)-1, "%d", GetCurrentThreadId());
    boinc_get_port(false, iWebServerPort);
    webserver_initialize(iWebServerPort, szWebServerUsername, szWebServerPassword, m_bDebugging);
        
    // Create Window Instance
    //
    m_pWnd = new CHTMLBrowserWnd();
	if (m_pWnd == NULL)
	{
		__super::PostMessageLoop();
		return E_OUTOFMEMORY;
	}

    // Store a copy of APP_INIT_DATA for future use
    //
    boinc_get_init_data(m_pWnd->aid);

    // Store web server information for future use
    //
    m_pWnd->m_iWebServerPort = iWebServerPort;
    m_pWnd->m_strWebServerUsername = szWebServerUsername;
    m_pWnd->m_strWebServerPassword = szWebServerPassword;

    // Construct the window caption
    //
    if (m_pWnd->aid.app_version) {
        snprintf(
            szWindowInfo, sizeof(szWindowInfo),
            "%s version %.2f [workunit: %s]",
            m_pWnd->aid.app_name, m_pWnd->aid.app_version/100.0, m_pWnd->aid.wu_name
        );
    } else {
        snprintf(
            szWindowInfo, sizeof(szWindowInfo),
            "%s [workunit: %s]",
            m_pWnd->aid.app_name, m_pWnd->aid.wu_name
        );
    }

    if (m_bDebugging) {
        snprintf(szDebuggingInfo, sizeof(szDebuggingInfo), "[Web Server Port: %d]", iWebServerPort);
    } else {
        strcpy(szDebuggingInfo, "");
    }

    snprintf(szWindowTitle, sizeof(szWindowTitle)-1, "%s %s", szWindowInfo, szDebuggingInfo);

    // Determine window size and placement
    if (m_bFullscreen) {
        HDC dc = GetDC(NULL);
        rc.left = 0;
        rc.top = 0;
        rc.right = GetDeviceCaps(dc, HORZRES);
        rc.bottom = GetDeviceCaps(dc, VERTRES);
        ReleaseDC(NULL, dc);

        dwStyle = WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_POPUP;
        dwExStyle = WS_EX_APPWINDOW|WS_EX_TOPMOST;
        while(ShowCursor(false) >= 0);
    } else {
        rc.left = 0;
        rc.top = 0;
        rc.right = 1024;
        rc.bottom = 768;

        dwStyle = WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_OVERLAPPEDWINDOW;
        dwExStyle = WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;
        while(ShowCursor(true) < 0);
    }

    // Create Window
    //
	m_pWnd->Create(GetDesktopWindow(), rc, szWindowTitle, dwStyle, dwExStyle);
	m_pWnd->ShowWindow(nShowCmd);

	return S_OK;
}