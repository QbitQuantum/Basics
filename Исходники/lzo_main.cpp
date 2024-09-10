void pause_cmdline( int argc, char **argv )
{
	char lzo_file[MAX_PATH];
	char files[MAX_PATH];
	bool brecurse;
	bool bpath;

	if( argc == 1 )
	{
		show_help();
	}
	else if( argc == 2 )
	{
		if( strcmp( argv[1], "-h" ) == 0 || strcmp( argv[1], "-help" ) == 0 )
		{
			show_help();
		}
	}
	else if( argc == 3 )
	{
		if( strcmp( argv[1], "-l" ) == 0 )
		{
			/// display the file info in the archive
			get_archive_info( argv[2] );
		}
		else if( strcmp( argv[1], "-d" ) == 0 )
		{
			/// decompress files in the current directory
			decompress( argv[2], "./" );
		}
		else
		{
			/// normal compress files
			strncpy( files, argv[1], MAX_PATH );
			strncpy( lzo_file, argv[2], MAX_PATH );
			compress( lzo_file, files, false, false );
		}
	}
	else if( argc == 4 )
	{
		if( strcmp( argv[1], "-d" ) == 0 )
		{
			/// decompress files in the specified directory
			decompress( argv[2], argv[3] );
		}
		else if( strcmp( argv[1], "-vcprj" ) == 0 )
		{
			/// compress vcprj file
			compress_vcproj( argv[3], argv[2] );
		}
		else if( strcmp( argv[1], "-sln" ) == 0 )
		{
			/// compress solution file
			compress_sln( argv[3], argv[2] );
		}
		else
		{
			/// compress files
			char cmd[64];
			strncpy( cmd, argv[1], 63 );
		
			bpath = strcmp( cmd, "-p" ) == 0 ? true : false;
			brecurse = strcmp( cmd, "-r" ) == 0 ? true : false;
			if( strcmp( cmd, "-rp" ) == 0 || strcmp( cmd, "-pr" ) == 0 )
			{
				bpath = brecurse = true;
			}

			strncpy( files, argv[2], MAX_PATH );
			strncpy( lzo_file, argv[3], MAX_PATH );

			compress( lzo_file, files, bpath, brecurse );
		}
	}
}