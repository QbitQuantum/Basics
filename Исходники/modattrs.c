int
main( int argc, char **argv )
{
    LDAP	*ld;
    LDAPMod	mod0, mod1, *mods[ 3 ];
    char	*vals0[ 2 ], *vals1[ 2 ], buf[ 128 ];
    time_t	now;

    /* get an LDAP session handle and authenticate */
    if ( (ld = ldap_init( MY_HOST, MY_PORT )) == NULL ) {
	perror( "ldap_init" );
	return( 1 );
    }
    if ( ldap_simple_bind_s( ld, MGR_DN, MGR_PW ) != LDAP_SUCCESS ) {
	ldap_perror( ld, "ldap_simple_bind_s" );
	return( 1 );
    }

    /* construct the list of modifications to make */
    mod0.mod_op = LDAP_MOD_REPLACE;
    mod0.mod_type = "mail";
    vals0[0] = "*****@*****.**";
    vals0[1] = NULL;
    mod0.mod_values = vals0;

    mod1.mod_op = LDAP_MOD_ADD;
    mod1.mod_type = "description";
    time( &now );
    sprintf( buf, "This entry was modified with the modattrs program on %s",
	    ctime( &now ));
    /* Get rid of \n which ctime put on the end of the time string */
    if ( buf[ strlen( buf ) - 1 ] == '\n' ) {
	buf[ strlen( buf ) - 1 ] = '\0';
    }
    vals1[ 0 ] = buf;
    vals1[ 1 ] = NULL;
    mod1.mod_values = vals1;

    mods[ 0 ] = &mod0;
    mods[ 1 ] = &mod1;
    mods[ 2 ] = NULL;

    /* make the change and clean up after ourselves */
    if ( ldap_modify_s( ld, ENTRYDN, mods ) != LDAP_SUCCESS ) {
	ldap_perror( ld, "ldap_modify_s" );
	return( 1 );
    }
    ldap_unbind( ld );
    printf( "modification was successful\n" );
    return( 0 );
}