int
ldap_get_entry_controls(
	LDAP *ld,
	LDAPMessage *entry, 
	LDAPControl ***sctrls )
{
	int rc;
	BerElement be;

	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( entry != NULL );
	assert( sctrls != NULL );

	if ( entry->lm_msgtype != LDAP_RES_SEARCH_ENTRY ) {
		return LDAP_PARAM_ERROR;
	}

	/* make a local copy of the BerElement */
	AC_MEMCPY(&be, entry->lm_ber, sizeof(be));

	if ( ber_scanf( &be, "{xx" /*}*/ ) == LBER_ERROR ) {
		rc = LDAP_DECODING_ERROR;
		goto cleanup_and_return;
	}

	rc = ldap_pvt_get_controls( &be, sctrls );

cleanup_and_return:
	if( rc != LDAP_SUCCESS ) {
		ld->ld_errno = rc;

		if( ld->ld_matched != NULL ) {
			LDAP_FREE( ld->ld_matched );
			ld->ld_matched = NULL;
		}

		if( ld->ld_error != NULL ) {
			LDAP_FREE( ld->ld_error );
			ld->ld_error = NULL;
		}
	}

	return rc;
}