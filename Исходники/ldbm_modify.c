/* Function removes mods which are not allowed over-the-wire */
static void
remove_illegal_mods(LDAPMod **mods)
{
	int		i, j;
	LDAPMod		*tmp;

	/* remove any attempts by the user to modify these attrs */
	for ( i = 0; (mods != NULL) && (mods[i] != NULL); i++ ) {
		if ( strcasecmp( mods[i]->mod_type, numsubordinates ) == 0
		    || strcasecmp( mods[i]->mod_type, hassubordinates ) == 0 )
		{
			tmp = mods[i];
			for ( j = i; mods[j] != NULL; j++ ) {
				mods[j] = mods[j + 1];
			}
			slapi_ch_free( (void**)&(tmp->mod_type) );
			if ( tmp->mod_bvalues != NULL ) {
				ber_bvecfree( tmp->mod_bvalues );
			}
			slapi_ch_free( (void**)&tmp );
			i--;
		}
	}
}