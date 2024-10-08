int
main( int argc, char **argv )
{
    LDAP	    	*ld;
    LDAPMessage	    	*result, *e;
    BerElement	    	*ber;
    char	    	*a, *dn;
    char	  	**vals;
    int		    	i;
    int		   	rc;
    int			finished;
    int			msgid;
    int			num_entries = 0;
    int			version = LDAP_VERSION3;
    LDAPControl		*ctrls[2], *psctrl, **ectrls;

    /* arrange to use LDAP version 3 */
    if ( ldap_set_option( NULL, LDAP_OPT_PROTOCOL_VERSION, &version ) != 0 ) {
	perror( "ldap_set_option" );
	return( 1 );
    }

    /* get a handle to an LDAP connection */
    if ( (ld = ldap_init( MY_HOST, MY_PORT )) == NULL ) {
	perror( "ldap_init" );
	return( 1 );
    }

    /* authenticate to the directory as nobody */
    if ( ldap_simple_bind_s( ld, NULL, NULL ) != LDAP_SUCCESS ) {
	ldap_perror( ld, "ldap_simple_bind_s" );
	ldap_unbind( ld );
	return( 1 );
    }

    /* construct the Persistent Search control */
    if ( ldap_create_persistentsearch_control( ld, LDAP_CHANGETYPE_ANY,
		1 /* changesOnly */, 1 /* request entry change controls */,
		1 /* critical */, &psctrl ) != LDAP_SUCCESS ) {
	ldap_perror( ld, "ldap_create_persistentsearch_control" );
	ldap_unbind( ld );
	return( 1 );
    }
    ctrls[0] = psctrl;
    ctrls[1] = NULL;

    /* issue a persistent search for all entries with surname of Jensen */
    if ( LDAP_SUCCESS != ldap_search_ext( ld, MY_SEARCHBASE,
	    LDAP_SCOPE_SUBTREE, MY_FILTER, NULL /* all attrs */,
	    0 /* get attrs and values */, ctrls, NULL /* no client ctrls */,
	    NULL /* no timeout */, 0 /* no sizelimit */, &msgid )) {
	ldap_perror( ld, "ldap_search_ext" );
	ldap_unbind( ld );
	return( 1 );
    }

    ldap_control_free( psctrl );	/* no longer needed */

    /*
     * Loop, polling for results until finished.
     * Since this is a persistent search, this loop won't end until the
     * server shuts down or we lose the connection for some other reason.
     * We could abandon the persistent search or close the connection of
     * course, but we don't in this example.
     */
    finished = 0;
    while ( !finished ) {
	/*
	 * Poll for results.   We call ldap_result with the "all" argument
	 * set to LDAP_MSG_ONE.  This causes ldap_result() to return exactly one
	 * entry if at least one entry is available.  This allows us to
	 * display the entries as they are received.
	 */
	result = NULL;
	rc = ldap_result( ld, msgid, LDAP_MSG_ONE, NULL /* no timeout */, &result );
	switch ( rc ) {
	case -1:
	    /* some error occurred */
	    ldap_perror( ld, "ldap_result" );
	    ldap_unbind( ld );
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
	    num_entries++;

	    /* for each entry print out name */
	    if (( dn = ldap_get_dn( ld, e )) != NULL ) {
		printf( "dn: %s\n", dn );
		ldap_memfree( dn );
	    }

	    /* print entry change info. if it was returned */
	    if ( LDAP_SUCCESS == ldap_get_entry_controls( ld, e, &ectrls )) {
		int         chgnumpresent;
        ber_int_t   chgtype;
		ber_int_t   chgnum;
		char        *prevdn;

		if ( LDAP_SUCCESS == ldap_parse_entrychange_control( ld,
			ectrls, &chgtype, &prevdn, &chgnumpresent, &chgnum )) {
		    printf( "changeType: %s\n",
			    changetype_num2string( chgtype ));
		    if ( prevdn != NULL ) {
			printf( "previousDN: %s\n", prevdn );
			ldap_memfree( prevdn );
		    }
		    if ( chgnumpresent ) {
			printf( "changeNumber: %d\n", chgnum );
		    }
		    ldap_controls_free( ectrls );
		}
	    }

	    /* print out all attrs and values */
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
    }

    /* All done.  Print a summary. */
    printf( "%d entries retrieved.\n", num_entries );
    ldap_unbind( ld );
    return( 0 );
}