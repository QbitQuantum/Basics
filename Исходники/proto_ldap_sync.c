/** Process an entry modification operation
 *
 * @note This is a callback for the sync_demux function.
 *
 * @param[in] conn	the sync belongs to.
 * @param[in] config	of the sync that received an entry.
 * @param[in] sync_id	of the sync that received an entry.
 * @param[in] phase	Refresh phase the sync is currently in.
 * @param[in] uuid	of the entry.
 * @param[in] msg	containing the entry.
 * @param[in] state	The type of modification we need to perform to our
 *			representation of the entry.
 * @param[in] user_ctx	The listener.
 * @return
 *	- 0 on success.
 *	- -1 on failure.
 */
static int _proto_ldap_entry(fr_ldap_connection_t *conn, sync_config_t const *config,
			     int sync_id, UNUSED sync_phases_t phase,
			     uint8_t const uuid[SYNC_UUID_LENGTH], LDAPMessage *msg,
			     sync_states_t state, void *user_ctx)
{
	rad_listen_t		*listen = talloc_get_type_abort(user_ctx, rad_listen_t);
	proto_ldap_inst_t	*inst = talloc_get_type_abort(listen->data, proto_ldap_inst_t);
	fr_ldap_map_exp_t	expanded;
	REQUEST			*request;

	request = proto_ldap_request_setup(listen, inst, sync_id);
	if (!request) return -1;

	proto_ldap_attributes_add(request, config);
	request->packet->code = state;

	/*
	 *	Add the entry DN and attributes
	 */
	if (msg) {
		char *entry_dn;
		VALUE_PAIR *vp;

		entry_dn = ldap_get_dn(conn->handle, msg);

		MEM(pair_update_request(&vp, attr_ldap_sync_entry_dn) >= 0);
		ldap_memfree(entry_dn);

		MEM(pair_update_request(&vp, attr_ldap_sync_entry_uuid) >= 0);
		fr_pair_value_memcpy(vp, uuid, SYNC_UUID_LENGTH);
	}

	/*
	 *	Apply the attribute map
	 */
	if (fr_ldap_map_expand(&expanded, request, config->entry_map) < 0) {
	error:
		talloc_free(request);
		return -1;
	}
	if (fr_ldap_map_do(request, conn, NULL, &expanded, msg) < 0) goto error;

//	request_enqueue(request);

	return 0;
}