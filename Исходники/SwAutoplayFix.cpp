void FixAutoplay( LPCWSTR wszApplicationName, LPCWSTR wszCommandLine, LPCWSTR wszCurrentDirectory )
{
	LPCWSTR uppApplicationName = _wcsupr( _wcsdup( wszApplicationName ) );

	// only UT2004
	if( wcsstr(uppApplicationName,L"UT2004.EXE") == NULL )
		return;

	// read mod name from commandline, must be specified
	LPCWSTR uppCommandLine = _wcsupr( _wcsdup( wszCommandLine ) );
	LPWSTR pb = wcsstr(uppCommandLine,L"-MOD=");
	if( pb == NULL )
		return;
	
	// mod name must be valid
	LPWSTR ps = pb + wcslen(L"-MOD=");
	LPWSTR token = wcstok( ps, L" " );
	if( token == NULL )
		return;

	// mod directory must be valid
	if( !SetCurrentDirectoryW(wszCurrentDirectory)
	||	!SetCurrentDirectoryW(L"..")
	||	!SetCurrentDirectoryW(token) )
		return;

	// copy Autoplay.ut2
	if( !CopyFileW( L"..\\Maps\\Autoplay.ut2", L"Maps\\Autoplay.ut2", FALSE ) )
		return;

	//MessageBox( NULL, TEXT("Copy OK"), TEXT("SwAutoplayFix"), MB_OK );
}