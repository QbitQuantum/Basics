	void cBreakpoint::GetMainThreadFromCurrentProcess()
	{
		unsigned long uProcessId = GetCurrentProcessId();
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, uProcessId);

		if (!hSnapshot)
			return;

		THREADENTRY32 lpThread;

		lpThread.dwSize = sizeof(THREADENTRY32);

		if (Thread32First(hSnapshot, &lpThread))
		{
			do
			{
				if (lpThread.th32OwnerProcessID == uProcessId)
					break;
			} while (Thread32Next(hSnapshot, &lpThread));

			CloseHandle(hSnapshot);
			thread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, 1, lpThread.th32ThreadID);
		}
	}