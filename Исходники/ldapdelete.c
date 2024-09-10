/*
 * Delete all the children of an entry recursively until leaf nodes are reached.
 */
static int deletechildren(
	LDAP *ld,
	const char *base,
	int subentries )
{
	LDAPMessage *res, *e;
	int entries;
	int rc = LDAP_SUCCESS, srch_rc;
	static char *attrs[] = { LDAP_NO_ATTRS, NULL };
	LDAPControl c, *ctrls[2], **ctrlsp = NULL;
	BerElement *ber = NULL;

	if ( verbose ) printf ( _("deleting children of: %s\n"), base );

	if ( subentries ) {
		/*
		 * Do a one level search at base for subentry children.
		 */

		if ((ber = ber_alloc_t(LBER_USE_DER)) == NULL) {
			return EXIT_FAILURE;
		}
		rc = ber_printf( ber, "b", 1 );
		if ( rc == -1 ) {
			ber_free( ber, 1 );
			fprintf( stderr, _("Subentries control encoding error!\n"));
			return EXIT_FAILURE;
		}
		if ( ber_flatten2( ber, &c.ldctl_value, 0 ) == -1 ) {
			return EXIT_FAILURE;
		}
		c.ldctl_oid = LDAP_CONTROL_SUBENTRIES;
		c.ldctl_iscritical = 1;
		ctrls[0] = &c;
		ctrls[1] = NULL;
		ctrlsp = ctrls;
	}

	/*
	 * Do a one level search at base for children.  For each, delete its children.
	 */
more:;
	srch_rc = ldap_search_ext_s( ld, base, LDAP_SCOPE_ONELEVEL, NULL, attrs, 1,
		ctrlsp, NULL, NULL, sizelimit, &res );
	switch ( srch_rc ) {
	case LDAP_SUCCESS:
	case LDAP_SIZELIMIT_EXCEEDED:
		break;
	default:
		tool_perror( "ldap_search", srch_rc, NULL, NULL, NULL, NULL );
		return( srch_rc );
	}

	entries = ldap_count_entries( ld, res );

	if ( entries > 0 ) {
		int i;

		for (e = ldap_first_entry( ld, res ), i = 0; e != NULL;
			e = ldap_next_entry( ld, e ), i++ )
		{
			char *dn = ldap_get_dn( ld, e );

			if( dn == NULL ) {
				ldap_get_option( ld, LDAP_OPT_RESULT_CODE, &rc );
				tool_perror( "ldap_prune", rc, NULL, NULL, NULL, NULL );
				ber_memfree( dn );
				return rc;
			}

			rc = deletechildren( ld, dn, 0 );
			if ( rc != LDAP_SUCCESS ) {
				tool_perror( "ldap_prune", rc, NULL, NULL, NULL, NULL );
				ber_memfree( dn );
				return rc;
			}

			if ( verbose ) {
				printf( _("\tremoving %s\n"), dn );
			}

			rc = ldap_delete_ext_s( ld, dn, NULL, NULL );
			if ( rc != LDAP_SUCCESS ) {
				tool_perror( "ldap_delete", rc, NULL, NULL, NULL, NULL );
				ber_memfree( dn );
				return rc;

			}
			
			if ( verbose ) {
				printf( _("\t%s removed\n"), dn );
			}

			ber_memfree( dn );
		}
	}

	ldap_msgfree( res );

	if ( srch_rc == LDAP_SIZELIMIT_EXCEEDED ) {
		goto more;
	}

	return rc;
}