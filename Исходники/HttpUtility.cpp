bool HttpQuery(const HttpRequest& request, HttpResponse& response) {
	// initialize
	response.statusCode = -1;
	HINTERNET internet = NULL;
	HINTERNET connectedInternet = NULL;
	HINTERNET requestInternet = NULL;
	BOOL httpResult = FALSE;
	DWORD error = 0;
	std::deque<LPCWSTR> acceptTypes;
	std::deque<BufferPair> availableBuffers;

	// access http
	internet = WinHttpOpen(L"Raven", WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, 0);
	error = GetLastError();
	if (!internet) goto CLEANUP;

	// connect
	connectedInternet = WinHttpConnect(internet, request.server.c_str(), (int)request.port, 0);
	error = GetLastError();
	if (!connectedInternet) goto CLEANUP;

	// open request
	for (int i = 0; i<(int)request.acceptTypes.size(); i++) {
		acceptTypes.push_front(request.acceptTypes[i].c_str());
	}
	acceptTypes.push_front(0);
	requestInternet = WinHttpOpenRequest(connectedInternet, request.method.c_str(), request.query.c_str(), NULL, WINHTTP_NO_REFERER, &acceptTypes[0], (request.secure ? WINHTTP_FLAG_SECURE : 0));
	error = GetLastError();
	if (!requestInternet) goto CLEANUP;

	// authentication, cookie and request
	if (request.username != L"" && request.password != L"") {
		WinHttpSetCredentials(requestInternet, WINHTTP_AUTH_TARGET_SERVER, WINHTTP_AUTH_SCHEME_BASIC, request.username.c_str(), request.password.c_str(), NULL);
	}
	if (request.contentType != L"") {
		httpResult = WinHttpAddRequestHeaders(requestInternet, (L"Content-type:" + request.contentType).c_str(), -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD);
	}
	if (request.cookie != L"") {
		WinHttpAddRequestHeaders(requestInternet, (L"Cookie:" + request.cookie).c_str(), -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD);
	}

	// extra headers
	for (auto it = request.extraHeaders.begin(); it != request.extraHeaders.end(); it++) {
		std::wstring key = it->first;
		std::wstring value = it->second;
		WinHttpAddRequestHeaders(requestInternet, (key + L":" + value).c_str(), -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD);
	}

	if (request.body.size()>0) {
		httpResult = WinHttpSendRequest(requestInternet, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)&request.body[0], (int)request.body.size(), (int)request.body.size(), NULL);
	}
	else {
		httpResult = WinHttpSendRequest(requestInternet, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, NULL);
	}
	error = GetLastError();
	if (httpResult == FALSE) goto CLEANUP;

	// receive response
	httpResult = WinHttpReceiveResponse(requestInternet, NULL);
	error = GetLastError();
	if (httpResult != TRUE) goto CLEANUP;

	DWORD headerLength = sizeof(DWORD);

	// read response status code
	DWORD statusCode = 0;
	httpResult = WinHttpQueryHeaders(requestInternet, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &headerLength, WINHTTP_NO_HEADER_INDEX);
	error = GetLastError();
	if (httpResult == FALSE) goto CLEANUP;
	response.statusCode = statusCode;
	
	// read respons cookie
	httpResult = WinHttpQueryHeaders(requestInternet, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &headerLength, WINHTTP_NO_HEADER_INDEX);
	error = GetLastError();
	if (error == ERROR_INSUFFICIENT_BUFFER) {
		wchar_t* rawHeader = new wchar_t[headerLength / sizeof(wchar_t)];
		ZeroMemory(rawHeader, headerLength);
		httpResult = WinHttpQueryHeaders(requestInternet, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, rawHeader, &headerLength, WINHTTP_NO_HEADER_INDEX);

		const wchar_t* cookieStart = wcsstr(rawHeader, L"Cookie:");
		if (cookieStart) {
			const wchar_t* cookieEnd = wcsstr(cookieStart, L";");
			if (cookieEnd) {
				response.cookie = std::wstring(cookieStart + 7, cookieEnd - cookieStart - 7);
			}
		}
		delete[] rawHeader;
	}

	// read response body
	while (true) {
		DWORD bytesAvailable = 0;
		BOOL queryDataAvailableResult = WinHttpQueryDataAvailable(requestInternet, &bytesAvailable);
		error = GetLastError();
		if (queryDataAvailableResult == TRUE && bytesAvailable != 0) {
			char* utf8 = new char[bytesAvailable];
			DWORD bytesRead = 0;
			BOOL readDataResult = WinHttpReadData(requestInternet, utf8, bytesAvailable, &bytesRead);
			error = GetLastError();
			if (readDataResult == TRUE) {
				availableBuffers.push_front(BufferPair(utf8, bytesRead));
			}
			else {
				delete[] utf8;
			}
		}
		else {
			break;
		}
	}

	// concatincate response body
	int totalSize = 0;
	for each (BufferPair p in availableBuffers) {
		totalSize += p.length;
	}
	response.body.resize(totalSize);
	if (totalSize>0) {
		char* utf8 = new char[totalSize];
		{
			char* temp = utf8;
			for each (BufferPair p in availableBuffers) {
				memcpy(temp, p.buffer, p.length);
				temp += p.length;
			}
		}