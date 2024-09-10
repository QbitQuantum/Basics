/*
 * private static bool WaitForInputIdle(IntPtr processHandle,
 *										int processID, int milliseconds);
 */
ILBool _IL_Process_WaitForInputIdle(ILExecThread *_thread,
									ILNativeInt processHandle,
									ILInt32 processID,
									ILInt32 milliseconds)
{
#ifdef IL_WIN32_PLATFORM
	return WaitForInputIdle((HANDLE)processHandle, (DWORD)milliseconds);
#else
	/* "Idle" has no meaning on non-Win32 platforms so just pretend
	   that the process is fully initialized and ready to go */
	return 1;
#endif
}