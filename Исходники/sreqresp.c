static int testTSP( const CRYPT_SESSION cryptSession,
					const BOOLEAN isServer,
					const BOOLEAN isRecycledConnection,
					const BOOLEAN useAltHash,
					const BOOLEAN localSession )
	{
	int status;

	/* If we're the client, wait for the server to finish initialising */
	if( localSession && !isServer && waitMutex() == CRYPT_ERROR_TIMEOUT )
		{
		printf( "Timed out waiting for server to initialise, line %d.\n", 
				__LINE__ );
		return( FALSE );
		}

	/* If we're the client, create a message imprint to timestamp */
	if( !isServer )
		{
		CRYPT_CONTEXT hashContext;

		/* Create the hash value to add to the TSP request */
		status = cryptCreateContext( &hashContext, CRYPT_UNUSED, 
									 useAltHash ? CRYPT_ALGO_SHA256 : \
												  CRYPT_ALGO_SHA1 );
		if( cryptStatusError( status ) )
			return( FALSE );
		cryptEncrypt( hashContext, "12345678", 8 );
		cryptEncrypt( hashContext, "", 0 );
		if( isRecycledConnection )
			{
			/* If we're moving further data over an existing connection, 
			   delete the message imprint from the previous run */
			status = cryptDeleteAttribute( cryptSession,
										   CRYPT_SESSINFO_TSP_MSGIMPRINT );
			if( cryptStatusError( status ) )
				{
				printf( "cryptDeleteAttribute() failed with error code %d, "
						"line %d.\n", status, __LINE__ );
				return( FALSE );
				}
			}
		status = cryptSetAttribute( cryptSession,
									CRYPT_SESSINFO_TSP_MSGIMPRINT,
									hashContext );
		if( cryptStatusError( status ) )
			{
			printf( "cryptSetAttribute() failed with error code %d, line "
					"%d.\n", status, __LINE__ );
			return( FALSE );
			}
		cryptDestroyContext( hashContext );

		/* If it's a local session, wait for the server to finish 
		   initialising */
		if( localSession && waitMutex() == CRYPT_ERROR_TIMEOUT )
			{
			printf( "Timed out waiting for server to initialise, line %d.\n",
					__LINE__ );
			return( FALSE );
			}		
		}
	else
		{
		/* We're the server, if this is the first connect tell the client 
		   that we're ready to go */
		if( localSession && !isRecycledConnection )
			releaseMutex();
		}

	/* Activate the session and timestamp the message */
#if TSP_SERVER_NO == 11
	cryptSetAttribute( cryptSession, CRYPT_OPTION_NET_READTIMEOUT, 30 );
#endif /* Very slow TSP */
	status = cryptSetAttribute( cryptSession, CRYPT_SESSINFO_ACTIVE, TRUE );
	if( isServer )
		printConnectInfo( cryptSession );
	if( cryptStatusError( status ) )
		{
		printExtError( cryptSession, isServer ? \
					   "SVR: Attempt to activate TSP server session" : \
					   "Attempt to activate TSP client session", status,
					   __LINE__ );
		if( !isServer && isServerDown( cryptSession, status ) )
			{
			puts( "  (Server could be down, faking it and continuing...)\n" );
			cryptDestroySession( cryptSession );
			return( CRYPT_ERROR_FAILED );
			}
		cryptDestroySession( cryptSession );
		return( FALSE );
		}

	/* There's not much more we can do in the client at this point since the 
	   TSP data is only used internally by cryptlib, OTOH if we get to here 
	   then we've received a valid response from the TSA so all is OK */
	if( !isServer )
		{
		CRYPT_ENVELOPE cryptEnvelope;
		BYTE buffer[ BUFFER_SIZE ];
		int bytesCopied;

		status = cryptGetAttribute( cryptSession, CRYPT_SESSINFO_RESPONSE,
									&cryptEnvelope );
		if( cryptStatusError( status ) )
			{
			printExtError( cryptSession, "Attempt to process returned "
						   "timestamp", status, __LINE__ );
			return( FALSE );
			}
		status = cryptPopData( cryptEnvelope, buffer, BUFFER_SIZE,
							   &bytesCopied );
		if( cryptStatusError( status ) )
			{
			printf( "cryptPopData() failed with error code %d, line %d.\n",
					status, __LINE__ );
			return( FALSE );
			}
		printf( "Timestamp data size = %d bytes.\n", bytesCopied );
		debugDump( "tstinfo", buffer, bytesCopied );
		cryptDestroyEnvelope( cryptEnvelope );
		}

	return( TRUE );
	}