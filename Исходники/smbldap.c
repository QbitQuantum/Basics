 char * smbldap_talloc_single_attribute(LDAP *ldap_struct, LDAPMessage *entry,
					const char *attribute,
					TALLOC_CTX *mem_ctx)
{
	char **values;
	char *result;

	if (attribute == NULL) {
		return NULL;
	}

	values = ldap_get_values(ldap_struct, entry, attribute);

	if (values == NULL) {
		DEBUG(10, ("attribute %s does not exist\n", attribute));
		return NULL;
	}

	if (ldap_count_values(values) != 1) {
		DEBUG(10, ("attribute %s has %d values, expected only one\n",
			   attribute, ldap_count_values(values)));
		ldap_value_free(values);
		return NULL;
	}

	if (pull_utf8_talloc(mem_ctx, &result, values[0]) == (size_t)-1) {
		DEBUG(10, ("pull_utf8_talloc failed\n"));
		ldap_value_free(values);
		return NULL;
	}

	ldap_value_free(values);

#ifdef DEBUG_PASSWORDS
	DEBUG (100, ("smbldap_get_single_attribute: [%s] = [%s]\n",
		     attribute, result));
#endif	
	return result;
}