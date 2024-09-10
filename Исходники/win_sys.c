void Sys_Quit( void )
{
	timeEndPeriod( 1 );

	SV_Shutdown( "Server quit\n" );
	CL_Shutdown();

	if( dedicated && dedicated->integer )
		FreeConsole();

	// shut down QHOST hooks if necessary
	DeinitConProc();

	Qcommon_Shutdown();

	exit( 0 );
}