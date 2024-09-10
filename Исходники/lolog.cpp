	const wchar_t *log::get_currentFile()
	{
		__time64_t	_time;
		_time = time(&_time);
		struct tm *_tm;
		_tm = _localtime64(&_time);
		size_t i = wcslen(wcscpy(m_logFile,get_appdataDir()));
		if( *(m_logFile + i - 1) != '\\' )
		{	// Append a backslash if it is missing.
			m_logFile[i++] = '\\';
			m_logFile[i] = 0;
		}
		wcscat(m_logFile,L"lologs");
		_wmkdir(m_logFile);
		_snwprintf( m_logFile + wcslen(m_logFile), MAX_PATH - i, L"\\%s-%04d%02d%02d.log", get_moduleName(), _tm->tm_year+1970, _tm->tm_mon + 1, _tm->tm_mday );

		return m_logFile;
	}