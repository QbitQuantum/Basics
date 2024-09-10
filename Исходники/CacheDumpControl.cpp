bool CacheDumpControl::Execute(const char* lpszPSExecPath, const char* lpszDumpPath, char* lpszMachine, bool bIs64Bit, char* lpszPipeName)
{
	char* lpszCmdLineFormat;
	int nArgSize;
	char* lpszStopCmdLine;
	char* lpszParams;
	bool result = false;
	
	if (lpszPipeName == NULL)
	{
		// Set the local cachedump path
		if (!bIs64Bit)
			lpszCmdLineFormat = "%s\\cachedump.exe";
		else
			lpszCmdLineFormat = "%s\\cachedump64.exe";

		nArgSize = _scprintf(lpszCmdLineFormat, lpszDumpPath);
		lpszStopCmdLine = new char[nArgSize + 1];
		memset(lpszStopCmdLine, 0, nArgSize + 1);
		_snprintf_s(lpszStopCmdLine, nArgSize, strlen(lpszCmdLineFormat)-1+strlen(lpszDumpPath), lpszCmdLineFormat, lpszDumpPath);

		// Now set the parameters
		lpszCmdLineFormat = " -v";
		lpszParams = new char[nArgSize + 1];
		memset(lpszParams, 0, nArgSize + 1);
		_snprintf_s(lpszParams, nArgSize, strlen(lpszCmdLineFormat)-1, lpszCmdLineFormat);
	}
	else
	{
		lpszStopCmdLine = new char[strlen(lpszPSExecPath) + 1];
		memset(lpszStopCmdLine, 0, strlen(lpszPSExecPath) + 1);
		strncpy_s(lpszStopCmdLine, strlen(lpszPSExecPath) + 1, lpszPSExecPath, strlen(lpszPSExecPath));

		if (!bIs64Bit)
			lpszCmdLineFormat = " -c -n %s %s \"%s\\cachedump.exe\" -v";
		else
			lpszCmdLineFormat = " -c -n %s %s \"%s\\cachedump64.exe\" -v";

		nArgSize = _scprintf(lpszCmdLineFormat, lpszPipeName, lpszMachine, lpszDumpPath);
		lpszParams = new char[nArgSize + 1];
		memset(lpszParams, 0, nArgSize + 1);
		_snprintf_s(lpszParams, nArgSize, strlen(lpszCmdLineFormat)-3+strlen(lpszPipeName)+strlen(lpszMachine)+strlen(lpszDumpPath), lpszCmdLineFormat, lpszPipeName, lpszMachine, lpszDumpPath);
	}

	try
	{
		Process p;

		HANDLE hProcess = p.CreateProcess(lpszStopCmdLine, lpszParams);
		if (hProcess != 0)
		{
			DWORD dwResult = WaitForSingleObject(hProcess, 1200000);	// Wait 20 minutes for process to complete
			if (dwResult != WAIT_OBJECT_0)
			{
				Log.CachedReportError(m_nCacheID, CRITICAL, "Warning: cachedump did not complete in a timely manner - exiting");
				result = false;
			}
			else
			{
				// Read from process's output
				char* szResult;
				int nSize = 65535;

				szResult = new char[nSize];
				memset(szResult, 0, nSize);
				p.ReadFromPipe(&szResult, nSize);

				// Was it successful?
				if (strstr(szResult, "successfully removed") != NULL)
				{
					// Success
					// Write results to a file
					size_t nLen = strlen(lpszMachine) + 10;		// 10 chars accounts for ".cachedump" extension
					char* szTempFilename = new char[nLen + 1];
					memset(szTempFilename, 0, nLen + 1);
					_snprintf_s(szTempFilename, nLen, strlen(lpszMachine)+10, "%s.cachedump", lpszMachine);

					std::ofstream outputFile(szTempFilename, std::ios::out | std::ios::trunc);
					outputFile.write((const char*)szResult, (DWORD)strlen(szResult));
					outputFile.close();
					delete [] szTempFilename;
					Log.CachedReportError(m_nCacheID, CRITICAL, "Cache dumped successfully\n", lpszMachine);
					result = true;
				}
				else
				{
					// Failed
					Log.CachedReportError(m_nCacheID, CRITICAL, "Failed to dump cache (the text returned follows):\n%s", szResult);
					result = false;
				}

				delete [] szResult;
			}
		}
		else
			result = false;
	}
	catch(...)
	{
		result = false;
	}

	delete [] lpszStopCmdLine;
	delete [] lpszParams;

	return result;
}