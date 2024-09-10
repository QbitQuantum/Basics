int
ldap_back_search(
		Operation	*op,
		SlapReply	*rs )
{
	ldapinfo_t	*li = (ldapinfo_t *) op->o_bd->be_private;

	ldapconn_t	*lc = NULL;
	struct timeval	tv;
	time_t		stoptime = (time_t)(-1);
	LDAPMessage	*res,
			*e;
	int		rc = 0,
			msgid; 
	struct berval	match = BER_BVNULL,
			filter = BER_BVNULL;
	int		i, x;
	char		**attrs = NULL;
	int		freetext = 0, filter_undef = 0;
	int		do_retry = 1, dont_retry = 0;
	LDAPControl	**ctrls = NULL;
	char		**references = NULL;

	rs_assert_ready( rs );
	rs->sr_flags &= ~REP_ENTRY_MASK; /* paranoia, we can set rs = non-entry */

	if ( !ldap_back_dobind( &lc, op, rs, LDAP_BACK_SENDERR ) ) {
		return rs->sr_err;
	}

	/*
	 * FIXME: in case of values return filter, we might want
	 * to map attrs and maybe rewrite value
	 */

	if ( op->ors_tlimit != SLAP_NO_LIMIT ) {
		tv.tv_sec = op->ors_tlimit;
		tv.tv_usec = 0;
		stoptime = op->o_time + op->ors_tlimit;

	} else {
		LDAP_BACK_TV_SET( &tv );
	}

	i = 0;
	if ( op->ors_attrs ) {
		for ( ; !BER_BVISNULL( &op->ors_attrs[i].an_name ); i++ )
			/* just count attrs */ ;
	}

	x = 0;
	if ( op->o_bd->be_extra_anlist ) {
		for ( ; !BER_BVISNULL( &op->o_bd->be_extra_anlist[x].an_name ); x++ )
			/* just count attrs */ ;
	}

	if ( i > 0 || x > 0 ) {
		int j = 0;

		attrs = op->o_tmpalloc( ( i + x + 1 )*sizeof( char * ),
			op->o_tmpmemctx );
		if ( attrs == NULL ) {
			rs->sr_err = LDAP_NO_MEMORY;
			rc = -1;
			goto finish;
		}

		if ( i > 0 ) {	
			for ( i = 0; !BER_BVISNULL( &op->ors_attrs[i].an_name ); i++, j++ ) {
				attrs[ j ] = op->ors_attrs[i].an_name.bv_val;
			}
		}

		if ( x > 0 ) {
			for ( x = 0; !BER_BVISNULL( &op->o_bd->be_extra_anlist[x].an_name ); x++, j++ ) {
				if ( op->o_bd->be_extra_anlist[x].an_desc &&
					ad_inlist( op->o_bd->be_extra_anlist[x].an_desc, op->ors_attrs ) )
				{
					continue;
				}

				attrs[ j ] = op->o_bd->be_extra_anlist[x].an_name.bv_val;
			}
		}

		attrs[ j ] = NULL;
	}

	ctrls = op->o_ctrls;
	rc = ldap_back_controls_add( op, rs, lc, &ctrls );
	if ( rc != LDAP_SUCCESS ) {
		goto finish;
	}

	/* deal with <draft-zeilenga-ldap-t-f> filters */
	filter = op->ors_filterstr;
retry:
	/* this goes after retry because ldap_back_munge_filter()
	 * optionally replaces RFC 4526 T-F filters (&) (|)
	 * if already computed, they will be re-installed
	 * by filter2bv_undef_x() later */
	if ( !LDAP_BACK_T_F( li ) ) {
		ldap_back_munge_filter( op, &filter );
	}

	rs->sr_err = ldap_pvt_search( lc->lc_ld, op->o_req_dn.bv_val,
			op->ors_scope, filter.bv_val,
			attrs, op->ors_attrsonly, ctrls, NULL,
			tv.tv_sec ? &tv : NULL,
			op->ors_slimit, op->ors_deref, &msgid );

	ldap_pvt_thread_mutex_lock( &li->li_counter_mutex );
	ldap_pvt_mp_add( li->li_ops_completed[ SLAP_OP_SEARCH ], 1 );
	ldap_pvt_thread_mutex_unlock( &li->li_counter_mutex );

	if ( rs->sr_err != LDAP_SUCCESS ) {
		switch ( rs->sr_err ) {
		case LDAP_SERVER_DOWN:
			if ( do_retry ) {
				do_retry = 0;
				if ( ldap_back_retry( &lc, op, rs, LDAP_BACK_DONTSEND ) ) {
					goto retry;
				}
			}

			if ( lc == NULL ) {
				/* reset by ldap_back_retry ... */
				rs->sr_err = slap_map_api2result( rs );

			} else {
				rc = ldap_back_op_result( lc, op, rs, msgid, 0, LDAP_BACK_DONTSEND );
			}
				
			goto finish;

		case LDAP_FILTER_ERROR:
			/* first try? */
			if ( !filter_undef &&
				strstr( filter.bv_val, "(?" ) &&
				!LDAP_BACK_NOUNDEFFILTER( li ) )
			{
				BER_BVZERO( &filter );
				filter2bv_undef_x( op, op->ors_filter, 1, &filter );
				filter_undef = 1;
				goto retry;
			}

			/* invalid filters return success with no data */
			rs->sr_err = LDAP_SUCCESS;
			rs->sr_text = NULL;
			goto finish;
		
		default:
			rs->sr_err = slap_map_api2result( rs );
			rs->sr_text = NULL;
			goto finish;
		}
	}

	/* if needed, initialize timeout */
	if ( li->li_timeout[ SLAP_OP_SEARCH ] ) {
		if ( tv.tv_sec == 0 || tv.tv_sec > li->li_timeout[ SLAP_OP_SEARCH ] ) {
			tv.tv_sec = li->li_timeout[ SLAP_OP_SEARCH ];
			tv.tv_usec = 0;
		}
	}

	/* We pull apart the ber result, stuff it into a slapd entry, and
	 * let send_search_entry stuff it back into ber format. Slow & ugly,
	 * but this is necessary for version matching, and for ACL processing.
	 */

	for ( rc = -2; rc != -1; rc = ldap_result( lc->lc_ld, msgid, LDAP_MSG_ONE, &tv, &res ) )
	{
		/* check for abandon */
		if ( op->o_abandon || LDAP_BACK_CONN_ABANDON( lc ) ) {
			if ( rc > 0 ) {
				ldap_msgfree( res );
			}
			(void)ldap_back_cancel( lc, op, rs, msgid, LDAP_BACK_DONTSEND );
			rc = SLAPD_ABANDON;
			goto finish;
		}

		if ( rc == 0 || rc == -2 ) {
			ldap_pvt_thread_yield();

			/* check timeout */
			if ( li->li_timeout[ SLAP_OP_SEARCH ] ) {
				if ( rc == 0 ) {
					(void)ldap_back_cancel( lc, op, rs, msgid, LDAP_BACK_DONTSEND );
					rs->sr_text = "Operation timed out";
					rc = rs->sr_err = op->o_protocol >= LDAP_VERSION3 ?
						LDAP_ADMINLIMIT_EXCEEDED : LDAP_OTHER;
					goto finish;
				}

			} else {
				LDAP_BACK_TV_SET( &tv );
			}

			/* check time limit */
			if ( op->ors_tlimit != SLAP_NO_LIMIT
					&& slap_get_time() > stoptime )
			{
				(void)ldap_back_cancel( lc, op, rs, msgid, LDAP_BACK_DONTSEND );
				rc = rs->sr_err = LDAP_TIMELIMIT_EXCEEDED;
				goto finish;
			}
			continue;

		} else {
			/* only touch when activity actually took place... */
			if ( li->li_idle_timeout && lc ) {
				lc->lc_time = op->o_time;
			}

			/* don't retry any more */
			dont_retry = 1;
		}


		if ( rc == LDAP_RES_SEARCH_ENTRY ) {
			Entry		ent = { 0 };
			struct berval	bdn = BER_BVNULL;

			do_retry = 0;

			e = ldap_first_entry( lc->lc_ld, res );
			rc = ldap_build_entry( op, e, &ent, &bdn );
			if ( rc == LDAP_SUCCESS ) {
				ldap_get_entry_controls( lc->lc_ld, res, &rs->sr_ctrls );
				rs->sr_entry = &ent;
				rs->sr_attrs = op->ors_attrs;
				rs->sr_operational_attrs = NULL;
				rs->sr_flags = 0;
				rs->sr_err = LDAP_SUCCESS;
				rc = rs->sr_err = send_search_entry( op, rs );
				if ( rs->sr_ctrls ) {
					ldap_controls_free( rs->sr_ctrls );
					rs->sr_ctrls = NULL;
				}
				rs->sr_entry = NULL;
				rs->sr_flags = 0;
				if ( !BER_BVISNULL( &ent.e_name ) ) {
					assert( ent.e_name.bv_val != bdn.bv_val );
					op->o_tmpfree( ent.e_name.bv_val, op->o_tmpmemctx );
					BER_BVZERO( &ent.e_name );
				}
				if ( !BER_BVISNULL( &ent.e_nname ) ) {
					op->o_tmpfree( ent.e_nname.bv_val, op->o_tmpmemctx );
					BER_BVZERO( &ent.e_nname );
				}
				entry_clean( &ent );
			}
			ldap_msgfree( res );
			switch ( rc ) {
			case LDAP_SUCCESS:
			case LDAP_INSUFFICIENT_ACCESS:
				break;

			default:
				if ( rc == LDAP_UNAVAILABLE ) {
					rc = rs->sr_err = LDAP_OTHER;
				} else {
					(void)ldap_back_cancel( lc, op, rs, msgid, LDAP_BACK_DONTSEND );
				}
				goto finish;
			}

		} else if ( rc == LDAP_RES_SEARCH_REFERENCE ) {
			if ( LDAP_BACK_NOREFS( li ) ) {
				ldap_msgfree( res );
				continue;
			}

			do_retry = 0;
			rc = ldap_parse_reference( lc->lc_ld, res,
					&references, &rs->sr_ctrls, 1 );

			if ( rc != LDAP_SUCCESS ) {
				continue;
			}

			/* FIXME: there MUST be at least one */
			if ( references && references[ 0 ] && references[ 0 ][ 0 ] ) {
				int		cnt;

				for ( cnt = 0; references[ cnt ]; cnt++ )
					/* NO OP */ ;

				/* FIXME: there MUST be at least one */
				rs->sr_ref = op->o_tmpalloc( ( cnt + 1 ) * sizeof( struct berval ),
					op->o_tmpmemctx );

				for ( cnt = 0; references[ cnt ]; cnt++ ) {
					ber_str2bv( references[ cnt ], 0, 0, &rs->sr_ref[ cnt ] );
				}
				BER_BVZERO( &rs->sr_ref[ cnt ] );

				/* ignore return value by now */
				RS_ASSERT( !(rs->sr_flags & REP_ENTRY_MASK) );
				rs->sr_entry = NULL;
				( void )send_search_reference( op, rs );

			} else {
				Debug( LDAP_DEBUG_ANY,
					"%s ldap_back_search: "
					"got SEARCH_REFERENCE "
					"with no referrals\n",
					op->o_log_prefix, 0, 0 );
			}

			/* cleanup */
			if ( references ) {
				ber_memvfree( (void **)references );
				op->o_tmpfree( rs->sr_ref, op->o_tmpmemctx );
				rs->sr_ref = NULL;
				references = NULL;
			}

			if ( rs->sr_ctrls ) {
				ldap_controls_free( rs->sr_ctrls );
				rs->sr_ctrls = NULL;
			}

		} else if ( rc == LDAP_RES_INTERMEDIATE ) {
			/* FIXME: response controls
			 * are passed without checks */
			rc = ldap_parse_intermediate( lc->lc_ld,
				res,
				(char **)&rs->sr_rspoid,
				&rs->sr_rspdata,
				&rs->sr_ctrls,
				0 );
			if ( rc != LDAP_SUCCESS ) {
				continue;
			}

			slap_send_ldap_intermediate( op, rs );

			if ( rs->sr_rspoid != NULL ) {
				ber_memfree( (char *)rs->sr_rspoid );
				rs->sr_rspoid = NULL;
			}

			if ( rs->sr_rspdata != NULL ) {
				ber_bvfree( rs->sr_rspdata );
				rs->sr_rspdata = NULL;
			}

			if ( rs->sr_ctrls != NULL ) {
				ldap_controls_free( rs->sr_ctrls );
				rs->sr_ctrls = NULL;
			}

		} else {
			char		*err = NULL;

			rc = ldap_parse_result( lc->lc_ld, res, &rs->sr_err,
					&match.bv_val, &err,
					&references, &rs->sr_ctrls, 1 );
			if ( rc == LDAP_SUCCESS ) {
				if ( err ) {
					rs->sr_text = err;
					freetext = 1;
				}
			} else {
				rs->sr_err = rc;
			}
			rs->sr_err = slap_map_api2result( rs );

			/* RFC 4511: referrals can only appear
			 * if result code is LDAP_REFERRAL */
			if ( references 
				&& references[ 0 ]
				&& references[ 0 ][ 0 ] )
			{
				if ( rs->sr_err != LDAP_REFERRAL ) {
					Debug( LDAP_DEBUG_ANY,
						"%s ldap_back_search: "
						"got referrals with err=%d\n",
						op->o_log_prefix,
						rs->sr_err, 0 );

				} else {
					int	cnt;

					for ( cnt = 0; references[ cnt ]; cnt++ )
						/* NO OP */ ;
				
					rs->sr_ref = op->o_tmpalloc( ( cnt + 1 ) * sizeof( struct berval ),
						op->o_tmpmemctx );

					for ( cnt = 0; references[ cnt ]; cnt++ ) {
						/* duplicating ...*/
						ber_str2bv( references[ cnt ], 0, 0, &rs->sr_ref[ cnt ] );
					}
					BER_BVZERO( &rs->sr_ref[ cnt ] );
				}

			} else if ( rs->sr_err == LDAP_REFERRAL ) {
				Debug( LDAP_DEBUG_ANY,
					"%s ldap_back_search: "
					"got err=%d with null "
					"or empty referrals\n",
					op->o_log_prefix,
					rs->sr_err, 0 );

				rs->sr_err = LDAP_NO_SUCH_OBJECT;
			}

			if ( match.bv_val != NULL ) {
				match.bv_len = strlen( match.bv_val );
			}

			rc = 0;
			break;
		}

		/* if needed, restore timeout */
		if ( li->li_timeout[ SLAP_OP_SEARCH ] ) {
			if ( tv.tv_sec == 0 || tv.tv_sec > li->li_timeout[ SLAP_OP_SEARCH ] ) {
				tv.tv_sec = li->li_timeout[ SLAP_OP_SEARCH ];
				tv.tv_usec = 0;
			}
		}
	}

 	if ( rc == -1 ) {
		if ( dont_retry == 0 ) {
			if ( do_retry ) {
				do_retry = 0;
				if ( ldap_back_retry( &lc, op, rs, LDAP_BACK_DONTSEND ) ) {
					goto retry;
				}
			}

			rs->sr_err = LDAP_SERVER_DOWN;
			rs->sr_err = slap_map_api2result( rs );
			goto finish;

		} else if ( LDAP_BACK_ONERR_STOP( li ) ) {
			/* if onerr == STOP */
			rs->sr_err = LDAP_SERVER_DOWN;
			rs->sr_err = slap_map_api2result( rs );
			goto finish;
		}
	}

	/*
	 * Rewrite the matched portion of the search base, if required
	 */
	if ( !BER_BVISNULL( &match ) && !BER_BVISEMPTY( &match ) ) {
		struct berval	pmatch;

		if ( dnPretty( NULL, &match, &pmatch, op->o_tmpmemctx ) != LDAP_SUCCESS ) {
			pmatch.bv_val = match.bv_val;
			match.bv_val = NULL;
		}
		rs->sr_matched = pmatch.bv_val;
		rs->sr_flags |= REP_MATCHED_MUSTBEFREED;
	}

finish:;
	if ( !BER_BVISNULL( &match ) ) {
		ber_memfree( match.bv_val );
	}

	if ( rs->sr_v2ref ) {
		rs->sr_err = LDAP_REFERRAL;
	}

	if ( LDAP_BACK_QUARANTINE( li ) ) {
		ldap_back_quarantine( op, rs );
	}

	if ( filter.bv_val != op->ors_filterstr.bv_val ) {
		op->o_tmpfree( filter.bv_val, op->o_tmpmemctx );
	}

#if 0
	/* let send_ldap_result play cleanup handlers (ITS#4645) */
	if ( rc != SLAPD_ABANDON )
#endif
	{
		send_ldap_result( op, rs );
	}

	(void)ldap_back_controls_free( op, rs, &ctrls );

	if ( rs->sr_ctrls ) {
		ldap_controls_free( rs->sr_ctrls );
		rs->sr_ctrls = NULL;
	}

	if ( rs->sr_text ) {
		if ( freetext ) {
			ber_memfree( (char *)rs->sr_text );
		}
		rs->sr_text = NULL;
	}

	if ( rs->sr_ref ) {
		op->o_tmpfree( rs->sr_ref, op->o_tmpmemctx );
		rs->sr_ref = NULL;
	}

	if ( references ) {
		ber_memvfree( (void **)references );
	}

	if ( attrs ) {
		op->o_tmpfree( attrs, op->o_tmpmemctx );
	}

	if ( lc != NULL ) {
		ldap_back_release_conn( li, lc );
	}

	return rs->sr_err;
}