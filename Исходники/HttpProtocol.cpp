void HttpProtocol::initialize(dictionary* ini, const char* section)
{
	char* url = INI::GetString(ini, section, FS_URL, NULL);
	if(!url) {
		Log::Error("Missing URL for HTTP protocol");
		return;
	}
	Log::Info("Setup session for: %s", url);
	int usz = MultiByteToWideChar(CP_ACP, 0, url, strlen(url), 0, 0);
	this->url = (wchar_t*) malloc((usz + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, url, strlen(url), this->url, usz);
	this->url[usz] = 0;
	memset(&urlc, 0, sizeof(URL_COMPONENTS));
	urlc.dwStructSize = sizeof(URL_COMPONENTS);
	urlc.dwSchemeLength = 1;
	urlc.dwHostNameLength = 1;
	urlc.dwUserNameLength = 1;
	urlc.dwPasswordLength = 1;
	urlc.dwUrlPathLength = 1;
	urlc.dwExtraInfoLength = 1;
	WinHttpCrackUrl(this->url, usz, 0, &urlc);
	this->host = (wchar_t*) malloc((urlc.dwHostNameLength + 1) * sizeof(wchar_t));
	memcpy(this->host, urlc.lpszHostName, urlc.dwHostNameLength*sizeof(wchar_t));
	this->host[urlc.dwHostNameLength] = 0;
	this->path = (wchar_t*) malloc((urlc.dwUrlPathLength + 1) * sizeof(wchar_t));
	memcpy(this->path, urlc.lpszUrlPath, urlc.dwUrlPathLength*sizeof(wchar_t));
	this->path[urlc.dwUrlPathLength] = 0;

	// Determine proxy
	char* proxy = INI::GetString(ini, section, FS_PROXY, NULL);
	if(proxy) {
		Log::Info("Using proxy: %s", proxy);
		int psz = MultiByteToWideChar(CP_ACP, 0, url, strlen(url), 0, 0);
		wchar_t* wproxy = (wchar_t*) malloc((psz + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, proxy, strlen(proxy), wproxy, psz);
		wproxy[psz] = 0;
		hSession = WinHttpOpen(USER_AGENT, WINHTTP_ACCESS_TYPE_NO_PROXY,
			wproxy, 0, 0);
		free(wproxy);
	} else {
		WINHTTP_CURRENT_USER_IE_PROXY_CONFIG proxy;
		WinHttpGetIEProxyConfigForCurrentUser(&proxy);
		int proxyType = WINHTTP_ACCESS_TYPE_NO_PROXY;
		if(proxy.lpszProxy) {
			proxyType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
			Log::Info("Using proxy: %s", proxy.lpszProxy);
		}
		hSession = WinHttpOpen(USER_AGENT, proxyType,
			proxy.lpszProxy, proxy.lpszProxyBypass, 0);
	}
}