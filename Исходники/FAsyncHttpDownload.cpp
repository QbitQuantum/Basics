HRESULT FAsyncDownload::FHttpDownloadTP::ProcessDownload(FAsyncDownData *pData)
{
    HRESULT hr = E_FAIL; 


    FString ReqUrl = pData->m_pUrlInfo->m_DownloadUrl;
    UrlUnescapeInPlace(ReqUrl.GetBuffer(), 0); 

    CUrl url;
    url.CrackUrl(ReqUrl);

	const tchar* pszUserAgent = "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)";
    FHInternet hIn = NULL; 
	if (g_AppSettings.m_Proxy.GetLength() > 0)
	{
		hIn = InternetOpen(pszUserAgent, INTERNET_OPEN_TYPE_PROXY, g_AppSettings.m_Proxy, g_AppSettings.m_ProxyA, 0);
	}
	else
	{
		hIn = InternetOpen(pszUserAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	}

     
    if (NULL == hIn)
        return E_HTTP_NET_ERROR; 

    FHInternet hCon = InternetConnect(hIn, url.GetHostName(), url.GetPortNumber(), url.GetUserName(), url.GetPassword(), INTERNET_SERVICE_HTTP, 0, 0); 

    if (NULL == hCon)
    {
        _DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: InternetConnect() failed: %d\n", GetLastError()); 
        return E_HTTP_NET_ERROR; 
    }

	ULONG ulRecvTimeout = 15000; 
	InternetSetOption(hCon, INTERNET_OPTION_RECEIVE_TIMEOUT, &ulRecvTimeout, sizeof(ULONG));


    FString StrRes = url.GetUrlPath();
    StrRes+= url.GetExtraInfo(); 
    
    FHInternet hReq = HttpOpenRequest(hCon, "GET", StrRes, NULL, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_DONT_CACHE, 0); 

    if (NULL == hReq)
    {
        _DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: HttpOpenRequest() failed: %d\n", GetLastError()); 
        return E_HTTP_NET_ERROR; 
    }

	size_type FileSize = 0;
	
	

	if (!(pData->m_pUrlInfo->m_dwDownloadFlags & HTTP_FLAG_NO_RESUME))
		FileSize = GetFileSize(pData->m_pUrlInfo->m_DownloadFile);

    // See if file already exists on the disk.
    if (FileSize > 0)
    {
        FString StrRange; 
        StrRange.Format("Range: bytes=%I64d-", FileSize); 
        HttpAddRequestHeaders(hReq, StrRange, StrRange.GetLength(), HTTP_ADDREQ_FLAG_ADD_IF_NEW);
    }


	FString StrVersion; 
	StrVersion.Format("LTV_VERSION: %s", g_AppSettings.m_AppVersion); 
	HttpAddRequestHeaders(hReq, StrVersion, StrVersion.GetLength(), HTTP_ADDREQ_FLAG_ADD_IF_NEW);

    if (!HttpSendRequest(hReq, NULL, 0, NULL, 0))
    {
		int err = GetLastError(); 
        _DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: HttpSendRequest() failed: %d (0x%x)\n", err, HRESULT_FROM_WIN32(err)); 
        InternetCloseHandle(hCon);
        InternetCloseHandle(hIn); 
        return E_HTTP_NET_ERROR; 
    }

    const DWORD dwBufferSize = 8192;
    char pBuffer[dwBufferSize];

    FHttpConnection FConn = hReq;

    DWORD dwStatusCode = FConn.GetStatusCode(); 

	FString ReqContentType = pData->m_pUrlInfo->m_ContentType; 
	pData->m_pUrlInfo->m_ContentType = FConn.GetHeader(HTTP_QUERY_CONTENT_TYPE);
	pData->m_pUrlInfo->m_dwStatusCode = dwStatusCode; 

	if (!MatchContentType(ReqContentType, pData->m_pUrlInfo->m_ContentType))
	{
		_DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: Content type mismatch: %s/%s\n", ReqContentType, pData->m_pUrlInfo->m_ContentType); 
		return E_NOINTERFACE; //E_NOINTERFACE = content type mismatch
	}

	if (dwStatusCode == 416 && FileSize > 0)
	{
		_DBGAlert("FAsyncDownload::FHttpDownloadTP::ProcessDownload: Server status code: %d. Download complete\n", dwStatusCode); 
		return S_OK; 
	}

    if (dwStatusCode < 200 || dwStatusCode > 206)
    {
        _DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: Server status code: %d\n", dwStatusCode); 
		if (dwStatusCode == 404)
			return E_HTTP_NOTFOUND; 
		return E_HTTP_INVALID_STATUS; 
    }

    CAtlFile OutFile; 

	if (pData->m_pUrlInfo->m_dwDownloadFlags & HTTP_FLAG_NO_RESUME)
		DeleteFile(pData->m_pUrlInfo->m_DownloadFile); 

    hr = OutFile.Create(pData->m_pUrlInfo->m_DownloadFile, GENERIC_WRITE, 0, OPEN_ALWAYS);

    if (FAILED(hr))
    {
		_DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: CreateFile failed: 0x%x, %d : %s\n", hr, GetLastError(), pData->m_pUrlInfo->m_DownloadFile); 
        return E_HTTP_WRITE_FILE; 
    }

    size_type llTotalRead = 0; 
    size_type llSizeMax = 0; 

	size_type ContentLen = FConn.GetContentLength(); 

	pData->m_pUrlInfo->m_ContentLength = ContentLen; 

    if (dwStatusCode == 206)
    {
        FString FStrRange = FConn.GetHeader(HTTP_QUERY_CONTENT_RANGE);
        
        if (FStrRange)
        {
           //Content-Range: bytes 21010-47021/47022
           const char* pszBytes = strstr(FStrRange, "bytes ");
           if (pszBytes != NULL)
           {
               pszBytes+=sizeof("bytes");
               LONGLONG llOffset = _strtoi64(pszBytes, NULL, 10); 
               hr = OutFile.Seek(llOffset, FILE_BEGIN); 
               llTotalRead = (size_type)llOffset; 
               if (FAILED(hr))
               {
                   _DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: Seek to position %d failed: 0x%x, %d\n", hr, GetLastError()); 
               }

               const char* pszTotal = strchr(pszBytes, '/');
               if (pszTotal != NULL)
                   llSizeMax = _strtoi64(pszTotal + 1, NULL, 10); 
           }
        }
    }
	else
	{
		if (ContentLen > 0 && ContentLen == FileSize)
		{
			OutFile.Close();
			return S_OK; 
		}
	}

    if (llSizeMax == 0)
		llSizeMax = ContentLen;


    pData->pBindStatusCallback.OnProgress((ULONG)llTotalRead, (ULONG)llSizeMax, BINDSTATUS_BEGINDOWNLOADDATA, L"");

    DWORD dwBytesRead = 0; 
    for (;;)
    {
        if (!InternetReadFile(hReq, pBuffer, dwBufferSize, &dwBytesRead))
        {
            _DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: InternetReadFile() failed: %d\n", GetLastError()); 
			OutFile.Close();
            return E_HTTP_NET_ERROR; 
        }

		if (dwBytesRead == 0)
		{
			hr = S_OK; 
			break; 
		}

        DWORD dwBytesWritten = 0; 
        hr = OutFile.Write(pBuffer, dwBytesRead, &dwBytesWritten); 

		if (FAILED(hr))
        {
            _DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: FileWrite failed: 0x%x, %d\n", hr, GetLastError()); 
			OutFile.Close();
            return E_HTTP_WRITE_FILE; 
        }

        llTotalRead+=dwBytesRead;
		
		pData->pBindStatusCallback.OnProgress((ULONG)llTotalRead, llSizeMax > 0 ? (ULONG)llSizeMax : llTotalRead , BINDSTATUS_DOWNLOADINGDATA, L"");


        if (m_pThis->m_Stopping || pData->pBindStatusCallback.m_Abort)
        {
            _DBGAlert("**FAsyncDownload::FHttpDownloadTP::ProcessDownload: Download aborted\n", hr, GetLastError()); 
            hr = E_ABORT; 
            break; 
        }
    }

	OutFile.Close();
    return hr; 
}