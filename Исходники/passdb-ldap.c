static void ldap_bind_lookup_dn_callback(struct ldap_connection *conn,
					 struct ldap_request *ldap_request,
					 LDAPMessage *res)
{
	struct passdb_ldap_request *passdb_ldap_request =
		(struct passdb_ldap_request *)ldap_request;
	struct auth_request *auth_request = ldap_request->auth_request;
	struct passdb_ldap_request *brequest;
	char *dn;

	if (res != NULL && ldap_msgtype(res) == LDAP_RES_SEARCH_ENTRY) {
		if (passdb_ldap_request->entries++ > 0) {
			/* too many replies */
			return;
		}

		/* first entry */
		ldap_query_save_result(conn, auth_request,
				       &passdb_ldap_request->request.search, res);

		/* save dn */
		dn = ldap_get_dn(conn->ld, res);
		passdb_ldap_request->dn = p_strdup(auth_request->pool, dn);
		ldap_memfree(dn);
	} else if (res == NULL || passdb_ldap_request->entries != 1) {
		/* failure */
		ldap_bind_lookup_dn_fail(auth_request, passdb_ldap_request, res);
	} else {
		/* create a new bind request */
		brequest = p_new(auth_request->pool,
				 struct passdb_ldap_request, 1);
		brequest->dn = passdb_ldap_request->dn;
		brequest->callback = passdb_ldap_request->callback;
		brequest->request.bind.dn = brequest->dn;
		brequest->request.bind.request.type = LDAP_REQUEST_TYPE_BIND;
		brequest->request.bind.request.auth_request = auth_request;

		ldap_auth_bind(conn, &brequest->request.bind);
	}
}