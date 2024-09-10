void
ldap_mods_free( LDAPMod **mods, int freemods )
{
	int	i;

	if ( mods == NULL )
		return;

	for ( i = 0; mods[i] != NULL; i++ ) {
		if ( mods[i]->mod_op & LDAP_MOD_BVALUES ) {
			if( mods[i]->mod_bvalues != NULL )
				ber_bvecfree( mods[i]->mod_bvalues );

		} else if( mods[i]->mod_values != NULL ) {
			LDAP_VFREE( mods[i]->mod_values );
		}

		if ( mods[i]->mod_type != NULL ) {
			LDAP_FREE( mods[i]->mod_type );
		}

		LDAP_FREE( (char *) mods[i] );
	}

	if ( freemods ) {
		LDAP_FREE( (char *) mods );
	}
}