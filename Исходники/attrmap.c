/** Convert attribute map into valuepairs
 *
 * Use the attribute map built earlier to convert LDAP values into valuepairs and insert them into whichever
 * list they need to go into.
 *
 * This is *NOT* atomic, but there's no condition for which we should error out...
 *
 * @param[in] inst rlm_ldap configuration.
 * @param[in] request Current request.
 * @param[in] handle associated with entry.
 * @param[in] expanded attributes (rhs of map).
 * @param[in] entry to retrieve attributes from.
 * @return
 *	- Number of maps successfully applied.
 *	- -1 on failure.
 */
int rlm_ldap_map_do(const rlm_ldap_t *inst, REQUEST *request, LDAP *handle,
		    rlm_ldap_map_exp_t const *expanded, LDAPMessage *entry)
{
	vp_map_t const 	*map;
	unsigned int		total = 0;
	int			applied = 0;	/* How many maps have been applied to the current request */

	rlm_ldap_result_t	result;
	char const		*name;

	RINDENT();
	for (map = expanded->maps; map != NULL; map = map->next) {
		int ret;

		name = expanded->attrs[total++];

		/*
		 *	Binary safe
		 */
		result.values = ldap_get_values_len(handle, entry, name);
		if (!result.values) {
			RDEBUG3("Attribute \"%s\" not found in LDAP object", name);

			goto next;
		}

		/*
		 *	Find out how many values there are for the
		 *	attribute and extract all of them.
		 */
		result.count = ldap_count_values_len(result.values);

		/*
		 *	If something bad happened, just skip, this is probably
		 *	a case of the dst being incorrect for the current
		 *	request context
		 */
		ret = map_to_request(request, map, rlm_ldap_map_getvalue, &result);
		if (ret == -1) return -1;	/* Fail */

		/*
		 *	How many maps we've processed
		 */
		applied++;

	next:
		ldap_value_free_len(result.values);
	}
	REXDENT();

	/*
	 *	Retrieve any valuepair attributes from the result, these are generic values specifying
	 *	a radius list, operator and value.
	 */
	if (inst->valuepair_attr) {
		struct berval	**values;
		int		count, i;

		values = ldap_get_values_len(handle, entry, inst->valuepair_attr);
		count = ldap_count_values_len(values);

		RINDENT();
		for (i = 0; i < count; i++) {
			vp_map_t *attr;
			char *value;

			value = rlm_ldap_berval_to_string(request, values[i]);
			RDEBUG3("Parsing attribute string '%s'", value);
			if (map_afrom_attr_str(request, &attr, value,
					       REQUEST_CURRENT, PAIR_LIST_REPLY,
					       REQUEST_CURRENT, PAIR_LIST_REQUEST) < 0) {
				RWDEBUG("Failed parsing '%s' value \"%s\" as valuepair (%s), skipping...",
					fr_strerror(), inst->valuepair_attr, value);
				talloc_free(value);
				continue;
			}
			if (map_to_request(request, attr, map_to_vp, NULL) < 0) {
				RWDEBUG("Failed adding \"%s\" to request, skipping...", value);
			} else {
				applied++;
			}
			talloc_free(attr);
			talloc_free(value);
		}
		REXDENT();
		ldap_value_free_len(values);
	}

	return applied;
}