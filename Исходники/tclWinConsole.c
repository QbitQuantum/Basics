static DWORD WINAPI
ConsoleReaderThread(LPVOID arg)
{
    ConsoleInfo *infoPtr = (ConsoleInfo *)arg;
    HANDLE *handle = infoPtr->handle;
    DWORD count, waitResult;
    HANDLE wEvents[2];

    /* The first event takes precedence. */
    wEvents[0] = infoPtr->stopReader;
    wEvents[1] = infoPtr->startReader;

    for (;;) {
	/*
	 * Wait for the main thread to signal before attempting to wait.
	 */

	waitResult = WaitForMultipleObjects(2, wEvents, FALSE, INFINITE);

	if (waitResult != (WAIT_OBJECT_0 + 1)) {
	    /*
	     * The start event was not signaled.  It must be the stop event
	     * or an error, so exit this thread.
	     */

	    break;
	}

	count = 0;

	/* 
	 * Look for data on the console, but first ignore any events
	 * that are not KEY_EVENTs 
	 */
	if (ReadConsoleA(handle, infoPtr->buffer, CONSOLE_BUFFER_SIZE,
		(LPDWORD) &infoPtr->bytesRead, NULL) != FALSE) {
	    /*
	     * Data was stored in the buffer.
	     */
	    
	    infoPtr->readFlags |= CONSOLE_BUFFERED;
	} else {
	    DWORD err;
	    err = GetLastError();
	    
	    if (err == EOF) {
		infoPtr->readFlags = CONSOLE_EOF;
	    }
	}

	/*
	 * Signal the main thread by signalling the readable event and
	 * then waking up the notifier thread.
	 */

	SetEvent(infoPtr->readable);

	/*
	 * Alert the foreground thread.  Note that we need to treat this like
	 * a critical section so the foreground thread does not terminate
	 * this thread while we are holding a mutex in the notifier code.
	 */

	Tcl_MutexLock(&consoleMutex);
	Tcl_ThreadAlert(infoPtr->threadId);
	Tcl_MutexUnlock(&consoleMutex);
    }

    return 0;
}