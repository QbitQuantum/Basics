BOOL SuspendAllThreads(BOOL stop)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
	THREADENTRY32 te32;
	DWORD dwOwnerPID = GetCurrentProcessId();
	DWORD dwOwnerTID = GetCurrentThreadId();
	HANDLE hThread;

	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		dbg_msg("[-] SuspendAllThreads - CreateToolhelp32Snapshot() failed\n");
		return FALSE;
	}
	te32.dwSize = sizeof(THREADENTRY32);
	if (!Thread32First(hThreadSnap, &te32)) 
	{
		dbg_msg("[-] SuspendAllThreads - Thread32First() failed\n");
		CloseHandle(hThreadSnap);
		return FALSE;
	}
	do 
	{ 
		if (te32.th32OwnerProcessID == dwOwnerPID && te32.th32ThreadID != dwOwnerTID)
		{
			hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
			if (stop == TRUE)
			{
 				SuspendThread(hThread);
			}
			else
			{
				ResumeThread(hThread);
			}
			CloseHandle(hThread);
		}
	} while (Thread32Next(hThreadSnap, &te32));

	CloseHandle(hThreadSnap);
	return TRUE;
}