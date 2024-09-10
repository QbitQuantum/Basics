bool Windows::LoadProfile()
{
#ifdef WIN32
	char szPath[MAX_PATH];
	ALLEGRO_PATH* alPath;
	bool res;

	if( al_filename_exists( "c4a-prof" ) )
		return ParseProfileFile( "c4a-prof" );

	if( SHGetFolderPathA( 0, CSIDL_PERSONAL, 0, 0, (char*)&szPath ) == S_OK )
	{
		alPath = al_create_path( (char*)&szPath );
		al_append_path_component( alPath, "c4a-prof" );

		if( al_filename_exists( al_path_cstr( alPath, '/' ) ) )
			res = ParseProfileFile( (char*)al_path_cstr( alPath, '/' ) );

		al_destroy_path( alPath );
		return res;
	}
	return false;

#else
	return false;
#endif
}