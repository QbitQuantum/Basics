BOOL CFileLogger::CheckLogFile()
{
	if (!m_pOptions->GetOptionVal(OPTION_ENABLELOGGING)) {
		if (m_hLogFile != INVALID_HANDLE_VALUE) {
			CloseHandle(m_hLogFile);
			m_hLogFile = INVALID_HANDLE_VALUE;
		}
		return TRUE;
	}

	//Get logfile path
	TCHAR path[MAX_PATH + 1000]; //Make it large enough
	GetModuleFileName( 0, path, MAX_PATH );
	LPTSTR pos=_tcsrchr(path, '\\');
	if (pos)
		*++pos=0;
	_tcscat(path, _T("Logs\\"));

	//Get logfile name
	_int64 nLogType = m_pOptions->GetOptionVal(OPTION_LOGTYPE);
	TCHAR filename[MAX_PATH + 1];
	if (!nLogType) {
		_tcscpy(filename, _T("FileZilla Server.log"));
	}
	else {
		SYSTEMTIME time;
		GetLocalTime(&time);
		_stprintf(filename, _T("fzs-%d-%02d-%02d.log"), time.wYear, time.wMonth, time.wDay);
	}

	if (m_hLogFile == INVALID_HANDLE_VALUE || !m_pFileName || _tcscmp(m_pFileName, filename)) {
		TCHAR buffer[MAX_PATH + 1000]; //Make it large enough
		_tcscpy(buffer, path);
		CreateDirectory(buffer, NULL);

		if (m_pFileName)
			delete [] m_pFileName;
		m_pFileName = new TCHAR[_tcslen(filename)+1];
		_tcscpy(m_pFileName, filename);
		_tcscat(buffer, filename);

		if (m_hLogFile != INVALID_HANDLE_VALUE)
			CloseHandle(m_hLogFile);
		m_hLogFile = CreateFile(buffer, GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ, 0, OPEN_ALWAYS, 0, 0);
		if (m_hLogFile == INVALID_HANDLE_VALUE)
			return FALSE;

		SetFilePointer(m_hLogFile, 0, 0, FILE_END);
	}
	_int64 nLimit = m_pOptions->GetOptionVal(OPTION_LOGLIMITSIZE);

	if (nLogType) {
		//Different logfiles for each day
		//Find all log files, delete old ones
		//Also delete newer ones if total size exceeds limit

		//Get current date

		SYSTEMTIME time;
		FILETIME curFileTime;
		GetSystemTime(&time);
		SystemTimeToFileTime(&time, &curFileTime);
		_int64 nTime = curFileTime.dwLowDateTime + ((_int64)curFileTime.dwHighDateTime<<32);

		TCHAR buffer[MAX_PATH + 1000]; //Make it large enough
		_tcscpy(buffer, path);
		_tcscat(buffer, _T("fzs-*.log"));

		WIN32_FIND_DATA FindFileData;
		WIN32_FIND_DATA NextFindFileData;
		HANDLE hFind;
		hFind = FindFirstFile(buffer, &NextFindFileData);

		_int64 nDeleteTime = (_int64)m_pOptions->GetOptionVal(OPTION_LOGDELETETIME);
		if (nDeleteTime)
			nDeleteTime = (nDeleteTime+1) * 60 * 60 * 24 * 10000000;

		//Count total size of all logs, delete the oldest log if exceeding limit
		_int64 totalsize = 0;
		CStdString oldestname;
		_int64 oldestDate = 0;

		while (hFind != INVALID_HANDLE_VALUE)
		{
			FindFileData=NextFindFileData;
			if (!FindNextFile(hFind, &NextFindFileData))
			{
				FindClose(hFind);
				hFind = INVALID_HANDLE_VALUE;
			}

			if (!_tcscmp(FindFileData.cFileName, _T(".")) || !_tcscmp(FindFileData.cFileName, _T("..")))
				continue;

			_int64 size = ((_int64)FindFileData.nFileSizeHigh<<32) + FindFileData.nFileSizeLow;
			if (!_tcscmp(FindFileData.cFileName, m_pFileName))
			{
				totalsize += size;
				continue;
			}

			_int64 curtime=FindFileData.ftLastWriteTime.dwLowDateTime + ((_int64)FindFileData.ftLastWriteTime.dwHighDateTime<<32);
			_int64 span = nTime - curtime;
			TCHAR filename[MAX_PATH + 1000];
			_tcscpy(filename, path);
			_tcscat(filename, FindFileData.cFileName);
			if (nDeleteTime && span > nDeleteTime)
				DeleteFile(filename); //File is too old, delete it
			else
			{
				totalsize += size;
				if (curtime < oldestDate || !oldestDate)
				{
					oldestDate = curtime;
					oldestname = filename;
				}
			}
		}

		if (_tcscmp(oldestname, _T("")) && nLimit && totalsize > nLimit*1024)
		{
			DeleteFile(oldestname);
			return TRUE;
		}
	}

	//Single logfile, check size...
	if (nLimit)
	{
		_int64 size = GetPosition64(m_hLogFile);
		size /= 1024;
		if (size > nLimit) //Log file too large, shrink it...
		{
			int curReadPos = (int)(size * 1024 - (nLimit * 1024) * 0.9); //New log size is 10% smaller than the set limit
			int curWritePos =0;
			const int bufsize = 1024 * 64;
			char buffer[bufsize];
			DWORD numread;
			DWORD numwritten;
			BOOL bFirst = TRUE;;
			do {
				SetFilePointer(m_hLogFile, curReadPos, 0, FILE_BEGIN);
				if (!ReadFile(m_hLogFile, buffer, bufsize, &numread, 0))
					break;
				curReadPos += numread;

				SetFilePointer(m_hLogFile, curWritePos, 0, FILE_BEGIN);
				if (bFirst) //Assure log starts with complete line
				{
					unsigned int i;
					for (i=0; i<numread; i++)
					{
						if (buffer[i] == '\n')
							break;
					}
					if (i >= (numread-1))
						continue;
					bFirst = FALSE;
					if (!WriteFile(m_hLogFile, buffer + i + 1, numread - i - 1, &numwritten, 0))
						break;
				}
				else
					if (!WriteFile(m_hLogFile, buffer, numread, &numwritten, 0))
						break;
					curWritePos += numwritten;

			} while (numread == bufsize);

			SetFilePointer(m_hLogFile, curWritePos, 0, FILE_BEGIN);
			SetEndOfFile(m_hLogFile);
		}
	}
	return TRUE;
}