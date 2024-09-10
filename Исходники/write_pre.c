static int addStandardExtensions( INOUT CERT_INFO *certInfoPtr )
	{
	BOOLEAN isCA = FALSE;
	int keyUsage, extKeyUsage, value, status;

	assert( isWritePtr( certInfoPtr, sizeof( CERT_INFO ) ) );

	/* Get the implicit keyUsage flags (based on any extended key usage 
	   extensions present) and explicit key usage flags, which we use to 
	   extend the basic keyUsage flags if required */
 	status = getKeyUsageFromExtKeyUsage( certInfoPtr, &extKeyUsage,
						&certInfoPtr->errorLocus, &certInfoPtr->errorType );
	if( cryptStatusError( status ) )
		return( status );
	status = getAttributeFieldValue( certInfoPtr->attributes,
									 CRYPT_CERTINFO_KEYUSAGE,
									 CRYPT_ATTRIBUTE_NONE, &keyUsage );
	if( cryptStatusError( status ) )
		{
		if( status != CRYPT_ERROR_NOTFOUND )
			return( status );

		/* There's no keyUsage attribute present, mark the value as being 
		   not set so that we explicitly set it later */
		keyUsage = CRYPT_ERROR;
		}

	/* If there's an explicit key usage present, make sure that it's
	   consistent with the implicit key usage flags derived from the 
	   extended key usage.  We mask out the nonRepudiation bit for reasons 
	   given in chk_cert.c.

	   This check is also performed by checkCert(), however we need to
	   explicitly perform it here as well since we need to add a key usage 
	   to match the extKeyUsage before calling checkCert() if one wasn't
	   explicitly set or checkCert() will reject the certificate because of 
	   the inconsistent keyUsage */
	if( keyUsage > 0 )
		{
		const int effectiveKeyUsage = \
						extKeyUsage & ~CRYPT_KEYUSAGE_NONREPUDIATION;

		if( ( keyUsage & effectiveKeyUsage ) != effectiveKeyUsage )
			{
			setErrorInfo( certInfoPtr, CRYPT_CERTINFO_KEYUSAGE,
						  CRYPT_ERRTYPE_CONSTRAINT );
			return( CRYPT_ERROR_INVALID );
			}
		}

	/* Check whether this is a CA certificate.  If there's no 
	   basicConstraints attribute present, add one and make it a non-CA 
	   certificate */
	status = getAttributeFieldValue( certInfoPtr->attributes,
									 CRYPT_CERTINFO_CA, CRYPT_ATTRIBUTE_NONE,
									 &value );
	if( cryptStatusOK( status ) )
		isCA = ( value > 0 ) ? TRUE : FALSE;
	else
		{
		status = addCertComponent( certInfoPtr, CRYPT_CERTINFO_CA, FALSE );
		if( cryptStatusError( status ) )
			return( status );
		}

	/* If there's no explicit keyUsage information present add it based on
	   various implicit information.  We also add key feature information
	   which is used to help automate key management, for example to inhibit
	   speculative reads of keys held in removable tokens, which can result
	   in spurious insert-token dialogs being presented to the user outside
	   the control of cryptlib if the token isn't present */
	if( keyUsage <= 0 )
		{
		/* If there's no implicit key usage present and it's not a CA (for 
		   which we don't want to set things like encryption flags for the
		   CA certificate), set the key usage flags based on the 
		   capabilities of the associated context.  Because no-one can 
		   figure out what the nonRepudiation flag signifies we don't set 
		   this, if the user wants it they have to specify it explicitly.  
		   Similarly we don't try and set the keyAgreement encipher/decipher-
		   only flags, which were tacked on as variants of keyAgreement long 
		   after the basic keyAgreement flag was defined */
		if( extKeyUsage <= 0 && !isCA )
			{
			keyUsage = 0;	/* Reset key usage */
			if( certInfoPtr->iPubkeyContext != CRYPT_ERROR )
				{
				/* There's a context present, check its capabilities.  This
				   has the advantage that it takes into account any ACLs
				   that may exist for the key */
				if( cryptStatusOK( \
						krnlSendMessage( certInfoPtr->iPubkeyContext, 
										 IMESSAGE_CHECK, NULL, 
										 MESSAGE_CHECK_PKC_SIGCHECK ) ) )
					keyUsage = CRYPT_KEYUSAGE_DIGITALSIGNATURE;
				if( cryptStatusOK( \
						krnlSendMessage( certInfoPtr->iPubkeyContext, 
										 IMESSAGE_CHECK, NULL, 
										 MESSAGE_CHECK_PKC_ENCRYPT ) ) )
					keyUsage |= CRYPT_KEYUSAGE_KEYENCIPHERMENT;
				if( cryptStatusOK( \
						krnlSendMessage( certInfoPtr->iPubkeyContext, 
										 IMESSAGE_CHECK, NULL, 
										 MESSAGE_CHECK_PKC_KA_EXPORT ) ) || \
					cryptStatusOK( \
						krnlSendMessage( certInfoPtr->iPubkeyContext, 
										 IMESSAGE_CHECK, NULL, 
										 MESSAGE_CHECK_PKC_KA_IMPORT ) ) )
					keyUsage |= CRYPT_KEYUSAGE_KEYAGREEMENT;
				}
			else
				{
				/* There's no context present (the key is present as encoded
				   data), assume we can do whatever the algorithm allows */
				if( isSigAlgo( certInfoPtr->publicKeyAlgo ) )
					keyUsage = CRYPT_KEYUSAGE_DIGITALSIGNATURE;
				if( isCryptAlgo( certInfoPtr->publicKeyAlgo ) )
					keyUsage |= CRYPT_KEYUSAGE_KEYENCIPHERMENT;
				if( isKeyxAlgo( certInfoPtr->publicKeyAlgo ) )
					keyUsage |= CRYPT_KEYUSAGE_KEYAGREEMENT;
				}
			}
		else
			{
			/* There's an extended key usage set but no basic keyUsage, make 
			   the keyUsage consistent with the usage flags derived from the 
			   extended usage */
			keyUsage = extKeyUsage;

			/* If it's a CA key, make sure that it's a signing key and
			   enable its use for certification-related purposes*/
			if( isCA )
				{
				BOOLEAN usageOK;

				if( certInfoPtr->iPubkeyContext != CRYPT_ERROR )
					{
					usageOK = cryptStatusOK( \
								krnlSendMessage( certInfoPtr->iPubkeyContext, 
												 IMESSAGE_CHECK, NULL, 
												 MESSAGE_CHECK_PKC_SIGCHECK ) );
					}
				else
					usageOK = isSigAlgo( certInfoPtr->publicKeyAlgo );
				if( !usageOK )
					{
					setErrorInfo( certInfoPtr, CRYPT_CERTINFO_CA,
								  CRYPT_ERRTYPE_CONSTRAINT );
					return( CRYPT_ERROR_INVALID );
					}
				keyUsage |= KEYUSAGE_CA;
				}
			}
		ENSURES( keyUsage > CRYPT_KEYUSAGE_NONE && \
				 keyUsage < CRYPT_KEYUSAGE_LAST );
		status = addCertComponent( certInfoPtr, CRYPT_CERTINFO_KEYUSAGE,
								   keyUsage );
		if( cryptStatusError( status ) )
			return( status );
		}
	if( certInfoPtr->publicKeyFeatures > 0 )
		{
		/* This is a bitstring so we only add it if there are feature flags
		   present to avoid writing zero-length values */
		status = addCertComponent( certInfoPtr, CRYPT_CERTINFO_KEYFEATURES,
								   certInfoPtr->publicKeyFeatures );
		if( cryptStatusError( status ) && status != CRYPT_ERROR_INITED )
			return( status );
		}

	/* Add the subjectKeyIdentifier */
	return( addCertComponentString( certInfoPtr, 
									CRYPT_CERTINFO_SUBJECTKEYIDENTIFIER,
									certInfoPtr->publicKeyID, KEYID_SIZE ) );
	}