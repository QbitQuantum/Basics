void fastPoll( void )
	{
	static BOOLEAN addedFixedItems = FALSE, hasHardwareRNG = FALSE;
	static CEGENRANDOM pCeGenRandom = NULL;
	static GETSYSTEMPOWERSTATUS pGetSystemPowerStatusEx2 = NULL;
	FILETIME  creationTime, exitTime, kernelTime, userTime;
	LARGE_INTEGER performanceCount;
	SYSTEM_POWER_STATUS_EX2 powerStatus;
	MEMORYSTATUS memoryStatus;
	HANDLE handle;
	POINT point;
	RANDOM_STATE randomState;
	BYTE buffer[ RANDOM_BUFSIZE ];
	int length;

	if( krnlIsExiting() )
		return;

	/* Initialize the native function pointers if necessary.  CeGetRandom()
	   is only available in relatively new versions of WinCE, so we have to
	   link it dynamically */
	if( pCeGenRandom == NULL )
		{
		HANDLE hCoreDLL;

		if( ( hCoreDLL = GetModuleHandle( TEXT( "Coredll.dll" ) ) ) != NULL )
			pCeGenRandom = ( CEGENRANDOM ) GetProcAddress( hCoreDLL, TEXT( "CeGenRandom" ) );
		}
	if( pGetSystemPowerStatusEx2 == NULL )
		{
		HANDLE hGetpower;

		if( ( hGetpower = GetModuleHandle( TEXT( "Getpower.dll" ) ) ) != NULL )
			pGetSystemPowerStatusEx2 = ( GETSYSTEMPOWERSTATUS ) \
							GetProcAddress( hGetpower, TEXT( "GetSystemPowerStatusEx2" ) );
		}

	initRandomData( randomState, buffer, RANDOM_BUFSIZE );

	/* Get various basic pieces of system information: Handle of active
	   window, handle of window with mouse capture, handle of clipboard owner
	   handle of start of clpboard viewer list, pseudohandle of current
	   process, current process ID, pseudohandle of current thread, current
	   thread ID, handle of desktop window, handle  of window with keyboard
	   focus, whether system queue has any events, cursor position for last
	   message, 1 ms time for last message, handle of window with clipboard
	   open, handle of process heap, handle of procs window station, types of
	   events in input queue, and milliseconds since Windows was started */
	addRandomValue( randomState, GetActiveWindow() );
	addRandomValue( randomState, GetCapture() );
	addRandomValue( randomState, GetCaretBlinkTime() );
	addRandomValue( randomState, GetClipboardOwner() );
	addRandomValue( randomState, GetCurrentProcess() );
	addRandomValue( randomState, GetCurrentProcessId() );
	addRandomValue( randomState, GetCurrentThread() );
	addRandomValue( randomState, GetCurrentThreadId() );
	addRandomValue( randomState, GetDesktopWindow() );
	addRandomValue( randomState, GetDC( NULL ) );
	addRandomValue( randomState, GetDoubleClickTime() );
	addRandomValue( randomState, GetFocus() );
	addRandomValue( randomState, GetForegroundWindow() );
	addRandomValue( randomState, GetMessagePos() );
	addRandomValue( randomState, GetOpenClipboardWindow() );
	addRandomValue( randomState, GetProcessHeap() );
	addRandomValue( randomState, GetQueueStatus( QS_ALLINPUT ) );
	addRandomValue( randomState, GetTickCount() );
	if( krnlIsExiting() )
		return;

	/* Get multiword system information: Current caret position, current
	   mouse cursor position */
	GetCaretPos( &point );
	addRandomData( randomState, &point, sizeof( POINT ) );
	GetCursorPos( &point );
	addRandomData( randomState, &point, sizeof( POINT ) );

	/* Get percent of memory in use, bytes of physical memory, bytes of free
	   physical memory, bytes in paging file, free bytes in paging file, user
	   bytes of address space, and free user bytes */
	memoryStatus.dwLength = sizeof( MEMORYSTATUS );
	GlobalMemoryStatus( &memoryStatus );
	addRandomData( randomState, &memoryStatus, sizeof( MEMORYSTATUS ) );

	/* Get thread and process creation time, exit time, time in kernel mode,
	   and time in user mode in 100ns intervals */
	handle = GetCurrentThread();
	GetThreadTimes( handle, &creationTime, &exitTime, &kernelTime, &userTime );
	addRandomData( randomState, &creationTime, sizeof( FILETIME ) );
	addRandomData( randomState, &exitTime, sizeof( FILETIME ) );
	addRandomData( randomState, &kernelTime, sizeof( FILETIME ) );
	addRandomData( randomState, &userTime, sizeof( FILETIME ) );

	/* Get extended battery/power status information.  We set the fUpdate
	   flag to force a re-read of fresh data rather than a re-use of cached
	   information */
	if( pGetSystemPowerStatusEx2 != NULL && \
		( length = \
				pGetSystemPowerStatusEx2( &powerStatus,
										  sizeof( SYSTEM_POWER_STATUS_EX2 ),
										  TRUE ) ) > 0 )
		addRandomData( randomState, &powerStatus, length );

	/* Get random data provided by the OS.  Since this is expected to be
	   provided by the system vendor, it's quite likely to be the usual
	   process ID + time */
	if( pCeGenRandom != NULL )
		{
		BYTE randomBuffer[ 32 ];

		if( pCeGenRandom( 32, randomBuffer ) )
			addRandomData( randomState, randomBuffer, 32 );
		}

	/* The following are fixed for the lifetime of the process so we only
	   add them once */
	if( !addedFixedItems )
		{
		SYSTEM_INFO systemInfo;

		GetSystemInfo( &systemInfo );
		addRandomData( randomState, &systemInfo, sizeof( SYSTEM_INFO ) );
		addedFixedItems = TRUE;
		}

	/* The performance of QPC varies depending on the architecture it's
	   running on, and is completely platform-dependant.  If there's no
	   hardware performance counter available, it uses the 1ms system timer,
	   although usually there's some form of hardware timer available.
	   Since there may be no correlation, or only a weak correlation,
	   between the performance counter and the system clock, we get the
	   time from both sources */
	if( QueryPerformanceCounter( &performanceCount ) )
		addRandomData( randomState, &performanceCount,
					   sizeof( LARGE_INTEGER ) );
	addRandomValue( randomState, GetTickCount() );

	/* Flush any remaining data through.  Quality = int( 33 1/3 % ) */
	endRandomData( randomState, 34 );
	}