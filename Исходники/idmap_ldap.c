static NTSTATUS idmap_ldap_set_mapping(struct idmap_domain *dom,
				       const struct id_map *map)
{
	NTSTATUS ret;
	TALLOC_CTX *memctx;
	struct idmap_ldap_context *ctx;
	LDAPMessage *entry = NULL;
	LDAPMod **mods = NULL;
	const char *type;
	char *id_str;
	char *sid;
	char *dn;
	int rc = -1;

	/* Only do query if we are online */
	if (idmap_is_offline())	{
		return NT_STATUS_FILE_IS_OFFLINE;
	}

	ctx = talloc_get_type(dom->private_data, struct idmap_ldap_context);

	switch(map->xid.type) {
	case ID_TYPE_UID:
		type = get_attr_key2string(sidmap_attr_list,
					   LDAP_ATTR_UIDNUMBER);
		break;

	case ID_TYPE_GID:
		type = get_attr_key2string(sidmap_attr_list,
					   LDAP_ATTR_GIDNUMBER);
		break;

	default:
		return NT_STATUS_INVALID_PARAMETER;
	}

	memctx = talloc_new(ctx);
	if ( ! memctx) {
		DEBUG(0, ("Out of memory!\n"));
		return NT_STATUS_NO_MEMORY;
	}

	id_str = talloc_asprintf(memctx, "%lu", (unsigned long)map->xid.id);
	CHECK_ALLOC_DONE(id_str);

	sid = talloc_strdup(memctx, sid_string_talloc(memctx, map->sid));
	CHECK_ALLOC_DONE(sid);

	dn = talloc_asprintf(memctx, "%s=%s,%s",
			get_attr_key2string(sidmap_attr_list, LDAP_ATTR_SID),
			sid,
			ctx->suffix);
	CHECK_ALLOC_DONE(dn);

	smbldap_set_mod(&mods, LDAP_MOD_ADD,
			"objectClass", LDAP_OBJ_IDMAP_ENTRY);

	smbldap_make_mod(ctx->smbldap_state->ldap_struct,
			 entry, &mods, type, id_str);

	smbldap_make_mod(ctx->smbldap_state->ldap_struct, entry, &mods,
			 get_attr_key2string(sidmap_attr_list, LDAP_ATTR_SID),
			 sid);

	if ( ! mods) {
		DEBUG(2, ("ERROR: No mods?\n"));
		ret = NT_STATUS_UNSUCCESSFUL;
		goto done;
	}

	/* TODO: remove conflicting mappings! */

	smbldap_set_mod(&mods, LDAP_MOD_ADD, "objectClass", LDAP_OBJ_SID_ENTRY);

	DEBUG(10, ("Set DN %s (%s -> %s)\n", dn, sid, id_str));

	rc = smbldap_add(ctx->smbldap_state, dn, mods);
	ldap_mods_free(mods, True);

	if (rc != LDAP_SUCCESS) {
		char *ld_error = NULL;
		ldap_get_option(ctx->smbldap_state->ldap_struct,
				LDAP_OPT_ERROR_STRING, &ld_error);
		DEBUG(0,("ldap_set_mapping_internals: Failed to add %s to %lu "
			 "mapping [%s]\n", sid,
			 (unsigned long)map->xid.id, type));
		DEBUG(0, ("ldap_set_mapping_internals: Error was: %s (%s)\n",
			ld_error ? ld_error : "(NULL)", ldap_err2string (rc)));
		if (ld_error) {
			ldap_memfree(ld_error);
		}
		ret = NT_STATUS_UNSUCCESSFUL;
		goto done;
	}

	DEBUG(10,("ldap_set_mapping: Successfully created mapping from %s to "
		  "%lu [%s]\n",	sid, (unsigned long)map->xid.id, type));

	ret = NT_STATUS_OK;

done:
	talloc_free(memctx);
	return ret;
}