bool HttpGateway::upload(wstring& server, wstring& uri, wstring& local) {
	HINTERNET conn = ::InternetConnectW(
		inetCore, 
		server.c_str(), 
		INTERNET_DEFAULT_HTTP_PORT, 
		NULL, 
		NULL, 
		INTERNET_SERVICE_HTTP, 
		0, 
		0
	);
	
	LPCWSTR acc[] = {
		L"*/*", NULL
	};
	
	HINTERNET req = ::HttpOpenRequestW(
		conn, 
		L"POST", 
		uri.c_str(), 
		NULL, 
		NULL, 
		acc, 
		0, 
		INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_HYPERLINK
	);
	
	wstring mac = query_mac_addrw();
	wstring headers;
	headers.append(L"X-mac-addr: ");
	headers.append(mac);
	
	HttpAddRequestHeadersW(req, mac.c_str(), 0, HTTP_ADDREQ_FLAG_ADD_IF_NEW);
	
	FILE* f = wfopen(local.c_str(), L"rb");
	DWORD bufsize = 1024*100;
	DWORD totalsize = wfsize(local.c_str());

	INTERNET_BUFFERS ib;
	memset(&ib, 0, sizeof(INTERNET_BUFFERS));
	ib.dwStructSize = sizeof(INTERNET_BUFFERS);
	ib.dwBufferTotal = totalsize;
	ib.dwBufferLength = bufsize;

	::HttpSendRequestEx(req, &ib, NULL, 0, 0);
	
    char *buffer = new char[bufsize];
    DWORD dwWritten = 0;
    size_t readBytes = 0;
    while (!feof(f)) {
    	memset(buffer, 0, bufsize * sizeof(char));
    	readBytes = fread(buffer, sizeof(char), bufsize, f);
    	::InternetWriteFile(req, buffer, readBytes, &dwWritten);
    }

    fclose(f);
	::HttpEndRequest(req, NULL, 0, 0);
	::InternetCloseHandle(conn);
}