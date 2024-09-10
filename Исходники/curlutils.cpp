CURL* InitCurlHandle()
{
	CURL* curl = curl_easy_init();

	if (settings->GetProxyType() != Proxy_None)
	{
		curl_easy_setopt(curl, CURLOPT_PROXY, TOASCII(settings->GetProxyHostName()));
		curl_easy_setopt(curl, CURLOPT_PROXYPORT, settings->GetProxyPort());

		switch (settings->GetProxyType())
		{
		case Proxy_HTTP:
			curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
			break;

		case Proxy_SOCKS4:
			curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
			break;

		case Proxy_SOCKS5:
			if (settings->GetProxyDNS())
				curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5_HOSTNAME);
			else
				curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
			break;
		}
	}

	return curl;
}