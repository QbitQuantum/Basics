int
main( int argc, char **argv )
{
	char		*rbuf = NULL, *rejbuf = NULL;
	FILE		*rejfp;
	struct LDIFFP *ldiffp = NULL, ldifdummy = {0};
	char		*matched_msg, *error_msg;
	int		rc, retval, ldifrc;
	int		len;
	int		i = 0, lmax = 0;
	unsigned long	lineno, nextline = 0;
	LDAPControl	c[1];

	prog = lutil_progname( "ldapmodify", argc, argv );

	/* strncmp instead of strcmp since NT binaries carry .exe extension */
	ldapadd = ( strncasecmp( prog, "ldapadd", sizeof("ldapadd")-1 ) == 0 );

	tool_init( ldapadd ? TOOL_ADD : TOOL_MODIFY );

	tool_args( argc, argv );

	if ( argc != optind ) usage();

	if ( rejfile != NULL ) {
		if (( rejfp = fopen( rejfile, "w" )) == NULL ) {
			perror( rejfile );
			retval = EXIT_FAILURE;
			goto fail;
		}
	} else {
		rejfp = NULL;
	}

	if ( infile != NULL ) {
		if (( ldiffp = ldif_open( infile, "r" )) == NULL ) {
			perror( infile );
			retval = EXIT_FAILURE;
			goto fail;
		}
	} else {
		ldifdummy.fp = stdin;
		ldiffp = &ldifdummy;
	}

	if ( debug ) ldif_debug = debug;

	ld = tool_conn_setup( dont, 0 );

	if ( !dont ) {
		tool_bind( ld );
	}

#ifdef LDAP_X_TXN
	if( txn ) {
		/* start transaction */
		rc = ldap_txn_start_s( ld, NULL, NULL, &txn_id );
		if( rc != LDAP_SUCCESS ) {
			tool_perror( "ldap_txn_start_s", rc, NULL, NULL, NULL, NULL );
			if( txn > 1 ) {
				retval = EXIT_FAILURE;
				goto fail;
			}
			txn = 0;
		}
	}
#endif

	if ( 0
#ifdef LDAP_X_TXN
		|| txn
#endif
		)
	{
#ifdef LDAP_X_TXN
		if( txn ) {
			c[i].ldctl_oid = LDAP_CONTROL_X_TXN_SPEC;
			c[i].ldctl_value = *txn_id;
			c[i].ldctl_iscritical = 1;
			i++;
		}
#endif
	}

	tool_server_controls( ld, c, i );

	rc = 0;
	retval = 0;
	lineno = 1;
	while (( rc == 0 || contoper ) && ( ldifrc = ldif_read_record( ldiffp, &nextline,
		&rbuf, &lmax )) > 0 )
	{
		if ( rejfp ) {
			len = strlen( rbuf );
			if (( rejbuf = (char *)ber_memalloc( len+1 )) == NULL ) {
				perror( "malloc" );
				retval = EXIT_FAILURE;
				goto fail;
			}
			memcpy( rejbuf, rbuf, len+1 );
		}

		rc = process_ldif_rec( rbuf, lineno );
		lineno = nextline+1;

		if ( rc ) retval = rc;
		if ( rc && rejfp ) {
			fprintf(rejfp, _("# Error: %s (%d)"), ldap_err2string(rc), rc);

			matched_msg = NULL;
			ldap_get_option(ld, LDAP_OPT_MATCHED_DN, &matched_msg);
			if ( matched_msg != NULL ) {
				if ( *matched_msg != '\0' ) {
					fprintf( rejfp, _(", matched DN: %s"), matched_msg );
				}
				ldap_memfree( matched_msg );
			}

			error_msg = NULL;
			ldap_get_option(ld, LDAP_OPT_DIAGNOSTIC_MESSAGE, &error_msg);
			if ( error_msg != NULL ) {
				if ( *error_msg != '\0' ) {
					fprintf( rejfp, _(", additional info: %s"), error_msg );
				}
				ldap_memfree( error_msg );
			}
			fprintf( rejfp, "\n%s\n", rejbuf );
		}

		if (rejfp) ber_memfree( rejbuf );
	}
	ber_memfree( rbuf );

	if ( ldifrc < 0 )
		retval = LDAP_OTHER;

#ifdef LDAP_X_TXN
	if( retval == 0 && txn ) {
		rc = ldap_set_option( ld, LDAP_OPT_SERVER_CONTROLS, NULL );
		if ( rc != LDAP_OPT_SUCCESS ) {
			fprintf( stderr, "Could not unset controls for ldap_txn_end\n");
		}

		/* create transaction */
		rc = ldap_txn_end_s( ld, !txnabort, txn_id, NULL, NULL, NULL );
		if( rc != LDAP_SUCCESS ) {
			tool_perror( "ldap_txn_end_s", rc, NULL, NULL, NULL, NULL );
			retval = rc;
		}
	}
#endif

fail:;
	if ( rejfp != NULL ) {
		fclose( rejfp );
	}

	if ( ldiffp != NULL && ldiffp != &ldifdummy ) {
		ldif_close( ldiffp );
	}

	tool_exit( ld, retval );
}