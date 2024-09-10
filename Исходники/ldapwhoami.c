int
main( int argc, char *argv[] )
{
	int		rc;
	LDAP		*ld = NULL;
	char		*matcheddn = NULL, *text = NULL, **refs = NULL;
	char		*retoid = NULL;
	struct berval	*retdata = NULL;
	int		id, code = 0;
	LDAPMessage	*res;
	LDAPControl	**ctrls = NULL;

	tool_init( TOOL_WHOAMI );
	prog = lutil_progname( "ldapwhoami", argc, argv );

	/* LDAPv3 only */
	protocol = LDAP_VERSION3;

	tool_args( argc, argv );

	if( argc - optind > 0 ) {
		usage();
	}

	if ( pw_file || want_bindpw ) {
		if ( pw_file ) {
			rc = lutil_get_filed_password( pw_file, &passwd );
			if( rc ) return EXIT_FAILURE;
		} else {
			passwd.bv_val = getpassphrase( _("Enter LDAP Password: "******"ldap_whoami", rc, NULL, NULL, NULL, NULL );
		rc = EXIT_FAILURE;
		goto skip;
	}

	for ( ; ; ) {
		struct timeval	tv;

		if ( tool_check_abandon( ld, id ) ) {
			return LDAP_CANCELLED;
		}

		tv.tv_sec = 0;
		tv.tv_usec = 100000;

		rc = ldap_result( ld, LDAP_RES_ANY, LDAP_MSG_ALL, &tv, &res );
		if ( rc < 0 ) {
			tool_perror( "ldap_result", rc, NULL, NULL, NULL, NULL );
			return rc;
		}

		if ( rc != 0 ) {
			break;
		}
	}

	rc = ldap_parse_result( ld, res,
		&code, &matcheddn, &text, &refs, &ctrls, 0 );

	if ( rc == LDAP_SUCCESS ) {
		rc = code;
	}

	if ( rc != LDAP_SUCCESS ) {
		tool_perror( "ldap_parse_result", rc, NULL, matcheddn, text, refs );
		rc = EXIT_FAILURE;
		goto skip;
	}

	rc = ldap_parse_extended_result( ld, res, &retoid, &retdata, 1 );

	if( rc != LDAP_SUCCESS ) {
		tool_perror( "ldap_parse_extended_result", rc, NULL, NULL, NULL, NULL );
		rc = EXIT_FAILURE;
		goto skip;
	}

	if( retdata != NULL ) {
		if( retdata->bv_len == 0 ) {
			printf(_("anonymous\n") );
		} else {
			printf("%s\n", retdata->bv_val );
		}
	}

skip:
	if ( verbose || ( code != LDAP_SUCCESS ) ||
		matcheddn || text || refs || ctrls )
	{
		printf( _("Result: %s (%d)\n"), ldap_err2string( code ), code );

		if( text && *text ) {
			printf( _("Additional info: %s\n"), text );
		}

		if( matcheddn && *matcheddn ) {
			printf( _("Matched DN: %s\n"), matcheddn );
		}

		if( refs ) {
			int i;
			for( i=0; refs[i]; i++ ) {
				printf(_("Referral: %s\n"), refs[i] );
			}
		}

		if (ctrls) {
			tool_print_ctrls( ld, ctrls );
			ldap_controls_free( ctrls );
		}
	}

	ber_memfree( text );
	ber_memfree( matcheddn );
	ber_memvfree( (void **) refs );
	ber_memfree( retoid );
	ber_bvfree( retdata );

	/* disconnect from server */
	tool_unbind( ld );
	tool_destroy();

	return code == LDAP_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
}