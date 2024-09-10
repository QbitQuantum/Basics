/* synchronous bind to DSA using kerberos */
int
ldap_kerberos_bind2_s( LDAP *ld, LDAP_CONST char *dn )
{
	int		msgid;
	LDAPMessage	*res;

	Debug( LDAP_DEBUG_TRACE, "ldap_kerberos_bind2_s\n", 0, 0, 0 );

	/* initiate the bind */
	if ( (msgid = ldap_kerberos_bind2( ld, dn )) == -1 )
		return( ld->ld_errno );

	/* wait for a result */
	if ( ldap_result( ld, msgid, 1, (struct timeval *) 0, &res )
	    == -1 ) {
		return( ld->ld_errno );	/* ldap_result sets ld_errno */
	}

	return( ldap_result2error( ld, res, 1 ) );
}