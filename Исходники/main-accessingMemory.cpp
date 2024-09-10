void printExplorerPid()
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			std::wstring binaryPath = entry.szExeFile;
			if (binaryPath.find(L"explorer.exe") != std::wstring::npos)
			{
				printf("Explorer's pid is %d\n", entry.th32ProcessID);
				break;
			}
		}
	}

	CloseHandle(snapshot);
}