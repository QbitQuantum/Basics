int
TclpThreadCreate(
    Tcl_ThreadId *idPtr,	/* Return, the ID of the thread. */
    Tcl_ThreadCreateProc *proc,	/* Main() function of the thread. */
    ClientData clientData,	/* The one argument to Main(). */
    int stackSize,		/* Size of stack for the new thread. */
    int flags)			/* Flags controlling behaviour of the new
				 * thread. */
{
    WinThread *winThreadPtr;		/* Per-thread startup info */
    HANDLE tHandle;

    winThreadPtr = (WinThread *)ckalloc(sizeof(WinThread));
    winThreadPtr->lpStartAddress = (LPTHREAD_START_ROUTINE) proc;
    winThreadPtr->lpParameter = clientData;
    winThreadPtr->fpControl = _controlfp(0, 0);

    EnterCriticalSection(&joinLock);

    *idPtr = 0; /* must initialize as Tcl_Thread is a pointer and
                 * on WIN64 sizeof void* != sizeof unsigned
		 */

#if defined(_MSC_VER) || defined(__MSVCRT__) || defined(__BORLANDC__)
    tHandle = (HANDLE) _beginthreadex(NULL, (unsigned) stackSize,
	    (Tcl_ThreadCreateProc*) TclWinThreadStart, winThreadPtr,
	    0, (unsigned *)idPtr);
#else
    tHandle = CreateThread(NULL, (DWORD) stackSize,
	    TclWinThreadStart, winThreadPtr, 0, (LPDWORD)idPtr);
#endif

    if (tHandle == NULL) {
	LeaveCriticalSection(&joinLock);
	return TCL_ERROR;
    } else {
	if (flags & TCL_THREAD_JOINABLE) {
	    TclRememberJoinableThread(*idPtr);
	}

	/*
	 * The only purpose of this is to decrement the reference count so the
	 * OS resources will be reaquired when the thread closes.
	 */

	CloseHandle(tHandle);
	LeaveCriticalSection(&joinLock);
	return TCL_OK;
    }
}