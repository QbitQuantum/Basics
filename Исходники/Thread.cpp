	void ScopedThreadExclusive::GetThreads(std::vector<DWORD>& threads)
	{
		ScopedHandle hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (hSnapshot == INVALID_HANDLE_VALUE)
		{
			return;
		}
		
		THREADENTRY32 te = { sizeof(te) };
		if (Thread32First(hSnapshot, &te))
		{
			do 
			{
				if (te.th32OwnerProcessID == GetCurrentProcessId()
					&& te.th32ThreadID != GetCurrentThreadId())
				{
					threads.push_back(te.th32ThreadID);
				}
			} 
			while (Thread32Next(hSnapshot, &te));
		}
	}