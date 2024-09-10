/**
 * Attempt to discover the base DN for a server using LDAP version 3.
 * \param  ld  LDAP handle for a connected server.
 * \param  tov Timeout value (seconds), or 0 for none, default 30 secs.
 * \return List of Base DN's, or NULL if could not read. List should be
 *         g_free() when done.
 */
static GList *ldaputil_test_v3( LDAP *ld, gint tov ) {
	GList *baseDN = NULL;
	gint rc, i;
	LDAPMessage *result, *e;
	gchar *attribs[2];
	BerElement *ber;
	gchar *attribute;
	gchar **vals;
	struct timeval timeout;

	/* Set timeout */
	timeout.tv_usec = 0L;
	if( tov > 0 ) {
		timeout.tv_sec = tov;
	}
	else {
		timeout.tv_sec = 30L;
	}

	/* Test for LDAP version 3 */
	attribs[0] = SYLDAP_V3_TEST_ATTR;
	attribs[1] = NULL;
	rc = ldap_search_ext_s(
		ld, SYLDAP_SEARCHBASE_V3, LDAP_SCOPE_BASE, SYLDAP_TEST_FILTER,
		attribs, 0, NULL, NULL, &timeout, 0, &result );

	if( rc == LDAP_SUCCESS ) {
		/* Process entries */
		for( e = ldap_first_entry( ld, result );
		     e != NULL;
		     e = ldap_next_entry( ld, e ) ) 
		{
			/* Process attributes */
			for( attribute = ldap_first_attribute( ld, e, &ber );
			     attribute != NULL;
			     attribute = ldap_next_attribute( ld, e, ber ) )
			{
				if( strcasecmp(
					attribute, SYLDAP_V3_TEST_ATTR ) == 0 )
				{
					vals = ldap_get_values( ld, e, attribute );
					if( vals != NULL ) {
						for( i = 0; vals[i] != NULL; i++ ) {
							baseDN = g_list_append(
								baseDN, g_strdup( vals[i] ) );
						}
					}
					ldap_value_free( vals );
				}
				ldap_memfree( attribute );
			}
			if( ber != NULL ) {
				ber_free( ber, 0 );
			}
			ber = NULL;
		}
	}
	ldap_msgfree( result );
	return baseDN;
}