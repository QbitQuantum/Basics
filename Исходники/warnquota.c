static char *lookup_user(struct configparams *config, char *user)
{
#ifdef USE_LDAP_MAIL_LOOKUP
       	char searchbuf[256];
	LDAPMessage *result, *entry;
	BerElement     *ber = NULL;
	struct berval  **bvals = NULL;
	int ret, cnt;
	char *a;
	char *to = NULL;

	if (!config->use_ldap_mail)
		return sstrdup(user);

	if (ldapconn == NULL && config->ldap_is_setup == 0) {
		/* need init */
		if (setup_ldap(config)) {
			errstr(_("Could not setup ldap connection.\n"));
			return NULL;
		}
		config->ldap_is_setup = 1;
	}

	if (ldapconn == NULL) {
		/*
		 * ldap was never setup correctly so just use
		 * the offender_name
		 */
		return sstrdup(user);
	}

	/* search for the offender_name in ldap */
	snprintf(searchbuf, 256, "(%s=%s)", config->ldap_search_attr, user);
	ret = ldap_search_ext_s(ldapconn,
		config->ldap_basedn, LDAP_SCOPE_SUBTREE,
		searchbuf, NULL, 0, NULL, NULL, NULL,
		0, &result);

	if (ret < 0) {
		errstr(_("Error with %s.\n"), user);
		errstr(_("ldap_search_ext_s() failed: %s\n"), ldap_err2string(ret));
		return NULL;
	}
		
	cnt = ldap_count_entries(ldapconn, result);
	if (cnt > 1) {
		errstr(_("Multiple entries found for client %s (%d).\n"),
		       user, cnt);
		return NULL;
	} else if (cnt == 0) {
		errstr(_("Entry not found for client %s.\n"), user);
		return NULL;
	}
	/* get the attr */
	entry = ldap_first_entry(ldapconn, result);
	for (a = ldap_first_attribute(ldapconn, entry, &ber); a != NULL;
	     a = ldap_next_attribute(ldapconn, entry, ber)) {
		if (strcasecmp(a, config->ldap_mail_attr) == 0) {
			bvals = ldap_get_values_len(ldapconn, entry, a);
			if (bvals == NULL) {
				errstr(_("Could not get values for %s.\n"), 
				       user);
				return NULL;
			}
			to = sstrdup(bvals[0]->bv_val);
			ldap_memfree(a);
			ldap_value_free_len(bvals);
			break;
		}
		ldap_memfree(a);
	} 

	ber_free(ber, 0);

	if (to == NULL) {
		/* 
		 * use just the name and default domain as we didn't find the
		 * attribute we wanted in this entry
		 */
		to = smalloc(strlen(user) + strlen(config->default_domain) + 1);
		sprintf(to, "%s@%s", user, config->default_domain);
	}
	return to;
#else
	return sstrdup(user);
#endif
}