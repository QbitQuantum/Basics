static void
do_modify( char *uri, char *manager,
           struct berval *passwd, char *entry, char* attr, char* value,
           int maxloop, int maxretries, int delay, int friendly, int chaserefs )
{
    LDAP	*ld = NULL;
    int  	i = 0, do_retry = maxretries;
    int     rc = LDAP_SUCCESS;

    struct ldapmod mod;
    struct ldapmod *mods[2];
    char *values[2];
    int version = LDAP_VERSION3;

    values[0] = value;
    values[1] = NULL;
    mod.mod_op = LDAP_MOD_ADD;
    mod.mod_type = attr;
    mod.mod_values = values;
    mods[0] = &mod;
    mods[1] = NULL;

retry:
    ;
    ldap_initialize( &ld, uri );
    if ( ld == NULL ) {
        tester_perror( "ldap_initialize", NULL );
        exit( EXIT_FAILURE );
    }

    (void) ldap_set_option( ld, LDAP_OPT_PROTOCOL_VERSION, &version );
    (void) ldap_set_option( ld, LDAP_OPT_REFERRALS,
                            chaserefs ? LDAP_OPT_ON : LDAP_OPT_OFF );

    if ( do_retry == maxretries ) {
        fprintf( stderr, "PID=%ld - Modify(%d): entry=\"%s\".\n",
                 (long) pid, maxloop, entry );
    }

    rc = ldap_sasl_bind_s( ld, manager, LDAP_SASL_SIMPLE, passwd, NULL, NULL, NULL );
    if ( rc != LDAP_SUCCESS ) {
        tester_ldap_error( ld, "ldap_sasl_bind_s", NULL );
        switch ( rc ) {
        case LDAP_BUSY:
        case LDAP_UNAVAILABLE:
            if ( do_retry > 0 ) {
                do_retry--;
                if ( delay > 0 ) {
                    sleep( delay );
                }
                goto retry;
            }
        /* fallthru */
        default:
            break;
        }
        exit( EXIT_FAILURE );
    }

    for ( ; i < maxloop; i++ ) {
        mod.mod_op = LDAP_MOD_ADD;
        rc = ldap_modify_ext_s( ld, entry, mods, NULL, NULL );
        if ( rc != LDAP_SUCCESS ) {
            tester_ldap_error( ld, "ldap_modify_ext_s", NULL );
            switch ( rc ) {
            case LDAP_TYPE_OR_VALUE_EXISTS:
                /* NOTE: this likely means
                 * the second modify failed
                 * during the previous round... */
                if ( !friendly ) {
                    goto done;
                }
                break;

            case LDAP_BUSY:
            case LDAP_UNAVAILABLE:
                if ( do_retry > 0 ) {
                    do_retry--;
                    goto retry;
                }
            /* fall thru */

            default:
                goto done;
            }
        }

        mod.mod_op = LDAP_MOD_DELETE;
        rc = ldap_modify_ext_s( ld, entry, mods, NULL, NULL );
        if ( rc != LDAP_SUCCESS ) {
            tester_ldap_error( ld, "ldap_modify_ext_s", NULL );
            switch ( rc ) {
            case LDAP_NO_SUCH_ATTRIBUTE:
                /* NOTE: this likely means
                 * the first modify failed
                 * during the previous round... */
                if ( !friendly ) {
                    goto done;
                }
                break;

            case LDAP_BUSY:
            case LDAP_UNAVAILABLE:
                if ( do_retry > 0 ) {
                    do_retry--;
                    goto retry;
                }
            /* fall thru */

            default:
                goto done;
            }
        }

    }

done:
    ;
    fprintf( stderr, "  PID=%ld - Modify done (%d).\n", (long) pid, rc );

    ldap_unbind_ext( ld, NULL, NULL );
}