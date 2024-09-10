int
ldap_passwd( LDAP *ld,
	struct berval	*user,
	struct berval	*oldpw,
	struct berval	*newpw,
	LDAPControl		**sctrls,
	LDAPControl		**cctrls,
	int				*msgidp )
{
	int rc;
	struct berval bv = BER_BVNULL;
	BerElement *ber = NULL;

	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( msgidp != NULL );

	if( user != NULL || oldpw != NULL || newpw != NULL ) {
		/* build change password control */
		ber = ber_alloc_t( LBER_USE_DER );

		if( ber == NULL ) {
			ld->ld_errno = LDAP_NO_MEMORY;
			return ld->ld_errno;
		}

		ber_printf( ber, "{" /*}*/ );

		if( user != NULL ) {
			ber_printf( ber, "tO",
				LDAP_TAG_EXOP_MODIFY_PASSWD_ID, user );
		}

		if( oldpw != NULL ) {
			ber_printf( ber, "tO",
				LDAP_TAG_EXOP_MODIFY_PASSWD_OLD, oldpw );
		}

		if( newpw != NULL ) {
			ber_printf( ber, "tO",
				LDAP_TAG_EXOP_MODIFY_PASSWD_NEW, newpw );
		}

		ber_printf( ber, /*{*/ "N}" );

		rc = ber_flatten2( ber, &bv, 0 );

		if( rc < 0 ) {
			ld->ld_errno = LDAP_ENCODING_ERROR;
			return ld->ld_errno;
		}

	}
	
	rc = ldap_extended_operation( ld, LDAP_EXOP_MODIFY_PASSWD,
		bv.bv_val ? &bv : NULL, sctrls, cctrls, msgidp );

	ber_free( ber, 1 );

	return rc;
}