int _ldap_lookup(void)
{
	char *attrs[] = { NULL };
	char *filter, *dn;
	char **values;
	LDAP *ld;
	LDAPMessage *res, *entry;
	int ret;

	ld = ldap_init(LDAP_HOST, LDAP_PORT);
	if (!ld) {
		fprintf(stderr, "%s: unable to initialise ldap connection\n",
				prog);
		return 1;
	}

	ret = ldap_simple_bind_s(ld, LDAP_BIND_DN, LDAP_BIND_PASSWD);

	if (ret)
		return 1;

	filter = malloc(sizeof(LDAP_FILTER) + strlen(user) + strlen(host));
	sprintf(filter, LDAP_FILTER, user, host);

	ret = ldap_search_s(ld, LDAP_BASE, LDAP_SCOPE, filter, attrs, 0, &res);
	if (ret) {
		fprintf(stderr, "%s: ldap search failed: %s\n", prog,
				ldap_err2string(ret));
		return 1;
	}

	entry = ldap_first_entry(ld, res);


	if (!entry)
		return 1;

	dn = ldap_get_dn(ld, res);
	
	ldap_msgfree(res);

	ret = ldap_simple_bind_s(ld, dn, password);

	if (ret)
		return 1;

	ldap_memfree(dn);
	ldap_unbind(ld);
	return 0;
}