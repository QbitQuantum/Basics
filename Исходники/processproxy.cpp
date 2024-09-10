void ProcessProxy::KillProcess(const wchar_t* processName)
{
	HANDLE tool = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32W pe = {0};
	pe.dwSize = sizeof(PROCESSENTRY32W);

	if ( !Process32First(tool, &pe) )
	{
		int errorId = GetLastError();
		CloseHandle(tool);
		return;
	}

	do 
	{
		if ( 0 == wcscmp(pe.szExeFile, processName) )
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
			TerminateProcess(hProcess, -1);
		}

	} while ( Process32NextW(tool, &pe) );

	CloseHandle(tool);
}