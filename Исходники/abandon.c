static int
do_abandon(
	LDAP *ld,
	ber_int_t origid,
	ber_int_t msgid,
	LDAPControl **sctrls,
	int sendabandon )
{
	BerElement	*ber;
	int		i, err;
	Sockbuf		*sb;
	LDAPRequest	*lr;

	Debug( LDAP_DEBUG_TRACE, "do_abandon origid %d, msgid %d\n",
		origid, msgid, 0 );

	/* find the request that we are abandoning */
start_again:;
	lr = ld->ld_requests;
	while ( lr != NULL ) {
		/* this message */
		if ( lr->lr_msgid == msgid ) {
			break;
		}

		/* child: abandon it */
		if ( lr->lr_origid == msgid && !lr->lr_abandoned ) {
			(void)do_abandon( ld, lr->lr_origid, lr->lr_msgid,
				sctrls, sendabandon );

			/* restart, as lr may now be dangling... */
			goto start_again;
		}

		lr = lr->lr_next;
	}

	if ( lr != NULL ) {
		if ( origid == msgid && lr->lr_parent != NULL ) {
			/* don't let caller abandon child requests! */
			ld->ld_errno = LDAP_PARAM_ERROR;
			return( LDAP_PARAM_ERROR );
		}
		if ( lr->lr_status != LDAP_REQST_INPROGRESS ) {
			/* no need to send abandon message */
			sendabandon = 0;
		}
	}

	/* ldap_msgdelete locks the res_mutex. Give up the req_mutex
	 * while we're in there.
	 */
#ifdef LDAP_R_COMPILE
	ldap_pvt_thread_mutex_unlock( &ld->ld_req_mutex );
#endif
	err = ldap_msgdelete( ld, msgid );
#ifdef LDAP_R_COMPILE
	ldap_pvt_thread_mutex_lock( &ld->ld_req_mutex );
#endif
	if ( err == 0 ) {
		ld->ld_errno = LDAP_SUCCESS;
		return LDAP_SUCCESS;
	}

	/* fetch again the request that we are abandoning */
	if ( lr != NULL ) {
		for ( lr = ld->ld_requests; lr != NULL; lr = lr->lr_next ) {
			/* this message */
			if ( lr->lr_msgid == msgid ) {
				break;
			}
		}
	}

	err = 0;
	if ( sendabandon ) {
		if ( ber_sockbuf_ctrl( ld->ld_sb, LBER_SB_OPT_GET_FD, NULL ) == -1 ) {
			/* not connected */
			err = -1;
			ld->ld_errno = LDAP_SERVER_DOWN;

		} else if ( ( ber = ldap_alloc_ber_with_options( ld ) ) == NULL ) {
			/* BER element allocation failed */
			err = -1;
			ld->ld_errno = LDAP_NO_MEMORY;

		} else {
			/*
			 * We already have the mutex in LDAP_R_COMPILE, so
			 * don't try to get it again.
			 *		LDAP_NEXT_MSGID(ld, i);
			 */

			i = ++(ld)->ld_msgid;
#ifdef LDAP_CONNECTIONLESS
			if ( LDAP_IS_UDP(ld) ) {
				struct sockaddr sa = {0};
				/* dummy, filled with ldo_peer in request.c */
				err = ber_write( ber, &sa, sizeof(sa), 0 );
			}
			if ( LDAP_IS_UDP(ld) && ld->ld_options.ldo_version ==
				LDAP_VERSION2 )
			{
				char *dn = ld->ld_options.ldo_cldapdn;
				if (!dn) dn = "";
				err = ber_printf( ber, "{isti",  /* '}' */
					i, dn,
					LDAP_REQ_ABANDON, msgid );
			} else
#endif
			{
				/* create a message to send */
				err = ber_printf( ber, "{iti",  /* '}' */
					i,
					LDAP_REQ_ABANDON, msgid );
			}

			if ( err == -1 ) {
				/* encoding error */
				ld->ld_errno = LDAP_ENCODING_ERROR;

			} else {
				/* Put Server Controls */
				if ( ldap_int_put_controls( ld, sctrls, ber )
					!= LDAP_SUCCESS )
				{
					err = -1;

				} else {
					/* close '{' */
					err = ber_printf( ber, /*{*/ "N}" );

					if ( err == -1 ) {
						/* encoding error */
						ld->ld_errno = LDAP_ENCODING_ERROR;
					}
				}
			}

			if ( err == -1 ) {
				ber_free( ber, 1 );

			} else {
				/* send the message */
				if ( lr != NULL ) {
					assert( lr->lr_conn != NULL );
					sb = lr->lr_conn->lconn_sb;
				} else {
					sb = ld->ld_sb;
				}

				if ( ber_flush2( sb, ber, LBER_FLUSH_FREE_ALWAYS ) != 0 ) {
					ld->ld_errno = LDAP_SERVER_DOWN;
					err = -1;
				} else {
					err = 0;
				}
			}
		}
	}

	if ( lr != NULL ) {
		if ( sendabandon || lr->lr_status == LDAP_REQST_WRITING ) {
			ldap_free_connection( ld, lr->lr_conn, 0, 1 );
		}

		if ( origid == msgid ) {
			ldap_free_request( ld, lr );

		} else {
			lr->lr_abandoned = 1;
		}
	}

#ifdef LDAP_R_COMPILE
	/* ld_abandoned is actually protected by the ld_res_mutex;
	 * give up the ld_req_mutex and get the other */
	ldap_pvt_thread_mutex_unlock( &ld->ld_req_mutex );
	ldap_pvt_thread_mutex_lock( &ld->ld_res_mutex );
#endif

	/* use bisection */
	i = 0;
	if ( ld->ld_nabandoned == 0 ||
		ldap_int_bisect_find( ld->ld_abandoned, ld->ld_nabandoned, msgid, &i ) == 0 )
	{
		ldap_int_bisect_insert( &ld->ld_abandoned, &ld->ld_nabandoned, msgid, i );
	}

	if ( err != -1 ) {
		ld->ld_errno = LDAP_SUCCESS;
	}

#ifdef LDAP_R_COMPILE
	ldap_pvt_thread_mutex_unlock( &ld->ld_res_mutex );
	ldap_pvt_thread_mutex_lock( &ld->ld_req_mutex );
#endif
	return( ld->ld_errno );
}