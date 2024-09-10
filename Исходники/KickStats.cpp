bool KickStats::SendRequest()
{
	if (!Connected())
		return false;
	
	BOOL  bResults = FALSE;
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	TCHAR statusCode[8];
	DWORD statusCodeLen;
	int nStatusCode = -1;
	TCHAR contentLength[8];
	DWORD contentLengthLen;
	long nContentlength = -1;
	int runs = 0;

	m_sContent.clear();
	m_sContent.resize(0);
	
	bResults = WinHttpSendRequest(m_hRequest,
		WINHTTP_NO_ADDITIONAL_HEADERS, 0,
		WINHTTP_NO_REQUEST_DATA, 0,
		0, 0);
	int err = GetLastError();

	if (bResults)
		bResults = WinHttpReceiveResponse(m_hRequest, NULL);

	statusCodeLen = sizeof(statusCode);
	WinHttpQueryHeaders(m_hRequest, WINHTTP_QUERY_STATUS_CODE, WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &statusCodeLen, WINHTTP_NO_HEADER_INDEX);
	nStatusCode = _wtol(statusCode);

	contentLengthLen = sizeof(contentLength);
	WinHttpQueryHeaders(m_hRequest, WINHTTP_QUERY_CONTENT_LENGTH, WINHTTP_HEADER_NAME_BY_INDEX, &contentLength, &contentLengthLen, WINHTTP_NO_HEADER_INDEX);
	nContentlength = _wtol(contentLength);

//	KickLog(L"==============");

	if (bResults && nStatusCode == 200)
	{
		do
		{
			// Check for available data.
			dwSize = 0;
			dwDownloaded = 0;
			++runs;
			if (runs > 1)
			{
				wchar_t str[1024];
				swprintf(str, L"run: %d", runs);
//				KickLog(str);
			}

			if (!WinHttpQueryDataAvailable(m_hRequest, &dwSize))
				MessageBox(NULL, L"WinHttpQueryDataAvailable failed", L"error", 1);

			// Allocate space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				KickLog(L"KickStats::SendRequest: Out of memory");
				return false;
			}
			else
			{
				// Read the data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(m_hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
				{
					KickLog(L"KickStats::SendRequest: WinHttpReadData failed");
					delete[] pszOutBuffer;
					return false;
				}
				else
				{
					//wchar_t str[1024];
					//swprintf(str, L"down: %d - size: %d - length: %d", dwDownloaded, dwSize, nContentlength);
					//KickLog(str);
					//KickLog(pszOutBuffer);
					m_sContent.append(pszOutBuffer);
				}

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}

		} while (dwSize > 0);
	}

//	KickLog(m_sContent);

	if (!bResults)
		MessageBox(NULL, L"WinHttpReceiveResponse failed", L"error", MB_OK);

	return true;
}