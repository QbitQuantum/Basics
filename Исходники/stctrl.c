int
ldap_create_session_tracking_value(
	LDAP		*ld,
	char		*sessionSourceIp,
	char		*sessionSourceName,
	char		*formatOID,
	struct berval	*sessionTrackingIdentifier,
	struct berval	*value )
{
	BerElement	*ber = NULL;
	ber_tag_t	tag;

	struct berval	ip, name, oid, id;

	if ( ld == NULL ||
		formatOID == NULL ||
		value == NULL )
	{
param_error:;
		if ( ld ) {
			ld->ld_errno = LDAP_PARAM_ERROR;
		}

		return LDAP_PARAM_ERROR;
	}

	assert( LDAP_VALID( ld ) );
	ld->ld_errno = LDAP_SUCCESS;

	/* check sizes according to I.D. */
	if ( sessionSourceIp == NULL ) {
		BER_BVSTR( &ip, "" );

	} else {
		ber_str2bv( sessionSourceIp, 0, 0, &ip );
		/* NOTE: we're strict because we don't want
		 * to send out bad data */
		if ( ip.bv_len > 128 ) goto param_error;
	}

	if ( sessionSourceName == NULL ) {
		BER_BVSTR( &name, "" );

	} else {
		ber_str2bv( sessionSourceName, 0, 0, &name );
		/* NOTE: we're strict because we don't want
		 * to send out bad data */
		if ( name.bv_len > 65536 ) goto param_error;
	}

	ber_str2bv( formatOID, 0, 0, &oid );
	/* NOTE: we're strict because we don't want
	 * to send out bad data */
	if ( oid.bv_len > 1024 ) goto param_error;

	if ( sessionTrackingIdentifier == NULL ||
		sessionTrackingIdentifier->bv_val == NULL )
	{
		BER_BVSTR( &id, "" );

	} else {
		id = *sessionTrackingIdentifier;
	}

	/* prepare value */
	value->bv_val = NULL;
	value->bv_len = 0;

	ber = ldap_alloc_ber_with_options( ld );
	if ( ber == NULL ) {
		ld->ld_errno = LDAP_NO_MEMORY;
		return ld->ld_errno;
	}

	tag = ber_printf( ber, "{OOOO}", &ip, &name, &oid, &id );
	if ( tag == LBER_ERROR ) {
		ld->ld_errno = LDAP_ENCODING_ERROR;
		goto done;
	}

	if ( ber_flatten2( ber, value, 1 ) == -1 ) {
		ld->ld_errno = LDAP_NO_MEMORY;
	}

done:;
	if ( ber != NULL ) {
		ber_free( ber, 1 );
	}

	return ld->ld_errno;
}