static int
ldap_search_ext_s_wrapper(LDAP *ld, char *base, int scope, char *filter,
    char *attrs[], int attrsonly, LDAPControl **serverctrls,
    LDAPControl **clientctrls, struct timeval *timeout, int sizelimit,
    LDAPMessage **res)
{

#ifdef AUTH_LDAP_TEST_API
	return (ldap_search_ext_s(ld, base, scope, filter, attrs,
	    attrsonly, serverctrls, clientctrls, timeout, sizelimit, res));
#else
	return ((*ldap_search_ext_s_p)(ld, base, scope, filter, attrs,
	    attrsonly, serverctrls, clientctrls, timeout, sizelimit, res));
#endif
}