static int suitebServer( const int testNo, const char *hostName, 
						 const int port, const int flags,
						 const BOOLEAN isServerTest )
	{
	CRYPT_SESSION cryptSession;
	CRYPT_CONTEXT privateKey;
	const SUITEB_TEST_INFO *testInfoPtr = isServerTest ? \
					&serverTestInfo[ testNo ] : &clientTestInfo[ testNo ];
	const char *testName = testInfoPtr->testName;
	const BOOLEAN isLoopbackTest = \
			( !strcmp( hostName, "localhost" ) && port == 0 ) ? TRUE : FALSE;
	const BOOLEAN sendHTTP = \
			( flags & TESTFLAG_SENDHTTPREQ ) ? TRUE : FALSE;
	char filenameBuffer[ FILENAME_BUFFER_SIZE ];
#ifdef UNICODE_STRINGS
	wchar_t wcBuffer[ FILENAME_BUFFER_SIZE ];
#endif /* UNICODE_STRINGS */
	SPECIAL_HANDLING_TYPE handlingTypeAlt = SPECIAL_NONE;
	void *fileNamePtr = filenameBuffer;
	int status;

	/* Make sure that we've been given a valid test number to run */
	if( isServerTest )
		{
		if( testNo < SUITEB_FIRST_SERVER || testNo > SUITEB_LAST_SERVER )
			return( FALSE );
		}
	else
		{
		if( testNo < SUITEB_FIRST_CLIENT || testNo > SUITEB_LAST_CLIENT )
			return( FALSE );
		}

	/* If it's an alias for another test, select the base test */
	if( testInfoPtr->aliasTestName != NULL )
		{
		handlingTypeAlt = testInfoPtr->handlingType;
		testInfoPtr = findAliasTest( isServerTest ? \
								&serverTestInfo[ 1 ] : &clientTestInfo[ 1 ],
								testInfoPtr->aliasTestName );
		if( testInfoPtr == NULL )
			{
			assert( 0 );
			return( FALSE );
			}
		}

	/* Acquire the init mutex */
	acquireMutex();
	cryptSuiteBTestConfig( SUITEB_TEST_NONE );	/* Clear any custom config */

	printf( "SVR: Running Suite B server " );
	if( flags & TESTFLAG_GENERIC )
		printf( "as generic test server.\n" );
	else
		printf( "with test %s.\n", testInfoPtr->testName );

	/* Create the SSL/TLS session */
	status = cryptCreateSession( &cryptSession, CRYPT_UNUSED, 
								 CRYPT_SESSION_SSL_SERVER );
	if( status == CRYPT_ERROR_PARAM3 )	/* SSL/TLS session access not available */
		return( CRYPT_ERROR_NOTAVAIL );
	if( cryptStatusError( status ) )
		{
		printf( "cryptCreateSession() failed with error code %d, line %d.\n",
				status, __LINE__ );
		return( FALSE );
		}
	status = cryptSetAttribute( cryptSession, CRYPT_SESSINFO_VERSION, 3 );
	if( cryptStatusOK( status ) && testInfoPtr->serverOptions != 0 )
		{
		status = cryptSetAttribute( cryptSession, CRYPT_SESSINFO_SSL_OPTIONS, 
									testInfoPtr->serverOptions );
		}
	if( testInfoPtr->clientAuthKeySizeBits > 0 ) 
		{
		/* Tell the test code to expect a client certificate */
		cryptSuiteBTestConfig( 1000 );
		}
	if( cryptStatusError( status ) )
		{
		printf( "cryptSetAttribute() failed with error code %d, line %d.\n",
				status, __LINE__ );
		return( FALSE );
		}

	/* Set up the server information */
	if( isLoopbackTest )
		{
		/* We're running the loopback test, set up a local connect */
		if( !setLocalConnect( cryptSession, 443 ) )
			return( FALSE );
		}
	else
		{
		status = cryptSetAttributeString( cryptSession,
										  CRYPT_SESSINFO_SERVER_NAME,
										  hostName, strlen( hostName ) );
		if( cryptStatusOK( status ) && port != 0 && port != 443 )
			status = cryptSetAttribute( cryptSession, 
										CRYPT_SESSINFO_SERVER_PORT, port );
		if( cryptStatusError( status ) )
			{
			printf( "cryptSetAttribute()/cryptSetAttributeString() failed "
					"with error code %d, line %d.\n", status, __LINE__ );
			return( FALSE );
			}
		}

	/* Set any custom server configuration that may be required.  We have to 
	   do this before we set the server key since some of the tests involve
	   invalid server keys */
	switch( testInfoPtr->handlingType )
		{
		case SPECIAL_SVR_INVALIDCURVE:
			/* Server sends non-Suite B curve */
			status = cryptSuiteBTestConfig( SUITEB_TEST_SVRINVALIDCURVE );
			break;

		case SPECIAL_BOTH_SUPPCURVES:
			/* Client must send both P256 and P384 in supported curves 
			   extension */
			status = cryptSuiteBTestConfig( SUITEB_TEST_BOTHCURVES );
			break;

		case SPECIAL_BOTH_SIGALGO:
			/* Client must send both SHA256 and SHA384 in signature algos
			   extension */
			status = cryptSuiteBTestConfig( SUITEB_TEST_BOTHSIGALGOS );
			break;
		}
	if( cryptStatusError( status ) )
		{
		printf( "Custom config set failed with error code %d, line %d.\n", 
				status, __LINE__ );
		return( FALSE );
		}

	/* Add the server key */
	filenameFromTemplate( filenameBuffer, SERVER_ECPRIVKEY_FILE_TEMPLATE, 
						  testInfoPtr->serverKeySizeBits );
#ifdef UNICODE_STRINGS
	mbstowcs( wcBuffer, filenameBuffer, strlen( filenameBuffer ) + 1 );
	fileNamePtr = wcBuffer;
#endif /* UNICODE_STRINGS */
	status = getPrivateKey( &privateKey, fileNamePtr, USER_PRIVKEY_LABEL,
							TEST_PRIVKEY_PASSWORD );
	if( cryptStatusOK( status ) )
		{
		status = cryptSetAttribute( cryptSession, CRYPT_SESSINFO_PRIVATEKEY,
									privateKey );
		cryptDestroyContext( privateKey );
		}
	if( cryptStatusError( status ) )
		{
		printf( "SVR: cryptSetAttribute/AttributeString() failed with error "
				"code %d, line %d.\n", status, __LINE__ );
		return( FALSE );
		}

	/* For the loopback test we also increase the connection timeout to a 
	   higher-than-normal level, since this gives us more time for tracing 
	   through the code when debugging */
	cryptSetAttribute( cryptSession, CRYPT_OPTION_NET_CONNECTTIMEOUT, 120 );

	/* Tell the client that we're ready to go */
	releaseMutex();

	/* Activate the server session */
	status = cryptSetAttribute( cryptSession, CRYPT_SESSINFO_ACTIVE, TRUE );
	if( ( testInfoPtr->result && !cryptStatusOK( status ) ) || \
		( !testInfoPtr->result && !cryptStatusError( status ) ) )
		{
		if( testInfoPtr->result )
			printf( "SVR: Test %s failed, should have succeeded.\n",
					testName );
		else
			printf( "SVR: Test %s succeeded, should have failed.\n",
					testName );
		if( cryptStatusError( status ) )
			{
			printExtError( cryptSession, "SVR: Failure reason is:", status, 
						   __LINE__ );
			}
		cryptDestroySession( cryptSession );

		return( FALSE );
		}

	/* Perform any custom post-activation checking that may be required */
	if( testInfoPtr->handlingType != 0 || handlingTypeAlt != 0 )
		{
		const SPECIAL_HANDLING_TYPE handlingType = \
				( handlingTypeAlt != 0 ) ? handlingTypeAlt : \
										   testInfoPtr->handlingType;
		BYTE buffer[ 1024 ];
		int length;

		switch( handlingType )
			{
			case SPECIAL_CLI_TLSALERT:
				status = cryptGetAttributeString( cryptSession, 
									CRYPT_ATTRIBUTE_ERRORMESSAGE, buffer, 
									&length );
				if( cryptStatusError( status ) || \
					memcmp( buffer, "Received TLS alert", 18 ) )
					{
					printf( "SVR: Test %s should have returned a TLS alert "
							"but didn't.\n", testName );
					return( FALSE );
					}
				break;
			}
		}

	/* If we're being asked to send HTTP data, return a basic HTML page */
	if( sendHTTP )
		{
		const char serverReply[] = \
			"HTTP/1.0 200 OK\n"
			"Date: Fri, 7 September 2010 20:02:07 GMT\n"
			"Server: cryptlib Suite B test\n"
			"Content-Type: text/html\n"
			"Connection: Close\n"
			"\n"
			"<!DOCTYPE HTML SYSTEM \"html.dtd\">\n"
			"<html>\n"
			"<head>\n"
			"<title>cryptlib Suite B test page</title>\n"
			"<body>\n"
			"Test message from the cryptlib Suite B server.<p>\n"
			"</body>\n"
			"</html>\n";
		char buffer[ FILEBUFFER_SIZE ];
		int bytesCopied;

		/* Print the text of the request from the client */
		status = cryptPopData( cryptSession, buffer, FILEBUFFER_SIZE,
							   &bytesCopied );
		if( cryptStatusError( status ) )
			{
			printExtError( cryptSession, "SVR: Attempt to read data from "
						   "client", status, __LINE__ );
			cryptDestroySession( cryptSession );
			return( FALSE );
			}
		buffer[ bytesCopied ] = '\0';
		printf( "---- Client sent %d bytes ----\n", bytesCopied );
		puts( buffer );
		puts( "---- End of output ----" );

		/* Send a reply */
		status = cryptPushData( cryptSession, serverReply,
								sizeof( serverReply ) - 1, &bytesCopied );
		if( cryptStatusOK( status ) )
			status = cryptFlushData( cryptSession );
		if( cryptStatusError( status ) || \
			bytesCopied != sizeof( serverReply ) - 1 )
			{
			printExtError( cryptSession, "Attempt to send data to client", 
						   status, __LINE__ );
			cryptDestroySession( cryptSession );
			return( FALSE );
			}
		}

	/* Clean up */
	status = cryptDestroySession( cryptSession );
	if( cryptStatusError( status ) )
		{
		printf( "cryptDestroySession() failed with error code %d, line %d.\n",
				status, __LINE__ );
		return( FALSE );
		}
	printf( "SVR: Suite B server test %s succeeded.\n", testName );

	return( TRUE );
	}