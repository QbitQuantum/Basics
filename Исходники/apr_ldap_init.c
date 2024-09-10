/**
 * APR LDAP initialise function
 *
 * This function is responsible for initialising an LDAP
 * connection in a toolkit independant way. It does the
 * job of ldap_init() from the C api.
 *
 * It handles both the SSL and non-SSL case, and attempts
 * to hide the complexity setup from the user. This function
 * assumes that any certificate setup necessary has already
 * been done.
 *
 * If SSL or STARTTLS needs to be enabled, and the underlying
 * toolkit supports it, the following values are accepted for
 * secure:
 *
 * APR_LDAP_NONE: No encryption
 * APR_LDAP_SSL: SSL encryption (ldaps://)
 * APR_LDAP_STARTTLS: Force STARTTLS on ldap://
 */
APU_DECLARE_LDAP(int) apr_ldap_init(apr_pool_t *pool,
                                    LDAP **ldap,
                                    const char *hostname,
                                    int portno,
                                    int secure,
                                    apr_ldap_err_t **result_err)
{

    apr_ldap_err_t *result = (apr_ldap_err_t *)apr_pcalloc(pool, sizeof(apr_ldap_err_t));
    *result_err = result;

#if APR_HAS_LDAPSSL_INIT
#if APR_HAS_SOLARIS_LDAPSDK
    /*
     * Using the secure argument should aways be possible.  But as LDAP SDKs
     * tend to have different quirks and bugs, this needs to be tested for
     * for each of them, first. For Solaris LDAP it works, and the method
     * with ldap_set_option doesn't.
     */
    *ldap = ldapssl_init(hostname, portno, secure == APR_LDAP_SSL);
#else
    *ldap = ldapssl_init(hostname, portno, 0);
#endif
#elif APR_HAS_LDAP_SSLINIT
    *ldap = ldap_sslinit((char *)hostname, portno, 0);
#else
    *ldap = ldap_init((char *)hostname, portno);
#endif

    if (*ldap != NULL) {
#if APR_HAS_SOLARIS_LDAPSDK
        if (secure == APR_LDAP_SSL)
            return APR_SUCCESS;
        else
#endif
        return apr_ldap_set_option(pool, *ldap, APR_LDAP_OPT_TLS, &secure, result_err);
    }
    else {
        /* handle the error case */
        apr_ldap_err_t *result = (apr_ldap_err_t *)apr_pcalloc(pool, sizeof(apr_ldap_err_t));
        *result_err = result;

        result->reason = "APR LDAP: Unable to initialize the LDAP connection";
        result->rc = -1;
        return APR_EGENERAL;
    }

}