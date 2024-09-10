char *
gfarm_generic_info_get(
	void *key,
	void *info,
	const struct gfarm_generic_info_ops *ops)
{
	LDAPMessage *res, *e;
	int n, rv;
	char *a;
	BerElement *ptr;
	char **vals;
	char *dn = ops->make_dn(key);

	if (dn == NULL)
		return (GFARM_ERR_NO_MEMORY);
	rv = ldap_search_s(gfarm_ldap_server, dn, 
	    LDAP_SCOPE_BASE, ops->query_type, NULL, 0, &res);
	free(dn);
	if (rv != LDAP_SUCCESS) {
		if (rv == LDAP_NO_SUCH_OBJECT)
			return (GFARM_ERR_NO_SUCH_OBJECT);
		return (ldap_err2string(rv));
	}
	n = ldap_count_entries(gfarm_ldap_server, res);
	if (n == 0) {
		/* free the search results */
		ldap_msgfree(res);
		return (GFARM_ERR_NO_SUCH_OBJECT);
	}
	ops->clear(info);
	e = ldap_first_entry(gfarm_ldap_server, res);
	for (a = ldap_first_attribute(gfarm_ldap_server, e, &ptr); a != NULL;
	    a = ldap_next_attribute(gfarm_ldap_server, e, ptr)) {

		vals = ldap_get_values(gfarm_ldap_server, e, a);
		if (vals[0] == NULL) {
			ldap_value_free(vals);
			continue;
		}

		ops->set_field(info, a, vals);

		ldap_value_free(vals);
	}

	/* free the search results */
	ldap_msgfree(res);

	/* should check all fields are filled */
	if (!ops->validate(info)) {
		ops->free(info);
		/* XXX - different error code is better ? */
		return (GFARM_ERR_NO_SUCH_OBJECT);
	}

	return (NULL); /* success */
}