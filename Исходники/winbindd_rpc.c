static int get_ldap_seq(const char *server, int port, uint32 *seq)
{
	int ret = -1;
	struct timeval to;
	char *attrs[] = {"highestCommittedUSN", NULL};
	LDAPMessage *res = NULL;
	char **values = NULL;
	LDAP *ldp = NULL;

	*seq = DOM_SEQUENCE_NONE;

	/*
	 * Parameterised (5) second timeout on open. This is needed as the search timeout
	 * doesn't seem to apply to doing an open as well. JRA.
	 */

	if ((ldp = ldap_open_with_timeout(server, port, lp_ldap_timeout())) == NULL)
		return -1;

	/* Timeout if no response within 20 seconds. */
	to.tv_sec = 10;
	to.tv_usec = 0;

	if (ldap_search_st(ldp, "", LDAP_SCOPE_BASE, "(objectclass=*)", &attrs[0], 0, &to, &res))
		goto done;

	if (ldap_count_entries(ldp, res) != 1)
		goto done;

	values = ldap_get_values(ldp, res, "highestCommittedUSN");
	if (!values || !values[0])
		goto done;

	*seq = atoi(values[0]);
	ret = 0;

  done:

	if (values)
		ldap_value_free(values);
	if (res)
		ldap_msgfree(res);
	if (ldp)
		ldap_unbind(ldp);
	return ret;
}