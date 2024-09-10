static int user_bind(char *connstr, char *dn, const char *password)
{
	LDAP *ld;
	int opt, rc;

	if (ldap_initialize(&ld, connstr) != LDAP_SUCCESS) {
		_log(1, "Cannot ldap_initialize-2");
		return (FALSE);
	}

	opt = LDAP_VERSION3;
	ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &opt);

	if ((rc = ldap_simple_bind_s(ld, dn, password)) != LDAP_SUCCESS) {
		_log(1, "Cannot bind to LDAP as %s: %s", dn, ldap_err2string(rc));
		return (FALSE);
	}

	ldap_unbind(ld);
	return (TRUE);

}