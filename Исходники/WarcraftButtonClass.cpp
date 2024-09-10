	void DumpBtn( const char * filename )
	{
		if ( IsOk( ) && GetBtnAddr( ) > 1000 )
		{
			FILE *fp;
			fopen_s( &fp , filename , "wb" );
			if ( fp )
			{
				unsigned char buffer[ 520 ];
				if ( ReadProcessMemory( GetCurrentProcess( ) , ( void * ) ( GetBtnAddr( ) ) , &buffer , 520 , 0 ) )
				{
					fwrite( buffer , 1 , 520 , fp );
				}
				fclose( fp );
			}
		}
	}