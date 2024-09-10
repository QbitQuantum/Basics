/*static*/ SimpleString SimpleString::PrintF( const char* FormatString, ... )
{
	va_list Args;
	va_start( Args, FormatString );

	int Length = VSPRINTF_COUNT( FormatString, Args ) + 1;
	char* pBuffer = Allocate( Length );
	VSPRINTF( pBuffer, Length, FormatString, Args );

	SimpleString RetVal( pBuffer );
	SafeDeleteArray( pBuffer );

	return RetVal;
}