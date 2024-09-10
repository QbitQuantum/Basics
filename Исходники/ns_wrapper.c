/* ARGSUSED */
int _ns_ldap_result(char *service, int flags,
	int msgid, int all,
	struct timeval *timeout, LDAPMessage **result)
{
	LDAP *ld = __s_api_getLDAPconn(flags);

	return (ldap_result(ld, msgid, all, timeout, result));
}