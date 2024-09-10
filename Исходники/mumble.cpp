void CMumbleSystem::LevelInitPostEntity()
{
	if ( g_pMumbleMemory )
		return;

#if defined( WIN32 ) && !defined( _X360 )
	g_hMapObject = OpenFileMappingW( FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink" );
	if ( g_hMapObject == NULL )
		return;

	g_pMumbleMemory = (MumbleSharedMemory_t *) MapViewOfFile( g_hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MumbleSharedMemory_t) );
	if ( g_pMumbleMemory == NULL )
	{
		CloseHandle( g_hMapObject );
		g_hMapObject = NULL;
		return;
	}
#elif defined( POSIX )
	char memname[256];
	V_sprintf_safe( memname, "/MumbleLink.%d", getuid() );

	int shmfd = shm_open( memname, O_RDWR, S_IRUSR | S_IWUSR );

	if ( shmfd < 0 )
	{
		return;
	}

	g_pMumbleMemory = (MumbleSharedMemory_t *)( mmap( NULL, sizeof(struct MumbleSharedMemory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd,0 ) );

	if ( g_pMumbleMemory == (void *)(-1) )
	{
		g_pMumbleMemory = NULL;
		return;
	}
#endif
}