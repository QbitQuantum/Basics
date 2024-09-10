int
ldap_delete_s( LDAP *ld, LDAP_CONST char *dn )
{
	return ldap_delete_ext_s( ld, dn, NULL, NULL );
}