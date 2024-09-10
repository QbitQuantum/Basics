ALERROR CTextFileLog::Create (BOOL bAppend)

//	Create
//
//	Create a new log file

	{
	ASSERT(m_hFile == NULL);

	m_hFile = CreateFile(m_sFilename.GetASCIIZPointer(),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
		{
		DWORD dwError = ::GetLastError();
		m_hFile = NULL;
		return ERR_FAIL;
		}

	//	If we're appending to an existing log file, move the file pointer
	//	to the end of the file.

	if (bAppend)
		{
		LONG lFileHigh = 0;
		m_dwSessionStart = ::SetFilePointer(m_hFile, 0, &lFileHigh, FILE_END);
		}

	//	Otherwise, truncate the file

	else
		{
		SetFilePointer(m_hFile, 0, NULL, FILE_BEGIN);
		SetEndOfFile(m_hFile);
		m_dwSessionStart = 0;
		}

	return NOERROR;
	}