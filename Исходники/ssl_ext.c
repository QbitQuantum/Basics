static int processSNI( INOUT SSL_HANDSHAKE_INFO *handshakeInfo,
					   INOUT STREAM *stream, 
					   IN_LENGTH_SHORT_Z const int extLength,
					   const BOOLEAN isServer )
	{
	BYTE nameBuffer[ MAX_DNS_SIZE + 8 ];
	int listLen, nameLen, status;

	assert( isWritePtr( handshakeInfo, sizeof( SSL_HANDSHAKE_INFO ) ) );
	assert( isWritePtr( stream, sizeof( STREAM ) ) );

	REQUIRES( extLength >= 0 && extLength < MAX_INTLENGTH_SHORT );

	/* If we're the client then the server should have sent us an empty
	   extension */
	if( !isServer )
		return( ( extLength != 0 ) ? CRYPT_ERROR_BADDATA : CRYPT_OK );

	/* Remember that we've seen the server-name extension so that we can 
	   send a zero-length reply to the client */
	handshakeInfo->needSNIResponse = TRUE;

	/* Read the extension wrapper */
	status = listLen = readUint16( stream );
	if( cryptStatusError( status ) )
		return( status );
	if( listLen != extLength - UINT16_SIZE || \
		listLen < 1 + UINT16_SIZE || \
		listLen >= MAX_INTLENGTH_SHORT )
		return( CRYPT_ERROR_BADDATA );

	/* Read the name type and length */
	if( sgetc( stream ) != 0 )	/* Name type 0 = hostname */
		return( CRYPT_ERROR_BADDATA );
	status = nameLen = readUint16( stream );
	if( cryptStatusError( status ) )
		return( status );
	if( nameLen != listLen - ( 1 + UINT16_SIZE ) || \
		nameLen < MIN_DNS_SIZE || nameLen > MAX_DNS_SIZE )
		return( CRYPT_ERROR_BADDATA );

	/* Read the SNI and hash it */
	status = sread( stream, nameBuffer, nameLen );
	if( cryptStatusError( status ) )
		return( status );
	hashData( handshakeInfo->hashedSNI, KEYID_SIZE, nameBuffer, nameLen );
	handshakeInfo->hashedSNIpresent = TRUE;

	return( CRYPT_OK );
	}