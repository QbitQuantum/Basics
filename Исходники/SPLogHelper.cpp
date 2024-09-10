	void SPLogHelper::WriteLog( wstring log, ... )
	{
		wofstream outLogFile;

		outLogFile.open("log\\spengine.log", ios::app);

		if (!outLogFile)
		{
			CreatLogFile();
			if (!outLogFile)
				return;
		}

		TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
		const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
		const int LASTCHAR = NUMCHARS - 1;

		// Format the input string
		va_list pArgs;
		va_start(pArgs, log);

		// Use a bounded buffer size to prevent buffer overruns.  Limit count to
		// character size minus one to allow for a NULL terminating character.
		(void)StringCchVPrintfW(szBuffer, NUMCHARS - 1, log.c_str(), pArgs);
		va_end(pArgs);

		// Ensure that the formatted string is NULL-terminated
		szBuffer[LASTCHAR] = TEXT('\0');

		SYSTEMTIME sys; 
		GetLocalTime( &sys ); 

		wstring str;

		outLogFile <<
			sys.wYear << "-" << 
			setw(2) <<  setfill(L'0') << sys.wMonth << "-" << 
			setw(2) <<  setfill(L'0') << sys.wDay << " "<< 
			setw(2) <<  setfill(L'0') << sys.wHour << ":" <<
			setw(2) <<  setfill(L'0') << sys.wMinute << ":" <<
			setw(2) <<  setfill(L'0') << sys.wSecond << " : " <<
			str.append(szBuffer) << endl;

		outLogFile.close();
	}