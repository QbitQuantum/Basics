static int
ldap_back_exop_generic(
	Operation	*op,
	SlapReply	*rs,
	ldapconn_t	**lcp )
{
	ldapinfo_t	*li = (ldapinfo_t *) op->o_bd->be_private;

	ldapconn_t	*lc = *lcp;
	LDAPMessage	*res;
	ber_int_t	msgid;
	int		rc;
	int		do_retry = 1;
	char		*text = NULL;

	Debug( LDAP_DEBUG_ARGS, "==> ldap_back_exop_generic(%s, \"%s\")\n",
		op->ore_reqoid.bv_val, op->o_req_dn.bv_val, 0 );
	assert( lc != NULL );
	assert( rs->sr_ctrls == NULL );

retry:
	rc = ldap_extended_operation( lc->lc_ld,
		op->ore_reqoid.bv_val, op->ore_reqdata,
		op->o_ctrls, NULL, &msgid );

	if ( rc == LDAP_SUCCESS ) {
		/* TODO: set timeout? */
		/* by now, make sure no timeout is used (ITS#6282) */
		struct timeval tv = { -1, 0 };
		if ( ldap_result( lc->lc_ld, msgid, LDAP_MSG_ALL, &tv, &res ) == -1 ) {
			ldap_get_option( lc->lc_ld, LDAP_OPT_ERROR_NUMBER, &rc );
			rs->sr_err = rc;

		} else {
			/* only touch when activity actually took place... */
			if ( li->li_idle_timeout ) {
				lc->lc_time = op->o_time;
			}

			/* sigh. parse twice, because parse_passwd
			 * doesn't give us the err / match / msg info.
			 */
			rc = ldap_parse_result( lc->lc_ld, res, &rs->sr_err,
					(char **)&rs->sr_matched,
					&text,
					NULL, &rs->sr_ctrls, 0 );
			if ( rc == LDAP_SUCCESS ) {
				if ( rs->sr_err == LDAP_SUCCESS ) {
					rc = ldap_parse_extended_result( lc->lc_ld, res,
							(char **)&rs->sr_rspoid, &rs->sr_rspdata, 0 );
					if ( rc == LDAP_SUCCESS ) {
						rs->sr_type = REP_EXTENDED;
					}

				} else {
					rc = rs->sr_err;
				}
			}
			ldap_msgfree( res );
		}
	}

	if ( rc != LDAP_SUCCESS ) {
		rs->sr_err = slap_map_api2result( rs );
		if ( rs->sr_err == LDAP_UNAVAILABLE && do_retry ) {
			do_retry = 0;
			if ( ldap_back_retry( &lc, op, rs, LDAP_BACK_SENDERR ) ) {
				goto retry;
			}
		}

		if ( LDAP_BACK_QUARANTINE( li ) ) {
			ldap_back_quarantine( op, rs );
		}

		if ( text ) rs->sr_text = text;
		send_ldap_extended( op, rs );
		/* otherwise frontend resends result */
		rc = rs->sr_err = SLAPD_ABANDON;

	} else if ( LDAP_BACK_QUARANTINE( li ) ) {
		ldap_back_quarantine( op, rs );
	}

	ldap_pvt_thread_mutex_lock( &li->li_counter_mutex );
	ldap_pvt_mp_add( li->li_ops_completed[ SLAP_OP_EXTENDED ], 1 );
	ldap_pvt_thread_mutex_unlock( &li->li_counter_mutex );

	/* these have to be freed anyway... */
	if ( rs->sr_matched ) {
		free( (char *)rs->sr_matched );
		rs->sr_matched = NULL;
	}

	if ( rs->sr_ctrls ) {
		ldap_controls_free( rs->sr_ctrls );
		rs->sr_ctrls = NULL;
	}

	if ( text ) {
		free( text );
		rs->sr_text = NULL;
	}

	/* in case, cleanup handler */
	if ( lc == NULL ) {
		*lcp = NULL;
	}

	return rc;
}