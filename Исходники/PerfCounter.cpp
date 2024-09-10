PerfCounter::PerfCounter()
{
	PdhOpenQuery(NULL, NULL, &m_query);

	HMODULE hProcess = GetModuleHandle(NULL);
	wchar_t fileNameBuf[MAX_PATH];
	GetModuleFileName((HMODULE) hProcess, fileNameBuf, MAX_PATH);
	wchar_t baseNameBuf[MAX_PATH];
	_wsplitpath_s(fileNameBuf, NULL, 0, NULL, 0, baseNameBuf, MAX_PATH, NULL, 0);
	m_processName = baseNameBuf;
	DWORD processId = GetProcessId(GetCurrentProcess());

	//we need to figure out the correct instance name
	//start by asking for all the counters which match the process name
	std::wstring wildcard = (boost::wformat(L"\\Process(%1%*)\\ID Process") % m_processName).str();
	wchar_t paths[1024];
	DWORD size = 1024;
	PdhExpandWildCardPath(NULL, wildcard.c_str(), paths, &size, 0);

	//create each ProcessID counter, check its value to see if it's the one we want
	size_t len = wcslen(paths);
	wchar_t* pathPtr = paths;
	bool found = false;
	while(len != 0)
	{
		PDH_HCOUNTER counter;
		PdhAddCounter(m_query, pathPtr, NULL, &counter);
		PdhCollectQueryData(m_query);
		PDH_RAW_COUNTER counterValue;
		PdhGetRawCounterValue(counter, 0, &counterValue);
		PdhRemoveCounter(counter);

		if(counterValue.FirstValue == processId)
		{
			found = true;
			break;
		}

		pathPtr += len + 1;
		len = wcslen(pathPtr);
	}

	if(found)
	{
		//we've got our desired instance name, which is ProcessName#N
		const wchar_t* instStart = wcschr(wildcard.c_str(), L'(') + 1;
		const wchar_t* instEnd = wcschr(wildcard.c_str(), L')') - 1;
		m_instName = std::wstring(instStart, instEnd - instStart);
	}
	else
	{
		//oh well, just roll with what we've got
		m_instName = m_processName;
	}
}