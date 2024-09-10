DWORD WINAPI setUserNamePasswordThread(LPVOID lpDummy)
{
	DWORD dwPid = (DWORD)lpDummy;
	HANDLE mutex = CreateMutex(NULL, TRUE, _T("setUserNamePasswordMutex"));

	// Check double entrance
	if(GetLastError() == ERROR_ALREADY_EXISTS)
		return 0;

	WaitForSingleObject(SkypeReady, 5000);
	EnumWindows (EnumWindowsProc, dwPid);

	ReleaseMutex(mutex);
	CloseHandle(mutex);
	return 0;
}