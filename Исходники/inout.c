void Sys_Printf( const char *format, ... )
{
	char out_buffer[4096];
	va_list argptr;

	/* catch current stage */
	if( !strncmp( format, "--- ", 4) )
	{
		strncpy( currentStage, format + 4, sizeof(currentStage) - 1 );
		char *p = strstr( currentStage, " ---" );
		if( p != NULL )
			p[ 0 ] = 0;
	}

	/* print */
	va_start( argptr, format );
	vsprintf( out_buffer, format, argptr );
	va_end( argptr );

	/* send */
	FPrintf( SYS_STD, out_buffer );
}