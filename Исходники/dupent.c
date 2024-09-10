static int
dupent_parseCtrl (
	Operation *op,
	SlapReply *rs,
	LDAPControl *ctrl )
{
	ber_tag_t tag;
	BerElementBuffer berbuf;
	BerElement *ber = (BerElement *)&berbuf;
	ber_len_t len;
	BerVarray AttributeDescriptionList = NULL;
	ber_len_t cnt = sizeof(struct berval);
	ber_len_t off = 0;
	ber_int_t PartialApplicationAllowed = 1;
	dupent_t *ds = NULL;
	int i;

	if ( op->o_dupent != SLAP_CONTROL_NONE ) {
		rs->sr_text = "Dupent control specified multiple times";
		return LDAP_PROTOCOL_ERROR;
	}

	if ( BER_BVISNULL( &ctrl->ldctl_value ) ) {
		rs->sr_text = "Dupent control value is absent";
		return LDAP_PROTOCOL_ERROR;
	}

	if ( BER_BVISEMPTY( &ctrl->ldctl_value ) ) {
		rs->sr_text = "Dupent control value is empty";
		return LDAP_PROTOCOL_ERROR;
	}

	ber_init2( ber, &ctrl->ldctl_value, 0 );

	/*

   DuplicateEntryRequest ::= SEQUENCE { 
        AttributeDescriptionList, -- from [RFC2251] 
        PartialApplicationAllowed BOOLEAN DEFAULT TRUE } 

        AttributeDescriptionList ::= SEQUENCE OF 
                AttributeDescription 
    
        AttributeDescription ::= LDAPString 
    
        attributeDescription = AttributeType [ ";" <options> ] 

	 */

	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	if ( ber_scanf( ber, "{M}", &AttributeDescriptionList, &cnt, off )
		== LBER_ERROR )
	{
		rs->sr_text = "Dupent control: dupentSpec decoding error";
		rs->sr_err = LDAP_PROTOCOL_ERROR;
		goto done;
	}
	tag = ber_skip_tag( ber, &len );
	if ( tag == LBER_BOOLEAN ) {
		/* NOTE: PartialApplicationAllowed is ignored, since the control
		 * can always be honored
		 */
		if ( ber_scanf( ber, "b", &PartialApplicationAllowed ) == LBER_ERROR )
		{
			rs->sr_text = "Dupent control: dupentSpec decoding error";
			rs->sr_err = LDAP_PROTOCOL_ERROR;
			goto done;
		}
		tag = ber_skip_tag( ber, &len );
	}
	if ( len || tag != LBER_DEFAULT ) {
		rs->sr_text = "Dupent control: dupentSpec decoding error";
		rs->sr_err = LDAP_PROTOCOL_ERROR;
		goto done;
	}

	ds = (dupent_t *)op->o_tmpcalloc( 1,
		sizeof(dupent_t) + sizeof(AttributeName)*cnt,
		op->o_tmpmemctx );

	ds->ds_paa = PartialApplicationAllowed;

	if ( cnt == 0 ) {
		ds->ds_flags |= SLAP_USERATTRS_YES;

	} else {
		int c;

		ds->ds_an = (AttributeName *)&ds[ 1 ];

		for ( i = 0, c = 0; i < cnt; i++ ) {
			const char *text;
			int j;
			int rc;
			AttributeDescription *ad = NULL;

			if ( bvmatch( &AttributeDescriptionList[i],
				slap_bv_all_user_attrs ) )
			{
				if ( ds->ds_flags & SLAP_USERATTRS_YES ) {
					rs->sr_text = "Dupent control: AttributeDescription decoding error";
					rs->sr_err = LDAP_PROTOCOL_ERROR;
					goto done;
				}

				ds->ds_flags |= SLAP_USERATTRS_YES;
				continue;
			}

			rc = slap_bv2ad( &AttributeDescriptionList[i], &ad, &text );
			if ( rc != LDAP_SUCCESS ) {
				continue;
			}

			ds->ds_an[c].an_desc = ad;
			ds->ds_an[c].an_name = ad->ad_cname;

			/* FIXME: not specified; consider this an error, just in case */
			for ( j = 0; j < c; j++ ) {
				if ( ds->ds_an[c].an_desc == ds->ds_an[j].an_desc ) {
					rs->sr_text = "Dupent control: AttributeDescription must be unique within AttributeDescriptionList";
					rs->sr_err = LDAP_PROTOCOL_ERROR;
					goto done;
				}
			}

			c++;
		}

		ds->ds_nattrs = c;

		if ( ds->ds_flags & SLAP_USERATTRS_YES ) {
			/* purge user attrs */
			for ( i = 0; i < ds->ds_nattrs;  ) {
				if ( is_at_operational( ds->ds_an[i].an_desc->ad_type ) ) {
					i++;
					continue;
				}

				ds->ds_nattrs--;
				if ( i < ds->ds_nattrs ) {
					ds->ds_an[i] = ds->ds_an[ds->ds_nattrs];
				}
			}
		}
	}

	op->o_ctrldupent = (void *)ds;

	op->o_dupent = ctrl->ldctl_iscritical
		? SLAP_CONTROL_CRITICAL
		: SLAP_CONTROL_NONCRITICAL;

	rs->sr_err = LDAP_SUCCESS;

done:;
	if ( rs->sr_err != LDAP_SUCCESS ) {
		op->o_tmpfree( ds, op->o_tmpmemctx );
	}

	if ( AttributeDescriptionList != NULL ) {
		ber_memfree_x( AttributeDescriptionList, op->o_tmpmemctx );
	}

	return rs->sr_err;
}