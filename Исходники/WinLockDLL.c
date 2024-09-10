/************************************************
 * Create a new Desktop and run a Thread in it. *
 * (Win NT+).                                   *
 ************************************************/
int DLL_EXP_IMP WINAPI Thread_Desktop(LPTHREAD_START_ROUTINE ThreadFunc, THREAD_DATA *td)
{
	HDESK	hOriginalThread;
	HDESK	hOriginalInput;
	HDESK	hNewDesktop;

	// Save original ...
	hOriginalThread = GetThreadDesktop(GetCurrentThreadId());
	hOriginalInput = OpenInputDesktop(0, FALSE, DESKTOP_SWITCHDESKTOP);

	// Create a new Desktop and switch to it
	hNewDesktop = CreateDesktop(td->szDesktopName, NULL, NULL, 0, GENERIC_ALL, NULL);
	SetThreadDesktop(hNewDesktop);
	SwitchDesktop(hNewDesktop);

	// Execute thread in new desktop
	td->hDesk = hNewDesktop;
	StartThread(ThreadFunc, td);

	// Restore original ...
	SwitchDesktop(hOriginalInput);
	SetThreadDesktop(hOriginalThread);

	// Close the Desktop
	CloseDesktop(hNewDesktop);

	return 0;
}