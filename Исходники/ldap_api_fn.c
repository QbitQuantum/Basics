int ldap_get_attr_vals(str *_attr_name, struct berval ***_vals)
{
	BerElement *ber;
	char *a;

	/*
	* check for last_ldap_result
	*/
	if (last_ldap_result == NULL) {
		LM_ERR("last_ldap_result == NULL\n");
		return -1;
	}
	if (last_ldap_handle == NULL)
	{
		LM_ERR("last_ldap_handle == NULL\n");
		return -1;
	}

	/*
	* search for attribute named _attr_name
	*/
	*_vals = NULL;
	for (a = ldap_first_attribute(last_ldap_handle,
			last_ldap_result,
			&ber);
		a != NULL;
		a = ldap_next_attribute(last_ldap_handle,
			last_ldap_result,
			ber))
	{
		if (strlen(a) == _attr_name->len &&
				strncmp(a, _attr_name->s, _attr_name->len) == 0) {
			*_vals = ldap_get_values_len(
				last_ldap_handle,
				last_ldap_result,
				a);
			ldap_memfree(a);
			break;
		}
		ldap_memfree(a);
	}

	if (ber != NULL) {
		ber_free(ber, 0);
	}

	if (*_vals != NULL)
	{
		return 0;
	} else {
		return 1;
	}
}