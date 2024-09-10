struct tester_conn_args *
tester_init( const char *pname, tester_t ptype )
{
	static struct tester_conn_args config = {
		.authmethod = -1,
		.retries = RETRIES,
		.loops = LOOPS,
		.outerloops = 1,

		.uri = NULL,
		.host = "localhost",
		.port = 389,
	};

	pid = getpid();
	srand( pid );
	snprintf( progname, sizeof( progname ), "%s PID=%d", pname, pid );
	progtype = ptype;

	return &config;
}

void
tester_ldap_error( LDAP *ld, const char *fname, const char *msg )
{
	int		err;
	char		*text = NULL;
	LDAPControl	**ctrls = NULL;

	ldap_get_option( ld, LDAP_OPT_RESULT_CODE, (void *)&err );
	if ( err != LDAP_SUCCESS ) {
		ldap_get_option( ld, LDAP_OPT_DIAGNOSTIC_MESSAGE, (void *)&text );
	}

	fprintf( stderr, "%s: %s: %s (%d) %s %s\n",
		progname, fname, ldap_err2string( err ), err,
		text == NULL ? "" : text,
		msg ? msg : "" );

	if ( text ) {
		ldap_memfree( text );
		text = NULL;
	}

	ldap_get_option( ld, LDAP_OPT_MATCHED_DN, (void *)&text );
	if ( text != NULL ) {
		if ( text[ 0 ] != '\0' ) {
			fprintf( stderr, "\tmatched: %s\n", text );
		}
		ldap_memfree( text );
		text = NULL;
	}

	ldap_get_option( ld, LDAP_OPT_SERVER_CONTROLS, (void *)&ctrls );
	if ( ctrls != NULL ) {
		int	i;

		fprintf( stderr, "\tcontrols:\n" );
		for ( i = 0; ctrls[ i ] != NULL; i++ ) {
			fprintf( stderr, "\t\t%s\n", ctrls[ i ]->ldctl_oid );
		}
		ldap_controls_free( ctrls );
		ctrls = NULL;
	}

	if ( err == LDAP_REFERRAL ) {
		char **refs = NULL;

		ldap_get_option( ld, LDAP_OPT_REFERRAL_URLS, (void *)&refs );

		if ( refs ) {
			int	i;

			fprintf( stderr, "\treferral:\n" );
			for ( i = 0; refs[ i ] != NULL; i++ ) {
				fprintf( stderr, "\t\t%s\n", refs[ i ] );
			}

			ber_memvfree( (void **)refs );
		}
	}
}