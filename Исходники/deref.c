static int
deref_response( Operation *op, SlapReply *rs )
{
	int rc = SLAP_CB_CONTINUE;

	if ( rs->sr_type == REP_SEARCH ) {
		BerElementBuffer berbuf;
		BerElement *ber = (BerElement *) &berbuf;
		deref_cb_t *dc = (deref_cb_t *)op->o_callback->sc_private;
		DerefSpec *ds;
		DerefRes *dr, *drhead = NULL, **drp = &drhead;
		struct berval bv = BER_BVNULL;
		int nDerefRes = 0, nDerefVals = 0, nAttrs = 0, nVals = 0;
		struct berval ctrlval;
		LDAPControl *ctrl, *ctrlsp[2];
		AccessControlState acl_state = ACL_STATE_INIT;
		static char dummy = '\0';
		Entry *ebase;
		int i;

		rc = overlay_entry_get_ov( op, &rs->sr_entry->e_nname, NULL, NULL, 0, &ebase, dc->dc_on );
		if ( rc != LDAP_SUCCESS || ebase == NULL ) {
			return SLAP_CB_CONTINUE;
		}

		for ( ds = dc->dc_ds; ds; ds = ds->ds_next ) {
			Attribute *a = attr_find( ebase->e_attrs, ds->ds_derefAttr );

			if ( a != NULL ) {
				DerefVal *dv;
				BerVarray *bva;

				if ( !access_allowed( op, rs->sr_entry, a->a_desc,
						NULL, ACL_READ, &acl_state ) )
				{
					continue;
				}

				dr = op->o_tmpcalloc( 1,
					sizeof( DerefRes ) + ( sizeof( DerefVal ) + sizeof( BerVarray * ) * ds->ds_nattrs ) * ( a->a_numvals + 1 ),
					op->o_tmpmemctx );
				dr->dr_spec = *ds;
				dv = dr->dr_vals = (DerefVal *)&dr[ 1 ];
				bva = (BerVarray *)&dv[ a->a_numvals + 1 ];

				bv.bv_len += ds->ds_derefAttr->ad_cname.bv_len;
				nAttrs++;
				nDerefRes++;

				for ( i = 0; !BER_BVISNULL( &a->a_nvals[ i ] ); i++ ) {
					Entry *e = NULL;

					dv[ i ].dv_attrVals = bva;
					bva += ds->ds_nattrs;


					if ( !access_allowed( op, rs->sr_entry, a->a_desc,
							&a->a_nvals[ i ], ACL_READ, &acl_state ) )
					{
						dv[ i ].dv_derefSpecVal.bv_val = &dummy;
						continue;
					}

					ber_dupbv_x( &dv[ i ].dv_derefSpecVal, &a->a_vals[ i ], op->o_tmpmemctx );
					bv.bv_len += dv[ i ].dv_derefSpecVal.bv_len;
					nVals++;
					nDerefVals++;

					rc = overlay_entry_get_ov( op, &a->a_nvals[ i ], NULL, NULL, 0, &e, dc->dc_on );
					if ( rc == LDAP_SUCCESS && e != NULL ) {
						int j;

						if ( access_allowed( op, e, slap_schema.si_ad_entry,
							NULL, ACL_READ, NULL ) )
						{
							for ( j = 0; j < ds->ds_nattrs; j++ ) {
								Attribute *aa;

								if ( !access_allowed( op, e, ds->ds_attributes[ j ], NULL,
									ACL_READ, &acl_state ) )
								{
									continue;
								}

								aa = attr_find( e->e_attrs, ds->ds_attributes[ j ] );
								if ( aa != NULL ) {
									unsigned k, h, last = aa->a_numvals;

									ber_bvarray_dup_x( &dv[ i ].dv_attrVals[ j ],
										aa->a_vals, op->o_tmpmemctx );

									bv.bv_len += ds->ds_attributes[ j ]->ad_cname.bv_len;

									for ( k = 0, h = 0; k < aa->a_numvals; k++ ) {
										if ( !access_allowed( op, e,
											aa->a_desc,
											&aa->a_nvals[ k ],
											ACL_READ, &acl_state ) )
										{
											op->o_tmpfree( dv[ i ].dv_attrVals[ j ][ h ].bv_val,
												op->o_tmpmemctx );
											dv[ i ].dv_attrVals[ j ][ h ] = dv[ i ].dv_attrVals[ j ][ --last ];
											BER_BVZERO( &dv[ i ].dv_attrVals[ j ][ last ] );
											continue;
										}
										bv.bv_len += dv[ i ].dv_attrVals[ j ][ h ].bv_len;
										nVals++;
										h++;
									}
									nAttrs++;
								}
							}
						}

						overlay_entry_release_ov( op, e, 0, dc->dc_on );
					}
				}

				*drp = dr;
				drp = &dr->dr_next;
			}
		}
		overlay_entry_release_ov( op, ebase, 0, dc->dc_on );

		if ( drhead == NULL ) {
			return SLAP_CB_CONTINUE;
		}

		/* cook the control value */
		bv.bv_len += nVals * sizeof(struct berval)
			+ nAttrs * sizeof(struct berval)
			+ nDerefVals * sizeof(DerefVal)
			+ nDerefRes * sizeof(DerefRes);
		bv.bv_val = op->o_tmpalloc( bv.bv_len, op->o_tmpmemctx );

		ber_init2( ber, &bv, LBER_USE_DER );
		ber_set_option( ber, LBER_OPT_BER_MEMCTX, &op->o_tmpmemctx );

		rc = ber_printf( ber, "{" /*}*/ );
		for ( dr = drhead; dr != NULL; dr = dr->dr_next ) {
			for ( i = 0; !BER_BVISNULL( &dr->dr_vals[ i ].dv_derefSpecVal ); i++ ) {
				int j, first = 1;

				if ( dr->dr_vals[ i ].dv_derefSpecVal.bv_val == &dummy ) {
					continue;
				}

				rc = ber_printf( ber, "{OO" /*}*/,
					&dr->dr_spec.ds_derefAttr->ad_cname,
					&dr->dr_vals[ i ].dv_derefSpecVal );
				op->o_tmpfree( dr->dr_vals[ i ].dv_derefSpecVal.bv_val, op->o_tmpmemctx );
				for ( j = 0; j < dr->dr_spec.ds_nattrs; j++ ) {
					if ( dr->dr_vals[ i ].dv_attrVals[ j ] != NULL ) {
						if ( first ) {
							rc = ber_printf( ber, "t{" /*}*/,
								(LBER_CONSTRUCTED|LBER_CLASS_CONTEXT) );
							first = 0;
						}
						rc = ber_printf( ber, "{O[W]}",
							&dr->dr_spec.ds_attributes[ j ]->ad_cname,
							dr->dr_vals[ i ].dv_attrVals[ j ] );
						op->o_tmpfree( dr->dr_vals[ i ].dv_attrVals[ j ],
							op->o_tmpmemctx );
					}
				}
				if ( !first ) {
					rc = ber_printf( ber, /*{{*/ "}N}" );
				} else {
					rc = ber_printf( ber, /*{*/ "}" );
				}
			}
		}
		rc = ber_printf( ber, /*{*/ "}" );
		if ( ber_flatten2( ber, &ctrlval, 0 ) == -1 ) {
			if ( op->o_deref == SLAP_CONTROL_CRITICAL ) {
				rc = LDAP_CONSTRAINT_VIOLATION;

			} else {
				rc = SLAP_CB_CONTINUE;
			}
			goto cleanup;
		}

		ctrl = op->o_tmpcalloc( 1,
			sizeof( LDAPControl ) + ctrlval.bv_len + 1,
			op->o_tmpmemctx );
		ctrl->ldctl_value.bv_val = (char *)&ctrl[ 1 ];
		ctrl->ldctl_oid = LDAP_CONTROL_X_DEREF;
		ctrl->ldctl_iscritical = 0;
		ctrl->ldctl_value.bv_len = ctrlval.bv_len;
		memcpy( ctrl->ldctl_value.bv_val, ctrlval.bv_val, ctrlval.bv_len );
		ctrl->ldctl_value.bv_val[ ctrl->ldctl_value.bv_len ] = '\0';

		ber_free_buf( ber );

		ctrlsp[0] = ctrl;
		ctrlsp[1] = NULL;
		slap_add_ctrls( op, rs, ctrlsp );

		rc = SLAP_CB_CONTINUE;

cleanup:;
		/* release all */
		for ( ; drhead != NULL; ) {
			DerefRes *drnext = drhead->dr_next;
			op->o_tmpfree( drhead, op->o_tmpmemctx );
			drhead = drnext;
		}

	} else if ( rs->sr_type == REP_RESULT ) {
		rc = deref_cleanup( op, rs );
	}

	return rc;
}