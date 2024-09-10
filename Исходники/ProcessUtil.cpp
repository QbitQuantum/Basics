CString GetProcessPath(CString strImageName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);
	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	DWORD dwPID = -1;
	CString strProcessName;
	if (processesSnapshot != INVALID_HANDLE_VALUE)
	{
		Process32First(processesSnapshot, &processInfo);
		strProcessName = processInfo.szExeFile;
		if (!_tcscmp(strProcessName, strImageName))
			dwPID = processInfo.th32ProcessID;
		while (dwPID == -1 && Process32Next(processesSnapshot, &processInfo))
		{
			strProcessName = processInfo.szExeFile;
			if (!_tcscmp(strProcessName, strImageName))
				dwPID = processInfo.th32ProcessID;
		}
		CloseHandle(processesSnapshot);
	}

	if (dwPID != -1)
	{
		TCHAR szModulePath[MAX_PATH] = {0};
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
		if (NULL != hProcess)
		{
			DWORD cbNeeded;
			HMODULE hMod;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
				GetModuleFileNameEx(hProcess, hMod, szModulePath, MAX_PATH);
			CloseHandle( hProcess );
		}
		return szModulePath;
	}
	else
		return _T("");
}