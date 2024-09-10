void ExplorerAliveChecker::init()
{
	DWORD dwExplorerProcessId = NULL;

	GetWindowThreadProcessId(_explorerHwnd, &dwExplorerProcessId);

	if (dwExplorerProcessId == NULL)
		ExplorerQuitCallback(this, FALSE);

	HANDLE explorerProcessHandle = OpenProcess(SYNCHRONIZE,
									FALSE,
									dwExplorerProcessId);
	
	if (explorerProcessHandle != NULL)
	{
		HANDLE waitObjectHandle;
		// request function to t
		RegisterWaitForSingleObject(&waitObjectHandle,
									explorerProcessHandle,
									ExplorerQuitCallback,
									this, // argument to pass to callback function
									INFINITE,
									WT_EXECUTEDEFAULT | WT_EXECUTEONLYONCE);
	}

			
}