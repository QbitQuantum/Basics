/*% checks that the LDAP URL parameters make sense */
static isc_result_t
ldap_checkURL(ldap_instance_t *db, char *URL, int attrCnt, const char *msg) {
	isc_result_t result = ISC_R_SUCCESS;
	int ldap_result;
	LDAPURLDesc *ldap_url = NULL;

	if (!ldap_is_ldap_url(URL)) {
		db->log(ISC_LOG_ERROR,
			"%s query is not a valid LDAP URL", msg);
		result = ISC_R_FAILURE;
		goto cleanup;
	}

	ldap_result = ldap_url_parse(URL, &ldap_url);
	if (ldap_result != LDAP_SUCCESS || ldap_url == NULL) {
		db->log(ISC_LOG_ERROR, "parsing %s query failed", msg);
		result = ISC_R_FAILURE;
		goto cleanup;
	}

	if (ldap_count_values(ldap_url->lud_attrs) < attrCnt) {
		db->log(ISC_LOG_ERROR,
			"%s query must specify at least "
			"%d attributes to return", msg, attrCnt);
		result = ISC_R_FAILURE;
		goto cleanup;
	}

	if (ldap_url->lud_host != NULL) {
		db->log(ISC_LOG_ERROR,
			"%s query must not specify a host", msg);
		result = ISC_R_FAILURE;
		goto cleanup;
	}

	if (ldap_url->lud_port != 389) {
		db->log(ISC_LOG_ERROR,
			"%s query must not specify a port", msg);
		result = ISC_R_FAILURE;
		goto cleanup;
	}

	if (ldap_url->lud_dn == NULL || strlen (ldap_url->lud_dn) < 1) {
		db->log(ISC_LOG_ERROR,
			"%s query must specify a search base", msg);
		result = ISC_R_FAILURE;
		goto cleanup;
	}

	if (ldap_url->lud_exts != NULL || ldap_url->lud_crit_exts != 0) {
		db->log(ISC_LOG_ERROR,
			"%s uses extensions. "
			"The driver does not support LDAP extensions.", msg);
		result = ISC_R_FAILURE;
		goto cleanup;
	}

 cleanup:
	if (ldap_url != NULL)
		ldap_free_urldesc(ldap_url);

	return (result);
}