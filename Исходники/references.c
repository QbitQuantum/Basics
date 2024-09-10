LDAPMessage *
ldap_first_reference( LDAP *ld, LDAPMessage *chain )
{
	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( chain != NULL );

	return chain->lm_msgtype == LDAP_RES_SEARCH_REFERENCE
		? chain
		: ldap_next_reference( ld, chain );
}