/*
 * dict_ldap_get_values: for each entry returned by a search, get the values
 * of all its attributes. Recurses to resolve any DN or URL values found.
 *
 * This and the rest of the handling of multiple attributes, DNs and URLs
 * are thanks to LaMont Jones.
 */
static void dict_ldap_get_values(DICT_LDAP *dict_ldap, LDAPMessage * res,
				         VSTRING *result)
{
    static int recursion = 0;
    static int expansion;
    long    entries = 0;
    long    i = 0;
    int     rc = 0;
    LDAPMessage *resloop = 0;
    LDAPMessage *entry = 0;
    BerElement *ber;
    char  **vals;
    char   *attr;
    char   *myname = "dict_ldap_get_values";
    struct timeval tv;
    LDAPURLDesc *url;

    tv.tv_sec = dict_ldap->timeout;
    tv.tv_usec = 0;

    if (++recursion == 1)
	expansion = 0;

    if (msg_verbose)
	msg_info("%s[%d]: Search found %d match(es)", myname, recursion,
		 ldap_count_entries(dict_ldap->ld, res));

    for (entry = ldap_first_entry(dict_ldap->ld, res); entry != NULL;
	 entry = ldap_next_entry(dict_ldap->ld, entry)) {
	ber = NULL;

	/*
	 * LDAP should not, but may produce more than the requested maximum
	 * number of entries.
	 */
	if (dict_errno == 0 && ++entries > dict_ldap->size_limit
	    && dict_ldap->size_limit) {
	    msg_warn("%s[%d]: %s: Query size limit (%ld) exceeded", myname,
		   recursion, dict_ldap->ldapsource, dict_ldap->size_limit);
	    dict_errno = DICT_ERR_RETRY;
	}
	for (attr = ldap_first_attribute(dict_ldap->ld, entry, &ber);
	     attr != NULL;
	     ldap_memfree(attr), attr = ldap_next_attribute(dict_ldap->ld,
							    entry, ber)) {
	    vals = ldap_get_values(dict_ldap->ld, entry, attr);
	    if (vals == NULL) {
		if (msg_verbose)
		    msg_info("%s[%d]: Entry doesn't have any values for %s",
			     myname, recursion, attr);
		continue;
	    }

	    /*
	     * If we previously encountered an error, we still continue
	     * through the loop, to avoid memory leaks, but we don't waste
	     * time accumulating any further results.
	     * 
	     * XXX: There may be a more efficient way to exit the loop with no
	     * leaks, but it will likely be more fragile and not worth the
	     * extra code.
	     */
	    if (dict_errno != 0 || vals[0] == 0) {
		ldap_value_free(vals);
		continue;
	    }

	    /*
	     * The "result_attributes" list enumerates all the requested
	     * attributes, first the ordinary result attribtutes and then the
	     * special result attributes that hold DN or LDAP URL values.
	     * 
	     * The number of ordinary attributes is "num_attributes".
	     * 
	     * We compute the attribute type (ordinary or special) from its
	     * index on the "result_attributes" list.
	     */
	    for (i = 0; dict_ldap->result_attributes->argv[i]; i++) {
		if (strcasecmp(dict_ldap->result_attributes->argv[i], attr) == 0)
		    break;
	    }

	    /*
	     * Append each returned address to the result list, possibly
	     * recursing (for dn or url attributes).
	     */
	    if (i < dict_ldap->num_attributes) {
		/* Ordinary result attribute */
		for (i = 0; vals[i] != NULL; i++) {
		    if (++expansion > dict_ldap->expansion_limit &&
			dict_ldap->expansion_limit) {
			msg_warn("%s[%d]: %s: Expansion limit exceeded at"
			       " result attribute %s=%s", myname, recursion,
				 dict_ldap->ldapsource, attr, vals[i]);
			dict_errno = DICT_ERR_RETRY;
			break;
		    }
		    if (VSTRING_LEN(result) > 0)
			vstring_strcat(result, ",");
		    if (dict_ldap->result_filter == NULL)
			vstring_strcat(result, vals[i]);
		    else
			dict_ldap_expand_filter(dict_ldap->ldapsource,
						dict_ldap->result_filter,
						vals[i], result);
		}
		if (dict_errno != 0)
		    continue;
		if (msg_verbose)
		    msg_info("%s[%d]: search returned %ld value(s) for"
			     " requested result attribute %s",
			     myname, recursion, i, attr);
	    } else if (recursion < dict_ldap->recursion_limit
		       && dict_ldap->result_attributes->argv[i]) {
		/* Special result attribute */
		for (i = 0; vals[i] != NULL; i++) {
		    if (ldap_is_ldap_url(vals[i])) {
			if (msg_verbose)
			    msg_info("%s[%d]: looking up URL %s", myname,
				     recursion, vals[i]);
			rc = ldap_url_parse(vals[i], &url);
			if (rc == 0) {
			    rc = ldap_search_st(dict_ldap->ld, url->lud_dn,
					    url->lud_scope, url->lud_filter,
						url->lud_attrs, 0, &tv,
						&resloop);
			    ldap_free_urldesc(url);
			}
		    } else {
			if (msg_verbose)
			    msg_info("%s[%d]: looking up DN %s",
				     myname, recursion, vals[i]);
			rc = ldap_search_st(dict_ldap->ld, vals[i],
					    LDAP_SCOPE_BASE, "objectclass=*",
					 dict_ldap->result_attributes->argv,
					    0, &tv, &resloop);
		    }
		    switch (rc) {
		    case LDAP_SUCCESS:
			dict_ldap_get_values(dict_ldap, resloop, result);
			break;
		    case LDAP_NO_SUCH_OBJECT:

			/*
			 * Go ahead and treat this as though the DN existed
			 * and just didn't have any result attributes.
			 */
			msg_warn("%s[%d]: DN %s not found, skipping ", myname,
				 recursion, vals[i]);
			break;
		    default:
			msg_warn("%s[%d]: search error %d: %s ", myname,
				 recursion, rc, ldap_err2string(rc));
			dict_errno = DICT_ERR_RETRY;
			break;
		    }

		    if (resloop != 0)
			ldap_msgfree(resloop);

		    if (dict_errno != 0)
			break;
		}
		if (dict_errno != 0)
		    continue;
		if (msg_verbose)
		    msg_info("%s[%d]: search returned %ld value(s) for"
			     " special result attribute %s",
			     myname, recursion, i, attr);
	    } else if (recursion >= dict_ldap->recursion_limit
		       && dict_ldap->result_attributes->argv[i]) {
		msg_warn("%s[%d]: %s: Recursion limit exceeded"
			 " for special attribute %s=%s",
		   myname, recursion, dict_ldap->ldapsource, attr, vals[0]);
		dict_errno = DICT_ERR_RETRY;
	    }
	    ldap_value_free(vals);
	}
	if (ber)
	    ber_free(ber, 0);
    }

    if (msg_verbose)
	msg_info("%s[%d]: Leaving %s", myname, recursion, myname);
    --recursion;
}