int main( int argc, char *argv[] )
{
	wchar_t server[256];
	AT_ENUM *pBuf, *pJob;
	DWORD i, rc, nRead, nLeftBeforeCall, hResume;
	bool goForIt;

	if ( argc > 2 )
	{
		puts( "usage: nsje [\\\\server]" );
		return 1;
	}


	if ( argc == 2 )
		mbstowcs( server, argv[1], lenof( server ) );
	else
		server[0] = L'\0';

	hResume = 0;
	printf( "%8.8s %.70s\n", "JobId", "Command" );
	printf( "%8.8s %.70s\n", "--------", "----------------------------------------------------------------------" );

	goForIt = true;
	while ( goForIt )
	{
		pBuf = NULL;
		rc = NetScheduleJobEnum( *server == L'\0'? NULL: server, (BYTE **) &pBuf, 8192, &nRead, &nLeftBeforeCall, &hResume );

		if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
		{
			printf( "Doh! rc = %lu\n", rc );
			return 1;
		}

		for ( pJob = pBuf, i = 0; i < nRead; ++ i, ++ pJob )
		{
			printf( "%8lu %.70S\n", pJob->JobId, pJob->Command );
		}

		if ( pBuf != NULL )
			NetApiBufferFree( pBuf );

		if ( rc == ERROR_SUCCESS )
			goForIt = false;
	}

	return 0;
}