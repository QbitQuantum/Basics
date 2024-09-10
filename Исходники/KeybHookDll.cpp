__declspec (dllexport) void CALLBACK UninstallHook (void)
{ 
	//this function unhooks all threads
	UnhookWindowsHookEx(hHook);
	return;
} 