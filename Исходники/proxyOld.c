static int
proxyOld_parse(
	Operation *op,
	SlapReply *rs,
	LDAPControl *ctrl )
{
	int rc;
	BerElement	*ber;
	ber_tag_t	tag;
	struct berval dn = BER_BVNULL;
	struct berval authzDN = BER_BVNULL;


	/* We hijack the flag for the new control. Clearly only one or the
	 * other can be used at any given time.
	 */
	if ( op->o_proxy_authz != SLAP_CONTROL_NONE ) {
		rs->sr_text = "proxy authorization control specified multiple times";
		return LDAP_PROTOCOL_ERROR;
	}

	op->o_proxy_authz = ctrl->ldctl_iscritical
		? SLAP_CONTROL_CRITICAL
		: SLAP_CONTROL_NONCRITICAL;

	/* Parse the control value
	 *  proxyAuthzControlValue ::= SEQUENCE {
	 *		proxyDN	LDAPDN
	 *	}
	 */
	ber = ber_init( &ctrl->ldctl_value );
	if ( ber == NULL ) {
		rs->sr_text = "ber_init failed";
		return LDAP_OTHER;
	}

	tag = ber_scanf( ber, "{m}", &dn );

	if ( tag == LBER_ERROR ) {
		rs->sr_text = "proxyOld control could not be decoded";
		rc = LDAP_OTHER;
		goto done;
	}
	if ( BER_BVISEMPTY( &dn )) {
		Debug( LDAP_DEBUG_TRACE,
			"proxyOld_parse: conn=%lu anonymous\n",
				op->o_connid, 0, 0 );
		authzDN.bv_val = ch_strdup("");
	} else {
		Debug( LDAP_DEBUG_ARGS,
			"proxyOld_parse: conn %lu ctrl DN=\"%s\"\n",
				op->o_connid, dn.bv_val, 0 );
		rc = dnNormalize( 0, NULL, NULL, &dn, &authzDN, op->o_tmpmemctx );
		if ( rc != LDAP_SUCCESS ) {
			goto done;
		}
		rc = slap_sasl_authorized( op, &op->o_ndn, &authzDN );
		if ( rc ) {
			op->o_tmpfree( authzDN.bv_val, op->o_tmpmemctx );
			rs->sr_text = "not authorized to assume identity";
			/* new spec uses LDAP_PROXY_AUTHZ_FAILURE */
			rc = LDAP_INSUFFICIENT_ACCESS;
			goto done;
		}
	}
	free( op->o_ndn.bv_val );
	free( op->o_dn.bv_val );
	op->o_ndn = authzDN;
	ber_dupbv( &op->o_dn, &authzDN );

	Statslog( LDAP_DEBUG_STATS, "conn=%lu op=%lu PROXYOLD dn=\"%s\"\n",
		op->o_connid, op->o_opid,
		authzDN.bv_len ? authzDN.bv_val : "anonymous", 0, 0 );
	rc = LDAP_SUCCESS;
done:
	ber_free( ber, 1 );
	return rc;
}