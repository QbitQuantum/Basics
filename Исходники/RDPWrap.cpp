void SetThreadsState(bool Resume)
{
	HANDLE h, hThread;
	DWORD CurrTh, CurrPr;
	THREADENTRY32 Thread;

	CurrTh = GetCurrentThreadId();
	CurrPr = GetCurrentProcessId();

	h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (h != INVALID_HANDLE_VALUE)
	{
		Thread.dwSize = sizeof(THREADENTRY32);
		Thread32First(h, &Thread);
		do
		{
			if (Thread.th32ThreadID != CurrTh && Thread.th32OwnerProcessID == CurrPr)
			{
				hThread = OpenThread(THREAD_SUSPEND_RESUME, false, Thread.th32ThreadID);
				if (hThread != INVALID_HANDLE_VALUE)
				{
					if (Resume)		ResumeThread(hThread);
					else			SuspendThread(hThread);
					CloseHandle(hThread);
				}
			}
		} while (Thread32Next(h, &Thread));
		CloseHandle(h);
	}
}