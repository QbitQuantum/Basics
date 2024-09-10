ArchHooks_Win32::ArchHooks_Win32()
{
	HOOKS = this;

	/* Disable critical errors, and handle them internally.  We never want the
	 * "drive not ready", etc. dialogs to pop up. */
	SetErrorMode( SetErrorMode(0) | SEM_FAILCRITICALERRORS );

	CrashHandler::CrashHandlerHandleArgs( g_argc, g_argv );
	SetUnhandledExceptionFilter( CrashHandler::ExceptionHandler );

#if _MSC_VER >= 1400 // VC8
	_set_invalid_parameter_handler( InvalidParameterHandler );
#endif

	/* Windows boosts priority on keyboard input, among other things.  Disable that for
	 * the main thread. */
	SetThreadPriorityBoost( GetCurrentThread(), TRUE );

	g_hInstanceMutex = CreateMutex( NULL, TRUE, PRODUCT_ID );

	g_bIsMultipleInstance = false;
	if( GetLastError() == ERROR_ALREADY_EXISTS )
		g_bIsMultipleInstance = true;
}