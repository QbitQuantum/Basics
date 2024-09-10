int
main( int argc, char *argv[] )
{
	int		rc;
	LDAP		*ld = NULL;
	char		*matcheddn = NULL, *text = NULL, **refs = NULL;
	int rcode;
	char * diag = NULL;
	struct berval	*scookie = NULL;
	struct berval	*scred = NULL;
	int		id, code = 0;
	LDAPMessage	*res;
	LDAPControl	**ctrls = NULL;
	LDAPControl	**vcctrls = NULL;
	int nvcctrls = 0;

	tool_init( TOOL_VC );
	prog = lutil_progname( "ldapvc", argc, argv );

	/* LDAPv3 only */
	protocol = LDAP_VERSION3;

	tool_args( argc, argv );

	if (argc - optind > 0) {
		dn = argv[optind++];
	}
	if (argc - optind > 0) {
		cred.bv_val = strdup(argv[optind++]);
		cred.bv_len = strlen(cred.bv_val);
	}
	if (argc - optind > 0) {
		usage();
	}
	if (dn 
#ifdef LDAP_API_FEATURE_VERIFY_CREDENTIALS_INTERACTIVE
           && !vc_sasl_mech 
#endif
           && !cred.bv_val)
	{
		cred.bv_val = strdup(getpassphrase(_("User's password: "******"ldap_verify_credentials_interactive", rc, NULL, NULL, text, NULL);
				ldap_memfree(text);
				tool_exit(ld, rc);
			}
		} while (rc == LDAP_SASL_BIND_IN_PROGRESS);

	    lutil_sasl_freedefs(defaults);

	    if( rc != LDAP_SUCCESS ) {
			ldap_get_option(ld, LDAP_OPT_DIAGNOSTIC_MESSAGE, (void*) &text);
		    tool_perror( "ldap_verify_credentials", rc, NULL, NULL, text, NULL );
		    rc = EXIT_FAILURE;
		    goto skip;
	    }

	} else
#endif
#endif
    {
	    rc = ldap_verify_credentials( ld,
		    NULL,
		    dn, NULL, cred.bv_val ? &cred: NULL, vcctrls,
		    NULL, NULL, &id ); 
    
	    if( rc != LDAP_SUCCESS ) {
			ldap_get_option(ld, LDAP_OPT_DIAGNOSTIC_MESSAGE, (void*) &text);
		    tool_perror( "ldap_verify_credentials", rc, NULL, NULL, text, NULL );
		    rc = EXIT_FAILURE;
		    goto skip;
	    }

	    for ( ; ; ) {
		    struct timeval	tv;

		    if ( tool_check_abandon( ld, id ) ) {
			    tool_exit( ld, LDAP_CANCELLED );
		    }

		    tv.tv_sec = 0;
		    tv.tv_usec = 100000;

		    rc = ldap_result( ld, LDAP_RES_ANY, LDAP_MSG_ALL, &tv, &res );
		    if ( rc < 0 ) {
			    tool_perror( "ldap_result", rc, NULL, NULL, NULL, NULL );
			    tool_exit( ld, rc );
		    }

		    if ( rc != 0 ) {
			    break;
		    }
	    }
	}

	ldap_controls_free(vcctrls);
	vcctrls = NULL;

	rc = ldap_parse_result( ld, res,
		&code, &matcheddn, &text, &refs, &ctrls, 0 );

	if (rc == LDAP_SUCCESS) rc = code;

	if (rc != LDAP_SUCCESS) {
		tool_perror( "ldap_parse_result", rc, NULL, matcheddn, text, refs );
		rc = EXIT_FAILURE;
		goto skip;
	}

	rc = ldap_parse_verify_credentials( ld, res, &rcode, &diag, &scookie, &scred, &vcctrls );
	ldap_msgfree(res);

	if (rc != LDAP_SUCCESS) {
		tool_perror( "ldap_parse_verify_credentials", rc, NULL, NULL, NULL, NULL );
		rc = EXIT_FAILURE;
		goto skip;
	}

	if (rcode != LDAP_SUCCESS) {
		printf(_("Failed: %s (%d)\n"), ldap_err2string(rcode), rcode);
	}

	if (diag && *diag) {
	    printf(_("Diagnostic: %s\n"), diag);
	}

	if (vcctrls) {
		tool_print_ctrls( ld, vcctrls );
	}

skip:
	if ( verbose || code != LDAP_SUCCESS ||
		( matcheddn && *matcheddn ) || ( text && *text ) || refs || ctrls )
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
	ber_bvfree( scookie );
	ber_bvfree( scred );
	ber_memfree( diag );
	free( cred.bv_val );

	/* disconnect from server */
	tool_exit( ld, code == LDAP_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE );
}