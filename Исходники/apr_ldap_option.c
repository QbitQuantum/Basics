/**
 * Handle APR_LDAP_OPT_TLS
 *
 * This function sets the type of TLS to be applied to this connection.
 * The options are:
 * APR_LDAP_NONE: no encryption
 * APR_LDAP_SSL: SSL encryption (ldaps://)
 * APR_LDAP_STARTTLS: STARTTLS encryption
 * APR_LDAP_STOPTLS: Stop existing TLS connecttion
 */
static void option_set_tls(apr_pool_t *pool, LDAP *ldap, const void *invalue,
                          apr_ldap_err_t *result)
{
#if APR_HAS_LDAP_SSL /* compiled with ssl support */

    int tls = * (const int *)invalue;

    /* Netscape/Mozilla/Solaris SDK */
#if APR_HAS_NETSCAPE_LDAPSDK || APR_HAS_SOLARIS_LDAPSDK || APR_HAS_MOZILLA_LDAPSK
#if APR_HAS_LDAPSSL_INSTALL_ROUTINES
    if (tls == APR_LDAP_SSL) {
        result->rc = ldapssl_install_routines(ldap);
#ifdef LDAP_OPT_SSL
        /* apparently Netscape and Mozilla need this too, Solaris doesn't */
        if (result->rc == LDAP_SUCCESS) {
            result->rc = ldap_set_option(ldap, LDAP_OPT_SSL, LDAP_OPT_ON);
        }
#endif
        if (result->rc != LDAP_SUCCESS) {
            result->msg = ldap_err2string(result->rc);
            result->reason = "LDAP: Could not switch SSL on for this "
                             "connection.";
        }
    }
    else if (tls == APR_LDAP_STARTTLS) {
        result->reason = "LDAP: STARTTLS is not supported by the "
                         "Netscape/Mozilla/Solaris SDK";
        result->rc = -1;
    }
    else if (tls == APR_LDAP_STOPTLS) {
        result->reason = "LDAP: STOPTLS is not supported by the "
                         "Netscape/Mozilla/Solaris SDK";
        result->rc = -1;
    }
#else
    if (tls != APR_LDAP_NONE) {
        result->reason = "LDAP: SSL/TLS is not supported by this version "
                         "of the Netscape/Mozilla/Solaris SDK";
        result->rc = -1;
    }
#endif
#endif

    /* Novell SDK */
#if APR_HAS_NOVELL_LDAPSDK
    /* ldapssl_install_routines(ldap)
     * Behavior is unpredictable when other LDAP functions are called
     * between the ldap_init function and the ldapssl_install_routines
     * function.
     * 
     * STARTTLS is supported by the ldap_start_tls_s() method
     */
    if (tls == APR_LDAP_SSL) {
        result->rc = ldapssl_install_routines(ldap);
        if (result->rc != LDAP_SUCCESS) {
            result->msg = ldap_err2string(result->rc);
            result->reason = "LDAP: Could not switch SSL on for this "
                             "connection.";
        }
    }
    if (tls == APR_LDAP_STARTTLS) {
        result->rc = ldapssl_start_tls(ldap);
        if (result->rc != LDAP_SUCCESS) {
            result->msg = ldap_err2string(result->rc);
            result->reason = "LDAP: Could not start TLS on this connection";
        }
    }
    else if (tls == APR_LDAP_STOPTLS) {
        result->rc = ldapssl_stop_tls(ldap);
        if (result->rc != LDAP_SUCCESS) {
            result->msg = ldap_err2string(result->rc);
            result->reason = "LDAP: Could not stop TLS on this connection";
        }
    }
#endif

    /* OpenLDAP SDK */
#if APR_HAS_OPENLDAP_LDAPSDK
#ifdef LDAP_OPT_X_TLS
    if (tls == APR_LDAP_SSL) {
        int SSLmode = LDAP_OPT_X_TLS_HARD;
        result->rc = ldap_set_option(ldap, LDAP_OPT_X_TLS, &SSLmode);
        if (result->rc != LDAP_SUCCESS) {
            result->reason = "LDAP: ldap_set_option failed. "
                             "Could not set LDAP_OPT_X_TLS to "
                             "LDAP_OPT_X_TLS_HARD";
            result->msg = ldap_err2string(result->rc);
        }   
    }
    else if (tls == APR_LDAP_STARTTLS) {
        result->rc = ldap_start_tls_s(ldap, NULL, NULL);
        if (result->rc != LDAP_SUCCESS) {
            result->reason = "LDAP: ldap_start_tls_s() failed";
            result->msg = ldap_err2string(result->rc);
        }
    }
    else if (tls == APR_LDAP_STOPTLS) {
        result->reason = "LDAP: STOPTLS is not supported by the "
                         "OpenLDAP SDK";
        result->rc = -1;
    }
#else
    if (tls != APR_LDAP_NONE) {
        result->reason = "LDAP: SSL/TLS not yet supported by APR on this "
                         "version of the OpenLDAP toolkit";
        result->rc = -1;
    }
#endif
#endif

    /* Microsoft SDK */
#if APR_HAS_MICROSOFT_LDAPSDK
    if (tls == APR_LDAP_NONE) {
        ULONG ul = (ULONG) LDAP_OPT_OFF;
        result->rc = ldap_set_option(ldap, LDAP_OPT_SSL, &ul);
        if (result->rc != LDAP_SUCCESS) {
            result->reason = "LDAP: an attempt to set LDAP_OPT_SSL off "
                             "failed.";
            result->msg = ldap_err2string(result->rc);
        }
    }
    else if (tls == APR_LDAP_SSL) {
        ULONG ul = (ULONG) LDAP_OPT_ON;
        result->rc = ldap_set_option(ldap, LDAP_OPT_SSL, &ul);
        if (result->rc != LDAP_SUCCESS) {
            result->reason = "LDAP: an attempt to set LDAP_OPT_SSL on "
                             "failed.";
            result->msg = ldap_err2string(result->rc);
        }
    }
#if APR_HAS_LDAP_START_TLS_S
    else if (tls == APR_LDAP_STARTTLS) {
        result->rc = ldap_start_tls_s(ldap, NULL, NULL, NULL, NULL);
        if (result->rc != LDAP_SUCCESS) {
            result->reason = "LDAP: ldap_start_tls_s() failed";
            result->msg = ldap_err2string(result->rc);
        }
    }
    else if (tls == APR_LDAP_STOPTLS) {
        result->rc = ldap_stop_tls_s(ldap);
        if (result->rc != LDAP_SUCCESS) {
            result->reason = "LDAP: ldap_stop_tls_s() failed";
            result->msg = ldap_err2string(result->rc);
        }
    }
#endif
#endif

#if APR_HAS_OTHER_LDAPSDK
    if (tls != APR_LDAP_NONE) {
        result->reason = "LDAP: SSL/TLS is currently not supported by "
                         "APR on this LDAP SDK";
        result->rc = -1;
    }
#endif

#endif /* APR_HAS_LDAP_SSL */

}