fsInternetResult fsHttpFile::OpenEx(LPCSTR pszFilePath, UINT64 uStartPos, UINT64 uUploadPartSize, UINT64 uUploadTotalSize)
{
	if (uUploadTotalSize == _UI64_MAX)
		return Open_imp (pszFilePath, uStartPos, 0);

	if (uStartPos + uUploadPartSize > uUploadTotalSize)
		return IR_INVALIDPARAM;

	if (!m_pServer) 
		return IR_NOTINITIALIZED;

	HINTERNET hServer = m_pServer->GetHandle ();  

	if (!hServer)
		return IR_NOTINITIALIZED;

	CloseHandle ();

	if (lstrlen (pszFilePath) > 9000)
		return IR_BADURL;

	fsString strFilePath = pszFilePath;
	fsString strFileName;
	if (m_bUseMultipart)
	{
		LPSTR psz = strrchr (strFilePath, '/');
		if (psz)
		{
			strFileName = psz + 1;
			psz [1] = 0;
		}
		else
			strFileName = pszFilePath;
	}

	LPTSTR ppszAcceptedTypes [2] = { "*/*", NULL }; 

	m_hFile = HttpOpenRequest (hServer, "POST", strFilePath, m_pszHttpVersion,
		NULL, (LPCSTR*)ppszAcceptedTypes, INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_KEEP_CONNECTION, 0);

	if (m_hFile == NULL)
		return fsWinInetErrorToIR ();

	fsInternetResult ir = SetupProxy ();
	if (ir != IR_SUCCESS)
	{
		CloseHandle ();
		return ir;
	}

	
	CHAR szHdr [10000] = "";
	
	if (m_bUseMultipart)
		lstrcpy (szHdr, "Content-Type: multipart/form-data; boundary=---------------------------284583012225247");
	else
	{
		lstrcpy (szHdr, "Content-Type: application/x-www-form-urlencoded");
		if (m_strCharset.IsEmpty () == FALSE)
		{
			lstrcat (szHdr, "; charset=");
			lstrcat (szHdr, m_strCharset);
		}
	}

	if (uStartPos || uUploadPartSize != uUploadTotalSize)
	{
		if (*szHdr)
			lstrcat (szHdr, "\r\n");
		sprintf (szHdr + lstrlen (szHdr), "Range: bytes=%I64u-%I64u/%I64u", uStartPos, 
			uStartPos + uUploadPartSize - 1, uUploadTotalSize); 
	}

	if (m_pszCookies)
	{
		if (*szHdr)
			lstrcat (szHdr, "\r\n");
		sprintf (szHdr + lstrlen (szHdr), "Cookie: %s", m_pszCookies); 
	}

	if (m_pszAdditionalHeaders)
	{
		if (*szHdr)
			lstrcat (szHdr, "\r\n");
		lstrcat (szHdr, m_pszAdditionalHeaders);
	}

	
	IgnoreSecurityProblems ();

	int nSizeAdd = 0;
	fsString strMultipartHdr;

	if (m_bUseMultipart)
	{
		m_strLabel = "-----------------------------284583012225247";

		strMultipartHdr = m_strLabel; strMultipartHdr += "\r\n";
		strMultipartHdr += "Content-Disposition: form-data; name=\"uploadFormFile\"; filename=\"";
		strMultipartHdr += strFileName; strMultipartHdr += "\"\r\n";
		strMultipartHdr += "Content-Type: application/octet-stream\r\n\r\n";

		nSizeAdd = strMultipartHdr.GetLength () + m_strLabel.GetLength () + 6;
	}
 
	INTERNET_BUFFERS BufferIn = {0};
	BufferIn.dwStructSize = sizeof (INTERNET_BUFFERS);
	BufferIn.lpcszHeader = szHdr;
	BufferIn.dwHeadersLength = BufferIn.dwHeadersTotal = lstrlen (szHdr);
	BufferIn.dwBufferTotal = (DWORD) (uUploadPartSize + nSizeAdd);

	if (!HttpSendRequestEx (m_hFile, &BufferIn, NULL, HSR_INITIATE, 0))
	{
		ir = fsWinInetErrorToIR ();
		CloseHandle ();
		return  ir; 
	}

	if (m_bUseMultipart)
	{
		DWORD dw;
		if (FALSE == InternetWriteFile (m_hFile, strMultipartHdr, strMultipartHdr.GetLength (), &dw))
		{
			ir = fsWinInetErrorToIR ();
			CloseHandle ();
			return  ir; 
		}
	}

	m_uLeftToUpload = uUploadPartSize;

	return IR_SUCCESS;
}