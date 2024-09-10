/* used for debugging */
static void
print_dn( LDAP *ld, LDAPMessage *entry )
{
    char		*dn, *ufn;

    dn = ldap_get_dn( ld, entry );
    if ( ldif ) {
	write_ldif_value( "dn", dn, strlen( dn ));
    } else {
	printf( "%s\n", dn );
    }
    if ( includeufn ) {
	ufn = ldap_dn2ufn( dn );
	if ( ldif ) {
	    write_ldif_value( "ufn", ufn, strlen( ufn ));
	} else {
	    printf( "%s\n", ufn );
	}
	free( ufn );
    }
    ldap_memfree( dn );
}