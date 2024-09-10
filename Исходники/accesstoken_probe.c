static int collect_access_rights(probe_ctx *ctx, WCHAR *security_principle, bool include_group, bool resolve_group)
{
	char *security_principle_str = oscap_windows_wstr_to_str(security_principle);

	LSA_OBJECT_ATTRIBUTES object_attributes;
	ZeroMemory(&object_attributes, sizeof(LSA_OBJECT_ATTRIBUTES));
	LSA_HANDLE lsa_policy_handle;

	NTSTATUS status = LsaOpenPolicy(NULL, &object_attributes, POLICY_LOOKUP_NAMES, &lsa_policy_handle);
	if (status != STATUS_SUCCESS) {
		DWORD err = LsaNtStatusToWinError(status);
		char *error_message = oscap_windows_error_message(err);
		dD("LsaOpenPolicy failed for principle '%s': %s", security_principle_str, error_message);
		free(error_message);
		free(security_principle_str);
		return 1;
	}

	/* Convert the value of the security_principle element to a SID. */
	DWORD sid_len = 0;
	DWORD domain_name_len = 0;
	SID_NAME_USE sid_type;
	LookupAccountNameW(NULL, security_principle, NULL, &sid_len, NULL, &domain_name_len, &sid_type);
	SID *sid = malloc(sid_len);
	WCHAR *domain_name = malloc(domain_name_len * sizeof(WCHAR));
	if (!LookupAccountNameW(NULL, security_principle, sid, &sid_len, domain_name, &domain_name_len, &sid_type)) {
		DWORD err = GetLastError();
		char *error_message = oscap_windows_error_message(err);
		dD("LookupAccountNameW failed for '%s': %s", security_principle_str, error_message);
		free(error_message);
		free(security_principle_str);
		free(sid);
		free(domain_name);
		return 1;
	}

	/* Is it a group? */
	if (sid_type == SidTypeGroup || sid_type == SidTypeWellKnownGroup || sid_type == SidTypeAlias) {
		if (resolve_group) {
			struct oscap_list *group_members_list = oscap_list_new();
			get_local_group_members(security_principle, group_members_list);
			get_global_group_members(security_principle, group_members_list);
			struct oscap_iterator *group_members_it = oscap_iterator_new(group_members_list);
			while (oscap_iterator_has_more(group_members_it)) {
				WCHAR *group_member = oscap_iterator_next(group_members_it);
				collect_access_rights(ctx, group_member, include_group, resolve_group);
			}
			oscap_iterator_free(group_members_it);
			oscap_list_free(group_members_list, free);
		}
		if (!include_group) {
			free(sid);
			free(domain_name);
			free(security_principle_str);
			return 0;
		}
	}

	/* Users and groups can inherit their privileges from their parents */
	struct oscap_list *every_rights_sources = oscap_list_new();
	oscap_list_add(every_rights_sources, wcsdup(security_principle));
	get_user_local_groups(security_principle, every_rights_sources);
	get_user_global_groups(security_principle, every_rights_sources);

	/* Iterate over the items */
	bool privileges_enabled[OVAL_PRIVILEGES_COUNT] = { false };
	struct oscap_iterator *it = oscap_iterator_new(every_rights_sources);
	while (oscap_iterator_has_more(it)) {
		WCHAR *account_name = oscap_iterator_next(it);

		DWORD account_sid_len = 0;
		DWORD account_domain_name_len = 0;
		SID_NAME_USE account_sid_type;
		LookupAccountNameW(NULL, account_name, NULL, &account_sid_len, NULL, &account_domain_name_len, &account_sid_type);
		SID *account_sid = malloc(account_sid_len);
		WCHAR *account_domain_name = malloc(account_domain_name_len * sizeof(WCHAR));
		if (!LookupAccountNameW(NULL, account_name, account_sid, &account_sid_len, account_domain_name, &account_domain_name_len, &account_sid_type)) {
			free(account_sid);
			free(account_domain_name);
			DWORD err = GetLastError();
			char *error_message = oscap_windows_error_message(err);
			dD("LookupAccountNameW failed for '%s': %s", security_principle_str, error_message);
			free(error_message);
			free(security_principle_str);
			return 1;
		}

		LSA_UNICODE_STRING *granted_rights = NULL;
		ULONG granted_rights_count = 0;
		status = LsaEnumerateAccountRights(lsa_policy_handle, account_sid, &granted_rights, &granted_rights_count);
		if (status != STATUS_SUCCESS) {
			free(account_sid);
			free(account_domain_name);
			DWORD err = LsaNtStatusToWinError(status);
			char *error_message = oscap_windows_error_message(err);
			dD("LsaEnumerateAccountRights failed for '%s': %s", security_principle_str, error_message);
			free(error_message);
			/* We should not exit here, because when LsaEnumerateAccountRights
			* failed it can mean that the entity simply doesn't have any specific
			* privileges, it only inhertis privileges form its parent group(s).
			*/
			continue;
		}

		for (int i = 0; i < OVAL_PRIVILEGES_COUNT; i++) {
			if (!privileges_enabled[i]) {
				for (ULONG j = 0; j < granted_rights_count; j++) {
					if (wcscmp(granted_rights[j].Buffer, privileges_texts[i]) == 0) {
						privileges_enabled[i] = true;
						break;
					}
				}
			}
		}
		LsaFreeMemory(granted_rights);
		free(account_sid);
		free(account_domain_name);

	}
	oscap_iterator_free(it);
	oscap_list_free(every_rights_sources, free);

	/* Collect the OVAL item */
	SEXP_t *item = probe_item_create(OVAL_WINDOWS_ACCESS_TOKEN, NULL,
		"security_principle", OVAL_DATATYPE_STRING, strdup(security_principle_str), NULL);
	for (int i = 0; i < OVAL_PRIVILEGES_COUNT; i++) {
		char *privilege_name = oscap_windows_wstr_to_str(privileges_texts[i]);
		/* Convert the element name to lowercase */
		for (char *p = privilege_name; *p; p++) {
			*p = tolower(*p);
		}
		SEXP_t *privilege_value = SEXP_number_newb(privileges_enabled[i]);
		probe_item_ent_add(item, privilege_name, NULL, privilege_value);
		free(privilege_name);
		SEXP_free(privilege_value);
	}
	probe_item_collect(ctx, item);
	free(security_principle_str);

	return 0;
}