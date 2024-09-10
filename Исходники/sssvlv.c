/* Conforms to RFC4510 re: Criticality, original RFC2891 spec is broken
 * Also see ITS#7253 for discussion
 */
static int sss_parseCtrl(
	Operation		*op,
	SlapReply		*rs,
	LDAPControl		*ctrl )
{
	BerElementBuffer	berbuf;
	BerElement			*ber;
	ber_tag_t		tag;
	ber_len_t		len;
	int					i;
	sort_ctrl	*sc;

	rs->sr_err = LDAP_PROTOCOL_ERROR;

	if ( op->o_ctrlflag[sss_cid] > SLAP_CONTROL_IGNORED ) {
		rs->sr_text = "sorted results control specified multiple times";
	} else if ( BER_BVISNULL( &ctrl->ldctl_value ) ) {
		rs->sr_text = "sorted results control value is absent";
	} else if ( BER_BVISEMPTY( &ctrl->ldctl_value ) ) {
		rs->sr_text = "sorted results control value is empty";
	} else {
		rs->sr_err = LDAP_SUCCESS;
	}
	if ( rs->sr_err != LDAP_SUCCESS )
		return rs->sr_err;

	op->o_ctrlflag[sss_cid] = ctrl->ldctl_iscritical ?
		SLAP_CONTROL_CRITICAL : SLAP_CONTROL_NONCRITICAL;

	ber = (BerElement *)&berbuf;
	ber_init2( ber, &ctrl->ldctl_value, 0 );
	i = count_key( ber );

	sc = op->o_tmpalloc( sizeof(sort_ctrl) +
		(i-1) * sizeof(sort_key), op->o_tmpmemctx );
	sc->sc_nkeys = i;
	op->o_controls[sss_cid] = sc;

	/* peel off initial sequence */
	ber_scanf( ber, "{" );

	i = 0;
	do {
		if ( build_key( ber, rs, &sc->sc_keys[i] ) != LDAP_SUCCESS )
			break;
		i++;
		tag = ber_peek_tag( ber, &len );
	} while ( tag != LBER_DEFAULT );

	return rs->sr_err;
}