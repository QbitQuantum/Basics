int main( int argc, char** argv )
{
	fprintf( stderr, "DLL base address scheduler v.1.2, copyright 2001-2002 (c) George Hazan.\n\n" );

   //----[ Command line parsing ]--------------------------------------------------------

   for ( int i=1; i < argc; i++ )
   {
      if ( argv[ i ][ 0 ] != '/' )
      {
LBL_Usage:
         fprintf( stderr, "Usage: Rebaser.exe [/BASE:<hex_digit>] [/CHECK]\n" );
		   return 200;
      }

      if ( memicmp( &argv[ i ][ 1 ], "BASE:", 5 ) == 0 )
         sscanf( &argv[ i ][ 6 ], "%08X", &glbOffset );
		else if ( memicmp( &argv[ i ][ 1 ], "CHECK", 5 ) == 0 )
		{
			glbCheckMode = true;
			glbOffset = 0x400000;
		}
      else goto LBL_Usage;
   }

   //----[ Command line ok, opening data files ]-----------------------------------------

	fprintf( stdout, "Scanning DLLs...\n" );

	int  locResult = 0;
	char locFileName[ MAX_PATH ];

	while ( fgets( locFileName, sizeof( locFileName ), stdin ) != NULL )
	{
		rtrim( locFileName );
		fprintf( stdout, "Processing '%s'...\n", locFileName );

		//----| If we need to check files only, check them |-------------------------------
		if ( glbCheckMode )
		{
			DWORD locOldImageSize, locOldBase, locNewSize, locNewBase;
			if ( !ReBaseImage( locFileName, NULL, FALSE, FALSE, FALSE, FALSE, &locOldImageSize,
																&locOldBase, &locNewSize, &locNewBase, 0 ))
				PrintWin32Error( GetLastError() );

			if ( locOldBase == glbOffset )
			{
				fprintf( stdout, "Image is not based\n\n" );
				locResult = 2;
			}

			continue;
		}

		//----| Preparing files |----------------------------------------------------------
LBL_Ok:
		HANDLE locFileHandle = CreateFile( locFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
		if ( locFileHandle == INVALID_HANDLE_VALUE )
		{
			fprintf( stdout, "File '%s' cannot be opened, skipped.\n\n", locFileName );
			locResult = 2;
			continue;
		}

		FILETIME locCreateTime, locAccessTime, locModifyTime;
		GetFileTime( locFileHandle, &locCreateTime, &locAccessTime, &locModifyTime );
		CloseHandle( locFileHandle );

		//----| Processing |---------------------------------------------------------------

		DWORD locOldImageSize, locOldBase, locNewSize;
		if ( !ReBaseImage( locFileName, NULL, TRUE, FALSE, FALSE, FALSE, &locOldImageSize,
															&locOldBase, &locNewSize, &glbOffset, 0 ))
		{
			PrintWin32Error( GetLastError() );
			locResult = 2;
		}

		glbOffset += locNewSize;

		//----| Write down the original file timestamp |-----------------------------------

		locFileHandle = CreateFile( locFileName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
		if ( locFileHandle != INVALID_HANDLE_VALUE )
		{
			SetFileTime( locFileHandle, &locCreateTime, &locAccessTime, &locModifyTime );
			CloseHandle( locFileHandle );
	}	}

   return locResult;
}