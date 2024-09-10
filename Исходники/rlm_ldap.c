/** Expand an LDAP URL into a query, and return a string result from that query.
 *
 */
static ssize_t ldap_xlat(void *instance, REQUEST *request, char const *fmt, char *out, size_t freespace)
{
	ldap_rcode_t status;
	size_t len = 0;
	ldap_instance_t *inst = instance;
	LDAPURLDesc *ldap_url;
	LDAPMessage *result = NULL;
	LDAPMessage *entry = NULL;
	char **vals;
	ldap_handle_t *conn;
	int ldap_errno;
	char const *url;
	char const **attrs;

	url = fmt;

	if (!ldap_is_ldap_url(url)) {
		REDEBUG("String passed does not look like an LDAP URL");
		return -1;
	}

	if (ldap_url_parse(url, &ldap_url)){
		REDEBUG("Parsing LDAP URL failed");
		return -1;
	}

	/*
	 *	Nothing, empty string, "*" string, or got 2 things, die.
	 */
	if (!ldap_url->lud_attrs || !ldap_url->lud_attrs[0] ||
	    !*ldap_url->lud_attrs[0] ||
	    (strcmp(ldap_url->lud_attrs[0], "*") == 0) ||
	    ldap_url->lud_attrs[1]) {
		REDEBUG("Bad attributes list in LDAP URL. URL must specify exactly one attribute to retrieve");

		goto free_urldesc;
	}

	if (ldap_url->lud_host &&
	    ((strncmp(inst->server, ldap_url->lud_host, strlen(inst->server)) != 0) ||
	     (ldap_url->lud_port != inst->port))) {
		RDEBUG("Requested server/port is \"%s:%i\"", ldap_url->lud_host, inst->port);

		goto free_urldesc;
	}

	conn = rlm_ldap_get_socket(inst, request);
	if (!conn) goto free_urldesc;

	memcpy(&attrs, &ldap_url->lud_attrs, sizeof(attrs));

	status = rlm_ldap_search(inst, request, &conn, ldap_url->lud_dn, ldap_url->lud_scope, ldap_url->lud_filter,
				 attrs, &result);
	switch (status) {
		case LDAP_PROC_SUCCESS:
			break;
		case LDAP_PROC_NO_RESULT:
			RDEBUG("Search returned not found");
		default:
			goto free_socket;
	}

	rad_assert(conn);
	rad_assert(result);

	entry = ldap_first_entry(conn->handle, result);
	if (!entry) {
		ldap_get_option(conn->handle, LDAP_OPT_RESULT_CODE, &ldap_errno);
		REDEBUG("Failed retrieving entry: %s", ldap_err2string(ldap_errno));
		len = -1;
		goto free_result;
	}

	vals = ldap_get_values(conn->handle, entry, ldap_url->lud_attrs[0]);
	if (!vals) {
		RDEBUG("No \"%s\" attributes found in specified object", ldap_url->lud_attrs[0]);
		goto free_result;
	}

	len = strlen(vals[0]);
	if (len >= freespace){
		goto free_vals;
	}

	strlcpy(out, vals[0], freespace);

free_vals:
	ldap_value_free(vals);
free_result:
	ldap_msgfree(result);
free_socket:
	rlm_ldap_release_socket(inst, conn);
free_urldesc:
	ldap_free_urldesc(ldap_url);

	return len;
}