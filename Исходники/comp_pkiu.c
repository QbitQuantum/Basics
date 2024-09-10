static int copyPkiUserAttributes( INOUT CERT_INFO *certInfoPtr,
								  INOUT ATTRIBUTE_PTR *pkiUserAttributes )
	{
	ATTRIBUTE_PTR *requestAttrPtr, *pkiUserAttrPtr;
	int value, status;

	assert( isWritePtr( certInfoPtr, sizeof( CERT_INFO ) ) );
	assert( isWritePtr( pkiUserAttributes, sizeof( ATTRIBUTE_LIST ) ) );

	REQUIRES( certInfoPtr->type == CRYPT_CERTTYPE_CERTREQUEST || \
			  certInfoPtr->type == CRYPT_CERTTYPE_REQUEST_CERT );

	/* If there are altNames present in both the PKI user data and the 
	   request, make sure that they match */
	requestAttrPtr = findAttribute( certInfoPtr->attributes,
									CRYPT_CERTINFO_SUBJECTALTNAME, FALSE );
	pkiUserAttrPtr = findAttribute( pkiUserAttributes,
									CRYPT_CERTINFO_SUBJECTALTNAME, FALSE );
	if( requestAttrPtr != NULL && pkiUserAttrPtr != NULL )
		{
		/* Both the certificate request and the PKI user have altNames,
		   make sure that they're identical */
		if( !compareAttribute( requestAttrPtr, pkiUserAttrPtr ) )
			{
			setErrorInfo( certInfoPtr, CRYPT_CERTINFO_SUBJECTALTNAME,
						  CRYPT_ERRTYPE_ISSUERCONSTRAINT );
			return( CRYPT_ERROR_INVALID );
			}

		/* The two altNames are identical, delete the one in the request in 
		   order to allow the one from the PKI user data to be copied across 
		   when we call copyAttributes() */
		status = deleteAttribute( &certInfoPtr->attributes,
								  &certInfoPtr->attributeCursor, 
								  requestAttrPtr,
								  certInfoPtr->currentSelection.dnPtr );
		if( cryptStatusError( status ) )
			return( status );
		}

	/* There's one rather ugly special-case situation that we have to handle 
	   which is when the user has submitted a PnP PKI request for a generic 
	   signing certificate but their PKI user information indicates that 
	   they're intended to be a CA user.  The processing flow for this is:

			Read request data from an external source into certificate 
				request object, creating a state=high object;

			Add PKI user information to state=high request;

	   When augmenting the request with the PKI user information the 
	   incoming request will contain a keyUsage of digitalSignature while 
	   the PKI user information will contain a keyUsage of keyCertSign 
	   and/or crlSign.  We can't fix this up at the PnP processing level 
	   because the request object will be in the high state once it's
	   instantiated and no changes to the attributes can be made (the PKI 
	   user information is a special case that can be added to an object in 
	   the high state but which modifies attributes in it as if it were 
	   still in the low state).

	   To avoid the attribute conflict, if we find this situation in the 
	   request/pkiUser combination we delete the keyUsage in the request to 
	   allow it to be replaced by the pkiUser keyUsage.  Hardcoding in this 
	   special case isn't very elegant but it's the only way to make the PnP 
	   PKI issue work without requiring that the user explicitly specify 
	   that they want to be a CA in the request's keyUsage, which makes it 
	   rather non-PnP and would also lead to slightly strange requests since
	   basicConstraints can't be specified in requests while the CA keyUsage
	   can */
	status = getAttributeFieldValue( certInfoPtr->attributes,
									 CRYPT_CERTINFO_KEYUSAGE, 
									 CRYPT_ATTRIBUTE_NONE, &value );
	if( cryptStatusOK( status ) && value == CRYPT_KEYUSAGE_DIGITALSIGNATURE )
		{
		status = getAttributeFieldValue( pkiUserAttributes, 
										 CRYPT_CERTINFO_KEYUSAGE,
										 CRYPT_ATTRIBUTE_NONE, &value );
		if( cryptStatusOK( status ) && ( value & KEYUSAGE_CA ) )
			{
			/* The certificate contains a digitalSignature keyUsage and the 
			   PKI user information contains a CA usage, delete the 
			   certificate's keyUsage to make way for the PKI user's CA 
			   keyUsage */
			status = deleteCompleteAttribute( &certInfoPtr->attributes,
											  &certInfoPtr->attributeCursor, 
											  CRYPT_CERTINFO_KEYUSAGE, 
											  certInfoPtr->currentSelection.dnPtr );
			if( cryptStatusError( status ) )
				return( status );
			}
		}

	/* Copy the attributes from the PKI user information into the 
	   certificate */
	status = copyAttributes( &certInfoPtr->attributes, pkiUserAttributes,
							 &certInfoPtr->errorLocus,
							 &certInfoPtr->errorType );
	if( cryptStatusError( status ) )
		return( status );

	/* Perform any special-case adjustments on attributes that may be 
	   required after they've been copied from the PKI user to the 
	   certificate request */
	return( adjustPkiUserAttributes( certInfoPtr ) );
	}