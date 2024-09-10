char *
ldap_first_attribute( LDAP *ld, LDAPMessage *entry, BerElement **ber )
{
	int	len;
	char	*attrbuffer;

	if ((attrbuffer = (char *)malloc(LDAP_MAX_ATTR_LEN)) == NULL) {
		return (NULL);
	}

	Debug( LDAP_DEBUG_TRACE, catgets(slapdcat, 1, 179, "ldap_first_attribute\n"), 0, 0, 0 );

	if ( (*ber = alloc_ber_with_options( ld )) == NULLBER ) {
		free(attrbuffer);
		return( NULL );
	}

	**ber = *entry->lm_ber;

	/* 
	 * Skip past the sequence, dn, sequence of sequence, snarf the
	 * attribute type, and skip the set of values, leaving us
	 * positioned right before the next attribute type/value sequence.
	 */

	len = LDAP_MAX_ATTR_LEN;
	if ( ber_scanf( *ber, "{x{{sx}", attrbuffer, &len )
	    == LBER_ERROR ) {
		ld->ld_errno = LDAP_DECODING_ERROR;
		ber_free( *ber, 0 );
		*ber = NULL;
		free(attrbuffer);
		return( NULL );
	}

	return( attrbuffer );
}