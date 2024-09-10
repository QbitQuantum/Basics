int
ldap_whoami( LDAP *ld,
	LDAPControl		**sctrls,
	LDAPControl		**cctrls,
	int				*msgidp )
{
	int rc;

	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( msgidp != NULL );

	rc = ldap_extended_operation( ld, LDAP_EXOP_X_WHO_AM_I,
		NULL, sctrls, cctrls, msgidp );

	return rc;
}