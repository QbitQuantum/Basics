/*
* Add a single attribute value to a list.
*/
static GSList *syldap_add_single_value( LDAP *ld, LDAPMessage *entry, char *attr ) {
	GSList *list = NULL;
	gchar **vals;

	if( ( vals = ldap_get_values( ld, entry, attr ) ) != NULL ) {
		if( vals[0] != NULL ) {
			/* printf( "sv\t%s: %s\n", attr, vals[0] ); */
			list = g_slist_append( list, g_strdup( vals[0] ) );
		}
	}
	ldap_value_free( vals );
	return list;
}