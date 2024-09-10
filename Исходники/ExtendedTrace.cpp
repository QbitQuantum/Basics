// Initializes the symbol files
BOOL InitSymInfo( PCSTR lpszInitialSymbolPath )
{
	CHAR     lpszSymbolPath[BUFFERSIZE];
	DWORD    symOptions = SymGetOptions();

	symOptions |= SYMOPT_LOAD_LINES;
	symOptions &= ~SYMOPT_UNDNAME;
	SymSetOptions( symOptions );
	InitSymbolPath( lpszSymbolPath, lpszInitialSymbolPath );

	return SymInitialize( GetCurrentProcess(), lpszSymbolPath, TRUE);
}