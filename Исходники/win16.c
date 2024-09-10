void fastPoll( void )
	{
	RANDOM_STATE randomState;
	BYTE buffer[ RANDOM_BUFSIZE ];
	SYSHEAPINFO sysHeapInfo;
	MEMMANINFO memManInfo;
	TIMERINFO timerInfo;
	POINT point;

	initRandomData( randomState, buffer, RANDOM_BUFSIZE );

	/* Get various basic pieces of system information: Handle of the window
	   with mouse capture, handle of window with input focus, amount of
	   space in global heap, whether system queue has any events, cursor
	   position for last message, 55 ms time for last message, number of
	   active tasks, 55 ms time since Windows started, current mouse cursor
	   position, current caret position */
	addRandomValue( randomState, GetCapture() );
	addRandomValue( randomState, GetFocus() );
	addRandomValue( randomState, GetFreeSpace( 0 ) );
	addRandomValue( randomState, GetInputState() );
	addRandomValue( randomState, GetMessagePos() );
	addRandomValue( randomState, GetMessageTime() );
	addRandomValue( randomState, GetNumTasks() );
	addRandomValue( randomState, GetTickCount() );
	GetCursorPos( &point );
	addRandomData( randomState, &point, sizeof( POINT ) );
	GetCaretPos( &point );
	addRandomData( randomState, &point, sizeof( POINT ) );

	/* Get the largest free memory block, number of lockable pages, number of
	   unlocked pages, number of free and used pages, and number of swapped
	   pages */
	memManInfo.dwSize = sizeof( MEMMANINFO );
	MemManInfo( &memManInfo );
	addRandomData( randomState, &memManInfo, sizeof( MEMMANINFO ) );

	/* Get the execution times of the current task and VM to approximately
	   1ms resolution */
	timerInfo.dwSize = sizeof( TIMERINFO );
	TimerCount( &timerInfo );
	addRandomData( randomState, &timerInfo, sizeof( TIMERINFO ) );

	/* Get the percentage free and segment of the user and GDI heap */
	sysHeapInfo.dwSize = sizeof( SYSHEAPINFO );
	SystemHeapInfo( &sysHeapInfo );
	addRandomData( randomState, &sysHeapInfo, sizeof( SYSHEAPINFO ) );

	/* Flush any remaining data through */
	endRandomData( randomState, 25 );
	}