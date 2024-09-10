bool GetProxyForHost(const char *url, const char *hostname, cvs::string& proxy, cvs::string& proxy_port)
{
	static bool bInitialised = false, bWorking = false;

	char WPADLocation[1024]= "";
	char TempPath[MAX_PATH];
	char TempFile[MAX_PATH];
	DWORD dwProxyHostNameLength;
	DWORD returnVal;
	HMODULE hModJS;

	// Declare and populate an AutoProxyHelperVtbl structure, and then 
	// place a pointer to it in a containing AutoProxyHelperFunctions 
	// structure, which will be passed to InternetInitializeAutoProxyDll:

	// Failure to compile this line means you have an out of date platfrom SDK.
	static const AutoProxyHelperVtbl Vtbl =
	{
		IsResolvable,
		GetIPAddress,
		ResolveHostName,
		IsInNet
	};
	static const AutoProxyHelperFunctions HelperFunctions = { &Vtbl };

	// Declare function pointers for the three autoproxy functions
	static pfnInternetInitializeAutoProxyDll    pInternetInitializeAutoProxyDll;
	static pfnInternetDeInitializeAutoProxyDll  pInternetDeInitializeAutoProxyDll;
	static pfnInternetGetProxyInfo              pInternetGetProxyInfo;

	static cvs::string static_proxy,static_port;


	if(!bInitialised)
	{
		bInitialised=true;
		bWorking=false;

		if( !( hModJS = LoadLibraryA( "jsproxy.dll" ) ) )
			return false;

		if( !( pInternetInitializeAutoProxyDll = (pfnInternetInitializeAutoProxyDll)
					GetProcAddress( hModJS, "InternetInitializeAutoProxyDll" ) ) ||
			!( pInternetDeInitializeAutoProxyDll = (pfnInternetDeInitializeAutoProxyDll)
					GetProcAddress( hModJS, "InternetDeInitializeAutoProxyDll" ) ) ||
			!( pInternetGetProxyInfo = (pfnInternetGetProxyInfo)
					GetProcAddress( hModJS, "InternetGetProxyInfo" ) ) )
			return false;

		INTERNET_PER_CONN_OPTIONA pco[] =
		{
			{ INTERNET_PER_CONN_FLAGS },
			{ INTERNET_PER_CONN_AUTOCONFIG_URL },
			{ INTERNET_PER_CONN_PROXY_SERVER },
			{ INTERNET_PER_CONN_PROXY_BYPASS },
			{ INTERNET_PER_CONN_AUTOCONFIG_SECONDARY_URL }
		};
		INTERNET_PER_CONN_OPTION_LISTA pcol = { sizeof(pco), NULL, sizeof(pco)/sizeof(pco[0]), 0, pco }; 

		DWORD dwLen=sizeof(pcol);
		if(!InternetQueryOptionA(NULL,INTERNET_OPTION_PER_CONNECTION_OPTION,&pcol,&dwLen))
			return false;

		DWORD pt = pco[0].Value.dwValue;
		if(pt&PROXY_TYPE_AUTO_DETECT)
		{
			// Autodetect proxy file.  We only want to do this once becuase it's slow
			// We do DNS first... DHCP can take up to 10 seconds to complete.
			if(!DetectAutoProxyUrl( WPADLocation, sizeof(WPADLocation),PROXY_AUTO_DETECT_TYPE_DNS_A) &&
			   !DetectAutoProxyUrl( WPADLocation, sizeof(WPADLocation), PROXY_AUTO_DETECT_TYPE_DHCP ))
			return false;
		}
		else if(pt&PROXY_TYPE_AUTO_PROXY_URL)
		{
			// Download proxy.pac from url
			strncpy(WPADLocation,pco[1].Value.pszValue,sizeof(WPADLocation));
			LocalFree((HLOCAL)pco[1].Value.pszValue);
		}
		else if(pt&PROXY_TYPE_PROXY)
		{
			// Explicitly set proxy server
			LPSTR szValue = pco[2].Value.pszValue;
			static_port="";
			char *p=strrchr(szValue,':');
			if(p)
			{
				*p='\0';
				static_port=p+1;
			}
			static_proxy=szValue;
			LocalFree((HLOCAL)szValue);
		}
		else 
		{
			return false; // Fail the detect, forcing us to go direct
		}

		if(!static_proxy.length())
		{
			GetTempPathA( sizeof(TempPath)/sizeof(TempPath[0]), TempPath );
			GetTempFileNameA( TempPath, NULL, 0, TempFile );
			URLDownloadToFileA( NULL, WPADLocation, TempFile, NULL, NULL );

			if( !( returnVal = pInternetInitializeAutoProxyDll( 0, TempFile, NULL, 
																(AutoProxyHelperFunctions*)&HelperFunctions, NULL ) ) )
				return false;

			// Delete the temporary file
			DeleteFileA( TempFile );
		}

		bWorking = true;
	}

	if(!bWorking)
		return false;

	if(static_proxy.length())
	{
		proxy = static_proxy;
		proxy_port = static_port;
	}
	else
	{
		dwProxyHostNameLength=0;
		LPSTR szProxy = NULL;
		if( !pInternetGetProxyInfo( (LPSTR) url, (DWORD)strlen(url), 
									(LPSTR) hostname, (DWORD)strlen(hostname),
									&szProxy, &dwProxyHostNameLength ) )
			return false;

		if(!szProxy || !strcmp(szProxy,"DIRECT"))
			return false; // Direct connection

		if(strncmp(szProxy,"PROXY ",6))
			return false; // This should be the only possible string (maybe "SOCKS" but that's little used)

		proxy_port="";
		char *p = strrchr(szProxy,':');
		if(p)
		{
			proxy_port=p+1;
			*p='\0';
		}
		proxy=szProxy+6;
		// Not documented - how to free this?
		LocalFree((HLOCAL)szProxy);
	}
	return true;
}