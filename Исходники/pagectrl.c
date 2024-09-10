int
ldap_parse_pageresponse_control(
	LDAP *ld,
	LDAPControl *ctrl,
	ber_int_t *countp,
	struct berval *cookie )
{
	BerElement *ber;
	ber_tag_t tag;
	ber_int_t count;

	if ( ld == NULL || ctrl == NULL || cookie == NULL ) {
		if ( ld )
			ld->ld_errno = LDAP_PARAM_ERROR;
		return LDAP_PARAM_ERROR;
	}

	/* Create a BerElement from the berval returned in the control. */
	ber = ber_init( &ctrl->ldctl_value );

	if ( ber == NULL ) {
		ld->ld_errno = LDAP_NO_MEMORY;
		return ld->ld_errno;
	}

	/* Extract the count and cookie from the control. */
	tag = ber_scanf( ber, "{io}", &count, cookie );
        ber_free( ber, 1 );

	if ( tag == LBER_ERROR ) {
		ld->ld_errno = LDAP_DECODING_ERROR;
	} else {
		ld->ld_errno = LDAP_SUCCESS;

		if ( countp != NULL ) {
			*countp = (unsigned long)count;
		}
	}

	return ld->ld_errno;
}