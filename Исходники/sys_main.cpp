/*
=================
Sys_Error
=================
*/
void Sys_Error( const char *error, ... ) {
	va_list argptr;
	char    string[4096];
#if defined (_WIN32) && !defined (_DEBUG)
	MSG		msg;
#endif

	va_start (argptr,error);
	idStr::vsnPrintf (string, sizeof(string), error, argptr);
	va_end (argptr);

#if defined (_WIN32) && !defined (_DEBUG)
	Conbuf_AppendText( string );
	Conbuf_AppendText( "\n" );
#else
	// Print text in the console window/box
	Sys_Print( string );
	Sys_Print( "\n" );
#endif

#if defined (_WIN32) && !defined (_DEBUG)
	Sys_SetErrorText( string );
	Sys_ShowConsole( 1, qtrue );

	timeEndPeriod( 1 );

	IN_Shutdown();

	// wait for the user to quit
	while ( 1 ) {
		if ( !GetMessage( &msg, NULL, 0, 0 ) ) {
			Com_Quit_f();
		}
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	Sys_DestroyConsole();
#endif

	CL_Shutdown( );
	Sys_ErrorDialog( string );

	Sys_Exit( 1 );
}