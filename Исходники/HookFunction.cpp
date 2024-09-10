DWORD GetModuleHandleInjection(HANDLE proc, PCHAR dllName)
{
	LPVOID RemoteString = NULL, GetModuleHandleAddy;
	GetModuleHandleAddy = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetModuleHandleA");

	if (dllName != NULL)
	{
		RemoteString = (LPVOID)VirtualAllocEx(proc, NULL, strlen(dllName), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (RemoteString == NULL)
		{
			CloseHandle(proc); // Close the process handle.
			ErrorExit(TEXT("VirtualAllocEx"), NULL);
		}

		if (WriteProcessMemory(proc, (LPVOID)RemoteString, dllName, strlen(dllName), NULL) == 0)
		{
			VirtualFreeEx(proc, RemoteString, 0, MEM_RELEASE); // Free the memory we were going to use.
			CloseHandle(proc); // Close the process handle.
			ErrorExit(TEXT("WriteProcessMemory"), NULL);
		}
	}

	HANDLE hThread = CreateRemoteThread(proc, NULL, NULL, (LPTHREAD_START_ROUTINE)GetModuleHandleAddy, (LPVOID)RemoteString, NULL, NULL);
	if (hThread == NULL)
	{
		VirtualFreeEx(proc, RemoteString, 0, MEM_RELEASE); // Free the memory we were going to use.
		CloseHandle(proc); // Close the process handle.
		ErrorExit(TEXT("CreateRemoteThread"), NULL);
	}

	DWORD dwThreadExitCode = 0;

	// Lets wait for the thread to finish 10 seconds is our limit.
	// During this wait, DllMain is running in the injected DLL, so
	// DllMain has 10 seconds to run.
	WaitForSingleObject(hThread, 10000);

	// Lets see what it says...
	GetExitCodeThread(hThread, &dwThreadExitCode);

	// No need for this handle anymore, lets get rid of it.
	CloseHandle(hThread);

	// Lets clear up that memory we allocated earlier.
	VirtualFreeEx(proc, RemoteString, 0, MEM_RELEASE);

	return dwThreadExitCode;
}