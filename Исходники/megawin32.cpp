// POST request to URL
void WinHttpIO::post(HttpReq* req, const char* data /*= nullptr*/, unsigned len /*= 0*/)
{
	if (debug) {
		cout << "POST target URL: " << req->posturl << endl;

		if (req->binary) {
			cout << "[sending " << req->out->size() << " bytes of raw data]" << endl;
		} else {
			cout << "Sending: " << *req->out << endl;
		}
	}

	WinHttpContext* cpContext = new WinHttpContext;
	req->httpiohandle = (void*)cpContext;

	WCHAR szHost[256] = L"";
	URL_COMPONENTS urlComp = { sizeof(URL_COMPONENTS) };

	urlComp.lpszHostName = szHost;
	urlComp.dwHostNameLength = _countof(szHost);
    urlComp.dwUrlPathLength = (DWORD)-1;
    urlComp.dwSchemeLength = (DWORD)-1;

	try {
		// Crack the URL.
		std::wstring strURL = ConvertUTF16fromUTF8(req->posturl);
		BOOL bRet = WinHttpCrackUrl(strURL.c_str(), strURL.length(), 0, &urlComp);
		if (bRet == FALSE)
			throw std::exception("WinHttpCrackUrl failed");

		cpContext->hConnect = WinHttpConnect(hSession, szHost, urlComp.nPort, 0);
		if (cpContext->hConnect == NULL)
			throw std::exception("WinHttpConnect failed");

		cpContext->hRequest = WinHttpOpenRequest(cpContext->hConnect, L"POST", urlComp.lpszUrlPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES,
			(urlComp.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0);
		if (cpContext->hRequest == NULL)
			throw std::exception("WinHttpOpenRequest failed");

		if (data) {
			cpContext->data.assign(data, len);
		}
		req->status = REQ_INFLIGHT;
		cpContext->processThread = std::thread(_ProcessIO, req, cpContext);

		return;
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
		ATLASSERT(FALSE);
	}

	req->status = REQ_FAILURE;
}