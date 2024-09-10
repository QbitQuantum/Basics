/* Check the userid & password.
 * Return 0 on success, 1 on failure
 */
static int
checkLDAP(LDAP * persistent_ld, const char *userid, const char *password, const char *ldapServer, int port)
{
    char dn[1024];
    int ret = 0;
    LDAP *bind_ld = NULL;

    if (!*password) {
	/* LDAP can't bind with a blank password. Seen as "anonymous"
	 * and always granted access
	 */
	if (debug)
	    fprintf(stderr, "Blank password given\n");
	return 1;
    }
    if (searchfilter) {
	char filter[16384];
	char escaped_login[1024];
	LDAPMessage *res = NULL;
	LDAPMessage *entry;
	char *searchattr[] =
	{(char *)LDAP_NO_ATTRS, NULL};
	char *userdn;
	int rc;
	LDAP *search_ld = persistent_ld;

	if (!search_ld)
	    search_ld = open_ldap_connection(ldapServer, port);

	ldap_escape_value(escaped_login, sizeof(escaped_login), userid);
	if (binddn) {
	    rc = ldap_simple_bind_s(search_ld, binddn, bindpasswd);
	    if (rc != LDAP_SUCCESS) {
		fprintf(stderr, PROGRAM_NAME ": WARNING, could not bind to binddn '%s'\n", ldap_err2string(rc));
		ret = 1;
		goto search_done;
	    }
	}
	snprintf(filter, sizeof(filter), searchfilter, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login, escaped_login);
	if (debug)
	    fprintf(stderr, "user filter '%s', searchbase '%s'\n", filter, basedn);
	rc = ldap_search_s(search_ld, basedn, searchscope, filter, searchattr, 1, &res);
	if (rc != LDAP_SUCCESS) {
	    if (noreferrals && rc == LDAP_PARTIAL_RESULTS) {
		/* Everything is fine. This is expected when referrals
		 * are disabled.
		 */
		if (debug)
		    fprintf(stderr, "noreferrals && rc == LDAP_PARTIAL_RESULTS\n");
	    } else {
		fprintf(stderr, PROGRAM_NAME ": WARNING, LDAP search error '%s'\n", ldap_err2string(rc));
#if defined(NETSCAPE_SSL)
		if (sslpath && ((rc == LDAP_SERVER_DOWN) || (rc == LDAP_CONNECT_ERROR))) {
		    int sslerr = PORT_GetError();
		    fprintf(stderr, PROGRAM_NAME ": WARNING, SSL error %d (%s)\n", sslerr, ldapssl_err2string(sslerr));
		}
#endif
		ret = 1;
		goto search_done;
	    }
	}
	entry = ldap_first_entry(search_ld, res);
	if (!entry) {
	    if (debug)
		fprintf(stderr, "Ldap search returned nothing\n");
	    ret = 1;
	    goto search_done;
	}
	userdn = ldap_get_dn(search_ld, entry);
	if (!userdn) {
	    fprintf(stderr, PROGRAM_NAME ": ERROR, could not get user DN for '%s'\n", userid);
	    ret = 1;
	    goto search_done;
	}
	snprintf(dn, sizeof(dn), "%s", userdn);
	squid_ldap_memfree(userdn);

	if (ret == 0 && (!binddn || !bind_once || passwdattr)) {
	    /* Reuse the search connection for comparing the user password attribute */
	    bind_ld = search_ld;
	    search_ld = NULL;
	}
      search_done:
	if (res) {
	    ldap_msgfree(res);
	    res = NULL;
	}
	if (search_ld && search_ld != persistent_ld) {
	    ldap_unbind(search_ld);
	    search_ld = NULL;
	}
	if (ret != 0)
	    return ret;
    } else {
	snprintf(dn, sizeof(dn), "%s=%s,%s", userattr, userid, basedn);
    }

    if (debug)
	fprintf(stderr, "attempting to authenticate user '%s'\n", dn);
    if (!bind_ld && !bind_once)
	bind_ld = persistent_ld;
    if (!bind_ld)
	bind_ld = open_ldap_connection(ldapServer, port);
    if (passwdattr) {
	if (ldap_compare_s(bind_ld, dn, passwdattr, password) != LDAP_COMPARE_TRUE) {
	    ret = 1;
	}
    } else if (ldap_simple_bind_s(bind_ld, dn, password) != LDAP_SUCCESS)
	ret = 1;
    if (bind_ld != persistent_ld) {
	ldap_unbind(bind_ld);
	bind_ld = NULL;
    }
    return ret;
}