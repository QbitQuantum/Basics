static char * dm_ldap_user_getdn(u64_t user_idnr) 
{
	GString *t = g_string_new("");
	char *dn;
	int err;
	LDAPMessage *ldap_res;
	LDAPMessage *ldap_msg;
	LDAP *_ldap_conn = ldap_con_get();
	
	g_string_printf(t, "(%s=%llu)", _ldap_cfg.field_nid, user_idnr);
	TRACE(TRACE_DEBUG, "searching with query [%s]", t->str);
	
	if (! (ldap_res = authldap_search(t->str))) {
		g_string_free(t,TRUE);
		return NULL;
	}
		
	g_string_free(t,TRUE);

	if (ldap_count_entries(_ldap_conn, ldap_res) < 1) {
		TRACE(TRACE_DEBUG, "no entries found");
		ldap_msgfree(ldap_res);
		return NULL;
	}

	if (! (ldap_msg = ldap_first_entry(_ldap_conn, ldap_res))) {
		ldap_get_option(_ldap_conn, LDAP_OPT_ERROR_NUMBER, &err);
		TRACE(TRACE_ERR, "ldap_first_entry failed: %s", ldap_err2string(err));
		ldap_msgfree(ldap_res);
		return NULL;
	}

	if (! (dn = ldap_get_dn(_ldap_conn, ldap_msg))) {
		ldap_get_option(_ldap_conn, LDAP_OPT_ERROR_NUMBER, &err);
		TRACE(TRACE_ERR, "ldap_get_dn failed: %s", ldap_err2string(err));
		ldap_msgfree(ldap_res);
		return NULL;
	}

	ldap_msgfree(ldap_res);
	return dn;
}