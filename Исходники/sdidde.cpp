HXBOOL BrowserOpenURL(const char* pszUrl, const char* pszTarget, const char* pszDefBrowser) 
{
    HX_TRACE("BrowserOpenURL()\r\n");

    HXBOOL	result = TRUE;
    DWORD	dwResult = 0;
    HDDEDATA	hOpenRetVal = NULL;
    HSZ		hszOpenTopic = NULL;
    HSZ		hszOpenItem = NULL;
    HCONV	hOpenConv = NULL;
    HDDEDATA	hActivateRetVal = NULL;
    HSZ		hszActivateTopic = NULL;
    HSZ		hszActivateItem = NULL;
    HCONV	hActivateConv = NULL;
    UINT16	i = 0;
    UINT16	nNumberOfBrowsers = 0;
    char*	pMessage = NULL;
    DWORD	dwWindowID = 0xFFFFFFFF;	    // -1 = last active window
    DWORD	dwLockTimeout = 0;
    HXBOOL	bForceBroswserToForeground = FALSE;
    HXVERSIONINFO versionInfo;

    if (!pszUrl)
    {
	result = FALSE;
	goto cleanup;
    }

    pMessage = new char[strlen(pszUrl)+48];
    if (!pMessage)
    {
	result = FALSE;
	goto cleanup;
    }

    // handle pszTarget parameter according to:
    // https://common.helixcommunity.org/nonav/2003/HCS_SDK_r5/htmfiles/HyperNavigate.htm
    if (pszTarget && (0 == strcmp(pszTarget, "_new") || 0 == strcmp(pszTarget, "_blank")))
    {
        dwWindowID = 0;
    }

    ZeroInit(&versionInfo);
    HXGetWinVer(&versionInfo);
    bForceBroswserToForeground = ((versionInfo.dwPlatformId == HX_PLATFORM_WIN98) || (versionInfo.dwPlatformId == HX_PLATFORM_WINNT && versionInfo.wMajorVersion > 4));
    
    DDEStartup();

    // establish browser
    if (NULL == g_hszWWWService)
    {
	hszOpenTopic = DdeCreateStringHandle(g_dwIdInst, "WWW_OpenURL", CP_WINANSI);
	if (hszOpenTopic)
	{
	    nNumberOfBrowsers = sizeof(g_BrowsersSupportingDDE)/sizeof(DDE_Browsers);

	    // Look for a browser that supports DDE???
	    while (i < nNumberOfBrowsers)
	    {
		g_hszWWWService = DdeCreateStringHandle(g_dwIdInst,
						        g_BrowsersSupportingDDE[i].szDDEName,
							CP_WINANSI);

		hOpenConv = DdeConnect(g_dwIdInst, g_hszWWWService, hszOpenTopic, NULL);
		if (hOpenConv)
		{
		    break;
		}

		if(g_hszWWWService)
		{
		    DdeFreeStringHandle(g_dwIdInst, g_hszWWWService);
		    g_hszWWWService = NULL;  
		}

		i++;
	    }
	}

	if (NULL == g_hszWWWService)
	{
	    result = FALSE;
	    goto cleanup;
	}
    }
    else
    {
	hszOpenTopic = DdeCreateStringHandle(g_dwIdInst,"WWW_OpenURL", CP_WINANSI);
	hOpenConv = DdeConnect(g_dwIdInst, g_hszWWWService, hszOpenTopic, NULL);
    }

    if (!hOpenConv)
    {
	HX_TRACE("Conversation failed to start...\r\n");
	
	DdeFreeStringHandle(g_dwIdInst, g_hszWWWService);
	g_hszWWWService = NULL;

	result = FALSE;
	goto cleanup;
    }

    wsprintf(pMessage,"\"%s\",,%lu,0,,,,", pszUrl, dwWindowID); 
    hszOpenItem = DdeCreateStringHandle(g_dwIdInst, pMessage, CP_WINANSI);

    HX_TRACE("Conversation started, sending URL command...\r\n");

    // Request
    hOpenRetVal = DdeClientTransaction(NULL, 0, hOpenConv, hszOpenItem, CF_TEXT, XTYP_REQUEST, 60000, NULL);
    if (DDE_FNOTPROCESSED != hOpenRetVal)
    {
	DdeGetData(hOpenRetVal, (LPBYTE)&dwResult, sizeof(dwResult), 0);
	if (!dwResult)
	{
	    result = FALSE;
	    goto cleanup;
	}
    }

    // force the browser to the foreground then do it here.  This does not actually put the browser
    // in the foreground instead it enables the browser's call to SetForegroundWindow to bring the window to the
    // front instead of flashing it on the taskbar
    if (bForceBroswserToForeground)
    {
	// These are new flags that work on Win98 and WinNT5 ONLY.  First get the current foreground lock timeout and save
	// it off and then set it to 0.
	::SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT,0,&dwLockTimeout,0);
	::SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT,0,0,0);
    }

    // activate the browser
    wsprintf(pMessage, "%lu,0", dwWindowID); 
    hszActivateItem = DdeCreateStringHandle(g_dwIdInst, pMessage, CP_WINANSI);
    hszActivateTopic = DdeCreateStringHandle(g_dwIdInst,"WWW_Activate", CP_WINANSI);

    // Connect to server
    if (hszActivateTopic && hszActivateItem)
    {
	hActivateConv = DdeConnect(g_dwIdInst, g_hszWWWService, hszActivateTopic, NULL);
	if (hActivateConv)
	{
	    hActivateRetVal = DdeClientTransaction(NULL, 0, hActivateConv, hszActivateItem, CF_TEXT, XTYP_REQUEST, 10000, NULL);
	}
    }

    if (bForceBroswserToForeground)
    {
	// Restore the old foreground lock timeout
	::SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT,0,(PVOID)dwLockTimeout,0);
    }

cleanup:

    if (hOpenRetVal)
	DdeFreeDataHandle(hOpenRetVal);
    if (hActivateRetVal)
	DdeFreeDataHandle(hActivateRetVal);

    if (hszOpenTopic)
	DdeFreeStringHandle(g_dwIdInst, hszOpenTopic);    
    if (hszActivateTopic)
	DdeFreeStringHandle(g_dwIdInst, hszActivateTopic);    

    if (hszOpenItem)    
	DdeFreeStringHandle(g_dwIdInst, hszOpenItem);
    if (hszActivateItem)    
	DdeFreeStringHandle(g_dwIdInst, hszActivateItem);

    if (hOpenConv)
	DdeDisconnect(hOpenConv);
    if (hActivateConv)
	DdeDisconnect(hActivateConv);

    HX_VECTOR_DELETE(pMessage);
    
    DDEShutdown();

    return result;
}