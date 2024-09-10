BOOL  isGuiApp() {
	DWORD mypid;
	HANDLE myprocess;
	mypid = GetCurrentProcessId();
	myprocess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, mypid);
	return GetGuiResources(myprocess, 1) > 0;
	}