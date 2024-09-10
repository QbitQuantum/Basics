DWORD CUpdateDownloader::DownloadFile(const CString& url, const CString& dest, bool showProgress) const
{
	CString hostname;
	CString urlpath;
	URL_COMPONENTS urlComponents = {0};
	urlComponents.dwStructSize = sizeof(urlComponents);
	urlComponents.lpszHostName = hostname.GetBufferSetLength(INTERNET_MAX_HOST_NAME_LENGTH);
	urlComponents.dwHostNameLength = INTERNET_MAX_HOST_NAME_LENGTH;
	urlComponents.lpszUrlPath = urlpath.GetBufferSetLength(INTERNET_MAX_PATH_LENGTH);
	urlComponents.dwUrlPathLength = INTERNET_MAX_PATH_LENGTH;
	if (!InternetCrackUrl(url, url.GetLength(), 0, &urlComponents))
		return GetLastError();
	hostname.ReleaseBuffer();
	urlpath.ReleaseBuffer();

	if (m_bForce)
		DeleteUrlCacheEntry(url);

	BOOL bTrue = TRUE;
	BOOL enableDecoding = InternetSetOption(hOpenHandle, INTERNET_OPTION_HTTP_DECODING, &bTrue, sizeof(bTrue));

	bool isHttps = urlComponents.nScheme == INTERNET_SCHEME_HTTPS;
	HINTERNET hConnectHandle = InternetConnect(hOpenHandle, hostname, urlComponents.nPort, nullptr, nullptr, isHttps ? INTERNET_SCHEME_HTTP : urlComponents.nScheme, 0, 0);
	if (!hConnectHandle)
	{
		DWORD err = GetLastError();
		CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": Download of %s failed on InternetConnect: %d\n"), (LPCTSTR)url, err);
		return err;
	}
	SCOPE_EXIT{ InternetCloseHandle(hConnectHandle); };
	HINTERNET hResourceHandle = HttpOpenRequest(hConnectHandle, nullptr, urlpath, nullptr, nullptr, nullptr, INTERNET_FLAG_KEEP_CONNECTION | (isHttps ? INTERNET_FLAG_SECURE : 0) | (m_bForce ? INTERNET_FLAG_HYPERLINK : 0), 0);
	if (!hResourceHandle)
	{
		DWORD err = GetLastError();
		CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": Download of %s failed on HttpOpenRequest: %d\n"), (LPCTSTR)url, err);
		return err;
	}
	SCOPE_EXIT{ InternetCloseHandle(hResourceHandle); };

	if (enableDecoding)
		HttpAddRequestHeaders(hResourceHandle, L"Accept-Encoding: gzip, deflate\r\n", (DWORD)-1, HTTP_ADDREQ_FLAG_ADD);

	{
resend:
		BOOL httpsendrequest = HttpSendRequest(hResourceHandle, nullptr, 0, nullptr, 0);

		DWORD dwError = InternetErrorDlg(m_hWnd, hResourceHandle, ERROR_SUCCESS, FLAGS_ERROR_UI_FILTER_FOR_ERRORS | FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS | FLAGS_ERROR_UI_FLAGS_GENERATE_DATA, nullptr);

		if (dwError == ERROR_INTERNET_FORCE_RETRY)
			goto resend;
		else if (!httpsendrequest)
		{
			DWORD err = GetLastError();
			CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": Download of %s failed: %d, %d\n"), (LPCTSTR)url, httpsendrequest, err);
			return err;
		}
	}

	DWORD contentLength = 0;
	{
		DWORD length = sizeof(contentLength);
		HttpQueryInfo(hResourceHandle, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&contentLength, &length, NULL);
	}
	{
		DWORD statusCode = 0;
		DWORD length = sizeof(statusCode);
		if (!HttpQueryInfo(hResourceHandle, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&statusCode, &length, NULL) || statusCode != 200)
		{
			CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": Download of %s returned %d\n"), (LPCTSTR)url, statusCode);
			if (statusCode == 404)
				return ERROR_FILE_NOT_FOUND;
			else if (statusCode == 403)
				return ERROR_ACCESS_DENIED;
			return (DWORD)INET_E_DOWNLOAD_FAILURE;
		}
	}

	CFile destinationFile;
	if (!destinationFile.Open(dest, CFile::modeCreate | CFile::modeWrite))
	{
		return ERROR_ACCESS_DENIED;
	}
	DWORD downloadedSum = 0; // sum of bytes downloaded so far
	do
	{
		DWORD size; // size of the data available
		if (!InternetQueryDataAvailable(hResourceHandle, &size, 0, 0))
		{
			DWORD err = GetLastError();
			CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": Download of %s failed on InternetQueryDataAvailable: %d\n"), (LPCTSTR)url, err);
			return err;
		}

		DWORD downloaded; // size of the downloaded data
		auto buff = std::make_unique<TCHAR[]>(size + 1);
		if (!InternetReadFile(hResourceHandle, (LPVOID)buff.get(), size, &downloaded))
		{
			DWORD err = GetLastError();
			CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": Download of %s failed on InternetReadFile: %d\n"), (LPCTSTR)url, err);
			return err;
		}

		if (downloaded == 0)
			break;

		buff[downloaded] = '\0';
		destinationFile.Write(buff.get(), downloaded);

		downloadedSum += downloaded;

		if (!showProgress)
			continue;

		ASSERT(m_uiMsg && m_eventStop);

		if (contentLength == 0) // got no content-length from webserver
		{
			DOWNLOADSTATUS downloadStatus = { 0, 1 + 1 }; // + 1 for download of signature file
			::SendMessage(m_hWnd, m_uiMsg, 0, reinterpret_cast<LPARAM>(&downloadStatus));
		}
		else
		{
			if (downloadedSum > contentLength)
				downloadedSum = contentLength - 1;
			DOWNLOADSTATUS downloadStatus = { downloadedSum, contentLength + 1 }; // + 1 for download of signature file
			::SendMessage(m_hWnd, m_uiMsg, 0, reinterpret_cast<LPARAM>(&downloadStatus));
		}

		if (::WaitForSingleObject(*m_eventStop, 0) == WAIT_OBJECT_0)
		{
			return (DWORD)E_ABORT; // canceled by the user
		}
	}
	while (true);

	if (downloadedSum == 0)
	{
		CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": Download size of %s was zero.\n"), (LPCTSTR)url);
		return (DWORD)INET_E_DOWNLOAD_FAILURE;
	}
	return ERROR_SUCCESS;
}