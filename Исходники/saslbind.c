static int
nsldapi_sasl_bind_s(
    LDAP                *ld,
    const char          *dn,
    const char          *mechanism,
    const struct berval *cred,
    LDAPControl         **serverctrls,
    LDAPControl         **clientctrls,
    struct berval       **servercredp,
    LDAPControl         ***responsectrls
)
{
        int             err, msgid;
        LDAPMessage     *result;

        LDAPDebug( LDAP_DEBUG_TRACE, "nsldapi_sasl_bind_s\n", 0, 0, 0 );

        if ( !NSLDAPI_VALID_LDAP_POINTER( ld )) {
                return( LDAP_PARAM_ERROR );
        }

        if ( NSLDAPI_LDAP_VERSION( ld ) < LDAP_VERSION3 ) {
                LDAP_SET_LDERRNO( ld, LDAP_NOT_SUPPORTED, NULL, NULL );
                return( LDAP_NOT_SUPPORTED );
        }

        if ( ( err = ldap_sasl_bind( ld, dn, mechanism, cred, serverctrls,
            clientctrls, &msgid )) != LDAP_SUCCESS )
                return( err );

        if ( ldap_result( ld, msgid, 1, (struct timeval *) 0, &result ) == -1 )
                return( LDAP_GET_LDERRNO( ld, NULL, NULL ) );

        /* Get the controls sent by the server if requested */
        if ( responsectrls ) {
                if ( ( err = ldap_parse_result( ld, result, &err, NULL, NULL,
                       NULL, responsectrls, 0 )) != LDAP_SUCCESS )
                    return( err );
        }

        err = ldap_parse_sasl_bind_result( ld, result, servercredp, 0 );
        if (err != LDAP_SUCCESS  && err != LDAP_SASL_BIND_IN_PROGRESS) {
                ldap_msgfree( result );
                return( err );
        }

        return( ldap_result2error( ld, result, 1 ) );
}