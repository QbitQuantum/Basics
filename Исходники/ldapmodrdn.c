static int domodrdn(
    LDAP	*ld,
    char	*dn,
    char	*rdn,
    char	*newSuperior,
    int		remove ) /* flag: remove old RDN */
{
    int rc, code, id;
    char *matcheddn=NULL, *text=NULL, **refs=NULL;
    LDAPMessage *res;

    if ( verbose ) {
        printf( "Renaming \"%s\"\n", dn );
        printf( "\tnew rdn=\"%s\" (%s old rdn)\n",
                rdn, remove ? "delete" : "keep" );
        if( newSuperior != NULL ) {
            printf("\tnew parent=\"%s\"\n", newSuperior);
        }
    }

    if( not ) return LDAP_SUCCESS;

    rc = ldap_rename( ld, dn, rdn, newSuperior, remove,
                      NULL, NULL, &id );

    if ( rc != LDAP_SUCCESS ) {
        fprintf( stderr, "%s: ldap_rename: %s (%d)\n",
                 prog, ldap_err2string( rc ), rc );
        return rc;
    }

    rc = ldap_result( ld, LDAP_RES_ANY, LDAP_MSG_ALL, NULL, &res );
    if ( rc < 0 ) {
        ldap_perror( ld, "ldapmodrdn: ldap_result" );
        return rc;
    }

    rc = ldap_parse_result( ld, res, &code, &matcheddn, &text, &refs, NULL, 1 );

    if( rc != LDAP_SUCCESS ) {
        fprintf( stderr, "%s: ldap_parse_result: %s (%d)\n",
                 prog, ldap_err2string( rc ), rc );
        return rc;
    }

    if( verbose || code != LDAP_SUCCESS ||
            (matcheddn && *matcheddn) || (text && *text) || (refs && *refs) )
    {
        printf( "Rename Result: %s (%d)\n",
                ldap_err2string( code ), code );

        if( text && *text ) {
            printf( "Additional info: %s\n", text );
        }

        if( matcheddn && *matcheddn ) {
            printf( "Matched DN: %s\n", matcheddn );
        }

        if( refs ) {
            int i;
            for( i=0; refs[i]; i++ ) {
                printf("Referral: %s\n", refs[i] );
            }
        }
    }

    ber_memfree( text );
    ber_memfree( matcheddn );
    ber_memvfree( (void **) refs );

    return code;
}