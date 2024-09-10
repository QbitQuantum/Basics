int
ldap_parse_passwordpolicy_control(
	LDAP           *ld,
	LDAPControl    *ctrl,
	ber_int_t      *expirep,
	ber_int_t      *gracep,
	LDAPPasswordPolicyError *errorp )
{
	BerElement  *ber;
	int exp = -1, grace = -1;
	ber_tag_t tag;
	ber_len_t berLen;
        char *last;
	int err = PP_noError;
        
	assert( ld != NULL );
	assert( LDAP_VALID( ld ) );
	assert( ctrl != NULL );

	/* Create a BerElement from the berval returned in the control. */
	ber = ber_init(&ctrl->ldctl_value);

	if (ber == NULL) {
		ld->ld_errno = LDAP_NO_MEMORY;
		return(ld->ld_errno);
	}

	tag = ber_peek_tag( ber, &berLen );
	if (tag != LBER_SEQUENCE) goto exit;

	for( tag = ber_first_element( ber, &berLen, &last );
		tag != LBER_DEFAULT;
		tag = ber_next_element( ber, &berLen, last ) )
	{
		switch (tag) {
		case PPOLICY_WARNING:
			ber_skip_tag(ber, &berLen );
			tag = ber_peek_tag( ber, &berLen );
			switch( tag ) {
			case PPOLICY_EXPIRE:
				if (ber_get_int( ber, &exp ) == LBER_DEFAULT) goto exit;
				break;
			case PPOLICY_GRACE:
				if (ber_get_int( ber, &grace ) == LBER_DEFAULT) goto exit;
				break;
			default:
				goto exit;
			}
			break;
		case PPOLICY_ERROR:
			if (ber_get_enum( ber, &err ) == LBER_DEFAULT) goto exit;
			break;
		default:
			goto exit;
		}
	}

	ber_free(ber, 1);

	/* Return data to the caller for items that were requested. */
	if (expirep) *expirep = exp;
	if (gracep) *gracep = grace;
	if (errorp) *errorp = err;
        
	ld->ld_errno = LDAP_SUCCESS;
	return(ld->ld_errno);

  exit:
	ber_free(ber, 1);
	ld->ld_errno = LDAP_DECODING_ERROR;
	return(ld->ld_errno);
}