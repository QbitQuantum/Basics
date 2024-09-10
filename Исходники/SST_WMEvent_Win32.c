static int Win32_GetEvent(SST_DisplayTarget target, SST_WMEvent* eventReturn)
{
	MSG msg;
	SST_DisplayTarget_Win32* displayTarget = (SST_DisplayTarget_Win32*)target;
	SST_Window_Win32* win;
	int found = 0;

	/* First, get Win32 messages and dispatch to winproc. We
	do this immediately, otherwise the OS thinks we've hung. */
	while(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);	
	}

	/* Check for user events */
	if(RemoveFromEQ(&displayTarget->userEventQueue, eventReturn))
		return 1;

	/* Now check each window's event queue */
	win = displayTarget->firstWindow;
	while(win)
	{
		if(RemoveFromEQ(&win->eventQueue, eventReturn))
		{
			found = 1;
			break;
		}

		win = win->next;
	}

	return found;
}