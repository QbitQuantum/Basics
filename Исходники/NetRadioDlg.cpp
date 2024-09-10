void CNetRadioDlg::SetProxy( LPCSTR strProxy )
{
	INTERNET_PROXY_INFO_ANSI proxyInfo;
	proxyInfo.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
	proxyInfo.Proxy = strProxy;
	proxyInfo.lpszProxyBypass = NULL;
	UrlMkSetSessionOption(INTERNET_OPTION_PROXY,&proxyInfo,sizeof(proxyInfo),0);
}