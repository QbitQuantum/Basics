static void
do_modrdn( char *uri, char *host, int port, char *manager,
	char *passwd, char *entry, int maxloop )
{
	LDAP	*ld = NULL;
	int  	i;
	pid_t	pid;
	char *DNs[2];
	char *rdns[2];

	pid = getpid();
	DNs[0] = entry;
	DNs[1] = strdup( entry );

	/* reverse the RDN, make new DN */
	{
		char *p1, *p2;

		p1 = strchr( entry, '=' ) + 1;
		p2 = strchr( p1, ',' );

		*p2 = '\0';
		rdns[1] = strdup( entry );
		*p2-- = ',';

		for (i = p1 - entry;p2 >= p1;)
			DNs[1][i++] = *p2--;
		
		DNs[1][i] = '\0';
		rdns[0] = strdup( DNs[1] );
		DNs[1][i] = ',';
	}
		
	if ( uri ) {
		ldap_initialize( &ld, uri );
	} else {
		ld = ldap_init( host, port );
	}
	if ( ld == NULL ) {
		perror( "ldap_init" );
		exit( EXIT_FAILURE );
	}

	{
		int version = LDAP_VERSION3;
		(void) ldap_set_option( ld, LDAP_OPT_PROTOCOL_VERSION,
			&version ); 
	}

	if ( ldap_bind_s( ld, manager, passwd, LDAP_AUTH_SIMPLE ) != LDAP_SUCCESS ) {
		ldap_perror( ld, "ldap_bind" );
		 exit( EXIT_FAILURE );
	}


	fprintf( stderr, "PID=%ld - Modrdn(%d): entry=\"%s\".\n",
		 (long) pid, maxloop, entry );

	for ( i = 0; i < maxloop; i++ ) {
		int         rc;

		if (( rc = ldap_modrdn2_s( ld, DNs[0], rdns[0], 0 ))
			!= LDAP_SUCCESS ) {
			ldap_perror( ld, "ldap_modrdn" );
			if ( rc != LDAP_NO_SUCH_OBJECT ) break;
			continue;
		}
		if (( rc = ldap_modrdn2_s( ld, DNs[1], rdns[1], 1 ))
			!= LDAP_SUCCESS ) {
			ldap_perror( ld, "ldap_modrdn" );
			if ( rc != LDAP_NO_SUCH_OBJECT ) break;
			continue;
		}
	}

	fprintf( stderr, " PID=%ld - Modrdn done.\n", (long) pid );

	ldap_unbind( ld );
}