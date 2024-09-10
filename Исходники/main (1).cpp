void PrintProcessNameAndID(DWORD processID, bool theFirst)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}
	
	if (_tccmp(szProcessName, L"<unknown>"))
	{	
		if (theFirst)
		{
			twar[i] = processID;
			i++;
		}
		switch (GetPriorityClass(hProcess))	
		{
		case IDLE_PRIORITY_CLASS:
			ListBox_AddString(hWndListOne, _tcscat(szProcessName,L" - IDLE"));
			break;
		case NORMAL_PRIORITY_CLASS:
			ListBox_AddString(hWndListOne, _tcscat(szProcessName, L" - Normal"));
			break;
		case REALTIME_PRIORITY_CLASS:
			ListBox_AddString(hWndListOne, _tcscat(szProcessName, L" - Realtime") );
			break;
		case HIGH_PRIORITY_CLASS:
			ListBox_AddString(hWndListOne, _tcscat(szProcessName, L" - High"));
			break;
		}
	}

	CloseHandle(hProcess);
}