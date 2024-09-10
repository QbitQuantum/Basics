BOOL WINAPI breakHdl(DWORD dwCtrlType) {
#ifdef CCTERMINATE
	GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, pi.dwProcessId);
	/* if(!GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, pi.dwProcessId)) TerminateProcess(pi.hProcess, 1); */
#else
	TerminateProcess(pi.hProcess, 1);
#endif
        return TRUE;
}