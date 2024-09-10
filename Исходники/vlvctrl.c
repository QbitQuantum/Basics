int
ldap_create_vlv_control_value(
	LDAP *ld,
	LDAPVLVInfo *vlvinfop,
	struct berval *value )
{
	ber_tag_t tag;
	BerElement *ber;

	if ( ld == NULL || vlvinfop == NULL || value == NULL ) {
		if ( ld )
			ld->ld_errno = LDAP_PARAM_ERROR;
		return LDAP_PARAM_ERROR;
	}

	assert( LDAP_VALID( ld ) );

	value->bv_val = NULL;
	value->bv_len = 0;
	ld->ld_errno = LDAP_SUCCESS;

	ber = ldap_alloc_ber_with_options( ld );
	if ( ber == NULL ) {
		ld->ld_errno = LDAP_NO_MEMORY;
		return ld->ld_errno;
	}

	tag = ber_printf( ber, "{ii" /*}*/,
		vlvinfop->ldvlv_before_count,
		vlvinfop->ldvlv_after_count );
	if ( tag == LBER_ERROR ) {
		goto error_return;
	}

	if ( vlvinfop->ldvlv_attrvalue == NULL ) {
		tag = ber_printf( ber, "t{iiN}",
			LDAP_VLVBYINDEX_IDENTIFIER,
			vlvinfop->ldvlv_offset,
			vlvinfop->ldvlv_count );
		if ( tag == LBER_ERROR ) {
			goto error_return;
		}

	} else {
		tag = ber_printf( ber, "tO",
			LDAP_VLVBYVALUE_IDENTIFIER,
			vlvinfop->ldvlv_attrvalue );
		if ( tag == LBER_ERROR ) {
			goto error_return;
		}
	}

	if ( vlvinfop->ldvlv_context ) {
		tag = ber_printf( ber, "tO",
			LDAP_VLVCONTEXT_IDENTIFIER,
			vlvinfop->ldvlv_context );
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
		ld->ld_errno = LDAP_ENCODING_ERROR;
	}

	if ( ber != NULL ) {
		ber_free( ber, 1 );
	}

	return ld->ld_errno;
}