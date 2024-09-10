void WindowsHttpDownloader::InternalConnect(char* append_headers)
{
	WCHAR host_name[1024] = {};
	if (wcslen(_url.lpszHostName) > 1024) {
		SetEvent(_events[EventErr]);
		return;
	}
	wcscpy(host_name, _url.lpszHostName);
	if (wcsstr(host_name, L"/") != NULL)
		*wcsstr(host_name, L"/") = 0;
	if (wcsstr(host_name, L":") != NULL)
		*wcsstr(host_name, L":") = 0;

	_http.connect = WinHttpConnect(_http.session, host_name, _url.nPort, 0);
	if (_http.connect == NULL) {
		SetEvent(_events[EventErr]);
		return;
	}
	SetEvent(_events[EventConnect]);
	if (_abort_download)
		return;

	_http.request = WinHttpOpenRequest(_http.connect, L"GET",
		_url.dwUrlPathLength > 0 ? _url.lpszUrlPath : NULL,
		NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	if (_http.connect == NULL) {
		SetEvent(_events[EventErr]);
		return;
	}
	if (_abort_download)
		return;

	DWORD temp = WINHTTP_DISABLE_AUTHENTICATION;
	WinHttpSetOption(_http.request, WINHTTP_OPTION_DISABLE_FEATURE, &temp, sizeof(temp));

	int hcount = _user_heads.size();
	for (int i = 0; i < hcount; i++) {
		WCHAR header[MAX_PATH], hvalue[1024];
		header[0] = hvalue[0] = 0;
		auto h = _user_heads.front();
		_user_heads.pop();
		AnsiToUnicode(h.name, header);
		AnsiToUnicode(h.value, hvalue, _countof(hvalue));
		h.Free();
		auto str = (LPWSTR)malloc(4096);
		RtlZeroMemory(str, 4096);
		wcscpy(str, header);
		wcscat(str, L": ");
		wcscat(str, hvalue);
		WinHttpAddRequestHeaders(_http.request, str, -1, WINHTTP_ADDREQ_FLAG_ADD);
		free(str);
	}

	LPWSTR add_headers = NULL;
	if (append_headers) {
		int add_head_len = MultiByteToWideChar(CP_ACP, 0, append_headers, -1, NULL, 0);
		if (add_head_len > 1) {
			add_headers = (LPWSTR)calloc(2, add_head_len);
			if (add_headers)
				MultiByteToWideChar(CP_ACP, 0, append_headers, -1, add_headers, add_head_len + 1);
		}
	}
	if (!WinHttpSendRequest(_http.request,
		add_headers, -1,
		WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
		if (add_headers)
			free(add_headers);
		_http.Close();
		SetEvent(_events[EventErr]);
		return;
	}
	if (add_headers)
		free(add_headers);
	SetEvent(_events[EventSendRequest]);
	if (_abort_download)
		return;

	if (!WinHttpReceiveResponse(_http.request, NULL)) {
		_http.Close();
		SetEvent(_events[EventErr]);
		return;
	}

	//status code...
	temp = MAX_PATH;
	WCHAR scode[MAX_PATH] = {};
	WinHttpQueryHeaders(_http.request, WINHTTP_QUERY_STATUS_CODE,
		WINHTTP_HEADER_NAME_BY_INDEX, &scode, &temp, WINHTTP_NO_HEADER_INDEX);
	_http.status_code = wcstol(scode, NULL, 10);

	//headers...
	WinHttpQueryHeaders(_http.request, WINHTTP_QUERY_RAW_HEADERS_CRLF,
		WINHTTP_HEADER_NAME_BY_INDEX, NULL, (LPDWORD)&_recv_headers_zero_size, WINHTTP_NO_HEADER_INDEX);
	_recv_headers = (wchar_t*)calloc(_recv_headers_zero_size, 2);
	if (_recv_headers)
		WinHttpQueryHeaders(_http.request, WINHTTP_QUERY_RAW_HEADERS_CRLF,
		WINHTTP_HEADER_NAME_BY_INDEX, _recv_headers, (LPDWORD)&_recv_headers_zero_size, WINHTTP_NO_HEADER_INDEX);

	WinHttpQueryHeaders(_http.request, WINHTTP_QUERY_RAW_HEADERS,
		WINHTTP_HEADER_NAME_BY_INDEX, NULL, (LPDWORD)&_recv_headers_zero_size, WINHTTP_NO_HEADER_INDEX);
	_recv_headers_zero = (unsigned char*)calloc(_recv_headers_zero_size, 2);
	if (_recv_headers_zero)
		WinHttpQueryHeaders(_http.request, WINHTTP_QUERY_RAW_HEADERS,
		WINHTTP_HEADER_NAME_BY_INDEX, _recv_headers_zero, (LPDWORD)&_recv_headers_zero_size, WINHTTP_NO_HEADER_INDEX);

	SetEvent(_events[EventReceiveResponse]);
	if (_abort_download)
		return;

	if (_http.status_code >= 400)
		SetEvent(_events[EventStatusCode400]);
	else
		InternalDownload();
}