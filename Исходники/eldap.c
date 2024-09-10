static void signal_ldap_error(LDAP * ld, LDAPMessage * res, int ldap_err)
{
	if (ldap_err <= 0) {
#if defined HAVE_LDAP_PARSE_RESULT
		int err;
		ldap_err = ldap_parse_result(ld, res,
					     &err, NULL, NULL, NULL, NULL, 0);
		if (ldap_err == LDAP_SUCCESS)
			ldap_err = err;
#elif defined HAVE_LDAP_GET_LDERRNO
		ldap_err = ldap_get_lderrno(ld, NULL, NULL);
#elif defined HAVE_LDAP_RESULT2ERROR
		ldap_err = ldap_result2error(ld, res, 0);
#else
		ldap_err = ld->ld_errno;
#endif
	}
	signal_simple_error("LDAP error",
			    build_string(ldap_err2string(ldap_err)));
}