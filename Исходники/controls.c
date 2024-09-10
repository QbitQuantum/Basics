/*
 * Free an array of LDAPControl's
 */
void
ldap_controls_free( LDAPControl **controls )
{
#ifdef LDAP_MEMORY_DEBUG
	assert( controls != NULL );
#endif

	if ( controls != NULL ) {
		int i;

		for( i=0; controls[i] != NULL; i++) {
			ldap_control_free( controls[i] );
		}

		LDAP_FREE( controls );
	}
}