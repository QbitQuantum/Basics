int
asyncmeta_handle_search_msg(LDAPMessage *res, a_metaconn_t *mc, bm_context_t *bc, int candidate)
{
	a_metainfo_t	*mi;
	a_metatarget_t	*mt;
	a_metasingleconn_t *msc;
	Operation *op = bc->op;
	SlapReply *rs;
	int	   i, rc = LDAP_SUCCESS, sres;
	SlapReply *candidates;
	char		**references = NULL;
	LDAPControl	**ctrls = NULL;
	a_dncookie dc;
	LDAPMessage *msg;
	ber_int_t id;

	rs = &bc->rs;
	mi = mc->mc_info;
	mt = mi->mi_targets[ candidate ];
	msc = &mc->mc_conns[ candidate ];
	dc.op = op;
	dc.target = mt;
	dc.to_from = MASSAGE_REP;
	id = ldap_msgid(res);


	candidates = bc->candidates;
	i = candidate;

	while (res && !META_BACK_CONN_INVALID(msc)) {
	for (msg = ldap_first_message(msc->msc_ldr, res); msg; msg = ldap_next_message(msc->msc_ldr, msg)) {
		switch(ldap_msgtype(msg)) {
		case LDAP_RES_SEARCH_ENTRY:
			Debug( LDAP_DEBUG_TRACE,
				"%s asyncmeta_handle_search_msg: msc %p entry\n",
				op->o_log_prefix, msc );
			if ( candidates[ i ].sr_type == REP_INTERMEDIATE ) {
				/* don't retry any more... */
				candidates[ i ].sr_type = REP_RESULT;
			}
			/* count entries returned by target */
			candidates[ i ].sr_nentries++;
			if (bc->c_peer_name.bv_val == op->o_conn->c_peer_name.bv_val && !op->o_abandon) {
				rs->sr_err = asyncmeta_send_entry( &bc->copy_op, rs, mc, i, msg );
			} else {
				goto err_cleanup;
			}
			switch ( rs->sr_err ) {
			case LDAP_SIZELIMIT_EXCEEDED:
				asyncmeta_send_ldap_result(bc, op, rs);
				rs->sr_err = LDAP_SUCCESS;
				goto err_cleanup;
			case LDAP_UNAVAILABLE:
				rs->sr_err = LDAP_OTHER;
				break;
			default:
				break;
			}
			bc->is_ok++;
			break;

		case LDAP_RES_SEARCH_REFERENCE:
			if ( META_BACK_TGT_NOREFS( mt ) ) {
				rs->sr_err = LDAP_OTHER;
				asyncmeta_send_ldap_result(bc, op, rs);
				goto err_cleanup;
			}
			if ( candidates[ i ].sr_type == REP_INTERMEDIATE ) {
				/* don't retry any more... */
				candidates[ i ].sr_type = REP_RESULT;
			}
			bc->is_ok++;
			rc = ldap_parse_reference( msc->msc_ldr, msg,
				   &references, &rs->sr_ctrls, 0 );

			if ( rc != LDAP_SUCCESS || references == NULL ) {
				rs->sr_err = LDAP_OTHER;
				asyncmeta_send_ldap_result(bc, op, rs);
				goto err_cleanup;
			}

			/* FIXME: merge all and return at the end */

			{
				int cnt;
				for ( cnt = 0; references[ cnt ]; cnt++ )
					;

				rs->sr_ref = ber_memalloc_x( sizeof( struct berval ) * ( cnt + 1 ),
								 op->o_tmpmemctx );

				for ( cnt = 0; references[ cnt ]; cnt++ ) {
					ber_str2bv_x( references[ cnt ], 0, 1, &rs->sr_ref[ cnt ],
							  op->o_tmpmemctx );
				}
				BER_BVZERO( &rs->sr_ref[ cnt ] );
			}

			{
				dc.memctx = op->o_tmpmemctx;
				( void )asyncmeta_referral_result_rewrite( &dc, rs->sr_ref );
			}

			if ( rs->sr_ref != NULL ) {
				if (!BER_BVISNULL( &rs->sr_ref[ 0 ] ) ) {
					/* ignore return value by now */
					( void )send_search_reference( op, rs );
				}

				ber_bvarray_free_x( rs->sr_ref, op->o_tmpmemctx );
				rs->sr_ref = NULL;
			}

			/* cleanup */
			if ( references ) {
				ber_memvfree( (void **)references );
			}

			if ( rs->sr_ctrls ) {
				ldap_controls_free( rs->sr_ctrls );
				rs->sr_ctrls = NULL;
			}
			break;

		case LDAP_RES_INTERMEDIATE:
			if ( candidates[ i ].sr_type == REP_INTERMEDIATE ) {
				/* don't retry any more... */
				candidates[ i ].sr_type = REP_RESULT;
			}
			bc->is_ok++;

			/* FIXME: response controls
			 * are passed without checks */
			rs->sr_err = ldap_parse_intermediate( msc->msc_ldr,
								  msg,
								  (char **)&rs->sr_rspoid,
								  &rs->sr_rspdata,
								  &rs->sr_ctrls,
								  0 );
			if ( rs->sr_err != LDAP_SUCCESS ) {
				candidates[ i ].sr_type = REP_RESULT;
				rs->sr_err = LDAP_OTHER;
				asyncmeta_send_ldap_result(bc, op, rs);
				goto err_cleanup;
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
			break;

		case LDAP_RES_SEARCH_RESULT:
			if ( mi->mi_idle_timeout != 0 ) {
				asyncmeta_set_msc_time(msc);
			}
			Debug( LDAP_DEBUG_TRACE,
			       "%s asyncmeta_handle_search_msg: msc %p result\n",
			       op->o_log_prefix, msc );
			candidates[ i ].sr_type = REP_RESULT;
			candidates[ i ].sr_msgid = META_MSGID_IGNORE;
			/* NOTE: ignores response controls
			 * (and intermediate response controls
			 * as well, except for those with search
			 * references); this may not be correct,
			 * but if they're not ignored then
			 * back-meta would need to merge them
			 * consistently (think of pagedResults...)
			 */
			/* FIXME: response controls? */
			rs->sr_err = ldap_parse_result( msc->msc_ldr,
							msg,
							&candidates[ i ].sr_err,
								(char **)&candidates[ i ].sr_matched,
							(char **)&candidates[ i ].sr_text,
							&references,
							&ctrls /* &candidates[ i ].sr_ctrls (unused) */ ,
							0 );
			if ( rs->sr_err != LDAP_SUCCESS ) {
				candidates[ i ].sr_err = rs->sr_err;
				sres = slap_map_api2result( &candidates[ i ] );
				candidates[ i ].sr_type = REP_RESULT;
				goto finish;
			}

			rs->sr_err = candidates[ i ].sr_err;

			/* massage matchedDN if need be */
			if ( candidates[ i ].sr_matched != NULL ) {
				struct berval	match, mmatch;

				ber_str2bv( candidates[ i ].sr_matched,
						0, 0, &match );
				candidates[ i ].sr_matched = NULL;

				dc.memctx = NULL;
				asyncmeta_dn_massage( &dc, &match, &mmatch );
				if ( mmatch.bv_val == match.bv_val ) {
					candidates[ i ].sr_matched
						= ch_strdup( mmatch.bv_val );

				} else {
					candidates[ i ].sr_matched = mmatch.bv_val;
				}

				bc->candidate_match++;
				ldap_memfree( match.bv_val );
			}

			/* add references to array */
			/* RFC 4511: referrals can only appear
			 * if result code is LDAP_REFERRAL */
			if ( references != NULL
				 && references[ 0 ] != NULL
				 && references[ 0 ][ 0 ] != '\0' )
			{
				if ( rs->sr_err != LDAP_REFERRAL ) {
					Debug( LDAP_DEBUG_ANY,
						   "%s asncmeta_search_result[%d]: "
						   "got referrals with err=%d\n",
						   op->o_log_prefix,
						   i, rs->sr_err );

				} else {
					BerVarray	sr_ref;
					int		cnt;

					for ( cnt = 0; references[ cnt ]; cnt++ )
						;

					sr_ref = ber_memalloc_x( sizeof( struct berval ) * ( cnt + 1 ),
								 op->o_tmpmemctx );

					for ( cnt = 0; references[ cnt ]; cnt++ ) {
						ber_str2bv_x( references[ cnt ], 0, 1, &sr_ref[ cnt ],
								  op->o_tmpmemctx );
					}
					BER_BVZERO( &sr_ref[ cnt ] );

					dc.memctx = op->o_tmpmemctx;
					( void )asyncmeta_referral_result_rewrite( &dc, sr_ref );

					if ( rs->sr_v2ref == NULL ) {
						rs->sr_v2ref = sr_ref;

					} else {
						for ( cnt = 0; !BER_BVISNULL( &sr_ref[ cnt ] ); cnt++ ) {
							ber_bvarray_add_x( &rs->sr_v2ref, &sr_ref[ cnt ],
									   op->o_tmpmemctx );
						}
						ber_memfree_x( sr_ref, op->o_tmpmemctx );
					}
				}

			} else if ( rs->sr_err == LDAP_REFERRAL ) {
				Debug( LDAP_DEBUG_TRACE,
					   "%s asyncmeta_search_result[%d]: "
					   "got err=%d with null "
					   "or empty referrals\n",
					   op->o_log_prefix,
					   i, rs->sr_err );

				rs->sr_err = LDAP_NO_SUCH_OBJECT;
			}

			/* cleanup */
			ber_memvfree( (void **)references );

			sres = slap_map_api2result( rs );

			if ( candidates[ i ].sr_err == LDAP_SUCCESS ) {
				Debug( LDAP_DEBUG_TRACE, "%s asyncmeta_search_result[%d] "
				       "match=\"%s\" err=%ld",
				       op->o_log_prefix, i,
				       candidates[ i ].sr_matched ? candidates[ i ].sr_matched : "",
				       (long) candidates[ i ].sr_err );
			} else {
					Debug( LDAP_DEBUG_ANY,  "%s asyncmeta_search_result[%d] "
				       "match=\"%s\" err=%ld (%s)",
				       op->o_log_prefix, i,
				       candidates[ i ].sr_matched ? candidates[ i ].sr_matched : "",
					       (long) candidates[ i ].sr_err, ldap_err2string( candidates[ i ].sr_err ) );
			}

			switch ( sres ) {
			case LDAP_NO_SUCH_OBJECT:
				/* is_ok is touched any time a valid
				 * (even intermediate) result is
				 * returned; as a consequence, if
				 * a candidate returns noSuchObject
				 * it is ignored and the candidate
				 * is simply demoted. */
				if ( bc->is_ok ) {
					sres = LDAP_SUCCESS;
				}
				break;

			case LDAP_SUCCESS:
				if ( ctrls != NULL && ctrls[0] != NULL ) {
#ifdef SLAPD_META_CLIENT_PR
					LDAPControl *pr_c;

					pr_c = ldap_control_find( LDAP_CONTROL_PAGEDRESULTS, ctrls, NULL );
					if ( pr_c != NULL ) {
						BerElementBuffer berbuf;
						BerElement *ber = (BerElement *)&berbuf;
						ber_tag_t tag;
						ber_int_t prsize;
						struct berval prcookie;

						/* unsolicited, do not accept */
						if ( mt->mt_ps == 0 ) {
							rs->sr_err = LDAP_OTHER;
							goto err_pr;
						}

						ber_init2( ber, &pr_c->ldctl_value, LBER_USE_DER );

						tag = ber_scanf( ber, "{im}", &prsize, &prcookie );
						if ( tag == LBER_ERROR ) {
							rs->sr_err = LDAP_OTHER;
							goto err_pr;
						}

						/* more pages? new search request */
						if ( !BER_BVISNULL( &prcookie ) && !BER_BVISEMPTY( &prcookie ) ) {
							if ( mt->mt_ps > 0 ) {
								/* ignore size if specified */
								prsize = 0;

							} else if ( prsize == 0 ) {
								/* guess the page size from the entries returned so far */
								prsize = candidates[ i ].sr_nentries;
							}

							candidates[ i ].sr_nentries = 0;
							candidates[ i ].sr_msgid = META_MSGID_IGNORE;
							candidates[ i ].sr_type = REP_INTERMEDIATE;

							assert( candidates[ i ].sr_matched == NULL );
							assert( candidates[ i ].sr_text == NULL );
							assert( candidates[ i ].sr_ref == NULL );

							switch ( asyncmeta_back_search_start( &bc->copy_op, rs, mc, bc, i, &prcookie, prsize, 1 ) )
							{
							case META_SEARCH_CANDIDATE:
								assert( candidates[ i ].sr_msgid >= 0 );
								ldap_controls_free( ctrls );
								//	goto free_message;

							case META_SEARCH_ERR:
							case META_SEARCH_NEED_BIND:
err_pr:;
								candidates[ i ].sr_err = rs->sr_err;
								candidates[ i ].sr_type = REP_RESULT;
								if ( META_BACK_ONERR_STOP( mi ) ) {
									asyncmeta_send_ldap_result(bc, op, rs);
									ldap_controls_free( ctrls );
									goto err_cleanup;
								}
								/* fallthru */

							case META_SEARCH_NOT_CANDIDATE:
								/* means that asyncmeta_back_search_start()
								 * failed but onerr == continue */
								candidates[ i ].sr_msgid = META_MSGID_IGNORE;
								candidates[ i ].sr_type = REP_RESULT;
								break;

							default:
								/* impossible */
								assert( 0 );
								break;
							}
							break;
						}
					}
#endif /* SLAPD_META_CLIENT_PR */

					ldap_controls_free( ctrls );
				}
				/* fallthru */

			case LDAP_REFERRAL:
				bc->is_ok++;
				break;

			case LDAP_SIZELIMIT_EXCEEDED:
				/* if a target returned sizelimitExceeded
				 * and the entry count is equal to the
				 * proxy's limit, the target would have
				 * returned more, and the error must be
				 * propagated to the client; otherwise,
				 * the target enforced a limit lower
				 * than what requested by the proxy;
				 * ignore it */
				candidates[ i ].sr_err = rs->sr_err;
				if ( rs->sr_nentries == op->ors_slimit
					 || META_BACK_ONERR_STOP( mi ) )
				{
					const char *save_text;
got_err:
					save_text = rs->sr_text;
					rs->sr_text = candidates[ i ].sr_text;
					asyncmeta_send_ldap_result(bc, op, rs);
					if (candidates[ i ].sr_text != NULL) {
						ch_free( (char *)candidates[ i ].sr_text );
						candidates[ i ].sr_text = NULL;
					}
					rs->sr_text = save_text;
					ldap_controls_free( ctrls );
					goto err_cleanup;
				}
				break;

			default:
				candidates[ i ].sr_err = rs->sr_err;
				if ( META_BACK_ONERR_STOP( mi ) ) {
					goto got_err;
				}
				break;
			}
			/* if this is the last result we will ever receive, send it back  */
			rc = rs->sr_err;
			if (asyncmeta_is_last_result(mc, bc, i) == 0) {
				Debug( LDAP_DEBUG_TRACE,
					"%s asyncmeta_handle_search_msg: msc %p last result\n",
					op->o_log_prefix, msc );
				asyncmeta_search_last_result(mc, bc, i, sres);
err_cleanup:
				rc = rs->sr_err;
				ldap_pvt_thread_mutex_lock( &mc->mc_om_mutex );
				asyncmeta_drop_bc( mc, bc);
				asyncmeta_clear_bm_context(bc);
				ldap_pvt_thread_mutex_unlock( &mc->mc_om_mutex );
				ldap_msgfree(res);
				return rc;
			}
finish:
			break;

		default:
			continue;
		}
	}
		ldap_msgfree(res);
		res = NULL;
		if (candidates[ i ].sr_type != REP_RESULT) {
			struct timeval	tv = {0};
			rc = ldap_result( msc->msc_ldr, id, LDAP_MSG_RECEIVED, &tv, &res );
			if (res != NULL) {
				msc->msc_result_time = slap_get_time();
			}
		}
	}
	ldap_pvt_thread_mutex_lock( &mc->mc_om_mutex );
	bc->bc_active--;
	ldap_pvt_thread_mutex_unlock( &mc->mc_om_mutex );

	return rc;
}