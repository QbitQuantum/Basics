int ldap_parse_virtuallist_control(LDAP *ld, LDAPControl **ctrls,
	unsigned long *target_posp, unsigned long *list_sizep, int *errcodep)
{
	BerElement *ber;
	int i, foundListControl;
	LDAPControl *listCtrlp;

	if (NULL == ld)
		return (LDAP_PARAM_ERROR);

	/* only ldapv3 or higher can do virtual lists. */
	if (ld->ld_version != LDAP_VERSION3) {
		ld->ld_errno = LDAP_NOT_SUPPORTED;
		return (LDAP_NOT_SUPPORTED);
	}

	/* find the listControl in the list of controls if it exists */
	if (ctrls == NULL) {
		ld->ld_errno = LDAP_NOT_SUPPORTED;
		return (LDAP_NOT_SUPPORTED);
	}

	foundListControl = 0;
	for (i = 0; ((ctrls[i] != NULL) && (!foundListControl)); i++) {
		foundListControl = !(strcmp(ctrls[i]->ldctl_oid,
			LDAP_CONTROL_VLVRESPONSE));
	}
	if (!foundListControl) {
		ld->ld_errno = LDAP_CONTROL_NOT_FOUND;
		return (LDAP_CONTROL_NOT_FOUND);
	} else {
		/* let local var point to the listControl */
		listCtrlp = ctrls[i-1];
	}

	/* allocate a Ber element with the contents of the list_control's */
	/* struct berval */
	if ((ber = ber_init(&listCtrlp->ldctl_value)) == NULL) {
		ld->ld_errno = LDAP_NO_MEMORY;
		return (LDAP_NO_MEMORY);
	}

	/* decode the result from the Berelement */
	if (LBER_ERROR == ber_scanf(ber, "{iie}", target_posp, list_sizep,
		errcodep)) {
		ld->ld_errno = LDAP_DECODING_ERROR;
		ber_free(ber, 1);
		return (LDAP_DECODING_ERROR);
	}

	/* the ber encoding is no longer needed */
	ber_free(ber, 1);

	return (LDAP_SUCCESS);
}