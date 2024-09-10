static isc_result_t
ldapdb_search(const char *zone, const char *name, void *dbdata, void *retdata,
	      void *methods, void *clientinfo)
#endif /* DNS_CLIENTINFO_VERSION */
{
	struct ldapdb_data *data = dbdata;
	isc_result_t result = ISC_R_NOTFOUND;
	LDAP **ldp;
	LDAPMessage *res, *e;
	char *fltr, *a, **vals = NULL, **names = NULL;
	char type[64];
#ifdef LDAPDB_RFC1823API
	void *ptr;
#else
	BerElement *ptr;
#endif
	int i, j, errno, msgid;

	UNUSED(methods);
	UNUSED(clientinfo);

	ldp = ldapdb_getconn(data);
	if (ldp == NULL)
		return (ISC_R_FAILURE);
	if (*ldp == NULL) {
		ldapdb_bind(data, ldp);
		if (*ldp == NULL) {
			isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL, NS_LOGMODULE_SERVER, ISC_LOG_ERROR,	
				      "LDAP sdb zone '%s': bind failed", zone);
			return (ISC_R_FAILURE);
		}
	}

	if (name == NULL) {
		fltr = data->filterall;
	} else {
		if (strlen(name) > MAXNAMELEN) {
			isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL, NS_LOGMODULE_SERVER, ISC_LOG_ERROR,
                                      "LDAP sdb zone '%s': name %s too long", zone, name);
			return (ISC_R_FAILURE);
		}
		sprintf(data->filtername, "%s))", name);
		fltr = data->filterone;
	}

	msgid = ldap_search(*ldp, data->base, LDAP_SCOPE_SUBTREE, fltr, NULL, 0);
	if (msgid == -1) {
		ldapdb_bind(data, ldp);
		if (*ldp != NULL)
			msgid = ldap_search(*ldp, data->base, LDAP_SCOPE_SUBTREE, fltr, NULL, 0);
	}

	if (*ldp == NULL || msgid == -1) {
		isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL, NS_LOGMODULE_SERVER, ISC_LOG_ERROR,	
			      "LDAP sdb zone '%s': search failed, filter %s", zone, fltr);
		return (ISC_R_FAILURE);
	}

	/* Get the records one by one as they arrive and return them to bind */
	while ((errno = ldap_result(*ldp, msgid, 0, NULL, &res)) != LDAP_RES_SEARCH_RESULT ) {
		LDAP *ld = *ldp;
		int ttl = data->defaultttl;

		/* not supporting continuation references at present */
		if (errno != LDAP_RES_SEARCH_ENTRY) {
			isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL, NS_LOGMODULE_SERVER, ISC_LOG_ERROR,	
				      "LDAP sdb zone '%s': ldap_result returned %d", zone, errno);
			ldap_msgfree(res);
			return (ISC_R_FAILURE);
                }

		/* only one entry per result message */
		e = ldap_first_entry(ld, res);
		if (e == NULL) {
			ldap_msgfree(res);
			isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL, NS_LOGMODULE_SERVER, ISC_LOG_ERROR,	
				      "LDAP sdb zone '%s': ldap_first_entry failed", zone);
			return (ISC_R_FAILURE);
                }

		if (name == NULL) {
			names = ldap_get_values(ld, e, "relativeDomainName");
			if (names == NULL)
				continue;
		}

		vals = ldap_get_values(ld, e, "dNSTTL");
		if (vals != NULL) {
			ttl = atoi(vals[0]);
			ldap_value_free(vals);
		}

		for (a = ldap_first_attribute(ld, e, &ptr); a != NULL; a = ldap_next_attribute(ld, e, ptr)) {
			char *s;

			for (s = a; *s; s++)
				*s = toupper(*s);
			s = strstr(a, "RECORD");
			if ((s == NULL) || (s == a) || (s - a >= (signed int)sizeof(type))) {
#ifndef LDAPDB_RFC1823API
				ldap_memfree(a);
#endif
				continue;
			}

			strncpy(type, a, s - a);
			type[s - a] = '\0';
			vals = ldap_get_values(ld, e, a);
			if (vals != NULL) {
				for (i = 0; vals[i] != NULL; i++) {
					if (name != NULL) {
						result = dns_sdb_putrr(retdata, type, ttl, vals[i]);
					} else {
						for (j = 0; names[j] != NULL; j++) {
							result = dns_sdb_putnamedrr(retdata, names[j], type, ttl, vals[i]);
							if (result != ISC_R_SUCCESS)
								break;
						}
					}
;					if (result != ISC_R_SUCCESS) {
						isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL, NS_LOGMODULE_SERVER, ISC_LOG_ERROR,	
							      "LDAP sdb zone '%s': dns_sdb_put... failed for %s", zone, vals[i]);
						ldap_value_free(vals);
#ifndef LDAPDB_RFC1823API
						ldap_memfree(a);
						if (ptr != NULL)
							ber_free(ptr, 0);
#endif
						if (name == NULL)
							ldap_value_free(names);
						ldap_msgfree(res);
						return (ISC_R_FAILURE);
					}
				}
				ldap_value_free(vals);
			}
#ifndef LDAPDB_RFC1823API
			ldap_memfree(a);
#endif
		}
#ifndef LDAPDB_RFC1823API
		if (ptr != NULL)
			ber_free(ptr, 0);
#endif
		if (name == NULL)
			ldap_value_free(names);

		/* free this result */
		ldap_msgfree(res);
	}

	/* free final result */
	ldap_msgfree(res);
        return (result);
}