void CProxySetting::readProxy(){

	INTERNET_PER_CONN_OPTION_LIST    List;
	INTERNET_PER_CONN_OPTION         Option[5];
	unsigned long                    nSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);

	Option[0].dwOption = INTERNET_PER_CONN_AUTOCONFIG_URL;
	Option[1].dwOption = INTERNET_PER_CONN_AUTODISCOVERY_FLAGS;
	Option[2].dwOption = INTERNET_PER_CONN_FLAGS;
	Option[3].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
	Option[4].dwOption = INTERNET_PER_CONN_PROXY_SERVER;

	List.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
	List.pszConnection = NULL;
	List.dwOptionCount = 5;
	List.dwOptionError = 0;
	List.pOptions = Option;

	if(!InternetQueryOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &List, &nSize))
		printf("InternetQueryOption failed! (%d)\n", GetLastError());
	if(Option[0].Value.pszValue != NULL)
		AtlTrace("%s\n", Option[0].Value.pszValue);


	if((Option[2].Value.dwValue & PROXY_TYPE_AUTO_PROXY_URL) == PROXY_TYPE_AUTO_PROXY_URL)
		AtlTrace("PROXY_TYPE_AUTO_PROXY_URL\n");

	if((Option[2].Value.dwValue & PROXY_TYPE_AUTO_DETECT) == PROXY_TYPE_AUTO_DETECT)
		AtlTrace("PROXY_TYPE_AUTO_DETECT\n");

	INTERNET_VERSION_INFO      Version;
	nSize = sizeof(INTERNET_VERSION_INFO);

	InternetQueryOption(NULL, INTERNET_OPTION_VERSION, &Version, &nSize);

	if(Option[0].Value.pszValue != NULL)
		GlobalFree(Option[0].Value.pszValue);

	if(Option[3].Value.pszValue != NULL)
		GlobalFree(Option[3].Value.pszValue);

	if(Option[4].Value.pszValue != NULL)
		GlobalFree(Option[4].Value.pszValue);

	INTERNET_PROXY_INFO proxyInfo;
	proxyInfo.dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG;
	proxyInfo.lpszProxy = NULL;
	proxyInfo.lpszProxyBypass = NULL;

	HRESULT hr =UrlMkSetSessionOption(INTERNET_OPTION_PROXY,&proxyInfo,sizeof(proxyInfo),0); 


}	