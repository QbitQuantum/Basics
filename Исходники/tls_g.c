static void
tlsg_x509_cert_dn( struct berval *cert, struct berval *dn, int get_subject )
{
	BerElementBuffer berbuf;
	BerElement *ber = (BerElement *)&berbuf;
	ber_tag_t tag;
	ber_len_t len;
	ber_int_t i;

	ber_init2( ber, cert, LBER_USE_DER );
	tag = ber_skip_tag( ber, &len );	/* Sequence */
	tag = ber_skip_tag( ber, &len );	/* Sequence */
	tag = ber_skip_tag( ber, &len );	/* Context + Constructed (version) */
	if ( tag == 0xa0 )	/* Version is optional */
		tag = ber_get_int( ber, &i );	/* Int: Version */
	tag = ber_skip_tag( ber, &len );	/* Int: Serial (can be longer than ber_int_t) */
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );	/* Sequence: Signature */
	ber_skip_data( ber, len );
	if ( !get_subject ) {
		tag = ber_peek_tag( ber, &len );	/* Sequence: Issuer DN */
	} else {
		tag = ber_skip_tag( ber, &len );
		ber_skip_data( ber, len );
		tag = ber_skip_tag( ber, &len );	/* Sequence: Validity */
		ber_skip_data( ber, len );
		tag = ber_peek_tag( ber, &len );	/* Sequence: Subject DN */
	}
	len = ber_ptrlen( ber );
	dn->bv_val = cert->bv_val + len;
	dn->bv_len = cert->bv_len - len;
}