/*
 * handle the LDAP_RES_INTERMEDIATE response
 */
static int
ldap_sync_search_intermediate( ldap_sync_t *ls, LDAPMessage *res, int *refreshDone )
{
	int			rc;
	char			*retoid = NULL;
        struct berval		*retdata = NULL;
	BerElement		*ber = NULL;
	ber_len_t		len;
	ber_tag_t		syncinfo_tag;
	struct berval		cookie;
	int			refreshDeletes = 0;
	BerVarray		syncUUIDs = NULL;
	ldap_sync_refresh_t	phase;

#ifdef LDAP_SYNC_TRACE
	fprintf( stderr, "\tgot LDAP_RES_INTERMEDIATE\n" );
#endif /* LDAP_SYNC_TRACE */

	assert( ls != NULL );
	assert( res != NULL );
	assert( refreshDone != NULL );

	*refreshDone = 0;

	rc = ldap_parse_intermediate( ls->ls_ld, res,
		&retoid, &retdata, NULL, 0 );
#ifdef LDAP_SYNC_TRACE
	fprintf( stderr, "\t%sldap_parse_intermediate(%s) == %d\n",
		rc != LDAP_SUCCESS ? "!!! " : "",
		retoid == NULL ? "\"\"" : retoid,
		rc );
#endif /* LDAP_SYNC_TRACE */
	/* parsing must be successful, and yield the OID
	 * of the sync info intermediate response */
	if ( rc != LDAP_SUCCESS ) {
		goto done;
	}

	rc = LDAP_OTHER;

	if ( retoid == NULL || strcmp( retoid, LDAP_SYNC_INFO ) != 0 ) {
		goto done;
	}

	/* init ber using the value in the response */
	ber = ber_init( retdata );
	if ( ber == NULL ) {
		goto done;
	}

	syncinfo_tag = ber_peek_tag( ber, &len );
	switch ( syncinfo_tag ) {
	case LDAP_TAG_SYNC_NEW_COOKIE:
		if ( ber_scanf( ber, "m", &cookie ) == LBER_ERROR ) {
			goto done;
		}
		if ( cookie.bv_val != NULL ) {
			ber_bvreplace( &ls->ls_cookie, &cookie );
		}
#ifdef LDAP_SYNC_TRACE
		fprintf( stderr, "\t\tgot cookie=%s\n",
			cookie.bv_val ? cookie.bv_val : "(null)" );
#endif /* LDAP_SYNC_TRACE */
		break;

	case LDAP_TAG_SYNC_REFRESH_DELETE:
	case LDAP_TAG_SYNC_REFRESH_PRESENT:
		if ( syncinfo_tag == LDAP_TAG_SYNC_REFRESH_DELETE ) {
#ifdef LDAP_SYNC_TRACE
			fprintf( stderr, "\t\tgot refreshDelete\n" );
#endif /* LDAP_SYNC_TRACE */
			switch ( ls->ls_refreshPhase ) {
			case LDAP_SYNC_CAPI_NONE:
			case LDAP_SYNC_CAPI_PRESENTS:
				ls->ls_refreshPhase = LDAP_SYNC_CAPI_DELETES;
				break;

			default:
				/* TODO: impossible; handle */
				goto done;
			}

		} else {
#ifdef LDAP_SYNC_TRACE
			fprintf( stderr, "\t\tgot refreshPresent\n" );
#endif /* LDAP_SYNC_TRACE */
			switch ( ls->ls_refreshPhase ) {
			case LDAP_SYNC_CAPI_NONE:
				ls->ls_refreshPhase = LDAP_SYNC_CAPI_PRESENTS;
				break;

			default:
				/* TODO: impossible; handle */
				goto done;
			}
		}

		if ( ber_scanf( ber, "{" /*"}"*/ ) == LBER_ERROR ) {
			goto done;
		}
		if ( ber_peek_tag( ber, &len ) == LDAP_TAG_SYNC_COOKIE ) {
			if ( ber_scanf( ber, "m", &cookie ) == LBER_ERROR ) {
				goto done;
			}
			if ( cookie.bv_val != NULL ) {
				ber_bvreplace( &ls->ls_cookie, &cookie );
			}
#ifdef LDAP_SYNC_TRACE
			fprintf( stderr, "\t\tgot cookie=%s\n",
				cookie.bv_val ? cookie.bv_val : "(null)" );
#endif /* LDAP_SYNC_TRACE */
		}

		*refreshDone = 1;
		if ( ber_peek_tag( ber, &len ) == LDAP_TAG_REFRESHDONE ) {
			if ( ber_scanf( ber, "b", refreshDone ) == LBER_ERROR ) {
				goto done;
			}
		}

#ifdef LDAP_SYNC_TRACE
		fprintf( stderr, "\t\tgot refreshDone=%s\n",
			*refreshDone ? "TRUE" : "FALSE" );
#endif /* LDAP_SYNC_TRACE */

		if ( ber_scanf( ber, /*"{"*/ "}" ) == LBER_ERROR ) {
			goto done;
		}

		if ( *refreshDone ) {
			ls->ls_refreshPhase = LDAP_SYNC_CAPI_DONE;
		}

		if ( ls->ls_intermediate ) {
			ls->ls_intermediate( ls, res, NULL, ls->ls_refreshPhase );
		}

		break;

	case LDAP_TAG_SYNC_ID_SET:
#ifdef LDAP_SYNC_TRACE
		fprintf( stderr, "\t\tgot syncIdSet\n" );
#endif /* LDAP_SYNC_TRACE */
		if ( ber_scanf( ber, "{" /*"}"*/ ) == LBER_ERROR ) {
			goto done;
		}
		if ( ber_peek_tag( ber, &len ) == LDAP_TAG_SYNC_COOKIE ) {
			if ( ber_scanf( ber, "m", &cookie ) == LBER_ERROR ) {
				goto done;
			}
			if ( cookie.bv_val != NULL ) {
				ber_bvreplace( &ls->ls_cookie, &cookie );
			}
#ifdef LDAP_SYNC_TRACE
			fprintf( stderr, "\t\tgot cookie=%s\n",
				cookie.bv_val ? cookie.bv_val : "(null)" );
#endif /* LDAP_SYNC_TRACE */
		}

		if ( ber_peek_tag( ber, &len ) == LDAP_TAG_REFRESHDELETES ) {
			if ( ber_scanf( ber, "b", &refreshDeletes ) == LBER_ERROR ) {
				goto done;
			}
		}

		if ( ber_scanf( ber, /*"{"*/ "[W]}", &syncUUIDs ) == LBER_ERROR
			|| syncUUIDs == NULL )
		{
			goto done;
		}

#ifdef LDAP_SYNC_TRACE
		{
			int	i;

			fprintf( stderr, "\t\tgot refreshDeletes=%s\n",
				refreshDeletes ? "TRUE" : "FALSE" );
			for ( i = 0; syncUUIDs[ i ].bv_val != NULL; i++ ) {
				char	buf[ BUFSIZ ];
				fprintf( stderr, "\t\t%s\n", 
					lutil_uuidstr_from_normalized(
						syncUUIDs[ i ].bv_val, syncUUIDs[ i ].bv_len,
						buf, sizeof( buf ) ) );
			}
		}
#endif /* LDAP_SYNC_TRACE */

		if ( refreshDeletes ) {
			phase = LDAP_SYNC_CAPI_DELETES_IDSET;

		} else {
			phase = LDAP_SYNC_CAPI_PRESENTS_IDSET;
		}

		/* FIXME: should touch ls->ls_refreshPhase? */
		if ( ls->ls_intermediate ) {
			ls->ls_intermediate( ls, res, syncUUIDs, phase );
		}

		ber_bvarray_free( syncUUIDs );
		break;

	default:
#ifdef LDAP_SYNC_TRACE
		fprintf( stderr, "\t\tunknown tag!\n" );
#endif /* LDAP_SYNC_TRACE */
		goto done;
	}

	rc = LDAP_SUCCESS;

done:;
	if ( ber != NULL ) {
		ber_free( ber, 1 );
	}

	if ( retoid != NULL ) {
		ldap_memfree( retoid );
	}

	if ( retdata != NULL ) {
		ber_bvfree( retdata );
	}

	return rc;
}