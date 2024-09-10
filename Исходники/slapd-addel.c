static void
do_addel(
	char *uri,
	char *manager,
	struct berval *passwd,
	char *entry,
	LDAPMod **attrs,
	int maxloop,
	int maxretries,
	int delay,
	int friendly,
	int chaserefs )
{
	LDAP	*ld = NULL;
	int  	i = 0, do_retry = maxretries;
	int	rc = LDAP_SUCCESS;
	int	version = LDAP_VERSION3;

retry:;
	ldap_initialize( &ld, uri );
	if ( ld == NULL ) {
		tester_perror( "ldap_initialize", NULL );
		exit( EXIT_FAILURE );
	}

	(void) ldap_set_option( ld, LDAP_OPT_PROTOCOL_VERSION, &version );
	(void) ldap_set_option( ld, LDAP_OPT_REFERRALS,
		chaserefs ? LDAP_OPT_ON : LDAP_OPT_OFF );

	if ( do_retry == maxretries ) {
		fprintf( stderr, "PID=%ld - Add/Delete(%d): entry=\"%s\".\n",
			(long) pid, maxloop, entry );
	}

	rc = ldap_sasl_bind_s( ld, manager, LDAP_SASL_SIMPLE, passwd, NULL, NULL, NULL );
	if ( rc != LDAP_SUCCESS ) {
		tester_ldap_error( ld, "ldap_sasl_bind_s", NULL );
		switch ( rc ) {
		case LDAP_BUSY:
		case LDAP_UNAVAILABLE:
			if ( do_retry > 0 ) {
				do_retry--;
				if ( delay != 0 ) {
				    sleep( delay );
				}
				goto retry;
			}
		/* fallthru */
		default:
			break;
		}
		exit( EXIT_FAILURE );
	}

	for ( ; i < maxloop; i++ ) {

		/* add the entry */
		rc = ldap_add_ext_s( ld, entry, attrs, NULL, NULL );
		if ( rc != LDAP_SUCCESS ) {
			tester_ldap_error( ld, "ldap_add_ext_s", NULL );
			switch ( rc ) {
			case LDAP_ALREADY_EXISTS:
				/* NOTE: this likely means
				 * the delete failed
				 * during the previous round... */
				if ( !friendly ) {
					goto done;
				}
				break;

			case LDAP_BUSY:
			case LDAP_UNAVAILABLE:
				if ( do_retry > 0 ) {
					do_retry--;
					goto retry;
				}
				/* fall thru */

			default:
				goto done;
			}
		}

#if 0
		/* wait a second for the add to really complete */
		/* This masks some race conditions though. */
		sleep( 1 );
#endif

		/* now delete the entry again */
		rc = ldap_delete_ext_s( ld, entry, NULL, NULL );
		if ( rc != LDAP_SUCCESS ) {
			tester_ldap_error( ld, "ldap_delete_ext_s", NULL );
			switch ( rc ) {
			case LDAP_NO_SUCH_OBJECT:
				/* NOTE: this likely means
				 * the add failed
				 * during the previous round... */
				if ( !friendly ) {
					goto done;
				}
				break;

			case LDAP_BUSY:
			case LDAP_UNAVAILABLE:
				if ( do_retry > 0 ) {
					do_retry--;
					goto retry;
				}
				/* fall thru */

			default:
				goto done;
			}
		}
	}

done:;
	fprintf( stderr, "  PID=%ld - Add/Delete done (%d).\n", (long) pid, rc );

	ldap_unbind_ext( ld, NULL, NULL );
}