bool 
Application_ClientConfigManager::closeProcess(DWORD processId, DWORD* error)
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,TRUE, processId);
	if(hProcess == NULL)
	{
		*error = GetLastError();
		if(*error == ERROR_INVALID_PARAMETER)
		{
			*error = CAPTURE_PE_PROCESS_ALREADY_TERMINATED;
		}
	} else {
		EnumWindows(Application_ClientConfigManager::EnumWindowsProc, (LPARAM)processId);

		DWORD tempProcessId = GetProcessId(hProcess);
		if(tempProcessId == processId)
		{
			if(!TerminateProcess(hProcess, 0))
			{
				*error = GetLastError();
			} else {
				*error = CAPTURE_PE_PROCESS_TERMINATED_FORCEFULLY;
			}
		} else {
			return true;
		}
	}
	return false;
}