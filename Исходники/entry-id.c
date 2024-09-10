/*
 * NOTE: the dn must be normalized
 */
int
backsql_dn2id(
	Operation		*op,
	SlapReply		*rs,
	SQLHDBC			dbh,
	struct berval		*ndn,
	backsql_entryID		*id,
	int			matched,
	int			muck )
{
	backsql_info		*bi = op->o_bd->be_private;
	SQLHSTMT		sth = SQL_NULL_HSTMT; 
	BACKSQL_ROW_NTS		row = { 0 };
	RETCODE 		rc;
	int			res;
	struct berval		realndn = BER_BVNULL;

	/* TimesTen */
	char			upperdn[ BACKSQL_MAX_DN_LEN + 1 ];
	struct berval		tbbDN;
	int			i, j;

	/*
	 * NOTE: id can be NULL; in this case, the function
	 * simply checks whether the DN can be successfully 
	 * turned into an ID, returning LDAP_SUCCESS for
	 * positive cases, or the most appropriate error
	 */

	Debug( LDAP_DEBUG_TRACE, "==>backsql_dn2id(\"%s\")%s%s\n", 
			ndn->bv_val, id == NULL ? " (no ID expected)" : "",
			matched ? " matched expected" : "" );

	if ( id ) {
		/* NOTE: trap inconsistencies */
		assert( BER_BVISNULL( &id->eid_ndn ) );
	}

	if ( ndn->bv_len > BACKSQL_MAX_DN_LEN ) {
		Debug( LDAP_DEBUG_TRACE, 
			"   backsql_dn2id(\"%s\"): DN length=%ld "
			"exceeds max DN length %d:\n",
			ndn->bv_val, ndn->bv_len, BACKSQL_MAX_DN_LEN );
		return LDAP_OTHER;
	}

	/* return baseObject if available and matches */
	/* FIXME: if ndn is already mucked, we cannot check this */
	if ( bi->sql_baseObject != NULL &&
			dn_match( ndn, &bi->sql_baseObject->e_nname ) )
	{
		if ( id != NULL ) {
#ifdef BACKSQL_ARBITRARY_KEY
			ber_dupbv_x( &id->eid_id, &backsql_baseObject_bv,
					op->o_tmpmemctx );
			ber_dupbv_x( &id->eid_keyval, &backsql_baseObject_bv,
					op->o_tmpmemctx );
#else /* ! BACKSQL_ARBITRARY_KEY */
			id->eid_id = BACKSQL_BASEOBJECT_ID;
			id->eid_keyval = BACKSQL_BASEOBJECT_KEYVAL;
#endif /* ! BACKSQL_ARBITRARY_KEY */
			id->eid_oc_id = BACKSQL_BASEOBJECT_OC;

			ber_dupbv_x( &id->eid_ndn, &bi->sql_baseObject->e_nname,
					op->o_tmpmemctx );
			ber_dupbv_x( &id->eid_dn, &bi->sql_baseObject->e_name,
					op->o_tmpmemctx );

			id->eid_next = NULL;
		}

		return LDAP_SUCCESS;
	}
	
	/* begin TimesTen */
	Debug( LDAP_DEBUG_TRACE, "   backsql_dn2id(\"%s\"): id_query \"%s\"\n",
			ndn->bv_val, bi->sql_id_query, 0 );
	assert( bi->sql_id_query != NULL );
 	rc = backsql_Prepare( dbh, &sth, bi->sql_id_query, 0 );
	if ( rc != SQL_SUCCESS ) {
		Debug( LDAP_DEBUG_TRACE, 
			"   backsql_dn2id(\"%s\"): "
			"error preparing SQL:\n   %s", 
			ndn->bv_val, bi->sql_id_query, 0 );
		backsql_PrintErrors( bi->sql_db_env, dbh, sth, rc );
		res = LDAP_OTHER;
		goto done;
	}

	realndn = *ndn;
	if ( muck ) {
		if ( backsql_api_dn2odbc( op, rs, &realndn ) ) {
			Debug( LDAP_DEBUG_TRACE, "   backsql_dn2id(\"%s\"): "
				"backsql_api_dn2odbc(\"%s\") failed\n", 
				ndn->bv_val, realndn.bv_val, 0 );
			res = LDAP_OTHER;
			goto done;
		}
	}

	if ( BACKSQL_HAS_LDAPINFO_DN_RU( bi ) ) {
		/*
		 * Prepare an upper cased, byte reversed version 
		 * that can be searched using indexes
		 */

		for ( i = 0, j = realndn.bv_len - 1; realndn.bv_val[ i ]; i++, j--)
		{
			upperdn[ i ] = realndn.bv_val[ j ];
		}
		upperdn[ i ] = '\0';
		ldap_pvt_str2upper( upperdn );

		Debug( LDAP_DEBUG_TRACE, "   backsql_dn2id(\"%s\"): "
				"upperdn=\"%s\"\n",
				ndn->bv_val, upperdn, 0 );
		ber_str2bv( upperdn, 0, 0, &tbbDN );

	} else {
		if ( BACKSQL_USE_REVERSE_DN( bi ) ) {
			AC_MEMCPY( upperdn, realndn.bv_val, realndn.bv_len + 1 );
			ldap_pvt_str2upper( upperdn );
			Debug( LDAP_DEBUG_TRACE,
				"   backsql_dn2id(\"%s\"): "
				"upperdn=\"%s\"\n",
				ndn->bv_val, upperdn, 0 );
			ber_str2bv( upperdn, 0, 0, &tbbDN );

		} else {
			tbbDN = realndn;
		}
	}

	rc = backsql_BindParamBerVal( sth, 1, SQL_PARAM_INPUT, &tbbDN );
	if ( rc != SQL_SUCCESS) {
		/* end TimesTen */ 
		Debug( LDAP_DEBUG_TRACE, "   backsql_dn2id(\"%s\"): "
			"error binding dn=\"%s\" parameter:\n", 
			ndn->bv_val, tbbDN.bv_val, 0 );
		backsql_PrintErrors( bi->sql_db_env, dbh, sth, rc );
		res = LDAP_OTHER;
		goto done;
	}

	rc = SQLExecute( sth );
	if ( rc != SQL_SUCCESS ) {
		Debug( LDAP_DEBUG_TRACE, "   backsql_dn2id(\"%s\"): "
			"error executing query (\"%s\", \"%s\"):\n", 
			ndn->bv_val, bi->sql_id_query, tbbDN.bv_val );
		backsql_PrintErrors( bi->sql_db_env, dbh, sth, rc );
		res = LDAP_OTHER;
		goto done;
	}

	backsql_BindRowAsStrings_x( sth, &row, op->o_tmpmemctx );
	rc = SQLFetch( sth );
	if ( BACKSQL_SUCCESS( rc ) ) {
		char	buf[ SLAP_TEXT_BUFLEN ];

#ifdef LDAP_DEBUG
		snprintf( buf, sizeof(buf),
			"id=%s keyval=%s oc_id=%s dn=%s",
			row.cols[ 0 ], row.cols[ 1 ],
			row.cols[ 2 ], row.cols[ 3 ] );
		Debug( LDAP_DEBUG_TRACE,
			"   backsql_dn2id(\"%s\"): %s\n",
			ndn->bv_val, buf, 0 );
#endif /* LDAP_DEBUG */

		res = LDAP_SUCCESS;
		if ( id != NULL ) {
			struct berval	dn;

			id->eid_next = NULL;

#ifdef BACKSQL_ARBITRARY_KEY
			ber_str2bv_x( row.cols[ 0 ], 0, 1, &id->eid_id,
					op->o_tmpmemctx );
			ber_str2bv_x( row.cols[ 1 ], 0, 1, &id->eid_keyval,
					op->o_tmpmemctx );
#else /* ! BACKSQL_ARBITRARY_KEY */
			if ( lutil_atoulx( &id->eid_id, row.cols[ 0 ], 0 ) != 0 ) {
				res = LDAP_OTHER;
				goto done;
			}
			if ( lutil_atoulx( &id->eid_keyval, row.cols[ 1 ], 0 ) != 0 ) {
				res = LDAP_OTHER;
				goto done;
			}
#endif /* ! BACKSQL_ARBITRARY_KEY */
			if ( lutil_atoulx( &id->eid_oc_id, row.cols[ 2 ], 0 ) != 0 ) {
				res = LDAP_OTHER;
				goto done;
			}

			ber_str2bv( row.cols[ 3 ], 0, 0, &dn );

			if ( backsql_api_odbc2dn( op, rs, &dn ) ) {
				res = LDAP_OTHER;
				goto done;
			}
			
			res = dnPrettyNormal( NULL, &dn,
					&id->eid_dn, &id->eid_ndn,
					op->o_tmpmemctx );
			if ( res != LDAP_SUCCESS ) {
				Debug( LDAP_DEBUG_TRACE,
					"   backsql_dn2id(\"%s\"): "
					"dnPrettyNormal failed (%d: %s)\n",
					realndn.bv_val, res,
					ldap_err2string( res ) );

				/* cleanup... */
				(void)backsql_free_entryID( id, 0, op->o_tmpmemctx );
			}

			if ( dn.bv_val != row.cols[ 3 ] ) {
				free( dn.bv_val );
			}
		}

	} else {
		res = LDAP_NO_SUCH_OBJECT;
		if ( matched ) {
			struct berval	pdn = *ndn;

			/*
			 * Look for matched
			 */
			rs->sr_matched = NULL;
			while ( !be_issuffix( op->o_bd, &pdn ) ) {
				char		*matchedDN = NULL;
	
				dnParent( &pdn, &pdn );
	
				/*
				 * Empty DN ("") defaults to LDAP_SUCCESS
				 */
				rs->sr_err = backsql_dn2id( op, rs, dbh, &pdn, id, 0, 1 );
				switch ( rs->sr_err ) {
				case LDAP_NO_SUCH_OBJECT:
					/* try another one */
					break;
					
				case LDAP_SUCCESS:
					matchedDN = pdn.bv_val;
					/* fail over to next case */
	
				default:
					rs->sr_err = LDAP_NO_SUCH_OBJECT;
					rs->sr_matched = matchedDN;
					goto done;
				} 
			}
		}
	}

done:;
	backsql_FreeRow_x( &row, op->o_tmpmemctx );

	Debug( LDAP_DEBUG_TRACE,
		"<==backsql_dn2id(\"%s\"): err=%d\n",
		ndn->bv_val, res, 0 );
	if ( sth != SQL_NULL_HSTMT ) {
		SQLFreeStmt( sth, SQL_DROP );
	}

	if ( !BER_BVISNULL( &realndn ) && realndn.bv_val != ndn->bv_val ) {
		ch_free( realndn.bv_val );
	}

	return res;
}