	/*static*/
	void Win32UIBinding::SetProxyForURL(std::string& url)
	{
		SharedPtr<Proxy> proxy(ProxyConfig::GetProxyForURL(url));
		if (!proxy.isNull())
		{
			std::stringstream proxyEnv;
			if (proxy->type == HTTP)
				proxyEnv << "http_proxy=http://";
			else if (proxy->type = HTTPS)
				proxyEnv << "HTTPS_PROXY=https://";

			if (!proxy->username.empty() || !proxy->password.empty())
				proxyEnv << proxy->username << ":" << proxy->password << "@";

			proxyEnv << proxy->host;

			if (proxy->port != 0)
				proxyEnv << ":" << proxy->port;

			std::wstring proxyEnvStr(::UTF8ToWide(proxyEnv.str()));
			_wputenv(proxyEnvStr.c_str());
		}
	}