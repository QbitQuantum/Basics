void ProcessWatch::WriteToLog(TCHAR *strToWrite, int id, BOOL isError)
{
	string strWrite = UnicodeToANSI(strToWrite);
	char time[128] = {};
	if(isError)
	{
		HLOCAL hlocal = NULL;
		DWORD systemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
		BOOL fOk = FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_ALLOCATE_BUFFER,
			NULL,
			id,
			systemLocale,
			(PTSTR)&hlocal,
			0,
			NULL);
		if(fOk && (hlocal != NULL))
		{
			GetTime(time, sizeof(time));
			m_file << "[" << time << "]" << " ERROR: " << (PCTSTR)LocalLock(hlocal) << endl;
			LocalFree(hlocal);
		}
	}
	else
	{
		GetTime(time, sizeof(time));
		m_file <<  "[" << time << "]" << strWrite.c_str() << endl;
	}

}