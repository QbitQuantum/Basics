int mumble_link( const char *name )
{
#ifdef WIN32

	if ( lm )
	{
		return 0;
	}

	hMapObject = OpenFileMappingW( FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink" );

	if ( hMapObject == NULL )
	{
		return -1;
	}

	lm = ( LinkedMem * ) MapViewOfFile( hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof( LinkedMem ) );

	if ( lm == NULL )
	{
		CloseHandle( hMapObject );
		hMapObject = NULL;
		return -1;
	}

#else
	char file[ 256 ];
	int  shmfd;

	if ( lm )
	{
		return 0;
	}

	snprintf( file, sizeof( file ), "/MumbleLink.%d", getuid() );
	shmfd = shm_open( file, O_RDWR, S_IRUSR | S_IWUSR );

	if ( shmfd < 0 )
	{
		return -1;
	}

	lm = ( LinkedMem * )( mmap( NULL, sizeof( LinkedMem ), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0 ) );

	if ( lm == ( void * )( -1 ) )
	{
		lm = NULL;
		close( shmfd );
		return -1;
	}

	close( shmfd );
#endif
	memset( lm, 0, sizeof( LinkedMem ) );
	mbstowcs( lm->name, name, sizeof( lm->name ) );

	return 0;
}