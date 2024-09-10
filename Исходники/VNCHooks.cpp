DllExport BOOL UnSetHooks(DWORD thread_id)
{

	BOOL unHooked = TRUE;
	
	// Remove the extra property value from all local windows
	EnumWindows((WNDENUMPROC) &KillPropsProc, NULL);

	// Stop the keyboard & mouse hooks
	unHooked = unHooked && SetKeyboardFilterHook(FALSE);
	unHooked = unHooked && SetMouseFilterHook(FALSE);

	// Is the window handle valid?
	if (thread_id != vnc_thread_id)
		return FALSE;

	// Unhook the procs
	if (hCallWndHook != NULL)
	{
		unHooked = unHooked && UnhookWindowsHookEx(hCallWndHook);
		hCallWndHook = NULL;
	}

	if (hGetMsgHook != NULL)
	{
		unHooked = unHooked && UnhookWindowsHookEx(hGetMsgHook);
		hGetMsgHook = NULL;
	}

	if (hDialogMsgHook != NULL)
	{
		unHooked = unHooked && UnhookWindowsHookEx(hDialogMsgHook);
		hDialogMsgHook = NULL;
	}

	// If we managed to unhook then reset
	if (unHooked)
	{
		vnc_thread_id = 0;
		HookMaster = FALSE;
	}

	return unHooked;

}