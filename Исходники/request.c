/*
 * always protected by conn_mutex
 * optionally protected by req_mutex and res_mutex
 */
LDAPConn *
ldap_new_connection( LDAP *ld, LDAPURLDesc **srvlist, int use_ldsb,
	int connect, LDAPreqinfo *bind, int m_req, int m_res )
{
	LDAPConn	*lc;
	int		async = 0;

	LDAP_ASSERT_MUTEX_OWNER( &ld->ld_conn_mutex );
	Debug( LDAP_DEBUG_TRACE, "ldap_new_connection %d %d %d\n",
		use_ldsb, connect, (bind != NULL) );
	/*
	 * make a new LDAP server connection
	 * XXX open connection synchronously for now
	 */
	lc = (LDAPConn *)LDAP_CALLOC( 1, sizeof( LDAPConn ) );
	if ( lc == NULL ) {
		ld->ld_errno = LDAP_NO_MEMORY;
		return( NULL );
	}
	
	if ( use_ldsb ) {
		assert( ld->ld_sb != NULL );
		lc->lconn_sb = ld->ld_sb;

	} else {
		lc->lconn_sb = ber_sockbuf_alloc();
		if ( lc->lconn_sb == NULL ) {
			LDAP_FREE( (char *)lc );
			ld->ld_errno = LDAP_NO_MEMORY;
			return( NULL );
		}
	}

	if ( connect ) {
		LDAPURLDesc	**srvp, *srv = NULL;

		async = LDAP_BOOL_GET( &ld->ld_options, LDAP_BOOL_CONNECT_ASYNC );

		for ( srvp = srvlist; *srvp != NULL; srvp = &(*srvp)->lud_next ) {
			int		rc;

			rc = ldap_int_open_connection( ld, lc, *srvp, async );
			if ( rc != -1 ) {
				srv = *srvp;

				if ( ld->ld_urllist_proc && ( !async || rc != -2 ) ) {
					ld->ld_urllist_proc( ld, srvlist, srvp, ld->ld_urllist_params );
				}

				break;
			}
		}

		if ( srv == NULL ) {
			if ( !use_ldsb ) {
				ber_sockbuf_free( lc->lconn_sb );
			}
			LDAP_FREE( (char *)lc );
			ld->ld_errno = LDAP_SERVER_DOWN;
			return( NULL );
		}

		lc->lconn_server = ldap_url_dup( srv );
	}

	lc->lconn_status = async ? LDAP_CONNST_CONNECTING : LDAP_CONNST_CONNECTED;
	lc->lconn_next = ld->ld_conns;
	ld->ld_conns = lc;

	if ( connect ) {
#ifdef HAVE_TLS
		if ( lc->lconn_server->lud_exts ) {
			int rc, ext = find_tls_ext( lc->lconn_server );
			if ( ext ) {
				LDAPConn	*savedefconn;

				savedefconn = ld->ld_defconn;
				++lc->lconn_refcnt;	/* avoid premature free */
				ld->ld_defconn = lc;

				LDAP_REQ_UNLOCK_IF(m_req);
				LDAP_MUTEX_UNLOCK( &ld->ld_conn_mutex );
				LDAP_RES_UNLOCK_IF(m_res);
				rc = ldap_start_tls_s( ld, NULL, NULL );
				LDAP_RES_LOCK_IF(m_res);
				LDAP_MUTEX_LOCK( &ld->ld_conn_mutex );
				LDAP_REQ_LOCK_IF(m_req);
				ld->ld_defconn = savedefconn;
				--lc->lconn_refcnt;

				if ( rc != LDAP_SUCCESS && ext == 2 ) {
					ldap_free_connection( ld, lc, 1, 0 );
					return NULL;
				}
			}
		}
#endif
	}

	if ( bind != NULL ) {
		int		err = 0;
		LDAPConn	*savedefconn;

		/* Set flag to prevent additional referrals
		 * from being processed on this
		 * connection until the bind has completed
		 */
		lc->lconn_rebind_inprogress = 1;
		/* V3 rebind function */
		if ( ld->ld_rebind_proc != NULL) {
			LDAPURLDesc	*srvfunc;

			srvfunc = ldap_url_dup( *srvlist );
			if ( srvfunc == NULL ) {
				ld->ld_errno = LDAP_NO_MEMORY;
				err = -1;
			} else {
				savedefconn = ld->ld_defconn;
				++lc->lconn_refcnt;	/* avoid premature free */
				ld->ld_defconn = lc;

				Debug( LDAP_DEBUG_TRACE, "Call application rebind_proc\n", 0, 0, 0);
				LDAP_REQ_UNLOCK_IF(m_req);
				LDAP_MUTEX_UNLOCK( &ld->ld_conn_mutex );
				LDAP_RES_UNLOCK_IF(m_res);
				err = (*ld->ld_rebind_proc)( ld,
					bind->ri_url, bind->ri_request, bind->ri_msgid,
					ld->ld_rebind_params );
				LDAP_RES_LOCK_IF(m_res);
				LDAP_MUTEX_LOCK( &ld->ld_conn_mutex );
				LDAP_REQ_LOCK_IF(m_req);

				ld->ld_defconn = savedefconn;
				--lc->lconn_refcnt;

				if ( err != 0 ) {
					err = -1;
					ldap_free_connection( ld, lc, 1, 0 );
					lc = NULL;
				}
				ldap_free_urldesc( srvfunc );
			}

		} else {
			int		msgid, rc;
			struct berval	passwd = BER_BVNULL;

			savedefconn = ld->ld_defconn;
			++lc->lconn_refcnt;	/* avoid premature free */
			ld->ld_defconn = lc;

			Debug( LDAP_DEBUG_TRACE,
				"anonymous rebind via ldap_sasl_bind(\"\")\n",
				0, 0, 0);

			LDAP_REQ_UNLOCK_IF(m_req);
			LDAP_MUTEX_UNLOCK( &ld->ld_conn_mutex );
			LDAP_RES_UNLOCK_IF(m_res);
			rc = ldap_sasl_bind( ld, "", LDAP_SASL_SIMPLE, &passwd,
				NULL, NULL, &msgid );
			if ( rc != LDAP_SUCCESS ) {
				err = -1;

			} else {
				for ( err = 1; err > 0; ) {
					struct timeval	tv = { 0, 100000 };
					LDAPMessage	*res = NULL;

					switch ( ldap_result( ld, msgid, LDAP_MSG_ALL, &tv, &res ) ) {
					case -1:
						err = -1;
						break;

					case 0:
#ifdef LDAP_R_COMPILE
						ldap_pvt_thread_yield();
#endif
						break;

					case LDAP_RES_BIND:
						rc = ldap_parse_result( ld, res, &err, NULL, NULL, NULL, NULL, 1 );
						if ( rc != LDAP_SUCCESS ) {
							err = -1;

						} else if ( err != LDAP_SUCCESS ) {
							err = -1;
						}
						/* else err == LDAP_SUCCESS == 0 */
						break;

					default:
						Debug( LDAP_DEBUG_TRACE,
							"ldap_new_connection %p: "
							"unexpected response %d "
							"from BIND request id=%d\n",
							(void *) ld, ldap_msgtype( res ), msgid );
						err = -1;
						break;
					}
				}
			}
			LDAP_RES_LOCK_IF(m_res);
			LDAP_MUTEX_LOCK( &ld->ld_conn_mutex );
			LDAP_REQ_LOCK_IF(m_req);
			ld->ld_defconn = savedefconn;
			--lc->lconn_refcnt;

			if ( err != 0 ) {
				ldap_free_connection( ld, lc, 1, 0 );
				lc = NULL;
			}
		}
		if ( lc != NULL )
			lc->lconn_rebind_inprogress = 0;
	}
	return( lc );
}