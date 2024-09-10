static void rpc_ns__ldap_import_server_element(LDAP *ld,
	unsigned_char_p_t serverDN,
	rpc_if_handle_t if_spec,
	rpc_ns_handle_t *ctx,
	unsigned32 *status
	)
{
	unsigned_char_p_t filter = NULL;
	unsigned_char_p_t uuid = NULL;
	rpc_if_id_t if_id;
	LDAPMessage *msg = NULL, *e;
	rpc_ns_handle_rep_t *rep;
	unsigned_char_p_t *bindings;
	size_t len;

	rpc_if_inq_id(if_spec, &if_id, status);
	if (*status != rpc_s_ok) {
		goto out;
	}

	/* Get the interface ID */
	uuid_to_string(&if_id.uuid, &uuid, status);
	if (*status != rpc_s_ok) {
		goto out;
	}

	len = strlen(uuid);
	len += sizeof("(&(objectClass=rpcServerElement)(rpcNsInterfaceID=,65535.65535))");
	RPC_MEM_ALLOC(filter, unsigned_char_p_t, len,
		RPC_C_MEM_NSRESOLUTION, RPC_C_MEM_WAITOK);

	sprintf(filter, "(&(objectClass=rpcServerElement)(rpcNsInterfaceID=%s,%hu.%hu))",
		uuid, if_id.vers_major, if_id.vers_minor);

	if (ldap_search_s(ld, serverDN, LDAP_SCOPE_ONELEVEL,
		filter, NULL, 0, &msg) != LDAP_SUCCESS) {
		*status = rpc_s_not_found;
		goto out;
	}

	e = ldap_first_entry(ld, msg);
	if (e == NULL) {
		*status = rpc_s_not_found;
		goto out;
	}

	bindings = (unsigned_char_p_t *)ldap_get_values(ld, e, "rpcNsBindings");
	if (bindings == NULL) {
		*status = rpc_s_not_found;
		goto out;
	}

	RPC_MEM_ALLOC(rep, rpc_ns_handle_rep_p_t,
		sizeof(*rep),
		RPC_C_MEM_NSRESOLUTION, RPC_C_MEM_WAITOK);

	rep->count = ldap_count_values((char **)bindings);
	rep->bindings = bindings;
	rep->cursor = 0;

	*ctx = (rpc_ns_handle_t)rep;
	*status = rpc_s_ok;

out:
	if (filter != NULL) {
		RPC_MEM_FREE(filter, RPC_C_MEM_NSRESOLUTION);
	}

	if (msg != NULL) {
		ldap_msgfree(msg);
	}
}