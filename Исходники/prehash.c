// Console, ANSI
VOID my_putsCA( HANDLE h, LPCTSTR s )
{
	DWORD n1, n2;
	DWORD len = 0;
	LPSTR p;

#ifdef UNICODE
	UINT cp = GetConsoleOutputCP();

	if( ( len = WideCharToMultiByte( cp, 0, s, -1, NULL, 0, NULL, NULL ) ) == 0 ) return;
	if( ( p = (LPSTR)LocalAlloc( LMEM_FIXED, len ) ) == NULL ) return;
	len = WideCharToMultiByte( cp, 0, s, -1, p, len, NULL, NULL );
#else
	size_t n;
	p = (LPTSTR)s;
	if( StringCbLength( p, 4096, &n ) != S_OK ) len = 0;
	else len = n;
#endif

	n1 = len ? len -1 : 0;
	while( n1 ){
		if( !WriteFile( h, p, n1, &n2, NULL ) )  break;
		n1 -= n2;
	}
#ifdef UNICODE
	LocalFree( p );
#endif
}