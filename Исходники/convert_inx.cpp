const char* ConvertInx::GetName( const char* FullPath )
{
	static char Name[ 512 ] = { 0 };
	StringCbCopyA( Name, 512, FullPath );

	for( int i = sizeof( Name ); i >= 0; i-- )
	{
		if( Name[ i ] == '.' )
		{
			SecureZeroMemory( &Name[ i ], sizeof( Name ) - i );
			break;
		};
	};

	return Name;
};