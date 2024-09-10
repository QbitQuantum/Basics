/*
 * controlType = LDAP_CONTROL_GET_EFFECTIVE_RIGHTS;
 * criticality = n/a;
 * controlValue = OCTET STRING of BER encoding of the SEQUENCE of
 *				  ENUMERATED LDAP code
 */
void
_ger_set_response_control (
	Slapi_PBlock	*pb,
	int				iscritical,
	int				rc
	)
{
	LDAPControl **resultctrls = NULL;
	LDAPControl gerrespctrl;
	BerElement *ber = NULL;
	struct berval *berval = NULL;
	int found = 0;
	int i;

	if ( (ber = der_alloc ()) == NULL )
	{
		goto bailout;
	}

	/* begin sequence, enumeration, end sequence */
	ber_printf ( ber, "{e}", rc );
	if ( ber_flatten ( ber, &berval ) != LDAP_SUCCESS )
	{
		goto bailout;
	}
	gerrespctrl.ldctl_oid = LDAP_CONTROL_GET_EFFECTIVE_RIGHTS;
	gerrespctrl.ldctl_iscritical = iscritical;
	gerrespctrl.ldctl_value.bv_val = berval->bv_val;
	gerrespctrl.ldctl_value.bv_len = berval->bv_len;

	slapi_pblock_get ( pb, SLAPI_RESCONTROLS, &resultctrls );
	for (i = 0; resultctrls && resultctrls[i]; i++)
	{
		if (strcmp(resultctrls[i]->ldctl_oid, LDAP_CONTROL_GET_EFFECTIVE_RIGHTS) == 0)
		{
			/*
			 * We get here if search returns more than one entry
			 * and this is not the first entry.
			 */
			ldap_control_free ( resultctrls[i] );
			resultctrls[i] = slapi_dup_control (&gerrespctrl);
			found = 1;
			break;
		}
	}

	if ( !found )
	{
		/* slapi_pblock_set() will dup the control */
		slapi_pblock_set ( pb, SLAPI_ADD_RESCONTROL, &gerrespctrl );
	}

bailout:
	ber_free ( ber, 1 );	/* ber_free() checks for NULL param */
	ber_bvfree ( berval );	/* ber_bvfree() checks for NULL param */
}