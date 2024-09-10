int
ldap_modrdn_s( LDAP *ld, char *dn, char *newrdn, int deleteoldrdn )
{
	int		msgid;
	LDAPMessage	*res;

	if ( (msgid = ldap_modrdn( ld, dn, newrdn, deleteoldrdn )) == -1 )
		return( ld->ld_errno );

	if ( ldap_result( ld, msgid, 1, (struct timeval *) NULL, &res ) == -1 )
		return( ld->ld_errno );

	return( ldap_result2error( ld, res, 1 ) );
}