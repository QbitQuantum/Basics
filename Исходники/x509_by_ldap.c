/* wrappers to some depricated functions */
static void
ldaplookup_parse_result (
	LDAP *ld,
	LDAPMessage *res
) {
	static const int freeit = 0;
	int result;
#ifdef HAVE_LDAP_PARSE_RESULT
	int ret;
	char *matcheddn;
	char *errmsg;

	ret = ldap_parse_result(ld, res, &result, &matcheddn, &errmsg, NULL, NULL, freeit);
	if (ret == LDAP_SUCCESS) {
		if (errmsg) ERR_add_error_data(1, errmsg);
	}
	if (matcheddn) ldap_memfree(matcheddn);
	if (errmsg)    ldap_memfree(errmsg);
#else
	result = ldap_result2error(ld, res, freeit);
	openssl_add_ldap_error(result);
#endif
}