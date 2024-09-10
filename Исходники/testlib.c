static int fuzzSpecial( const int fuzzType, const char *fuzzFileName )
	{
	CRYPT_CONTEXT cryptPrivKey;
	BYTE buffer[ 8192 ];
	const int minLength = ( fuzzType == 4000 ) ? 2 : 16;
	int length, status;

	/* If we're fuzzing bignum ops, load the private key that we'll need */
	if( fuzzType == 4000 )
		{
		if( !loadRSAContexts( CRYPT_UNUSED, NULL, &cryptPrivKey ) )
			return( CRYPT_ERROR_FAILED );
		}

	/* We're ready to go, start the forkserver and read the mutable data */
#ifndef __WINDOWS__
	__afl_manual_init();
#endif /* !__WINDOWS__ */
	length = readFileData( fuzzFileName, fuzzFileName, buffer, 8192, 
						   minLength, TRUE );
	if( length < minLength )
		return( CRYPT_ERROR_READ );

	/* Process the input file */
	if( fuzzType == 4000 )
		{
		BYTE tmpBuffer[ 8192 ];

#if 0	/* We don't do an early-out in order to check that the bignum code 
		   can actually reject all invalid input values */
		/* Any value that's larger than the modulus will be trivially 
		   rejected so there's no point in trying to process it */
		if( buffer[ 0 ] > 0x9C )
			{
			cryptDestroyContext( cryptPrivKey );
			return( CRYPT_OK );
			}
#endif /* 0 */

		memcpy( tmpBuffer, buffer, length );
		status = cryptDecrypt( cryptPrivKey, buffer, length );
		if( cryptStatusOK( status ) )
			status = cryptEncrypt( cryptPrivKey, buffer, length );
		if( cryptStatusOK( status ) )
			{
			/* Make sure that we got back what we started with */
			assert( !memcmp( buffer, tmpBuffer, length ) );
			}
		cryptDestroyContext( cryptPrivKey );
		}