	static void InitializeWin32ProxyConfig()
	{
		static bool initialized = false;
		if (initialized)
			return;

		WINHTTP_CURRENT_USER_IE_PROXY_CONFIG ieProxyConfig;
		ZeroMemory(&ieProxyConfig, sizeof(WINHTTP_CURRENT_USER_IE_PROXY_CONFIG)); 
		
		if (WinHttpGetIEProxyConfigForCurrentUser(&ieProxyConfig))
		{
			if (ieProxyConfig.fAutoDetect)
			{
				useProxyAutoConfig = true;
			}
	
			if (ieProxyConfig.lpszAutoConfigUrl != NULL)
			{
				// We using an auto proxy configuration, but this one
				// has a URL which we must contact to get the configuration info.
				autoConfigURL = ieProxyConfig.lpszAutoConfigUrl;
			}

			// We always keep IE proxy information in case auto proxy
			// determination fails. We want to it as a fallback.
			if (ieProxyConfig.lpszProxy)
			{
				std::string bypassList;
				if (ieProxyConfig.lpszProxyBypass)
				{
					std::wstring bypassW = ieProxyConfig.lpszProxyBypass;
					bypassList = string(bypassW.begin(), bypassW.end());
				}

				std::wstring proxyListW = ieProxyConfig.lpszProxy;
				string proxyList = string(proxyListW.begin(), proxyListW.end());
				ParseProxyList(proxyList, bypassList, ieProxies);
			}
		}
		else
		{
			// If there is no IE configuration information, we default to
			// attempting to get auto proxy information.
			useProxyAutoConfig = true;
		}

		if (useProxyAutoConfig || !autoConfigURL.empty())
		{
			// We failed to open an HINTERNET handle! WTF. We'll have to have
			// disable auto proxy support, because we can't do a lookup.
			if (!httpSession.GetHandle())
			{
				useProxyAutoConfig = false;
				autoConfigURL = L"";
			}
		}

		if (ieProxyConfig.lpszProxy)
			GlobalFree(ieProxyConfig.lpszProxy);
		if (ieProxyConfig.lpszProxyBypass)
			GlobalFree(ieProxyConfig.lpszProxyBypass);
		if (ieProxyConfig.lpszAutoConfigUrl)
			GlobalFree(ieProxyConfig.lpszAutoConfigUrl);
	}