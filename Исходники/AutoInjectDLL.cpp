//通过进程PID获取线程TID
DWORD GetTIDbyPID(DWORD PID)
{
	if (PID != NULL)
	{
		DWORD dwThreadID=NULL;
		THREADENTRY32 te32 = { sizeof(te32) };
		HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (Thread32First(hThreadSnap, &te32))
		{
			do
			{
				if (PID == te32.th32OwnerProcessID)
				{
					dwThreadID = te32.th32ThreadID;
					break;
				}
			} while (Thread32Next(hThreadSnap, &te32));
		}
		wprintf(L"ThreadId:%d\n", dwThreadID);
		return dwThreadID;
	}
	else
		return NULL;
}