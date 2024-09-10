//-------------------------------------------------------------
LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* pExceptionInfo)
{
	if (IsDebuggerPresent())
		return EXCEPTION_CONTINUE_SEARCH;

	THREADENTRY32 te32;
	DWORD myThreadId = GetCurrentThreadId();
	DWORD myProcessId = GetCurrentProcessId();

	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap != INVALID_HANDLE_VALUE)
	{
		te32.dwSize = sizeof(THREADENTRY32);

		if (Thread32First(hThreadSnap, &te32))
		{
			do
			{
				if (te32.th32OwnerProcessID == myProcessId && te32.th32ThreadID != myThreadId)
				{
					HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
					if (hThread)
					{
						SuspendThread(hThread);
					}
				}

			} while (Thread32Next(hThreadSnap, &te32));

		}

		CloseHandle(hThreadSnap);
	}

	// dump文件
	MakeDump(pExceptionInfo);
	// 强制进程退出
	ExitProcess(1);

	return EXCEPTION_EXECUTE_HANDLER;
}