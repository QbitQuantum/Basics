/*!
 * @brief Prepare a winHTTP request with the given context.
 * @param ctx Pointer to the HTTP transport context to prepare the request from.
 * @param isGet Indication of whether this request is a GET request, otherwise POST is used.
 * @param direction String representing the direction of the communications (for debug).
 * @return An Internet request handle.
 */
static HINTERNET get_request_winhttp(HttpTransportContext *ctx, BOOL isGet, const char *direction)
{
	HINTERNET hReq = NULL;
	DWORD flags = WINHTTP_FLAG_BYPASS_PROXY_CACHE;

	if (ctx->ssl)
	{
		flags |= WINHTTP_FLAG_SECURE;
		dprintf("[%s] Setting secure flag..", direction);
	}

	vdprintf("[%s] opening request on connection %x to %S", direction, ctx->connection, ctx->uri);
	hReq = WinHttpOpenRequest(ctx->connection, isGet ? L"GET" : L"POST", ctx->uri, NULL, NULL, NULL, flags);

	if (hReq == NULL)
	{
		dprintf("[%s] Failed WinHttpOpenRequest: %u", direction, GetLastError());
		SetLastError(ERROR_NOT_FOUND);
		return NULL;
	}

	// if no proxy is set, we should look to see if we can (and should) use the system
	// proxy settings for the given user.
	if (!ctx->proxy)
	{
		if (!ctx->proxy_configured)
		{
			WINHTTP_CURRENT_USER_IE_PROXY_CONFIG ieConfig = { 0 };
			if (WinHttpGetIEProxyConfigForCurrentUser(&ieConfig))
			{
				dprintf("[PROXY] Got IE configuration");
				dprintf("[PROXY] AutoDetect: %s", ieConfig.fAutoDetect ? "yes" : "no");
				dprintf("[PROXY] Auto URL: %S", ieConfig.lpszAutoConfigUrl);
				dprintf("[PROXY] Proxy: %S", ieConfig.lpszProxy);
				dprintf("[PROXY] Proxy Bypass: %S", ieConfig.lpszProxyBypass);

				if (ieConfig.lpszAutoConfigUrl || ieConfig.fAutoDetect)
				{
					WINHTTP_AUTOPROXY_OPTIONS autoProxyOpts = { 0 };
					WINHTTP_PROXY_INFO proxyInfo = { 0 };

					if (ieConfig.fAutoDetect)
					{
						dprintf("[PROXY] IE config set to autodetect with DNS or DHCP");

						autoProxyOpts.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;
						autoProxyOpts.dwAutoDetectFlags = WINHTTP_AUTO_DETECT_TYPE_DHCP | WINHTTP_AUTO_DETECT_TYPE_DNS_A;
						autoProxyOpts.lpszAutoConfigUrl = 0;
					}
					else if (ieConfig.lpszAutoConfigUrl)
					{
						dprintf("[PROXY] IE config set to autodetect with URL %S", ieConfig.lpszAutoConfigUrl);

						autoProxyOpts.dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL;
						autoProxyOpts.dwAutoDetectFlags = 0;
						autoProxyOpts.lpszAutoConfigUrl = ieConfig.lpszAutoConfigUrl;
					}
					autoProxyOpts.fAutoLogonIfChallenged = TRUE;

					if (WinHttpGetProxyForUrl(ctx->internet, ctx->url, &autoProxyOpts, &proxyInfo))
					{
						ctx->proxy_for_url = malloc(sizeof(WINHTTP_PROXY_INFO));
						memcpy(ctx->proxy_for_url, &proxyInfo, sizeof(WINHTTP_PROXY_INFO));
					}
				}
				else if (ieConfig.lpszProxy)
				{
					WINHTTP_PROXY_INFO* proxyInfo = (WINHTTP_PROXY_INFO*)calloc(1, sizeof(WINHTTP_PROXY_INFO));
					ctx->proxy_for_url = proxyInfo;

					dprintf("[PROXY] IE config set to proxy %S with bypass %S", ieConfig.lpszProxy, ieConfig.lpszProxyBypass);

					proxyInfo->dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
					proxyInfo->lpszProxy = ieConfig.lpszProxy;
					proxyInfo->lpszProxyBypass = ieConfig.lpszProxyBypass;

					// stop the cleanup code from removing these as we're using them behind the scenes and they will
					// be freed later instead.
					ieConfig.lpszProxy = NULL;
					ieConfig.lpszProxyBypass = NULL;;
				}

				if (ieConfig.lpszAutoConfigUrl)
				{
					GlobalFree(ieConfig.lpszAutoConfigUrl);
				}
				if (ieConfig.lpszProxy)
				{
					GlobalFree(ieConfig.lpszProxy);
				}
				if (ieConfig.lpszProxyBypass)
				{
					GlobalFree(ieConfig.lpszProxyBypass);
				}
			}

			// mark as "configured" so we don't attempt to do this horrible PoS mess again.
			ctx->proxy_configured = TRUE;
		}

		if (ctx->proxy_for_url &&
			!WinHttpSetOption(hReq, WINHTTP_OPTION_PROXY, ctx->proxy_for_url, sizeof(WINHTTP_PROXY_INFO)))
		{
			dprintf("[%s] Unable to set proxy options: %u", GetLastError());
		}
	}
	else
	{
		if (ctx->proxy_user)
		{
			dprintf("[%s] Setting proxy username to %S", direction, ctx->proxy_user);
			if (!WinHttpSetOption(hReq, WINHTTP_OPTION_PROXY_USERNAME, ctx->proxy_user, (DWORD)(wcslen(ctx->proxy_user))));
			{
				dprintf("[%s] Failed to set username %u", direction, GetLastError());
			}
		}
		if (ctx->proxy_pass)
		{
			dprintf("[%s] Setting proxy password to %S", direction, ctx->proxy_pass);
			if (!WinHttpSetOption(hReq, WINHTTP_OPTION_PROXY_PASSWORD, ctx->proxy_pass, (DWORD)(wcslen(ctx->proxy_pass))));
			{
				dprintf("[%s] Failed to set password %u", direction, GetLastError());
			}
		}
	}

	if (ctx->ssl)
	{
		flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA
			| SECURITY_FLAG_IGNORE_CERT_DATE_INVALID
			| SECURITY_FLAG_IGNORE_CERT_CN_INVALID
			| SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE;
		if (!WinHttpSetOption(hReq, WINHTTP_OPTION_SECURITY_FLAGS, &flags, sizeof(flags)))
		{
			dprintf("[%s] failed to set the security flags on the request", direction);
		}
	}

	return hReq;
}