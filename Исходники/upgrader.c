void WaitForParentIfChesspark()
{
	PROCESSENTRY32 pe;
	HANDLE hSnapshot, hcpcprocess;
	BOOL next;
	DWORD cpcpid = 0;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	memset(&pe, 0, sizeof(pe));
	pe.dwSize = sizeof(pe);
	next = Process32First(hSnapshot, &pe);
	while(next && cpcpid == 0)
	{
		if (stricmp(pe.szExeFile, "chessparkclient.exe") == 0)
		{
			cpcpid = pe.th32ProcessID;
		}
		memset(&pe, 0, sizeof(pe));
		pe.dwSize = sizeof(pe);
		next = Process32Next(hSnapshot, &pe);
	}

	if (!cpcpid)
	{
		return;
	}

	hcpcprocess = OpenProcess(SYNCHRONIZE | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, cpcpid);

	if (!hcpcprocess)
	{
		return;
	}

	/* Wait 30 seconds, that's long enough, right? :) */
	WaitForSingleObject(hcpcprocess, 30000);
}