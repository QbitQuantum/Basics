	NTSTATUS ProcessCore::Open(DWORD pid, DWORD access) {
		// Prevent handle leak
		Close();
		// Handle current process differently
		_hProcess = (pid == GetCurrentProcessId()) ? GetCurrentProcess() : OpenProcess(access, false, pid);
		// Some routines in win10 does not support pseudo handle
		if(IsWindows10OrGreater() && pid == GetCurrentProcessId())
			_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if(_hProcess != NULL) {
			_pid = pid;
			return Init();
		}
		return LastNtStatus();
	}