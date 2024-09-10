LDAP_CALL
ldap_get_dn( LDAP *ld, LDAPMessage *entry )
{
	char			*dn;
	struct berelement	tmp;

	LDAPDebug( LDAP_DEBUG_TRACE, "ldap_get_dn\n", 0, 0, 0 );

	if ( !NSLDAPI_VALID_LDAP_POINTER( ld )) {
		return( NULL );		/* punt */
	}

	if ( !NSLDAPI_VALID_LDAPMESSAGE_ENTRY_POINTER( entry )) {
		LDAP_SET_LDERRNO( ld, LDAP_PARAM_ERROR, NULL, NULL );
		return( NULL );
	}

	tmp = *entry->lm_ber;	/* struct copy */
	if ( ber_scanf( &tmp, "{a", &dn ) == LBER_ERROR ) {
		LDAP_SET_LDERRNO( ld, LDAP_DECODING_ERROR, NULL, NULL );
		return( NULL );
	}

	return( dn );
}