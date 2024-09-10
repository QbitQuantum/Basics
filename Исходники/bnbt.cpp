// The main programme
int main( int argc, char *argv[] )
{
	printf( "%s\n", XBNBT_VER.c_str( ) );

#ifdef WIN32
	if( argv[0] )
	{
		char *szEndPos = strrchr( argv[0], CHAR_BS );

		if( szEndPos )
		{
			char *szEXEPath = new char[szEndPos - argv[0] + 1];
			memcpy( szEXEPath, argv[0], szEndPos - argv[0] );
			szEXEPath[szEndPos - argv[0]] = TERM_CHAR;

			SetCurrentDirectory( szEXEPath );

			delete [] szEXEPath;
		}
	}

	if( argc > 1 )
	{
		// The Trinity Edition 7.5r3 - Addition Begins
		// Added for Custom NT Service Name Code
		CFG_Open( CFG_FILE );
#define BNBT_SERVICE_NAME const_cast<LPSTR> (CFG_GetString( "cbtt_service_name", "BNBT Service" ).c_str())
		CFG_Close( CFG_FILE );

		printf( "Service name %s\n", string( BNBT_SERVICE_NAME ).c_str( ) );

		// install service
		if( _stricmp( argv[1], "-i" ) == 0 )
		{
			if( UTIL_NTServiceTest( ) )
				printf( "BNBT Service is already installed!\n" );
			else
			{
				if( UTIL_NTServiceInstall( ) )
					printf( "BNBT Service installed.\n" );
				else
					printf( "BNBT Service failed to install (error %d).\n", GetLastError( ) );
			}

			return 0;
		}
		// uninstall service
		else if( _stricmp( argv[1], "-u" ) == 0 )
		{
			if( !UTIL_NTServiceTest( ) )
				printf( "BNBT Service is not installed!\n" );
			else
			{
				if( UTIL_NTServiceUninstall( ) )
					printf( "BNBT Service uninstalled.\n" );
				else
					printf( "BNBT Service failed to uninstall (error %d).\n", GetLastError( ) );
			}

			return 0;
		}
		// start
		else if( _stricmp( argv[1], "-start" ) == 0 )
		{
			if( !UTIL_NTServiceTest( ) )
				printf( "BNBT Service is not installed!\n" );
			else
			{
				printf( "Starting BNBT Service.\n" );

				if( !UTIL_NTServiceStart( ) )
					printf( "BNBT Service failed to start (error %d).\n", GetLastError( ) );
			}

			return 0;
		}
		// stop
		else if( _stricmp( argv[1], "-stop" ) == 0 )
		{
			if( !UTIL_NTServiceTest( ) )
				printf( "BNBT Service is not installed!\n" );
			else
			{
				printf( "Stopping BNBT Service.\n" );

				if( !UTIL_NTServiceStop( ) )
					printf( "BNBT Service failed to stop (error %d).\n", GetLastError( ) );
			}

			return 0;
		}
		// internal start
		else if( _stricmp( argv[1], "-s" ) == 0 )
		{
			SERVICE_TABLE_ENTRY st[] = { { BNBT_SERVICE_NAME, NTServiceMain }, { 0, 0 }	};

			StartServiceCtrlDispatcher( st );

			return 0;
		}
		// Print version information
		else if( _stricmp( argv[1], "-v" ) == 0 )
		{
			printf( "%s\n", XBNBT_VER.c_str( ) );

			return 0;
		}
		// Print help
		else if( ( _stricmp( argv[1], "-h" ) || _stricmp( argv[1], "-?" ) ) == 0 )
		{
			printf("usage: bnbt [-i] [-u] [-start] [-stop] [-s] [-v] [-?|-h]\n" );
			printf("Options:\n" );
			printf("-?, -h          : This help\n" );
			printf("-i              : Install NT Service\n" );
			printf("-u              : Unstall NT Service\n" );
			printf("-start          : Start NT Service\n" );
			printf("-stop           : Stop NT Service\n" );
			printf("-s              : Internal start NT Service\n" );
			printf("-v              : Show version\n" );

			return 0;
		}
	}
#else
	// read command-line arguments
    //char *example = 0;
    for ( int arg = 0; arg < argc; arg++ )
	{
        if ( strcmp( argv[arg], "-v" ) == 0 || strcmp( argv[arg], "-version" ) == 0 )
		{
			printf( "%s\n", XBNBT_VER.c_str( ) );
			return 0;
        }
        //if (0 == strcmp(argv[arg], "-example")) {
        //    if (arg+1 < argc) example = argv[arg+1];
        //}
        if ( strcmp( argv[arg], "-help" ) == 0 || strcmp( argv[arg], "-?" ) == 0 || strcmp( argv[arg], "-h" ) == 0 )
		{
            fprintf( stderr, "usage:  %s [-v|-version] [-?|-h|-help]\n", argv[0] );
            return 0;
        }
    }
#endif

	printf( "Setting signals ... " );

#if defined ( SIGPIPE )
	// disable SIGPIPE since some systems like OS X don't define MSG_NOSIGNAL
	signal( SIGPIPE, SIG_IGN );
#endif

	// catch SIGABRT, SIGINT,  SIGTERM and SIGHUP
	signal( SIGABRT, sigCatcher );
	signal( SIGINT, sigCatcher );
	signal( SIGTERM, sigCatcher );
#if defined ( SIGHUP )
	signal( SIGHUP, sigCatcher );
#endif

	printf( "Done\n" );
	return bnbtmain( );
}