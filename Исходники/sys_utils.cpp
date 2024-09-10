//-----------------------------------------------------------------------------
//	Sys_Error
//
//-----------------------------------------------------------------------------
void Sys_Error( const char* format, ... )
{
	va_list		argptr;
	char		msg[MAX_SYSPRINTMSG];
		
	va_start( argptr,format );
	vsprintf_s( msg, sizeof( msg ), format, argptr );
	va_end( argptr );

	exit( 1 );
}