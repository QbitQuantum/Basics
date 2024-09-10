/*
================
rvDebuggerServer::Break

Halt execution of the game threads and inform the debugger client that
the game has been halted
================
*/
void rvDebuggerServer::Break ( idInterpreter* interpreter, idProgram* program, int instructionPointer )
{
	msg_t				msg;
	byte				buffer[MAX_MSGLEN];
	const statement_t*	st;
	const char*			filename;

	// Clear all the break types
	mBreakStepOver = false;
	mBreakStepInto = false;
	mBreakNext     = false;
	
	// Grab the current statement and the filename that it came from
	st       = &program->GetStatement ( instructionPointer );
	filename = program->GetFilename ( st->file );

	idStr qpath;
	OSPathToRelativePath(filename, qpath);	
	qpath.BackSlashesToSlashes ( );

	// Give the mouse cursor back to the world
	Sys_GrabMouseCursor( false );	
	
	// Set the break variable so we know the main thread is stopped
	mBreak = true;
	mBreakProgram = program;
	mBreakInterpreter = interpreter;
	mBreakInstructionPointer = instructionPointer;
	
	// Inform the debugger of the breakpoint hit
	MSG_Init( &msg, buffer, sizeof( buffer ) );
	MSG_WriteShort ( &msg, (int)DBMSG_BREAK );
	MSG_WriteLong ( &msg, st->linenumber );
	MSG_WriteString ( &msg, qpath );
	SendPacket ( msg.data, msg.cursize );
		
	// Suspend the game thread.  Since this will be called from within the main game thread
	// execution wont return until after the thread is resumed
	SuspendThread ( mGameThread );						
	
	// Let the debugger client know that we have started back up again
	SendMessage ( DBMSG_RESUMED );

	// This is to give some time between the keypress that 
	// told us to resume and the setforeground window.  Otherwise the quake window
	// would just flash
	Sleep ( 150 );

	// Bring the window back to the foreground	
	SetForegroundWindow ( win32.hWnd );
	SetActiveWindow ( win32.hWnd );
	UpdateWindow ( win32.hWnd );
	SetFocus ( win32.hWnd );	
	
	// Give the mouse cursor back to the game
	Sys_GrabMouseCursor( true );	
	
	// Clear all commands that were generated before we went into suspended mode.  This is
	// to ensure we dont have mouse downs with no ups because the context was changed.
	idKeyInput::ClearStates();
}