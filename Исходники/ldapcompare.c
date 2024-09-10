static int docompare(
	LDAP *ld,
	char *dn,
	char *attr,
	struct berval *bvalue,
	int quiet,
	LDAPControl **sctrls,
	LDAPControl **cctrls )
{
	int		rc, msgid, code;
	LDAPMessage	*res;
	char		*matcheddn;
	char		*text;
	char		**refs;
	LDAPControl **ctrls = NULL;

	if ( dont ) {
		return LDAP_SUCCESS;
	}

	rc = ldap_compare_ext( ld, dn, attr, bvalue,
		sctrls, cctrls, &msgid );
	if ( rc == -1 ) {
		return( rc );
	}

	for ( ; ; ) {
		struct timeval	tv;

		tv.tv_sec = 0;
		tv.tv_usec = 100000;

		if ( tool_check_abandon( ld, msgid ) ) {
			return LDAP_CANCELLED;
		}

		rc = ldap_result( ld, LDAP_RES_ANY, LDAP_MSG_ALL, &tv, &res );
		if ( rc < 0 ) {
			tool_perror( "ldap_result", rc, NULL, NULL, NULL, NULL );
			return rc;
		}

		if ( rc != 0 ) {
			break;
		}
	}

	rc = ldap_parse_result( ld, res, &code, &matcheddn, &text, &refs, &ctrls, 1 );

	if( rc != LDAP_SUCCESS ) {
		fprintf( stderr, "%s: ldap_parse_result: %s (%d)\n",
			prog, ldap_err2string( rc ), rc );
		return rc;
	}

	if ( !quiet && ( verbose || ( code != LDAP_SUCCESS && code != LDAP_COMPARE_TRUE && code != LDAP_COMPARE_FALSE )||
		(matcheddn && *matcheddn) || (text && *text) || (refs && *refs) ) )
	{
		printf( _("Compare Result: %s (%d)\n"),
			ldap_err2string( code ), code );

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
	}

	/* if we were told to be quiet, use the return value. */
	if ( !quiet ) {
		if ( code == LDAP_COMPARE_TRUE ) {
			printf(_("TRUE\n"));
		} else if ( code == LDAP_COMPARE_FALSE ) {
			printf(_("FALSE\n"));
		} else {
			printf(_("UNDEFINED\n"));
		}
	}

	if ( ctrls ) {
		tool_print_ctrls( ld, ctrls );
		ldap_controls_free( ctrls );
	}

	ber_memfree( text );
	ber_memfree( matcheddn );
	ber_memvfree( (void **) refs );

	return( code );
}