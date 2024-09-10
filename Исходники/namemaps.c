static
idmap_stat
winname2dn(idmap_nm_handle_t *p, char *winname,
    int *is_wuser, char **dn, char **unixuser, char **unixgroup)
{
	idmap_stat rc = IDMAP_SUCCESS;
	char *base;
	char *filter;
	int flen;
	char *attribs[4];
	int i;
	LDAPMessage *results = NULL;
	LDAPMessage *entry;
	int ldap_rc;

	/* Query: */

	base = dns2dn(p->windomain, "");
	if (base == NULL) {
		return (IDMAP_ERR_MEMORY);
	}

	i = 0;
	attribs[i++] = "objectClass";
	if (unixuser != NULL)
		attribs[i++] = p->ad_unixuser_attr;
	if (unixgroup != NULL)
		attribs[i++] = p->ad_unixgroup_attr;
	attribs[i] = NULL;

	flen = snprintf(NULL, 0, FILTER, winname) + 1;
	if ((filter = (char *)malloc(flen)) == NULL) {
		free(base);
		return (IDMAP_ERR_MEMORY);
	}
	(void) snprintf(filter, flen, FILTER, winname);

	ldap_rc = ldap_search_s(p->ad, base, LDAP_SCOPE_SUBTREE, filter,
	    attribs, 0, &results);

	free(base);
	free(filter);

	if (ldap_rc != LDAP_SUCCESS) {
		namemap_log(
		    gettext("Ldap query to server %s port %d failed. (%s)"),
		    p->ad_host, p->ad_port, ldap_err2string(ldap_rc));
		(void) ldap_msgfree(results);
		return (IDMAP_ERR_OTHER);
	}


	for (entry = ldap_first_entry(p->ad, results), *dn = NULL;
	    entry != NULL;
	    entry = ldap_next_entry(p->ad, entry)) {
		char	**values = NULL;
		int i = 0;
		values = ldap_get_values(p->ad, entry, "objectClass");

		if (values == NULL) {
			(void) ldap_msgfree(results);
			return (IDMAP_ERR_MEMORY);
		}

		for (i = 0; i < ldap_count_values(values); i++) {
		/*
		 * is_wuser can be IDMAP_UNKNOWN, in that case we accept
		 * both User/Group
		 */
			if (*is_wuser != IDMAP_NO &&
			    strcasecmp(values[i], "User") == 0 ||
			    *is_wuser != IDMAP_YES &&
			    strcasecmp(values[i], "Group") == 0) {
				*dn = ldap_get_dn(p->ad, entry);
				if (*dn == NULL) {
					ldap_value_free(values);
					(void) ldap_msgfree(results);
					return (IDMAP_ERR_MEMORY);
				}
				*is_wuser = strcasecmp(values[i], "User") == 0
				    ? IDMAP_YES : IDMAP_NO;
				break;
			}
		}

		ldap_value_free(values);
		if (*dn != NULL)
			break;
	}

	if (*dn == NULL) {
		namemap_log(
		    *is_wuser == IDMAP_YES ? gettext("User %s@%s not found") :
		    *is_wuser == IDMAP_NO ? gettext("Group %s@%s not found") :
		    gettext("%s@%s not found"), winname, p->windomain);
		return (IDMAP_ERR_NOTFOUND);
	}

	if (unixuser != NULL)
		rc = extract_attribute(p, entry, p->ad_unixuser_attr,
		    unixuser);

	if (rc == IDMAP_SUCCESS && unixgroup != NULL)
		rc = extract_attribute(p, entry, p->ad_unixgroup_attr,
		    unixgroup);

	(void) ldap_msgfree(results);

	return (rc);
}