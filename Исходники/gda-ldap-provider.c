/*
 * Function called during initialization phase => no need to use the GdaWorker object
 *
 * Using @url and @username, performs the following tasks:
 * - bind to the LDAP server anonymously
 * - search the directory to identify the entry for the provided user name,
 *   filter: (&(uid=##uid)(objectclass=inetOrgPerson))
 * - if one and only one entry is returned, get the DN of the entry and check that the UID is correct
 *
 * If all the steps are right, it returns the DN of the identified entry as a new string.
 */
static gchar *
fetch_user_dn (const gchar *url, const gchar *base, const gchar *username, LdapAuthMapping *mapping)
{
	LDAP *ld;
	int res;
	int version = LDAP_VERSION3;
	gchar *dn = NULL;
	LDAPMessage *msg = NULL;

	if (! username)
		return NULL;

	res = ldap_initialize (&ld, url);
	if (res != LDAP_SUCCESS)
		return NULL;

	res = ldap_set_option (ld, LDAP_OPT_PROTOCOL_VERSION, &version);
        if (res != LDAP_SUCCESS) {
		if (res == LDAP_PROTOCOL_ERROR) {
			version = LDAP_VERSION2;
			res = ldap_set_option (ld, LDAP_OPT_PROTOCOL_VERSION, &version);
		}
		if (res != LDAP_SUCCESS)
			goto out;
        }

	struct berval cred;
        memset (&cred, 0, sizeof (cred));
	res = ldap_sasl_bind_s (ld, NULL, NULL, &cred, NULL, NULL, NULL);
	if (res != LDAP_SUCCESS)
		goto out;

	gchar *filter;
	gchar *attributes[] = {NULL, NULL};
	attributes[0] = mapping->attribute;
	filter = g_strdup_printf (mapping->filter_format, username);
	res = ldap_search_ext_s (ld, base, LDAP_SCOPE_SUBTREE,
				 filter, attributes, 0,
				 NULL, NULL, NULL, 2, &msg);
	g_free (filter);
	if (res != LDAP_SUCCESS)
		goto out;

	LDAPMessage *ldap_row;
	for (ldap_row = ldap_first_entry (ld, msg);
	     ldap_row;
	     ldap_row = ldap_next_entry (ld, ldap_row)) {
		char *attr, *uid;
		attr = ldap_get_dn (ld, ldap_row);
		if (attr) {
			BerElement* ber;
			for (uid = ldap_first_attribute (ld, ldap_row, &ber);
			     uid;
			     uid = ldap_next_attribute (ld, ldap_row, ber)) {
				BerValue **bvals;
				bvals = ldap_get_values_len (ld, ldap_row, uid);
				if (!bvals || !bvals[0] || bvals[1] || strcmp (bvals[0]->bv_val, username)) {
					g_free (dn);
					dn = NULL;
				}
				ldap_value_free_len (bvals);
				ldap_memfree (uid);
			}

			if (dn) {
				/* more than 1 entry => unique DN could not be identified */
				g_free (dn);
				dn = NULL;
				goto out;
			}

			dn = g_strdup (attr);
			ldap_memfree (attr);
		}
	}

 out:
	if (msg)
		ldap_msgfree (msg);
	ldap_unbind_ext (ld, NULL, NULL);
	/*g_print ("Identified DN: [%s]\n", dn);*/
	return dn;
}