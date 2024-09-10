/** Convert group membership information into attributes
 *
 * @param[in] inst rlm_ldap configuration.
 * @param[in] request Current request.
 * @param[in,out] pconn to use. May change as this function calls functions which auto re-connect.
 * @param[in] entry retrieved by rlm_ldap_find_user or rlm_ldap_search.
 * @param[in] attr membership attribute to look for in the entry.
 * @return One of the RLM_MODULE_* values.
 */
rlm_rcode_t rlm_ldap_cacheable_userobj(ldap_instance_t const *inst, REQUEST *request, ldap_handle_t **pconn,
				       LDAPMessage *entry, char const *attr)
{
	rlm_rcode_t rcode = RLM_MODULE_OK;

	char **vals;

	char *group_name[LDAP_MAX_CACHEABLE + 1];
	char **name_p = group_name;

	char *group_dn[LDAP_MAX_CACHEABLE + 1];
	char **dn_p;

	char *name;

	int is_dn, i;

	rad_assert(entry);
	rad_assert(attr);

	/*
	 *	Parse the membership information we got in the initial user query.
	 */
	vals = ldap_get_values((*pconn)->handle, entry, attr);
	if (!vals) {
		RDEBUG2("No cacheable group memberships found in user object");

		return RLM_MODULE_OK;
	}

	for (i = 0; (vals[i] != NULL) && (i < LDAP_MAX_CACHEABLE); i++) {
		is_dn = rlm_ldap_is_dn(vals[i]);

		if (inst->cacheable_group_dn) {
			/*
			 *	The easy case, were caching DNs and we got a DN.
			 */
			if (is_dn) {
				pairmake(request, &request->config_items, inst->cache_da->name, vals[i], T_OP_ADD);
				RDEBUG("Added %s with value \"%s\" to control list", inst->cache_da->name, vals[i]);

			/*
			 *	We were told to cache DNs but we got a name, we now need to resolve
			 *	this to a DN. Store all the group names in an array so we can do one query.
			 */
			} else {
				*name_p++ = vals[i];
			}
		}

		if (inst->cacheable_group_name) {
			/*
			 *	The easy case, were caching names and we got a name.
			 */
			if (!is_dn) {
				pairmake(request, &request->config_items, inst->cache_da->name, vals[i], T_OP_ADD);
				RDEBUG("Added %s with value \"%s\" to control list", inst->cache_da->name, vals[i]);
			/*
			 *	We were told to cache names but we got a DN, we now need to resolve
			 *	this to a name.
			 *	Only Active Directory supports filtering on DN, so we have to search
			 *	for each individual group.
			 */
			} else {
				rcode = rlm_ldap_group_dn2name(inst, request, pconn, vals[i], &name);
				if (rcode != RLM_MODULE_OK) {
					ldap_value_free(vals);

					return rcode;
				}

				pairmake(request, &request->config_items, inst->cache_da->name, name, T_OP_ADD);
				RDEBUG("Added %s with value \"%s\" to control list", inst->cache_da->name, name);
				talloc_free(name);
			}
		}
	}
	*name_p = NULL;

	rcode = rlm_ldap_group_name2dn(inst, request, pconn, group_name, group_dn, sizeof(group_dn));

	ldap_value_free(vals);

	if (rcode != RLM_MODULE_OK) {
		return rcode;
	}

	dn_p = group_dn;
	while(*dn_p) {
		pairmake(request, &request->config_items, inst->cache_da->name, *dn_p, T_OP_ADD);
		RDEBUG("Added %s with value \"%s\" to control list", inst->cache_da->name, *dn_p);
		ldap_memfree(*dn_p);

		dn_p++;
	}

	return rcode;
}