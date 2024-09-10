	bool CLoggingImp::InitLogging()
	{
		if (!SHGetSpecialFolderPathW(0, m_wszLogDir, CSIDL_APPDATA, TRUE))
		{
			return false;
		}
		PathAppendW(m_wszLogDir, L"Logging");
		if (!CreateDirectoryW(m_wszLogDir, 0) && 
			GetLastError() != ERROR_ALREADY_EXISTS)
		{
			return false;
		}

		CleanOldLog();

		wchar_t wszBaseName[MAX_PATH] = {0};
		if (!GetModuleFileNameW(0, wszBaseName, MAX_PATH))
		{
			return false;
		}
		PathRemoveExtensionW(wszBaseName);
		PathStripPathW(wszBaseName);
		wchar_t wszLogFile[MAX_PATH] = {0};
		HRESULT hr = StringCchPrintfW(wszLogFile, MAX_PATH, L"%s\\%s_PID%d_%d.log", 
			m_wszLogDir, wszBaseName, GetCurrentProcessId(), GetTickCount());
		if (FAILED(hr))
		{
			return false;
		}
		//create file
		std::locale loc("");
		m_logwfstream.imbue(loc);
		m_logwfstream.open(wszLogFile, std::ios_base::out);	//TODO: what mode?
		if (!m_logwfstream)
		{
			return false;
		}
		//initialize critical section
		bool bOk = true;
		try
		{
			InitializeCriticalSection(&m_csWriteFile);
		}
		catch (...)
		{
			bOk = false;
			m_logwfstream.close();
		}
		
		m_logwfstream << L"\t\tIF ANY ERROR OCCURRED, "
			L"PLS CONTACT ME: [email protected].\n\n\n";
		
		return bOk;
	}