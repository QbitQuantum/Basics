static int
valsort_parseCtrl(
	Operation *op,
	SlapReply *rs,
	LDAPControl *ctrl )
{
	ber_tag_t tag;
	BerElementBuffer berbuf;
	BerElement *ber = (BerElement *)&berbuf;
	ber_int_t flag = 0;

	if ( BER_BVISNULL( &ctrl->ldctl_value )) {
		rs->sr_text = "valSort control value is absent";
		return LDAP_PROTOCOL_ERROR;
	}

	if ( BER_BVISEMPTY( &ctrl->ldctl_value )) {
		rs->sr_text = "valSort control value is empty";
		return LDAP_PROTOCOL_ERROR;
	}

	ber_init2( ber, &ctrl->ldctl_value, 0 );
	if (( tag = ber_scanf( ber, "{b}", &flag )) == LBER_ERROR ) {
		rs->sr_text = "valSort control: flag decoding error";
		return LDAP_PROTOCOL_ERROR;
	}

	op->o_ctrlflag[valsort_cid] = ctrl->ldctl_iscritical ?
		SLAP_CONTROL_CRITICAL : SLAP_CONTROL_NONCRITICAL;
	if ( flag )
		op->o_ctrlflag[valsort_cid] |= SLAP_CONTROL_DATA0;

	return LDAP_SUCCESS;
}