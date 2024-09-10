int
main( int argc, char **argv )
{
    int             version;
    LDAP            *ld;
    char            *target;
    int             rc;
    struct berval   userid;
    struct berval   oldpasswd;
    struct berval   newpasswd;
    struct berval   genpasswd;

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

    /* Authenticate to the directory. */
    if ( ldap_simple_bind_s( ld, ENTRYDN, ENTRYPW ) != LDAP_SUCCESS ) {
        ldap_perror( ld, "ldap_simple_bind_s" );
        return( 1 );
    }

    /* Change the password using the extended operation. */
    userid.bv_val = ENTRYDN;
    userid.bv_len = strlen(userid.bv_val);

    oldpasswd.bv_val = ENTRYPW;
    oldpasswd.bv_len = strlen(oldpasswd.bv_val);

    newpasswd.bv_val = "ChangeMe!";
    newpasswd.bv_len = strlen(newpasswd.bv_val);

    rc = ldap_passwd_s(
        ld, &userid, &oldpasswd, &newpasswd, &genpasswd, NULL, NULL );
    if ( rc != LDAP_SUCCESS ) {
        fprintf( stderr, "ldap_passwd_s: %s\n", ldap_err2string( rc ) );
        ldap_unbind( ld );
        return( 1 );
    } else {
        printf( "Successfully changed password for %s\n", userid.bv_val );
    }

    ldap_unbind( ld );
    return( 0 );
}