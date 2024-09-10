int
LDAP_CALL
ldap_modify_ext_s( LDAP *ld, const char *dn, LDAPMod **mods,
    LDAPControl **serverctrls, LDAPControl **clientctrls )
{
	int		msgid, err;
	LDAPMessage	*res;

	if (( err = ldap_modify_ext( ld, dn, mods, serverctrls, clientctrls,
	    &msgid )) != LDAP_SUCCESS ) {
		return( err );
	}

	if ( ldap_result( ld, msgid, 1, (struct timeval *)NULL, &res ) == -1 ) {
		return( LDAP_GET_LDERRNO( ld, NULL, NULL ) );
	}

	return( ldap_result2error( ld, res, 1 ) );
}