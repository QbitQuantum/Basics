int wmain(int iArgCnt, WCHAR ** argv)
{

    if(!ProcessArguments(iArgCnt, argv))
    {
        DisplayOptions();
        return 1;
	}

	if (wcslen(wServerName) > 0)
	{
		
		
		//prompt for credentials for a remote connection

		DWORD dwRes = CredUICmdLinePromptForCredentialsW(
									(const WCHAR *) wServerName, NULL, 0, 
									wFullUserName, sizeof(wFullUserName)/sizeof(WCHAR),
									wPassWord, sizeof(wPassWord)/sizeof(WCHAR),
									FALSE, 
									CREDUI_FLAGS_EXCLUDE_CERTIFICATES | CREDUI_FLAGS_DO_NOT_PERSIST );

		if (dwRes != NO_ERROR)
		{
			printf("Failed to retrieve credentials: error %d. Using the default credentials.", dwRes);
		}
		
		bUserNameSet = bPassWordSet = (dwRes == NO_ERROR);

	}
	else
	{
		//no server name passed in, assume local
		StringCbCopyW(wServerName, sizeof(wPath), L".");
	}

	StringCbCopyW(wPath, sizeof(wPath), L"\\\\");
	StringCbCatW(wPath, sizeof(wPath),  wServerName);
	StringCbCatW(wPath, sizeof(wPath),  L"\\");
	StringCbCatW(wPath, sizeof(wPath),  wNameSpace);
          
    IWbemLocator *pLocator = NULL;
    IWbemServices *pNamespace = 0;
    IWbemClassObject * pClass = NULL;

    // Initialize COM.

    HRESULT hr = CoInitialize(0);
	if (FAILED(hr))
	{
	    printf("\nCoInitialize returned 0x%x:", hr);
		return 1;
	}

    // This sets the default impersonation level to "Impersonate" which is what WMI 
	// providers will generally require. 
    //
    // DLLs cannot call this function.  To bump up the impersonation level, they must 
    // call CoSetProxyBlanket which is illustrated later on.  
	//  
	//  When using asynchronous WMI API's remotely in an environment where the "Local System" account 
	//  has no network identity (such as non-Kerberos domains), the authentication level of 
	//  RPC_C_AUTHN_LEVEL_NONE is needed. However, lowering the authentication level to 
	//  RPC_C_AUTHN_LEVEL_NONE makes your application less secure. It is wise to
	//	use semi-synchronous API's for accessing WMI data and events instead of the asynchronous ones.
    
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
                                RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
                                RPC_C_IMP_LEVEL_IMPERSONATE,
                                NULL, 
								EOAC_SECURE_REFS, //change to EOAC_NONE if you change dwAuthnLevel to RPC_C_AUTHN_LEVEL_NONE
								0);
	if (FAILED(hr))
	{
	    printf("\nCoInitializeSecurity returned 0x%x:", hr);
		return 1;
	}
                                
    hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
            IID_IWbemLocator, (LPVOID *) &pLocator);

	if (FAILED(hr))
	{
	    printf("\nCoCreateInstance for CLSID_WbemLocator returned 0x%x:", hr);
		return 1;
	}
   
    hr = pLocator->ConnectServer(wPath, 
                    (bUserNameSet) ? wFullUserName : NULL, 
                    (bPassWordSet) ? wPassWord : NULL, 
                    NULL, 0, NULL, NULL, &pNamespace);
    if(FAILED(hr))
    {
        wprintf(L"\nConnectServer  to %s failed, hr = 0x%x", wPath, hr);
    }
    else
    {
        printf("\nConnection succeeded");
        hr = SetProxySecurity(pNamespace);
        if(SUCCEEDED(hr))
        {
            ListClasses(pNamespace);
            ReadACL(pNamespace);
        }
        pNamespace->Release();
    }
    CoUninitialize();
    printf("\nTerminating normally");
    return 0;
}