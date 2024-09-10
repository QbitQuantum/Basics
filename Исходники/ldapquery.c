/**
 * Add all LDAP attribute values to a list.
 * \param ld LDAP handle.
 * \param entry LDAP entry to process.
 * \param attr  LDAP attribute.
 * \return List of values.
 */
static GSList *ldapqry_add_list_values(
		LDAP *ld, LDAPMessage *entry, char *attr )
{
	GSList *list = NULL;
	gint i;
	struct berval **vals;

	if( ( vals = ldap_get_values_len( ld, entry, attr ) ) != NULL ) {
		for( i = 0; vals[i] != NULL; i++ ) {
			/*debug_print("lv\t%s: %s\n", attr?attr:"null",
					vals[i]->bv_val?vals[i]->bv_val:"null");*/
			list = g_slist_append( list, g_strndup( vals[i]->bv_val, vals[i]->bv_len) );
		}
	}
	ldap_value_free_len( vals );
	return list;
}