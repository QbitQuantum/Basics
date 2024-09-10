static void
do_random( char *uri, char *manager, struct berval *passwd,
	char *sbase, int scope, char *filter, char *attr,
	char **srchattrs, int noattrs, int nobind,
	int innerloop, int maxretries, int delay, int force, int chaserefs )
{
	LDAP	*ld = NULL;
	int  	i = 0, do_retry = maxretries;
	char	*attrs[ 2 ];
	int     rc = LDAP_SUCCESS;
	int	version = LDAP_VERSION3;
	int	nvalues = 0;
	char	**values = NULL;
	LDAPMessage *res = NULL, *e = NULL;

	attrs[ 0 ] = attr;
	attrs[ 1 ] = NULL;

	ldap_initialize( &ld, uri );
	if ( ld == NULL ) {
		tester_perror( "ldap_initialize", NULL );
		exit( EXIT_FAILURE );
	}

	(void) ldap_set_option( ld, LDAP_OPT_PROTOCOL_VERSION, &version ); 
	(void) ldap_set_option( ld, LDAP_OPT_REFERRALS,
		chaserefs ? LDAP_OPT_ON : LDAP_OPT_OFF );

	if ( do_retry == maxretries ) {
		fprintf( stderr, "PID=%ld - Search(%d): base=\"%s\", filter=\"%s\" attr=\"%s\".\n",
				(long) pid, innerloop, sbase, filter, attr );
	}

	if ( nobind == 0 ) {
		rc = ldap_sasl_bind_s( ld, manager, LDAP_SASL_SIMPLE, passwd, NULL, NULL, NULL );
		if ( rc != LDAP_SUCCESS ) {
			tester_ldap_error( ld, "ldap_sasl_bind_s", NULL );
			switch ( rc ) {
			case LDAP_BUSY:
			case LDAP_UNAVAILABLE:
			/* fallthru */
			default:
				break;
			}
			exit( EXIT_FAILURE );
		}
	}

	rc = ldap_search_ext_s( ld, sbase, LDAP_SCOPE_SUBTREE,
		filter, attrs, 0, NULL, NULL, NULL, LDAP_NO_LIMIT, &res );
	switch ( rc ) {
	case LDAP_SIZELIMIT_EXCEEDED:
	case LDAP_TIMELIMIT_EXCEEDED:
	case LDAP_SUCCESS:
		if ( ldap_count_entries( ld, res ) == 0 ) {
			if ( rc ) {
				tester_ldap_error( ld, "ldap_search_ext_s", NULL );
			}
			break;
		}

		for ( e = ldap_first_entry( ld, res ); e != NULL; e = ldap_next_entry( ld, e ) )
		{
			struct berval **v = ldap_get_values_len( ld, e, attr );

			if ( v != NULL ) {
				int n = ldap_count_values_len( v );
				int j;

				values = realloc( values, ( nvalues + n + 1 )*sizeof( char * ) );
				for ( j = 0; j < n; j++ ) {
					values[ nvalues + j ] = strdup( v[ j ]->bv_val );
				}
				values[ nvalues + j ] = NULL;
				nvalues += n;
				ldap_value_free_len( v );
			}
		}

		ldap_msgfree( res );

		if ( !values ) {
			fprintf( stderr, "  PID=%ld - Search base=\"%s\" filter=\"%s\" got %d values.\n",
				(long) pid, sbase, filter, nvalues );
			exit(EXIT_FAILURE);
		}

		if ( do_retry == maxretries ) {
			fprintf( stderr, "  PID=%ld - Search base=\"%s\" filter=\"%s\" got %d values.\n",
				(long) pid, sbase, filter, nvalues );
		}

		for ( i = 0; i < innerloop; i++ ) {
			char	buf[ BUFSIZ ];
#if 0	/* use high-order bits for better randomness (Numerical Recipes in "C") */
			int	r = rand() % nvalues;
#endif
			int	r = ((double)nvalues)*rand()/(RAND_MAX + 1.0);

			snprintf( buf, sizeof( buf ), "(%s=%s)", attr, values[ r ] );

			do_search( uri, manager, passwd,
				sbase, scope, buf, &ld,
				srchattrs, noattrs, nobind,
				1, maxretries, delay, force, chaserefs );
		}
		break;

	default:
		tester_ldap_error( ld, "ldap_search_ext_s", NULL );
		break;
	}

	fprintf( stderr, "  PID=%ld - Search done (%d).\n", (long) pid, rc );

	if ( ld != NULL ) {
		ldap_unbind_ext( ld, NULL, NULL );
	}
}