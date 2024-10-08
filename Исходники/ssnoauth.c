int
main( int argc, char **argv )
{
	LDAP		*ld;
	LDAPMessage	*result, *e;
	BerElement	*ber;
	char		*a, *dn;
	char		**vals;
	int		i;

	/* Initialize the client */
	if ( ldapssl_client_init( MY_CERTDB_PATH, NULL ) < 0 ) {
		perror( "ldapssl_client_init" );
		return( 1 );
	}

	/* set the max I/O timeout option to 10 seconds */
	if ( prldap_set_session_option( NULL, NULL, PRLDAP_OPT_IO_MAX_TIMEOUT,
	    10000 /* 10 secs */ ) != LDAP_SUCCESS ) {
		ldap_perror( NULL,
		    "prldap_set_session_option PRLDAP_OPT_IO_MAX_TIMEOUT" );
		exit( 1 );
	}

	/* get a handle to an LDAP connection */
	if ( (ld = ldapssl_init( MY_HOST, MY_SSL_PORT, 1 )) == NULL ) {
		perror( "ldapssl_init" );
		return( 1 );
	}

	/* use LDAPv3 */
	i = LDAP_VERSION3;
	if ( ldap_set_option( ld, LDAP_OPT_PROTOCOL_VERSION, &i ) < 0 ) {
		ldap_perror( ld, "ldap_set_option LDAPv3" );
		ldap_unbind( ld );
		return( 1 );
	}

	/* search for all entries with surname of Jensen */
	if ( ldap_search_s( ld, PEOPLE_BASE, LDAP_SCOPE_SUBTREE,
		"(sn=jensen)", NULL, 0, &result ) != LDAP_SUCCESS ) {
		ldap_perror( ld, "ldap_search_s" );
		if ( result == NULL ) {
			ldap_unbind( ld );
			return( 1 );
		}
	}
	/* for each entry print out name + all attrs and values */
	for ( e = ldap_first_entry( ld, result ); e != NULL;
	    e = ldap_next_entry( ld, e ) ) {
		if ( (dn = ldap_get_dn( ld, e )) != NULL ) {
		    printf( "dn: %s\n", dn );
		    ldap_memfree( dn );
		}
		for ( a = ldap_first_attribute( ld, e, &ber );
		    a != NULL; a = ldap_next_attribute( ld, e, ber ) ) {
			if ((vals = ldap_get_values( ld, e, a)) != NULL ) {
				for ( i = 0; vals[i] != NULL; i++ ) {
				    printf( "%s: %s\n", a, vals[i] );
				}
				ldap_value_free( vals );
			}
			ldap_memfree( a );
		}
		if ( ber != NULL ) {
			ber_free( ber, 0 );
		}
		printf( "\n" );
	}
	ldap_msgfree( result );
	ldap_unbind( ld );
	return( 0 );
}