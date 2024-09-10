int debugPrintf( const char *format, ... )
	{
	va_list argPtr;
	char buffer[ 1024 ];
	int length;

	va_start( argPtr, format );

#if VC_GE_2005( _MSC_VER )
	length = vsnprintf_s( buffer, 1024, _TRUNCATE, format, argPtr );
#else
	length = vsprintf( buffer, format, argPtr );
#endif /* VC++ 2005 or newer */
	va_end( argPtr );
	OutputDebugString( buffer );

	return( length );
	}