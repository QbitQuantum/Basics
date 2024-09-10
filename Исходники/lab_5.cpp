void UpdateListBoxProcess()
{
	SendMessage(ListBoxProcess, LB_RESETCONTENT, 0, 0);

	HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(PROCESSENTRY32);
	Process32First(processSnapshot, &processInfo);
	do
	{
		HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processInfo.th32ProcessID);
		DWORD priorityClass = GetPriorityClass(process);

		TCHAR listBoxLine[1024];
		swprintf((wchar_t*)listBoxLine, L"%s\t%s", processInfo.szExeFile, 
			(LPARAM)ProcessPriorityClassToString(priorityClass));
		int id = SendMessage(ListBoxProcess, LB_ADDSTRING, 0, (LPARAM)listBoxLine);
		SendMessage(ListBoxProcess, LB_SETITEMDATA, id, (LPARAM)processInfo.th32ProcessID);
		CloseHandle(process);
	} while(Process32Next(processSnapshot, &processInfo));
	CloseHandle(processSnapshot);
}