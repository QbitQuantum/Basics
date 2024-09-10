static int 
pblock_set( Slapi_PBlock *pb, int param, void *value ) 
{
	int rc = PBLOCK_SUCCESS;

	pblock_lock( pb );	

	switch ( param ) {
	case SLAPI_OPERATION:
		pb->pb_op = (Operation *)value;
		break;
	case SLAPI_OPINITIATED_TIME:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_time = *((long *)value);
		break;
	case SLAPI_OPERATION_ID:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_opid = *((long *)value);
		break;
	case SLAPI_OPERATION_TYPE:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_tag = *((ber_tag_t *)value);
		break;
	case SLAPI_OPERATION_MSGID:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_msgid = *((long *)value);
		break;
	case SLAPI_X_OPERATION_DELETE_GLUE_PARENT:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_delete_glue_parent = *((int *)value);
		break;
	case SLAPI_X_OPERATION_NO_SCHEMA_CHECK:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_no_schema_check = *((int *)value);
		break;
	case SLAPI_X_OPERATION_NO_SUBORDINATE_GLUE:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_no_subordinate_glue = *((int *)value);
		break;
	case SLAPI_REQCONTROLS:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_ctrls = (LDAPControl **)value;
		break;
	case SLAPI_RESCONTROLS: {
		LDAPControl **ctrls = NULL;

		pblock_get_default( pb, param, (void **)&ctrls );
		if ( ctrls != NULL ) {
			/* free old ones first */
			ldap_controls_free( ctrls );
		}
		rc = pblock_set_default( pb, param, value );
		break;
	}
	case SLAPI_ADD_RESCONTROL:
		PBLOCK_ASSERT_OP( pb, 0 );
		rc = pblock_add_control( pb, (LDAPControl *)value );
		break;
	case SLAPI_REQUESTOR_DN:
		PBLOCK_ASSERT_OP( pb, 0 );
		rc = pblock_set_dn( value, &pb->pb_op->o_dn, &pb->pb_op->o_ndn, pb->pb_op->o_tmpmemctx );
		break;
	case SLAPI_MANAGEDSAIT:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_managedsait = *((int *)value);
		break;
	case SLAPI_X_RELAX:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_relax = *((int *)value);
		break;
	case SLAPI_BACKEND:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_op->o_bd = (BackendDB *)value;
		break;
	case SLAPI_CONNECTION:
		pb->pb_conn = (Connection *)value;
		break;
	case SLAPI_X_CONN_SSF:
		PBLOCK_ASSERT_CONN( pb );
		PBLOCK_LOCK_CONN( pb );
		pb->pb_conn->c_ssf = (slap_ssf_t)(long)value;
		PBLOCK_UNLOCK_CONN( pb );
		break;
	case SLAPI_X_CONN_SASL_CONTEXT:
		PBLOCK_ASSERT_CONN( pb );
		PBLOCK_LOCK_CONN( pb );
		pb->pb_conn->c_sasl_authctx = value;
		PBLOCK_UNLOCK_CONN( pb );
		break;
	case SLAPI_TARGET_DN:
		PBLOCK_ASSERT_OP( pb, 0 );
		rc = pblock_set_dn( value, &pb->pb_op->o_req_dn, &pb->pb_op->o_req_ndn, pb->pb_op->o_tmpmemctx );
		break;
	case SLAPI_CONN_ID:
		PBLOCK_ASSERT_CONN( pb );
		PBLOCK_LOCK_CONN( pb );
		pb->pb_conn->c_connid = *((long *)value);
		PBLOCK_UNLOCK_CONN( pb );
		break;
	case SLAPI_CONN_DN:
		PBLOCK_ASSERT_CONN( pb );
		PBLOCK_LOCK_CONN( pb );
		rc = pblock_set_dn( value, &pb->pb_conn->c_dn, &pb->pb_conn->c_ndn, NULL );
		PBLOCK_UNLOCK_CONN( pb );
		break;
	case SLAPI_RESULT_CODE:
	case SLAPI_PLUGIN_INTOP_RESULT:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_rs->sr_err = *((int *)value);
		break;
	case SLAPI_RESULT_TEXT:
		PBLOCK_ASSERT_OP( pb, 0 );
		snprintf( pb->pb_textbuf, sizeof( pb->pb_textbuf ), "%s", (char *)value );
		pb->pb_rs->sr_text = pb->pb_textbuf;
		break;
	case SLAPI_RESULT_MATCHED:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_rs->sr_matched = (char *)value; /* XXX should dup? */
		break;
	case SLAPI_ADD_ENTRY:
		PBLOCK_ASSERT_OP( pb, 0 );
		if ( pb->pb_op->o_tag == LDAP_REQ_ADD )
			pb->pb_op->ora_e = (Slapi_Entry *)value;
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_MODIFY_MODS: {
		Modifications **mlp;
		Modifications *newmods;

		PBLOCK_ASSERT_OP( pb, 0 );
		rc = pblock_set_default( pb, param, value );
		if ( rc != PBLOCK_SUCCESS ) {
			break;
		}

		if ( pb->pb_op->o_tag == LDAP_REQ_MODIFY ) {
			mlp = &pb->pb_op->orm_modlist;
		} else if ( pb->pb_op->o_tag == LDAP_REQ_ADD ) {
			mlp = &pb->pb_op->ora_modlist;
		} else if ( pb->pb_op->o_tag == LDAP_REQ_MODRDN ) {
			mlp = &pb->pb_op->orr_modlist;
		} else {
			break;
		}

		newmods = slapi_int_ldapmods2modifications( pb->pb_op, (LDAPMod **)value );
		if ( newmods != NULL ) {
			slap_mods_free( *mlp, 1 );
			*mlp = newmods;
		}
		break;
	}
	case SLAPI_MODRDN_NEWRDN:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );
		if ( pb->pb_op->o_tag == LDAP_REQ_MODRDN ) {
			rc = pblock_set_dn( value, &pb->pb_op->orr_newrdn, &pb->pb_op->orr_nnewrdn, pb->pb_op->o_tmpmemctx );
			if ( rc == LDAP_SUCCESS )
				rc = rdn_validate( &pb->pb_op->orr_nnewrdn );
		} else {
			rc = PBLOCK_ERROR;
		}
		break;
	case SLAPI_MODRDN_NEWSUPERIOR:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );
		if ( pb->pb_op->o_tag == LDAP_REQ_MODRDN ) {
			if ( value == NULL ) {
				if ( pb->pb_op->orr_newSup != NULL ) {
					pb->pb_op->o_tmpfree( pb->pb_op->orr_newSup, pb->pb_op->o_tmpmemctx );
					BER_BVZERO( pb->pb_op->orr_newSup );
					pb->pb_op->orr_newSup = NULL;
				}
				if ( pb->pb_op->orr_newSup != NULL ) {
					pb->pb_op->o_tmpfree( pb->pb_op->orr_nnewSup, pb->pb_op->o_tmpmemctx );
					BER_BVZERO( pb->pb_op->orr_nnewSup );
					pb->pb_op->orr_nnewSup = NULL;
				}
			} else {
				if ( pb->pb_op->orr_newSup == NULL ) {
					pb->pb_op->orr_newSup = (struct berval *)pb->pb_op->o_tmpalloc(
						sizeof(struct berval), pb->pb_op->o_tmpmemctx );
					BER_BVZERO( pb->pb_op->orr_newSup );
				}
				if ( pb->pb_op->orr_nnewSup == NULL ) {
					pb->pb_op->orr_nnewSup = (struct berval *)pb->pb_op->o_tmpalloc(
						sizeof(struct berval), pb->pb_op->o_tmpmemctx );
					BER_BVZERO( pb->pb_op->orr_nnewSup );
				}
				rc = pblock_set_dn( value, pb->pb_op->orr_newSup, pb->pb_op->orr_nnewSup, pb->pb_op->o_tmpmemctx );
			}
		} else {
			rc = PBLOCK_ERROR;
		}
		break;
	case SLAPI_MODRDN_DELOLDRDN:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );
		if ( pb->pb_op->o_tag == LDAP_REQ_MODRDN )
			pb->pb_op->orr_deleteoldrdn = *((int *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_SEARCH_SCOPE: {
		int scope = *((int *)value);

		PBLOCK_ASSERT_OP( pb, 0 );
		if ( pb->pb_op->o_tag == LDAP_REQ_SEARCH ) {
			switch ( *((int *)value) ) {
			case LDAP_SCOPE_BASE:
			case LDAP_SCOPE_ONELEVEL:
			case LDAP_SCOPE_SUBTREE:
			case LDAP_SCOPE_SUBORDINATE:
				pb->pb_op->ors_scope = scope;
				break;
			default:
				rc = PBLOCK_ERROR;
				break;
			}
		} else {
			rc = PBLOCK_ERROR;
		}
		break;
	}
	case SLAPI_SEARCH_DEREF:
		PBLOCK_ASSERT_OP( pb, 0 );
		if ( pb->pb_op->o_tag == LDAP_REQ_SEARCH )
			pb->pb_op->ors_deref = *((int *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_SEARCH_SIZELIMIT:
		PBLOCK_ASSERT_OP( pb, 0 );
		if ( pb->pb_op->o_tag == LDAP_REQ_SEARCH )
			pb->pb_op->ors_slimit = *((int *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_SEARCH_TIMELIMIT:
		PBLOCK_ASSERT_OP( pb, 0 );
		if ( pb->pb_op->o_tag == LDAP_REQ_SEARCH )
			pb->pb_op->ors_tlimit = *((int *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_SEARCH_FILTER:
		PBLOCK_ASSERT_OP( pb, 0 );
		if ( pb->pb_op->o_tag == LDAP_REQ_SEARCH )
			pb->pb_op->ors_filter = (Slapi_Filter *)value;
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_SEARCH_STRFILTER:
		PBLOCK_ASSERT_OP( pb, 0 );
		if ( pb->pb_op->o_tag == LDAP_REQ_SEARCH ) {
			pb->pb_op->ors_filterstr.bv_val = (char *)value;
			pb->pb_op->ors_filterstr.bv_len = strlen((char *)value);
		} else {
			rc = PBLOCK_ERROR;
		}
		break;
	case SLAPI_SEARCH_ATTRS: {
		AttributeName *an = NULL;
		size_t i = 0, j = 0;
		char **attrs = (char **)value;

		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag != LDAP_REQ_SEARCH ) {
			rc = PBLOCK_ERROR;
			break;
		}
		/* also set mapped attrs */
		rc = pblock_set_default( pb, param, value );
		if ( rc != PBLOCK_SUCCESS ) {
			break;
		}
		if ( pb->pb_op->ors_attrs != NULL ) {
			pb->pb_op->o_tmpfree( pb->pb_op->ors_attrs, pb->pb_op->o_tmpmemctx );
			pb->pb_op->ors_attrs = NULL;
		}
		if ( attrs != NULL ) {
			for ( i = 0; attrs[i] != NULL; i++ )
				;
		}
		if ( i ) {
			an = (AttributeName *)pb->pb_op->o_tmpcalloc( i + 1,
				sizeof(AttributeName), pb->pb_op->o_tmpmemctx );
			for ( i = 0; attrs[i] != NULL; i++ ) {
				an[j].an_desc = NULL;
				an[j].an_oc = NULL;
				an[j].an_flags = 0;
				an[j].an_name.bv_val = attrs[i];
				an[j].an_name.bv_len = strlen( attrs[i] );
				if ( slap_bv2ad( &an[j].an_name, &an[j].an_desc, &pb->pb_rs->sr_text ) == LDAP_SUCCESS ) {
					j++;
				}
			}
			an[j].an_name.bv_val = NULL;
			an[j].an_name.bv_len = 0;
		}	
		pb->pb_op->ors_attrs = an;
		break;
	}
	case SLAPI_SEARCH_ATTRSONLY:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag == LDAP_REQ_SEARCH )
			pb->pb_op->ors_attrsonly = *((int *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_SEARCH_RESULT_ENTRY:
		PBLOCK_ASSERT_OP( pb, 0 );
		rs_replace_entry( pb->pb_op, pb->pb_rs, NULL, (Slapi_Entry *)value );
		/* TODO: Should REP_ENTRY_MODIFIABLE be set? */
		pb->pb_rs->sr_flags |= REP_ENTRY_MUSTBEFREED;
		break;
	case SLAPI_BIND_RET_SASLCREDS:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_rs->sr_sasldata = (struct berval *)value;
		break;
	case SLAPI_EXT_OP_REQ_OID:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag == LDAP_REQ_EXTENDED ) {
			pb->pb_op->ore_reqoid.bv_val = (char *)value;
			pb->pb_op->ore_reqoid.bv_len = strlen((char *)value);
		} else {
			rc = PBLOCK_ERROR;
		}
		break;
	case SLAPI_EXT_OP_REQ_VALUE:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag == LDAP_REQ_EXTENDED )
			pb->pb_op->ore_reqdata = (struct berval *)value;
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_EXT_OP_RET_OID:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_rs->sr_rspoid = (char *)value;
		break;
	case SLAPI_EXT_OP_RET_VALUE:
		PBLOCK_ASSERT_OP( pb, 0 );
		pb->pb_rs->sr_rspdata = (struct berval *)value;
		break;
	case SLAPI_BIND_METHOD:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag == LDAP_REQ_BIND )
			pb->pb_op->orb_method = *((int *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_BIND_CREDENTIALS:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag == LDAP_REQ_BIND )
			pb->pb_op->orb_cred = *((struct berval *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_COMPARE_TYPE:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag == LDAP_REQ_COMPARE ) {
			const char *text;

			pb->pb_op->orc_ava->aa_desc = NULL;
			rc = slap_str2ad( (char *)value, &pb->pb_op->orc_ava->aa_desc, &text );
		} else {
			rc = PBLOCK_ERROR;
		}
		break;
	case SLAPI_COMPARE_VALUE:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag == LDAP_REQ_COMPARE )
			pb->pb_op->orc_ava->aa_value = *((struct berval *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_ABANDON_MSGID:
		PBLOCK_ASSERT_OP( pb, 0 );
		PBLOCK_VALIDATE_IS_INTOP( pb );

		if ( pb->pb_op->o_tag == LDAP_REQ_ABANDON)
			pb->pb_op->orn_msgid = *((int *)value);
		else
			rc = PBLOCK_ERROR;
		break;
	case SLAPI_REQUESTOR_ISROOT:
	case SLAPI_IS_REPLICATED_OPERATION:
	case SLAPI_CONN_AUTHTYPE:
	case SLAPI_CONN_AUTHMETHOD:
	case SLAPI_IS_INTERNAL_OPERATION:
	case SLAPI_X_CONN_IS_UDP:
	case SLAPI_CONN_CLIENTIP:
	case SLAPI_X_CONN_CLIENTPATH:
	case SLAPI_CONN_SERVERIP:
	case SLAPI_X_CONN_SERVERPATH:
	case SLAPI_X_ADD_STRUCTURAL_CLASS:
		/* These parameters cannot be set */
		rc = PBLOCK_ERROR;
		break;
	default:
		rc = pblock_set_default( pb, param, value );
		break;
	}

	pblock_unlock( pb );

	return rc;
}