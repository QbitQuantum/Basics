BOOL GetProcessHandle(PHANDLE lpTokenHandle, char *lpszProcName)
{
	if (NULL == lpszProcName)
		return NULL;
	
	PROCESSENTRY32 pe = {};
	
	__tfnCreateToolhelp32Snapshot lpfnCreateToolhelp32Snapshot = (__tfnCreateToolhelp32Snapshot)GetProcAddress(
		LoadLibrary("kernel32.dll"),
		"CreateToolhelp32Snapshot"
	);
	HANDLE hSnapshot = lpfnCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	if (INVALID_HANDLE_VALUE == hSnapshot)
		return NULL;
	
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hSnapshot, &pe))
	{
		for (char *i = lpszProcName; ; i = lpszProcName)
		{
			if (!strcmp(_strupr(pe.szExeFile), _strupr(i)))
				break;
			
			if (!Process32Next(hSnapshot, &pe))
				return NULL;
		}
		
		HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe.th32ProcessID);
		BOOL bOpenedProcToken = OpenProcessToken(hProc, TOKEN_ALL_ACCESS, lpTokenHandle);
		
		CloseHandle(hProc);
		return bOpenedProcToken;
	}
	
	CloseHandle(hSnapshot);
	return NULL;
}