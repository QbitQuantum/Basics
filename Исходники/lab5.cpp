void GetProcessList()
{
	PROCESSENTRY32 pe32;
	HANDLE hSnapshot;
	HANDLE hProcess;
	DWORD dwPriorityClass;
	
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);

	Process32First( hSnapshot, &pe32 );

	SendMessage(hListBox1, LB_RESETCONTENT, 0, 0);

	do {
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		dwPriorityClass = GetPriorityClass(hProcess);

		char text[1024];
		swprintf((wchar_t*)text, L"[%d] %s [%s]", pe32.th32ProcessID, pe32.szExeFile, GetPriorityClassName(dwPriorityClass));
		int index = SendMessage(hListBox1, LB_ADDSTRING, 0, (LPARAM)text);
		SendMessage(hListBox1, LB_SETITEMDATA, index, (LPARAM)pe32.th32ProcessID);

	} while (Process32Next(hSnapshot, &pe32));

	CloseHandle(hSnapshot);	
}