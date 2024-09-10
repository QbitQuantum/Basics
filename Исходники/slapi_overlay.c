static int
slapi_over_extended( Operation *op, SlapReply *rs )
{
	Slapi_PBlock	*pb;
	SLAPI_FUNC	callback;
	int		rc;
	int		internal_op;
	slap_callback	cb;

	slapi_int_get_extop_plugin( &op->ore_reqoid, &callback );
	if ( callback == NULL ) {
		return SLAP_CB_CONTINUE;
	}

	internal_op = slapi_op_internal_p( op, rs, &cb );
	if ( internal_op ) {
		return SLAP_CB_CONTINUE;
	}

	pb = SLAPI_OPERATION_PBLOCK( op );

	rc = (*callback)( pb );
	if ( rc == SLAPI_PLUGIN_EXTENDED_SENT_RESULT ) {
		goto cleanup;
	} else if ( rc == SLAPI_PLUGIN_EXTENDED_NOT_HANDLED ) {
		rc = SLAP_CB_CONTINUE;
		goto cleanup;
	}

	assert( rs->sr_rspoid != NULL );

	send_ldap_extended( op, rs );

#if 0
	slapi_ch_free_string( (char **)&rs->sr_rspoid );
#endif

	if ( rs->sr_rspdata != NULL )
		ber_bvfree( rs->sr_rspdata );

	rc = rs->sr_err;

cleanup:
	slapi_pblock_destroy( pb );
	op->o_callback = cb.sc_next;

	return rc;
}