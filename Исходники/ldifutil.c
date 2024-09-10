void
ldap_ldif_record_done( LDIFRecord *lr )
{
	int i;

	/* the LDAPControl stuff does not allow the use of memory contexts */
	if (lr->lr_ctrls != NULL) {
		ldap_controls_free( lr->lr_ctrls );
	}
	if ( lr->lr_lm != NULL ) {
		ber_memfree_x( lr->lr_lm, lr->lr_ctx );
	}
	if ( lr->lr_mops != NULL ) {
		ber_memfree_x( lr->lr_mops, lr->lr_ctx );
	}
	for (i=lr->lr_lines-1; i>=0; i--)
		if ( lr->lr_freeval[i] ) ber_memfree_x( lr->lr_vals[i].bv_val, lr->lr_ctx );
	ber_memfree_x( lr->lr_btype, lr->lr_ctx );

	memset( lr, 0, sizeof(LDIFRecord) );
}