int
main( int argc, char **argv )
{
    LDAP	    	*ld;
    LDAPMessage	    	*result, *e;
    BerElement	    	*ber;
    char	    	*host, *a, *dn;
    char	  	**vals;
    int		    	i;
    int		   	rc;
    int			finished;
    int			msgid;
    int			num_entries = 0;
    struct timeval	zerotime;

    if ( argc > 1 ) {
	host = argv[1];
    } else {
	host = MY_HOST;
    }

    zerotime.tv_sec = zerotime.tv_usec = 0L;

    if ( prldap_install_routines( NULL, 1 /* shared */ ) != LDAP_SUCCESS ) {
	ldap_perror( NULL, "prldap_install_routines" );
	return( 1 );
    }

    /* get a handle to an LDAP connection */
    if ( (ld = ldap_init( host, MY_PORT )) == NULL ) {
	perror( host );
	return( 1 );
    }

    /* authenticate to the directory as nobody */
    if ( ldap_simple_bind_s( ld, NULL, NULL ) != LDAP_SUCCESS ) {
	ldap_perror( ld, "ldap_simple_bind_s" );
	return( 1 );
    }
    /* search for all entries with surname of Jensen */
    if (( msgid = ldap_search( ld, MY_SEARCHBASE, LDAP_SCOPE_SUBTREE,
	    MY_FILTER, NULL, 0 )) < 0 ) {
	ldap_perror( ld, "ldap_search" );
	return( 1 );
    }

    /* Loop, polling for results until finished */
    finished = 0;
    while ( !finished ) {
	/*
	 * Poll for results.   We call ldap_result with the "all" argument
	 * set to LDAP_MSG_ONE.  This causes ldap_result() to return exactly one
	 * entry if at least one entry is available.  This allows us to
	 * display the entries as they are received.
	 */
	result = NULL;
	rc = ldap_result( ld, msgid, LDAP_MSG_ONE, &zerotime, &result );
	switch ( rc ) {
	case -1:
	    /* some error occurred */
	    ldap_perror( ld, "ldap_result" );
	    return( 1 );
	case 0:
	    /* Timeout was exceeded.  No entries are ready for retrieval. */
	    if ( result != NULL ) {
		ldap_msgfree( result );
	    }
	    break;
	default:
	    /*
	     * Either an entry is ready for retrieval, or all entries have
	     * been retrieved.
	     */
	    if (( e = ldap_first_entry( ld, result )) == NULL ) {
		/* All done */
		finished = 1;
		if ( result != NULL ) {
		    ldap_msgfree( result );
		}
		continue;
	    }
	    /* for each entry print out name + all attrs and values */
	    num_entries++;
	    if (( dn = ldap_get_dn( ld, e )) != NULL ) {
		printf( "dn: %s\n", dn );
		ldap_memfree( dn );
	    }
	    for ( a = ldap_first_attribute( ld, e, &ber );
		    a != NULL; a = ldap_next_attribute( ld, e, ber ) ) {
		if (( vals = ldap_get_values( ld, e, a )) != NULL ) {
		    for ( i = 0; vals[ i ] != NULL; i++ ) {
			printf( "%s: %s\n", a, vals[ i ] );
		    }
		    ldap_value_free( vals );
		}
		ldap_memfree( a );
	    }
	    if ( ber != NULL ) {
		ber_free( ber, 0 );
	    }
	    printf( "\n" );
	    ldap_msgfree( result );
	}
	/* Do other work here while you are waiting... */
	do_other_work();
    }

    /* All done.  Print a summary. */
    printf( "%d entries retrieved.  I counted to %ld "
	    "while I was waiting.\n", num_entries,
	    global_counter );
    ldap_unbind( ld );
    return( 0 );
}