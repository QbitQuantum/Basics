static int
ldap_get_fulldn(LD_session *session, char *username, char *userstr, int username_length)
{
	struct berval cred;
	struct berval *msgidp=NULL;
	char filter[MAXFILTERSTR], *dn;
	int rc = 0;
	char logbuf[MAXLOGBUF];
	LDAPMessage *res, *entry;

	memset(userstr, 0, username_length);

        cred.bv_val = ldap_authorization_bindpasswd;
        cred.bv_len = strlen(ldap_authorization_bindpasswd);

#if LDAP_API_VERSION > 3000
	if((rc = ldap_sasl_bind_s(session->sess, ldap_authorization_binddn, ldap_authorization_type, &cred, NULL, NULL, &msgidp))!=LDAP_SUCCESS) {
		snprintf(logbuf, MAXLOGBUF, "!!!Ldap server %s authentificate with method %s failed: %s", ldap_authorization_host, ldap_authorization_type, ldap_err2string(rc));	
		ldap_log(LOG_DEBUG, logbuf);
		return RETURN_FALSE;
	};

#else
	if((rc = ldap_bind_s(session->sess, ldap_authorization_binddn, ldap_authorization_bindpasswd, LDAP_AUTH_SIMPLE))!=LDAP_SUCCESS) {
		snprintf(logbuf, MAXLOGBUF, "Ldap server %s authentificate failed: %s", ldap_authorization_host, ldap_err2string(rc));	
		ldap_log(LOG_DEBUG, logbuf);
		return RETURN_FALSE;
	}
#endif

	/* create filter for search */
	memset(filter, 0, MAXFILTERSTR);
	snprintf(filter, MAXLOGBUF, "(uid=%s)", username);

	if ((rc = ldap_search_ext_s(session->sess, ldap_authorization_basedn, LDAP_SCOPE_SUBTREE, filter, NULL, 0, NULL, NULL, NULL, LDAP_NO_LIMIT, &res)) != LDAP_SUCCESS) {
#if LDAP_API_VERSION > 3000
		ldap_unbind_ext(session->sess, NULL, NULL);
#else   
		ldap_unbind(session->sess);
#endif
		return RETURN_FALSE;
	}

	if ((entry = ldap_first_entry(session->sess,res)) == NULL) {
		return RETURN_FALSE;
	} else {
		dn = ldap_get_dn(session->sess, entry);
		strncpy(userstr, dn, strlen(dn));
	};
	ldap_msgfree(res);
	return RETURN_TRUE;
}