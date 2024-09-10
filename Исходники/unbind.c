int
ldap_ld_free(
	LDAP *ld,
	int close,
	LDAPControl **sctrls,
	LDAPControl **cctrls )
{
	LDAPMessage	*lm, *next;
	int		err = LDAP_SUCCESS;

	LDAP_MUTEX_LOCK( &ld->ld_ldcmutex );
	/* Someone else is still using this ld. */
	if (ld->ld_ldcrefcnt > 1) {	/* but not last thread */
		/* clean up self only */
		ld->ld_ldcrefcnt--;
		if ( ld->ld_error != NULL ) {
			LDAP_FREE( ld->ld_error );
			ld->ld_error = NULL;
		}

		if ( ld->ld_matched != NULL ) {
			LDAP_FREE( ld->ld_matched );
			ld->ld_matched = NULL;
		}
		if ( ld->ld_referrals != NULL) {
			LDAP_VFREE(ld->ld_referrals);
			ld->ld_referrals = NULL;
		}  
		LDAP_MUTEX_UNLOCK( &ld->ld_ldcmutex );
		LDAP_FREE( (char *) ld );
		return( err );
	}

	/* This ld is the last thread. */

	/* free LDAP structure and outstanding requests/responses */
	LDAP_MUTEX_LOCK( &ld->ld_req_mutex );
	while ( ld->ld_requests != NULL ) {
		ldap_free_request( ld, ld->ld_requests );
	}
	LDAP_MUTEX_UNLOCK( &ld->ld_req_mutex );
	LDAP_MUTEX_LOCK( &ld->ld_conn_mutex );

	/* free and unbind from all open connections */
	while ( ld->ld_conns != NULL ) {
		ldap_free_connection( ld, ld->ld_conns, 1, close );
	}
	LDAP_MUTEX_UNLOCK( &ld->ld_conn_mutex );
	LDAP_MUTEX_LOCK( &ld->ld_res_mutex );
	for ( lm = ld->ld_responses; lm != NULL; lm = next ) {
		next = lm->lm_next;
		ldap_msgfree( lm );
	}
    
	if ( ld->ld_abandoned != NULL ) {
		LDAP_FREE( ld->ld_abandoned );
		ld->ld_abandoned = NULL;
	}
	LDAP_MUTEX_UNLOCK( &ld->ld_res_mutex );
	LDAP_MUTEX_LOCK( &ld->ld_ldopts_mutex );

	/* final close callbacks */
	{
		ldaplist *ll, *next;

		for ( ll = ld->ld_options.ldo_conn_cbs; ll; ll = next ) {
			ldap_conncb *cb = ll->ll_data;
			next = ll->ll_next;
			cb->lc_del( ld, NULL, cb );
			LDAP_FREE( ll );
		}
	}

	if ( ld->ld_error != NULL ) {
		LDAP_FREE( ld->ld_error );
		ld->ld_error = NULL;
	}

	if ( ld->ld_matched != NULL ) {
		LDAP_FREE( ld->ld_matched );
		ld->ld_matched = NULL;
	}

	if ( ld->ld_referrals != NULL) {
		LDAP_VFREE(ld->ld_referrals);
		ld->ld_referrals = NULL;
	}  
    
	if ( ld->ld_selectinfo != NULL ) {
		ldap_free_select_info( ld->ld_selectinfo );
		ld->ld_selectinfo = NULL;
	}

	if ( ld->ld_options.ldo_defludp != NULL ) {
		ldap_free_urllist( ld->ld_options.ldo_defludp );
		ld->ld_options.ldo_defludp = NULL;
	}

#ifdef LDAP_CONNECTIONLESS
	if ( ld->ld_options.ldo_peer != NULL ) {
		LDAP_FREE( ld->ld_options.ldo_peer );
		ld->ld_options.ldo_peer = NULL;
	}

	if ( ld->ld_options.ldo_cldapdn != NULL ) {
		LDAP_FREE( ld->ld_options.ldo_cldapdn );
		ld->ld_options.ldo_cldapdn = NULL;
	}
#endif

#ifdef HAVE_CYRUS_SASL
	if ( ld->ld_options.ldo_def_sasl_mech != NULL ) {
		LDAP_FREE( ld->ld_options.ldo_def_sasl_mech );
		ld->ld_options.ldo_def_sasl_mech = NULL;
	}

	if ( ld->ld_options.ldo_def_sasl_realm != NULL ) {
		LDAP_FREE( ld->ld_options.ldo_def_sasl_realm );
		ld->ld_options.ldo_def_sasl_realm = NULL;
	}

	if ( ld->ld_options.ldo_def_sasl_authcid != NULL ) {
		LDAP_FREE( ld->ld_options.ldo_def_sasl_authcid );
		ld->ld_options.ldo_def_sasl_authcid = NULL;
	}

	if ( ld->ld_options.ldo_def_sasl_authzid != NULL ) {
		LDAP_FREE( ld->ld_options.ldo_def_sasl_authzid );
		ld->ld_options.ldo_def_sasl_authzid = NULL;
	}
#endif

#ifdef HAVE_TLS
	ldap_int_tls_destroy( &ld->ld_options );
#endif

	if ( ld->ld_options.ldo_sctrls != NULL ) {
		ldap_controls_free( ld->ld_options.ldo_sctrls );
		ld->ld_options.ldo_sctrls = NULL;
	}

	if ( ld->ld_options.ldo_cctrls != NULL ) {
		ldap_controls_free( ld->ld_options.ldo_cctrls );
		ld->ld_options.ldo_cctrls = NULL;
	}
	LDAP_MUTEX_UNLOCK( &ld->ld_ldopts_mutex );

	ber_sockbuf_free( ld->ld_sb );   
   
#ifdef LDAP_R_COMPILE
	ldap_pvt_thread_mutex_destroy( &ld->ld_msgid_mutex );
	ldap_pvt_thread_mutex_destroy( &ld->ld_conn_mutex );
	ldap_pvt_thread_mutex_destroy( &ld->ld_req_mutex );
	ldap_pvt_thread_mutex_destroy( &ld->ld_res_mutex );
	ldap_pvt_thread_mutex_destroy( &ld->ld_abandon_mutex );
	ldap_pvt_thread_mutex_destroy( &ld->ld_ldopts_mutex );
	ldap_pvt_thread_mutex_unlock( &ld->ld_ldcmutex );
	ldap_pvt_thread_mutex_destroy( &ld->ld_ldcmutex );
#endif
#ifndef NDEBUG
	LDAP_TRASH(ld);
#endif
	LDAP_FREE( (char *) ld->ldc );
	LDAP_FREE( (char *) ld );
   
	return( err );
}