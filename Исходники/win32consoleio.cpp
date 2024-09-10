bool SetupWin32ConsoleIO()
{
#if defined( _WIN32 )
	// Only useful on Windows platforms

	bool newConsole( false );

	if ( GetFileType( GetStdHandle( STD_OUTPUT_HANDLE ) ) == FILE_TYPE_UNKNOWN )
	{

		HINSTANCE hInst = ::LoadLibrary( "kernel32.dll" );
		typedef BOOL ( WINAPI * pAttachConsole_t )( DWORD );
		pAttachConsole_t pAttachConsole( ( BOOL ( _stdcall * )( DWORD ) )GetProcAddress( hInst, "AttachConsole" ) );

		if ( !( pAttachConsole && (*pAttachConsole)( ( DWORD ) - 1 ) ) )
		{
			newConsole = true;
			AllocConsole();
		}

		*stdout = *_fdopen( _open_osfhandle( reinterpret_cast< long >( GetStdHandle( STD_OUTPUT_HANDLE ) ), _O_TEXT ), "w" );
		setvbuf( stdout, NULL, _IONBF, 0 );

		*stdin = *_fdopen( _open_osfhandle( reinterpret_cast< long >( GetStdHandle( STD_INPUT_HANDLE ) ), _O_TEXT ), "r" );
		setvbuf( stdin, NULL, _IONBF, 0 );

		*stderr = *_fdopen( _open_osfhandle( reinterpret_cast< long >( GetStdHandle( STD_ERROR_HANDLE ) ), _O_TEXT ), "w" );
		setvbuf( stdout, NULL, _IONBF, 0 );

		std::ios_base::sync_with_stdio();
	}

	return newConsole;

#else // defined( _WIN32 )

	return false;

#endif // defined( _WIN32 )
}