/* This is no longer actually implemented by throwing an exception, but it acts
 * the same way to code in practice. */
void RageException::Throw( const char *sFmt, ... )
{
	va_list	va;
	va_start( va, sFmt );
	RString error = vssprintf( sFmt, va );
	va_end( va );

	RString msg = ssprintf(
		"\n"
		"//////////////////////////////////////////////////////\n"
		"Exception: %s\n"
		"//////////////////////////////////////////////////////\n",
		error.c_str() );
	if( LOG )
	{
		LOG->Trace( "%s", msg.c_str() );
		LOG->Flush();
	}
	else
	{
		puts( msg );
		fflush( stdout );
	}

#if (defined(WINDOWS) && defined(DEBUG)) || defined(_XDBG) || defined(MACOSX)
	if( IsDebuggerPresent() )
		DebugBreak();
#endif

	ASSERT_M( g_HandlerThreadID == RageThread::GetInvalidThreadID() || g_HandlerThreadID == RageThread::GetCurrentThreadID(),
		  ssprintf("RageException::Throw() on another thread: %s", error.c_str()) );
	if( g_CleanupHandler != NULL )
		g_CleanupHandler( error );

	exit(1);
}