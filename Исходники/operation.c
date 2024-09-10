void
slap_op_free( Operation *op )
{
	assert( LDAP_STAILQ_NEXT(op, o_next) == NULL );

	if ( op->o_ber != NULL ) {
		ber_free( op->o_ber, 1 );
	}
	if ( op->o_dn.bv_val != NULL ) {
		free( op->o_dn.bv_val );
	}
	if ( op->o_ndn.bv_val != NULL ) {
		free( op->o_ndn.bv_val );
	}
	if ( op->o_authmech.bv_val != NULL ) {
		free( op->o_authmech.bv_val );
	}
	if ( op->o_ctrls != NULL ) {
		ldap_controls_free( op->o_ctrls );
	}

#ifdef LDAP_CONNECTIONLESS
	if ( op->o_res_ber != NULL ) {
		ber_free( op->o_res_ber, 1 );
	}
#endif
#ifdef LDAP_CLIENT_UPDATE
	if ( op->o_clientupdate_state.bv_val != NULL ) {
		free( op->o_clientupdate_state.bv_val );
	}
#endif
#ifdef LDAP_SYNC
	if ( op->o_sync_state.bv_val != NULL ) {
		free( op->o_sync_state.bv_val );
	}
#endif

#if defined( LDAP_SLAPI )
	if ( op->o_pb != NULL ) {
		slapi_pblock_destroy( (Slapi_PBlock *)op->o_pb );
	}
#endif /* defined( LDAP_SLAPI ) */

	memset( op, 0, sizeof(Operation) );
	ldap_pvt_thread_mutex_lock( &slap_op_mutex );
	LDAP_STAILQ_INSERT_HEAD( &slap_free_ops, op, o_next );
	ldap_pvt_thread_mutex_unlock( &slap_op_mutex );
}