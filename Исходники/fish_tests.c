/**
   Print formatted error string
*/
static void err( wchar_t *blah, ... )
{
	va_list va;
	va_start( va, blah );
	err_count++;
	
	wprintf( L"Error: " );
	vwprintf( blah, va );
	va_end( va );	
	wprintf( L"\n" );
}