static int initFunction( DEVICE_INFO *deviceInfo, const char *name,
						 const int nameLength )
	{
	CK_SESSION_HANDLE hSession;
	CK_SLOT_ID slotList[ MAX_PKCS11_SLOTS + 8 ];
	CK_ULONG slotCount = MAX_PKCS11_SLOTS;
	CK_SLOT_INFO slotInfo;
	CK_TOKEN_INFO tokenInfo;
	CK_RV status;
	PKCS11_INFO *pkcs11Info = deviceInfo->devicePKCS11;
	const PKCS11_MECHANISM_INFO *mechanismInfoPtr;
	char *labelPtr;
	int tokenSlot = DEFAULT_SLOT, i, labelLength, mechanismInfoSize;
	int cryptStatus, cryptStatus2;

	assert( isWritePtr( deviceInfo, sizeof( DEVICE_INFO ) ) );
	assert( isReadPtr( name, nameLength ) );

	/* Get information on all available slots */
	memset( slotList, 0, sizeof( slotList ) );
	status = C_GetSlotList( TRUE, slotList, &slotCount );
	if( status != CKR_OK )
		return( pkcs11MapError( status, CRYPT_ERROR_OPEN ) );
	if( slotCount <= 0 )
		{
		/* There are token slots present but no tokens in the slots */
		return( CRYPT_ERROR_OPEN );
		}

	/* Check whether a token name (used to select the slot) has been 
	   specified */
	for( i = 1; i < nameLength - 1; i++ )
		{
		if( name[ i ] == ':' && name[ i + 1 ] == ':' )
			break;
		}
	if( i < nameLength - 1 )
		{
		const char *tokenName = name + i + 2;	/* Skip '::' */
		const int tokenNameLength = nameLength - ( i + 2 );

		if( tokenNameLength <= 0 )
			return( CRYPT_ARGERROR_STR1 );

		/* Some tokens don't implement named slots, so we also allow them to 
		   be specified using slot counts */
		if( tokenNameLength == 1 && isDigit( *tokenName ) )
			{
			tokenSlot = *tokenName - '0';
			if( tokenSlot < 0 || tokenSlot > 9 )
				return( CRYPT_ARGERROR_STR1 );
			if( tokenSlot > slotCount - 1 )	/* Slots numbered from zero */
				return( CRYPT_ERROR_NOTFOUND );
			status = C_GetTokenInfo( slotList[ tokenSlot ], &tokenInfo );
			if( status != CKR_OK )
				return( CRYPT_ERROR_NOTFOUND );
			}
		else
			{
			/* Check each (named) slot for a token matching the given name */
			for( tokenSlot = 0; tokenSlot < slotCount && \
								tokenSlot < FAILSAFE_ITERATIONS_MED; 
				 tokenSlot++ )
				{
				status = C_GetTokenInfo( slotList[ tokenSlot ], &tokenInfo );
				if( status == CKR_OK && \
					!strCompare( tokenName, tokenInfo.label, tokenNameLength ) )
					break;
				}
			ENSURES( tokenSlot < FAILSAFE_ITERATIONS_MED );
			if( tokenSlot >= slotCount )
				return( CRYPT_ERROR_NOTFOUND );
			}
		}
	pkcs11Info->slotID = slotList[ tokenSlot ];

	/* Get information on device-specific capabilities */
	status = C_GetSlotInfo( pkcs11Info->slotID, &slotInfo );
	if( status != CKR_OK )
		{
		shutdownFunction( deviceInfo );
		return( pkcs11MapError( status, CRYPT_ERROR_OPEN ) );
		}
	if( slotInfo.flags & CKF_REMOVABLE_DEVICE )
		{
		/* The device is removable */
		deviceInfo->flags |= DEVICE_REMOVABLE;
		}
	status = C_GetTokenInfo( pkcs11Info->slotID, &tokenInfo );
	if( status != CKR_OK )
		{
		shutdownFunction( deviceInfo );
		return( pkcs11MapError( status, CRYPT_ERROR_OPEN ) );
		}
	if( tokenInfo.flags & CKF_RNG )
		{
		/* The device has an onboard RNG that we can use */
		deviceInfo->getRandomFunction = getRandomFunction;
		}
#if 0	/* The Spyrus driver for pre-Lynks-II cards returns the local system 
		   time (with a GMT/localtime offset), ignoring the fact that the 
		   token has an onboard clock, so having the CKF_CLOCK_ON_TOKEN not 
		   set is accurate, although having it ignore the presence of the 
		   clock isn't very valid */
	if( !( tokenInfo.flags & CKF_CLOCK_ON_TOKEN ) && \
		( !strCompare( tokenInfo.label, "Lynks Token", 11 ) || \
		  !strCompare( tokenInfo.model, "Rosetta", 7 ) ) )
		{
		/* Fix buggy Spyrus PKCS #11 drivers which claim that the token
		   doesn't have a RTC even though it does (the Rosetta (smart card) 
		   form of the token is even worse, it returns garbage in the label 
		   and manufacturer fields, but the model field is OK).  There is a 
		   chance that there's a genuine problem with the clock (there are 
		   batches of tokens with bad clocks) but the time check that  
		   follows below will catch those */
		tokenInfo.flags |= CKF_CLOCK_ON_TOKEN;
		}
#endif /* 0 */
	if( tokenInfo.flags & CKF_CLOCK_ON_TOKEN )
		{
		const time_t theTime = getTokenTime( &tokenInfo );
		const time_t currentTime = getTime();

		/* The token claims to have an onboard clock that we can use.  Since
		   this could be arbitrarily inaccurate we compare it with the 
		   system time and only rely on it if it's within +/- 1 day of the
		   system time.
		   
		   There is a second check that we should make to catch drivers that
		   claim to read the time from the token but actually use the local
		   computer's time, but this isn't easy to do.  The most obvious way
		   is to set the system time to a bogus value and check whether this
		   matches the returned time, but this is somewhat drastic and 
		   requires superuser privs on most systems.  An alternative is to 
		   check whether the claimed token time exactly matches the system 
		   time, but this will produce false positives if (for example) the
		   token has been recently synchronised to the system time.  For now
		   all we can do is throw an exception if it appears that the token
		   time is faked */
		if( theTime > MIN_TIME_VALUE && \
			theTime >= currentTime - 86400 && \
			theTime <= currentTime + 86400 )
			deviceInfo->flags |= DEVICE_TIME;

		/* If this check is triggered then the token time may be faked since 
		   it's identical to the host system time, see the comment above for 
		   details.  We make an exception for soft-tokens (if we can detect 
		   them), which will (by definition) have the same time as the 
		   system time */
		if( !( pkcs11InfoTbl[ pkcs11Info->deviceNo ].name[ 0 ] && \
			   !strCompare( pkcs11InfoTbl[ pkcs11Info->deviceNo ].name, 
							"Software", 8 ) ) && \
			theTime == currentTime )
			{
			DEBUG_DIAG(( "PKCS #11 token time is the same as the host "
						 "system time, token time may be faked by the "
						 "driver." ));
			assert( DEBUG_WARN );
			}
		}
	if( tokenInfo.flags & CKF_WRITE_PROTECTED )
		{
		/* The device can't have data on it changed */
		deviceInfo->flags |= DEVICE_READONLY;
		}
	if( ( tokenInfo.flags & CKF_LOGIN_REQUIRED ) || \
		!( tokenInfo.flags & CKF_USER_PIN_INITIALIZED ) )
		{
		/* The user needs to log in before using various device functions.
		   We check for the absence of CKF_USER_PIN_INITIALIZED as well as 
		   the more obvious CKF_LOGIN_REQUIRED because if we've got an 
		   uninitialised device there's no PIN set so some devices will 
		   report that there's no login required (or at least none is 
		   possible).  We need to introduce some sort of pipeline stall if 
		   this is the case because otherwise the user could successfully 
		   perform some functions that don't require a login (where the 
		   exact details of what's allowed without a login are device-
		   specific) before running into mysterious failures when they get 
		   to functions that do require a login.  To avoid this, we make an 
		   uninitialised device look like a login-required device, so the 
		   user gets an invalid-PIN error if they try and proceed */
		deviceInfo->flags |= DEVICE_NEEDSLOGIN;
		}
	if( ( pkcs11Info->minPinSize = ( int ) tokenInfo.ulMinPinLen ) < 4 )
		{
		/* Some devices report silly PIN sizes */
		DEBUG_DIAG(( "Driver reports suspicious minimum PIN size %lu, "
					 "using 4", tokenInfo.ulMinPinLen ));
		pkcs11Info->minPinSize = 4;
		}
	if( ( pkcs11Info->maxPinSize = ( int ) tokenInfo.ulMaxPinLen ) < 4 )
		{
		/* Some devices report silly PIN sizes (setting this to ULONG_MAX or
		   4GB, which becomes -1 as an int, counts as silly).  Since we can't
		   differentiate between 0xFFFFFFFF = bogus value and 0xFFFFFFFF = 
		   ULONG_MAX we play it safe and set the limit to 8 bytes, which most
		   devices should be able to handle */
		DEBUG_DIAG(( "Driver reports suspicious maximum PIN size %lu, "
					 "using 8", tokenInfo.ulMinPinLen ));
		pkcs11Info->maxPinSize = 8;
		}
	labelPtr = ( char * ) tokenInfo.label;
	for( labelLength = 32;
		 labelLength > 0 && \
		 ( labelPtr[ labelLength - 1 ] == ' ' || \
		   !labelPtr[ labelLength - 1 ] ); 
		  labelLength-- );	/* Strip trailing blanks/nulls */
	while( labelLength > 0 && *labelPtr == ' ' )
		{
		/* Strip leading blanks */
		labelPtr++;
		labelLength--;
		}
	if( labelLength > 0 )
		{
		memcpy( pkcs11Info->label, labelPtr, labelLength );
		pkcs11Info->labelLen = labelLength;
		sanitiseString( pkcs11Info->label, CRYPT_MAX_TEXTSIZE, 
						labelLength );
		}
	else
		{
		/* There's no label for the token, use the device label instead */
		if( pkcs11InfoTbl[ pkcs11Info->deviceNo ].name[ 0 ] )
			{
			labelLength = \
				min( strlen( pkcs11InfoTbl[ pkcs11Info->deviceNo ].name ),
					 CRYPT_MAX_TEXTSIZE );
			memcpy( pkcs11Info->label, 
					pkcs11InfoTbl[ pkcs11Info->deviceNo ].name, labelLength );
			}
		}
	pkcs11Info->hActiveSignObject = CK_OBJECT_NONE;
	deviceInfo->label = pkcs11Info->label;
	deviceInfo->labelLen = pkcs11Info->labelLen;

	/* Open a session with the device.  This gets a bit awkward because we 
	   can't tell whether a R/W session is OK without opening a session, but 
	   we can't open a session unless we know whether a R/W session is OK, 
	   so we first try for a RW session and if that fails we go for a read-
	   only session */
	status = C_OpenSession( pkcs11Info->slotID, 
							CKF_RW_SESSION | CKF_SERIAL_SESSION, NULL_PTR, 
							NULL_PTR, &hSession );
	if( status == CKR_TOKEN_WRITE_PROTECTED )
		{
		status = C_OpenSession( pkcs11Info->slotID, 
								CKF_SERIAL_SESSION, NULL_PTR, NULL_PTR, 
								&hSession );
		}
	if( status != CKR_OK )
		{
		cryptStatus = pkcs11MapError( status, CRYPT_ERROR_OPEN );
		if( cryptStatus == CRYPT_ERROR_OPEN && \
			!( tokenInfo.flags & CKF_USER_PIN_INITIALIZED ) )
			{
			/* We couldn't do much with the error code, it could be that the
			   token hasn't been initialised yet but unfortunately PKCS #11 
			   doesn't define an error code for this condition.  In addition
			   many tokens will allow a session to be opened and then fail 
			   with a "PIN not set" error at a later point (which allows for
			   more accurate error reporting), however a small number won't
			   allow a session to be opened and return some odd-looking error
			   because there's nothing useful available.  The best way to
			   report this in a meaningful manner to the caller is to check
			   whether the user PIN has been initialised, if it hasn't then 
			   it's likely that the token as a whole hasn't been initialised 
			   so we return a not initialised error */
			cryptStatus = CRYPT_ERROR_NOTINITED;
			}
		return( cryptStatus );
		}
	ENSURES( hSession != CK_OBJECT_NONE );
	pkcs11Info->hSession = hSession;
	deviceInfo->flags |= DEVICE_ACTIVE;

	/* Set up the capability information for this device.  Since there can 
	   be devices that have one set of capabilities but not the other (e.g.
	   a smart card that only performs RSA ops), we allow one of the two
	   sets of mechanism information setups to fail, but not both */
	mechanismInfoPtr = getMechanismInfoPKC( &mechanismInfoSize );
	cryptStatus = getCapabilities( deviceInfo, mechanismInfoPtr, 
								   mechanismInfoSize );
	mechanismInfoPtr = getMechanismInfoConv( &mechanismInfoSize );
	cryptStatus2 = getCapabilities( deviceInfo, mechanismInfoPtr, 
									mechanismInfoSize );
	if( cryptStatusError( cryptStatus ) && cryptStatusError( cryptStatus2 ) )
		{
		shutdownFunction( deviceInfo );
		return( ( cryptStatus == CRYPT_ERROR ) ? \
				CRYPT_ERROR_OPEN : ( int ) cryptStatus );
		}

	return( CRYPT_OK );
	}