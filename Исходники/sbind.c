/*
 * ldap_simple_bind - bind to the ldap server using simple
 * authentication.  The dn and password of the entry to which to bind are
 * supplied.  LDAP_SUCCESS is returned upon success, the ldap error code
 * otherwise.
 *
 * Example:
 *	ldap_simple_bind_s( ld, "cn=manager, o=university of michigan, c=us",
 *	    "secret" )
 */
int
LDAP_CALL
ldap_simple_bind_s( LDAP *ld, const char *dn, const char *passwd )
{
	int		msgid;
	LDAPMessage	*result;

	LDAPDebug( LDAP_DEBUG_TRACE, "ldap_simple_bind_s\n", 0, 0, 0 );

	if ( NSLDAPI_VALID_LDAP_POINTER( ld ) &&
	    ( ld->ld_options & LDAP_BITOPT_RECONNECT ) != 0 ) {
		return( simple_bindifnot_s( ld, dn, passwd ));
	}

	if ( (msgid = ldap_simple_bind( ld, dn, passwd )) == -1 )
		return( LDAP_GET_LDERRNO( ld, NULL, NULL ) );

	if ( ldap_result( ld, msgid, 1, (struct timeval *) 0, &result ) == -1 )
		return( LDAP_GET_LDERRNO( ld, NULL, NULL ) );

	return( ldap_result2error( ld, result, 1 ) );
}