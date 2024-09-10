int
ldap_create_sort_control_value(
	LDAP *ld,
	LDAPSortKey **keyList,
	struct berval *value )
{
	int		i;
	BerElement	*ber = NULL;
	ber_tag_t	tag;

	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );

	if ( ld == NULL ) return LDAP_PARAM_ERROR;
	if ( keyList == NULL || value == NULL ) {
		ld->ld_errno = LDAP_PARAM_ERROR;
		return LDAP_PARAM_ERROR;
	}

	value->bv_val = NULL;
	value->bv_len = 0;
	ld->ld_errno = LDAP_SUCCESS;

	ber = ldap_alloc_ber_with_options( ld );
	if ( ber == NULL) {
		ld->ld_errno = LDAP_NO_MEMORY;
		return ld->ld_errno;
	}

	tag = ber_printf( ber, "{" /*}*/ );
	if ( tag == LBER_ERROR ) {
		goto error_return;
	}

	for ( i = 0; keyList[i] != NULL; i++ ) {
		tag = ber_printf( ber, "{s" /*}*/, keyList[i]->attributeType );
		if ( tag == LBER_ERROR ) {
			goto error_return;
		}

		if ( keyList[i]->orderingRule != NULL ) {
			tag = ber_printf( ber, "ts",
				LDAP_MATCHRULE_IDENTIFIER,
				keyList[i]->orderingRule );

			if ( tag == LBER_ERROR ) {
				goto error_return;
			}
		}

		if ( keyList[i]->reverseOrder ) {
			tag = ber_printf( ber, "tb",
				LDAP_REVERSEORDER_IDENTIFIER,
				keyList[i]->reverseOrder );

			if ( tag == LBER_ERROR ) {
				goto error_return;
			}
		}

		tag = ber_printf( ber, /*{*/ "N}" );
		if ( tag == LBER_ERROR ) {
			goto error_return;
		}
	}

	tag = ber_printf( ber, /*{*/ "N}" );
	if ( tag == LBER_ERROR ) {
		goto error_return;
	}

	if ( ber_flatten2( ber, value, 1 ) == -1 ) {
		ld->ld_errno = LDAP_NO_MEMORY;
	}

	if ( 0 ) {
error_return:;
		ld->ld_errno =  LDAP_ENCODING_ERROR;
	}

	if ( ber != NULL ) {
		ber_free( ber, 1 );
	}

	return ld->ld_errno;
}