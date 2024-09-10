int
ldap_add_s( LDAP *ld, char *dn, LDAPMod **attrs )
{
	int		msgid;
	LDAPMessage	*res;

	if ( (msgid = ldap_add( ld, dn, attrs )) == -1 )
		return( ld->ld_errno );

	if ( ldap_result( ld, msgid, 1, (struct timeval *) NULL, &res ) == -1 )
		return( ld->ld_errno );

	return( ldap_result2error( ld, res, 1 ) );
}