bool		ProcInOut::Exec(const std::string & cmd, std::string & out, DWORD timeout) {
	bool	fSuccess; 

	ZeroMemory(&saAttr, sizeof(saAttr));
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 
	hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	if (! CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0)) 
		return false; 
	if (! SetStdHandle(STD_OUTPUT_HANDLE, hChildStdoutWr)) 
		return false; 
	fSuccess = (DuplicateHandle(GetCurrentProcess(), hChildStdoutRd,
		GetCurrentProcess(), &hChildStdoutRdDup , 0,
		(FALSE ? false : true),
		(BOOL)DUPLICATE_SAME_ACCESS) != 0);
	if( !fSuccess )
		return false;
	CloseHandle(hChildStdoutRd);
	if (! CreateChildProcess(cmd)) {
		CloseHandle(hChildStdoutWr);
		CloseHandle(hChildStdoutRdDup);
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
		return false;
	}
	if (! SetStdHandle(STD_OUTPUT_HANDLE, hSaveStdout)) 
		return false;
	if (!CloseHandle(hChildStdoutWr)) 
		return false;
	HANDLE			lpHandles[] = { piProcInfo.hProcess, hChildStdoutRdDup, NULL};
	DWORD			dwWait;
	DWORD			timerStart = GetTickCount();
	DWORD			timerEnd;
	for (;;) {
		dwWait = WaitForMultipleObjects(2, lpHandles, false, timeout);
		// process finished
		if (dwWait == WAIT_OBJECT_0 || dwWait == WAIT_ABANDONED_0 || dwWait == (WAIT_ABANDONED_0 + 1)) {
			break;
		}
		if (dwWait == (WAIT_OBJECT_0 + 1)) {
			timerEnd = GetTickCount();
			// timeout
			if (timerEnd < timerStart && ((MAXDWORD - timerStart) + timerEnd) >= timeout) // counter has been reinitialized
				break ;
			if (timerStart < timerEnd && (timerEnd - timerStart) >= timeout)
				break ;
			ReadFromPipe(out); 
		}
		if (dwWait == WAIT_TIMEOUT) {
			break;			
		}
	}
	CloseHandle(hChildStdoutRdDup);
	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);
	return true; 
}