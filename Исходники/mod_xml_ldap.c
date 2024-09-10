static switch_status_t xml_ldap_directory_result(void *ldap_connection, xml_binding_t *binding, switch_xml_t *xml, int *off)
{
	struct ldap_c *ldap = ldap_connection;
	switch_xml_t asdf = *xml;
	switch_xml_t param, variable, params = NULL, variables = NULL;
	int i = 0;
	int loff = *off;

	for (ldap->entry = ldap_first_entry(ldap->ld, ldap->msg); ldap->entry != NULL; ldap->entry = ldap_next_entry(ldap->ld, ldap->entry)) {
		ldap->key = ldap_first_attribute(ldap->ld, ldap->entry, &ldap->berkey);
		do {
			ldap->val = ldap_first_attribute(ldap->ld, ldap->entry, &ldap->berval);
			do {
				if (strstr(ldap->val, "value")) {
					if (strstr(ldap->val, ldap->key) && strcmp(ldap->val, ldap->key)) {
						if (!strcmp(ldap->key, "param")) {
							params = switch_xml_add_child_d(asdf, "params", loff++);
						} else if (!strcmp(ldap->key, "variable")) {
							variables = switch_xml_add_child_d(asdf, "variables", loff++);
						}

						ldap->keyvals = ldap_get_values(ldap->ld, ldap->entry, ldap->key);
						ldap->valvals = ldap_get_values(ldap->ld, ldap->entry, ldap->val);

						if (ldap->keyvals && ldap->valvals) {
							if (ldap_count_values(ldap->valvals) == ldap_count_values(ldap->keyvals)) {
								for (i = 0; ldap->keyvals[i] != NULL && ldap->valvals[i] != NULL; i++) {
									if (!strcmp(ldap->key, "param")) {
										param = switch_xml_add_child_d(params, "param", loff++);
										switch_xml_set_attr_d(param, "name", ldap->keyvals[i]);
										switch_xml_set_attr_d(param, "value", ldap->valvals[i]);
									} else if (!strcmp(ldap->key, "variable")) {
										variable = switch_xml_add_child_d(variables, "variable", loff++);
										switch_xml_set_attr_d(variable, "name", ldap->keyvals[i]);
										switch_xml_set_attr_d(variable, "value", ldap->valvals[i]);
									}
								}

								if (ldap->keyvals) {
									ldap_value_free(ldap->keyvals);
								}

								if (ldap->valvals) {
									ldap_value_free(ldap->valvals);
								}
							} else {
								switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Seems the values %d and %d are not the same??\n",
												  ldap_count_values(ldap->valvals), ldap_count_values(ldap->keyvals));
							}
						}
					}
				}
				if (ldap->val) {
					ldap_memfree(ldap->val);
				}

				ldap->val = ldap_next_attribute(ldap->ld, ldap->entry, ldap->berval);

			} while (ldap->val != NULL);

			if (ldap->key) {
				ldap_memfree(ldap->key);
			}

			if (ldap->berval) {
				ber_free(ldap->berval, 0);
			}

			ldap->key = ldap_next_attribute(ldap->ld, ldap->entry, ldap->berkey);

		} while (ldap->key != NULL);

		if (ldap->berkey) {
			ber_free(ldap->berkey, 0);
		}
	}
	return SWITCH_STATUS_SUCCESS;
}