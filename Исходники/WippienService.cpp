extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
    lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
    _Module.Init(ObjectMap, hInstance, IDS_SERVICENAME, &LIBID_WIPPIENSERVICELib);
    _Module.m_bService = TRUE;

    TCHAR szTokens[] = _T("-/");

    LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
    while (lpszToken != NULL)
    {
        if (_strnicmp(lpszToken, _T("UnregServer"), 11)==0)
			flagUnregServer = TRUE;

        // Register as Local Server
        if (_strnicmp(lpszToken, _T("RegServer"), 9)==0)
            flagRegServer = TRUE;
        
        // Register as Service
        if (_strnicmp(lpszToken, _T("Service"), 7)==0)
			flagService = TRUE;
        
        // Register as Service
        if (_strnicmp(lpszToken, _T("AutoStart"), 9)==0)
			flagAutoStart = SERVICE_AUTO_START;

        lpszToken = FindOneOf(lpszToken, szTokens);
    }


	if (flagUnregServer)
		return _Module.UnregisterServer();

	if (flagRegServer)
		return _Module.RegisterServer(TRUE, FALSE);
        
	if (flagService)
		return _Module.RegisterServer(TRUE, TRUE);


    // Are we Service or Local Server
    CRegKey keyAppID;
    LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_READ);
    if (lRes != ERROR_SUCCESS)
        return lRes;

    CRegKey key;
    lRes = key.Open(keyAppID, _T("{A3084FF8-63BF-40A1-8AE0-AD792B0078D9}"), KEY_READ);
    if (lRes != ERROR_SUCCESS)
        return lRes;

    TCHAR szValue[_MAX_PATH];
    DWORD dwLen = _MAX_PATH;
    lRes = key.QueryValue(szValue, _T("LocalService"), &dwLen);

    _Module.m_bService = FALSE;
    if (lRes == ERROR_SUCCESS)
        _Module.m_bService = TRUE;

	WODXMPP::_XMPP_LibInit(_Module.GetModuleInstance());
	WODVPN::_VPN_LibInit(_Module.GetModuleInstance());
	
	if (LoadConfig())
	{		
		_Jabber = new CJabberLib();
		_Ethernet = new CEthernet();


		if (_Ethernet->InitAdapter())
		{
			_Module.LogEvent("Connecting to the XMPP server." );
			
			_Ethernet->GetMyIP();
			_Module.Start();
		}
		else
			_Module.LogEvent(_T("Wippien Service failed to open Network adapter."));

	}
	else
	{
		char bf[8192];
		sprintf(bf, "Could not read: %s.config", __argv[0]);
		_Module.LogEvent(bf);

	}
	
	WODVPN::_VPN_LibDeinit();
	WODXMPP::_XMPP_LibDeInit();

    // When we get here, the service has been stopped
    return _Module.m_status.dwWin32ExitCode;
}