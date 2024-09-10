  unsigned __stdcall envelopeDataThread( void *arg )
#endif /* Different threading models */
	{
	static const char *envData = "qwertyuiopasdfghjklzxcvbnm";
	BYTE fileBuffer[ BUFFER_SIZE ];
	const unsigned uThread = ( unsigned ) arg;
	const time_t startTime = time( NULL );
	int count, status;

	printf( "Thread %d started.\n", uThread );
	fflush( stdout );

	filenameFromTemplate( fileBuffer, CERT_FILE_TEMPLATE, 13 );

	for( count = 0; count < 150; count++ )
		{
		CRYPT_ENVELOPE cryptEnvelope;
		CRYPT_CERTIFICATE cryptCert;
		BYTE envBuffer[ BUFFER_SIZE ];
		int bytesCopied;

		/* Create the cert and envelope and add the cert to the envelope */
		status = importCertFile( &cryptCert, fileBuffer );
		if( cryptStatusOK( status ) )
			status = cryptCreateEnvelope( &cryptEnvelope, CRYPT_UNUSED,
										  CRYPT_FORMAT_CRYPTLIB );
		if( cryptStatusOK( status ) )
			status = cryptSetAttribute( cryptEnvelope,
										CRYPT_ENVINFO_PUBLICKEY, cryptCert );
		if( cryptStatusError( status ) )
			break;

		/* Envelope data and destroy the envelope */
		status = cryptPushData( cryptEnvelope, envData, strlen( envData ),
								&bytesCopied );
		if( cryptStatusOK( status ) )
			status = cryptPushData( cryptEnvelope, NULL, 0, NULL );
		if( cryptStatusOK( status ) )
			status = cryptPopData( cryptEnvelope, envBuffer, BUFFER_SIZE,
									&bytesCopied );
		if( cryptStatusOK( status ) )
			status = cryptDestroyEnvelope( cryptEnvelope );
		if( cryptStatusError( status ) )
			break;
		printf( "%c", uThread + '0' );
		}

	printf( "Thread %u exited after %d seconds.\n", uThread,
			time( NULL ) - startTime );
	fflush( stdout );
#ifdef UNIX_THREADS
	pthread_exit( NULL );
#else
	_endthreadex( 0 );
#endif /* Different threading models */
	return( 0 );
	}