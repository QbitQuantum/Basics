int
ldap_open_internal_connection( LDAP **ldp, ber_socket_t *fdp )
{
	int rc;
	LDAPConn *c;
	LDAPRequest *lr;

	rc = ldap_create( ldp );
	if( rc != LDAP_SUCCESS ) {
		*ldp = NULL;
		return( rc );
	}

	/* Make it appear that a search request, msgid 0, was sent */
	lr = (LDAPRequest *)LDAP_CALLOC( 1, sizeof( LDAPRequest ));
	if( lr == NULL ) {
		ldap_unbind_ext( *ldp, NULL, NULL );
		*ldp = NULL;
		return( LDAP_NO_MEMORY );
	}
	memset(lr, 0, sizeof( LDAPRequest ));
	lr->lr_msgid = 0;
	lr->lr_status = LDAP_REQST_INPROGRESS;
	lr->lr_res_errno = LDAP_SUCCESS;
	/* no mutex lock needed, we just created this ld here */
	(*ldp)->ld_requests = lr;

	/* Attach the passed socket as the *LDAP's connection */
	c = ldap_new_connection( *ldp, NULL, 1, 0, NULL);
	if( c == NULL ) {
		ldap_unbind_ext( *ldp, NULL, NULL );
		*ldp = NULL;
		return( LDAP_NO_MEMORY );
	}
	ber_sockbuf_ctrl( c->lconn_sb, LBER_SB_OPT_SET_FD, fdp );
#ifdef LDAP_DEBUG
	ber_sockbuf_add_io( c->lconn_sb, &ber_sockbuf_io_debug,
		LBER_SBIOD_LEVEL_PROVIDER, (void *)"int_" );
#endif
	ber_sockbuf_add_io( c->lconn_sb, &ber_sockbuf_io_tcp,
	  LBER_SBIOD_LEVEL_PROVIDER, NULL );
	(*ldp)->ld_defconn = c;

	/* Add the connection to the *LDAP's select pool */
	ldap_mark_select_read( *ldp, c->lconn_sb );
	ldap_mark_select_write( *ldp, c->lconn_sb );

	/* Make this connection an LDAP V3 protocol connection */
	rc = LDAP_VERSION3;
	ldap_set_option( *ldp, LDAP_OPT_PROTOCOL_VERSION, &rc );

	return( LDAP_SUCCESS );
}