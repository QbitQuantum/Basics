String HTTPGetString (CTSTR url, CTSTR extraHeaders, int *responseCode, String verb)
{
    HINTERNET hSession = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    URL_COMPONENTS  urlComponents;
    BOOL secure = FALSE;
	String result = "";
	String body = TEXT("");
	String nurl = url;

    String hostName, path;

    const TCHAR *acceptTypes[] = {
        TEXT("*/*"),
        NULL
    };

	if (verb == TEXT("POST")){
		CTSTR s = srchr(url, TEXT('?'));
		body = String(s + 1);
		nurl = nurl.Left(s - url);
	}

    hostName.SetLength(256);
    path.SetLength(1024);

    zero(&urlComponents, sizeof(urlComponents));

    urlComponents.dwStructSize = sizeof(urlComponents);
    
    urlComponents.lpszHostName = hostName;
    urlComponents.dwHostNameLength = hostName.Length();

    urlComponents.lpszUrlPath = path;
    urlComponents.dwUrlPathLength = path.Length();

	WinHttpCrackUrl(nurl, 0, 0, &urlComponents);

    if (urlComponents.nPort == 443)
        secure = TRUE;

    hSession = WinHttpOpen(TEXT("gecko test"), WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession)
        goto failure;

    hConnect = WinHttpConnect(hSession, hostName, secure ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT, 0);
    if (!hConnect)
        goto failure;

    hRequest = WinHttpOpenRequest(hConnect, verb, path, NULL, WINHTTP_NO_REFERER, acceptTypes, secure ? WINHTTP_FLAG_SECURE|WINHTTP_FLAG_REFRESH : WINHTTP_FLAG_REFRESH);
    if (!hRequest)
        goto failure;

    BOOL bResults = WinHttpSendRequest(hRequest, extraHeaders, extraHeaders ? -1 : 0, body.Array(), 
		body.Length(), body.Length(), 0);

    // End the request.
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);
    else
        goto failure;

    TCHAR statusCode[8];
    DWORD statusCodeLen;

    statusCodeLen = sizeof(statusCode);
    if (!WinHttpQueryHeaders (hRequest, WINHTTP_QUERY_STATUS_CODE, WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &statusCodeLen, WINHTTP_NO_HEADER_INDEX))
        goto failure;

    *responseCode = wcstoul(statusCode, NULL, 10);	

    if (bResults && *responseCode == 200)
    {
        CHAR buffer[16384];
        DWORD dwSize, dwOutSize;

        do 
        {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                goto failure;

            if (!WinHttpReadData(hRequest, (LPVOID)buffer, dwSize, &dwOutSize))
            {
                goto failure;
            }
            else
            {
                if (!dwOutSize)
                    break;

				// Ensure the string is terminated.
				buffer[dwOutSize] = 0;

				String b = String((LPCSTR)buffer);
				result.AppendString(b);
            }
        } while (dwSize > 0);
    }

failure:
    if (hSession)
        WinHttpCloseHandle(hSession);
    if (hConnect)
        WinHttpCloseHandle(hConnect);
    if (hRequest)
        WinHttpCloseHandle(hRequest);

    return result;
}