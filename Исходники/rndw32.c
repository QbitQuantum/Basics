static int
gather_random_fast( void (*add)(const void*, size_t, int), int requester )
{
    static int addedFixedItems = 0;

    if ( debug_me )
	log_debug ("rndw32#gather_random_fast: req=%d\n", requester );

    /* Get various basic pieces of system information: Handle of active
     * window, handle of window with mouse capture, handle of clipboard owner
     * handle of start of clpboard viewer list, pseudohandle of current
     * process, current process ID, pseudohandle of current thread, current
     * thread ID, handle of desktop window, handle  of window with keyboard
     * focus, whether system queue has any events, cursor position for last
     * message, 1 ms time for last message, handle of window with clipboard
     * open, handle of process heap, handle of procs window station, types of
     * events in input queue, and milliseconds since Windows was started */
    {	byte buffer[20*sizeof(ulong)], *bufptr;
	bufptr = buffer;
      #define ADD(f)  do { ulong along = (ulong)(f);		      \
			   memcpy (bufptr, &along, sizeof (along) );  \
			   bufptr += sizeof (along); } while (0)
	ADD ( GetActiveWindow ());
	ADD ( GetCapture ());
	ADD ( GetClipboardOwner ());
	ADD ( GetClipboardViewer ());
	ADD ( GetCurrentProcess ());
	ADD ( GetCurrentProcessId ());
	ADD ( GetCurrentThread ());
	ADD ( GetCurrentThreadId ());
	ADD ( GetDesktopWindow ());
	ADD ( GetFocus ());
	ADD ( GetInputState ());
	ADD ( GetMessagePos ());
	ADD ( GetMessageTime ());
	ADD ( GetOpenClipboardWindow ());
	ADD ( GetProcessHeap ());
	ADD ( GetProcessWindowStation ());
	ADD ( GetQueueStatus (QS_ALLEVENTS));
	ADD ( GetTickCount ());

	assert ( bufptr-buffer < sizeof (buffer) );
	(*add) ( buffer, bufptr-buffer, requester );
      #undef ADD
    }

    /* Get multiword system information: Current caret position, current
     * mouse cursor position */
    {	POINT point;
	GetCaretPos (&point);
	(*add) ( &point, sizeof (point), requester );
	GetCursorPos (&point);
	(*add) ( &point, sizeof (point), requester );
    }

    /* Get percent of memory in use, bytes of physical memory, bytes of free
     * physical memory, bytes in paging file, free bytes in paging file, user
     * bytes of address space, and free user bytes */
    {	MEMORYSTATUS memoryStatus;
	memoryStatus.dwLength = sizeof (MEMORYSTATUS);
	GlobalMemoryStatus (&memoryStatus);
	(*add) ( &memoryStatus, sizeof (memoryStatus), requester );
    }

    /* Get thread and process creation time, exit time, time in kernel mode,
       and time in user mode in 100ns intervals */
    {	HANDLE handle;
	FILETIME creationTime, exitTime, kernelTime, userTime;
	DWORD minimumWorkingSetSize, maximumWorkingSetSize;

	handle = GetCurrentThread ();
	GetThreadTimes (handle, &creationTime, &exitTime,
					       &kernelTime, &userTime);
	(*add) ( &creationTime, sizeof (creationTime), requester );
	(*add) ( &exitTime, sizeof (exitTime), requester );
	(*add) ( &kernelTime, sizeof (kernelTime), requester );
	(*add) ( &userTime, sizeof (userTime), requester );

	handle = GetCurrentProcess ();
	GetProcessTimes (handle, &creationTime, &exitTime,
						&kernelTime, &userTime);
	(*add) ( &creationTime, sizeof (creationTime), requester );
	(*add) ( &exitTime, sizeof (exitTime), requester );
	(*add) ( &kernelTime, sizeof (kernelTime), requester );
	(*add) ( &userTime, sizeof (userTime), requester );

	/* Get the minimum and maximum working set size for the current process */
	GetProcessWorkingSetSize (handle, &minimumWorkingSetSize,
					  &maximumWorkingSetSize);
	(*add) ( &minimumWorkingSetSize,
				   sizeof (&minimumWorkingSetSize), requester );
	(*add) ( &maximumWorkingSetSize,
				   sizeof (&maximumWorkingSetSize), requester );
    }


    /* The following are fixed for the lifetime of the process so we only
     * add them once */
    if (!addedFixedItems) {
	STARTUPINFO startupInfo;

	/* Get name of desktop, console window title, new window position and
	 * size, window flags, and handles for stdin, stdout, and stderr */
	startupInfo.cb = sizeof (STARTUPINFO);
	GetStartupInfo (&startupInfo);
	(*add) ( &startupInfo, sizeof (STARTUPINFO), requester );
	addedFixedItems = 1;
    }

    /* The performance of QPC varies depending on the architecture it's
     * running on and on the OS.  Under NT it reads the CPU's 64-bit timestamp
     * counter (at least on a Pentium and newer '486's, it hasn't been tested
     * on anything without a TSC), under Win95 it reads the 1.193180 MHz PIC
     * timer.  There are vague mumblings in the docs that it may fail if the
     * appropriate hardware isn't available (possibly '386's or MIPS machines
     * running NT), but who's going to run NT on a '386? */
    {	LARGE_INTEGER performanceCount;
	if (QueryPerformanceCounter (&performanceCount)) {
	    if ( debug_me )
		log_debug ("rndw32#gather_random_fast: perf data\n");
	    (*add) (&performanceCount, sizeof (&performanceCount), requester);
	}
	else { /* Millisecond accuracy at best... */
	    DWORD aword = GetTickCount ();
	    (*add) (&aword, sizeof (aword), requester );
	}
    }

    return 0;
}