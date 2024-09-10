// thread handler for the main message thread
DWORD unix_process(DWORD lparam)
{
	MSG msg;
	HANDLE Window_created = (HANDLE)lparam;

	if ( !unix_create_window() )
		return 0;

	// Let the app continue once the window is created
	SetEvent(Window_created);

	while (1)	{	
		if (WaitMessage() == TRUE)	{
			EnterCriticalSection(&Os_lock);			
			while(PeekMessage(&msg,0,0,0,PM_REMOVE))	{
				if ( msg.message == WM_DESTROY )	{
					LeaveCriticalSection(&Os_lock);

					// cleanup and exit this thread!!
					DeleteCriticalSection(&Os_lock);
					return 0;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			LeaveCriticalSection(&Os_lock);
		} 
	}
	return 0;
}