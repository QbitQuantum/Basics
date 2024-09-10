int
main( int argc, char **argv )
{
    int             version;
    LDAP            *ld;
    int             rc;
    LDAPControl     *gerctrl = NULL;
    LDAPControl     *requestctrls[ 2 ];
    char            *authzid;
    char            **attrlist;
    LDAPMessage     *result;
    LDAPMessage     *entry;
    char            *attr;
    BerElement      *ber;
    char            **vals;
    int             i;

    /* Use LDAPv3. */
    version = LDAP_VERSION3;
    if ( ldap_set_option( NULL, LDAP_OPT_PROTOCOL_VERSION, &version )
            != 0 ) {
        fprintf( stderr,
                 "ldap_set_option protocol version to %d failed\n",
                 version );
        return ( 1 );
    }

    /* Get a handle to an LDAP connection. */
    if ( (ld = ldap_init( MY_HOST, MY_PORT )) == NULL ) {
        perror( "ldap_init" );
        return( 1 );
    }

    /* Authenticate to the directory as a user. */
    if ( ldap_simple_bind_s( ld, USER_DN, USER_PW ) != LDAP_SUCCESS ) {
        ldap_perror( ld, "ldap_simple_bind_s" );
        return( 1 );
    }

    /* Create a get effective rights control. */
    authzid = "dn: uid=kvaughan,ou=people,dc=example,dc=com";
    if ( !( attrlist = (char**)malloc(sizeof(char * [ 2 ]) ) ) ) {
        perror( "malloc" );
        ldap_unbind( ld );
        return ( 1 );
    }
    attrlist[ 0 ] = "aclRights";
    attrlist[ 1 ] = NULL;
    rc = ldap_create_geteffectiveRights_control( ld, authzid,
            (const char **)&attrlist, 1, &gerctrl );
    if ( rc != LDAP_SUCCESS ) {
        fprintf( stderr, "ldap_create_geteffectiveRights_control: %s\n",
                 ldap_err2string( rc ) );
        ldap_unbind( ld );
        return( 1 );
    }
    requestctrls[ 0 ] = gerctrl;
    requestctrls[ 1 ] = NULL;

    /* Read an entry using the control. */
    rc = ldap_search_ext_s( ld, ENTRYDN, LDAP_SCOPE_BASE,
                            "(objectclass=*)", attrlist, 0, requestctrls,
                            NULL, NULL, 0, &result );
    if ( rc != LDAP_SUCCESS ) {
        fprintf( stderr, "ldap_search_ext_s: %s\n", ldap_err2string( rc ) );
        ldap_unbind( ld );
        return( 1 );
    }

    /* Examine the entry for effective rights. */
    printf( "Bind DN:  %s\n", ENTRYDN );
    printf( "Authz ID: %s\n", authzid );
    printf( "***Rights***\n" );
    for ( entry = ldap_first_entry( ld, result );
            entry != NULL;
            entry = ldap_next_entry( ld, entry ) ) {
        for ( attr = ldap_first_attribute( ld, entry, &ber );
                attr != NULL;
                attr = ldap_next_attribute ( ld, entry, ber) ) {
            if ( (vals = ldap_get_values( ld, entry, attr ) ) != NULL) {
                for ( i = 0; vals[i] != NULL; ++i ) {
                    printf( "%s: %s\n", attr, vals[i] );
                }
                ldap_value_free( vals );
            }
            ldap_memfree( attr );
        }
        if ( ber != NULL ) {
            ber_free( ber, 0 );
        }
    }
    printf( "\n" );

    ldap_msgfree( result );
    ldap_control_free( gerctrl );
    ldap_unbind( ld );
    return( 0 );
}