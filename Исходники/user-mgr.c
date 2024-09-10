static LDAP *ldap_init_and_bind (const char *host,
#ifdef WIN32
                                 gboolean use_ssl,
#endif
                                 const char *user_dn,
                                 const char *password)
{
    LDAP *ld;
    int res;
    int desired_version = LDAP_VERSION3;

#ifndef WIN32
    res = ldap_initialize (&ld, host);
    if (res != LDAP_SUCCESS) {
        ccnet_warning ("ldap_initialize failed: %s.\n", ldap_err2string(res));
        return NULL;
    }
#else
    char *host_copy = g_strdup (host);
    if (!use_ssl)
        ld = ldap_init (host_copy, LDAP_PORT);
    else
        ld = ldap_sslinit (host_copy, LDAP_SSL_PORT, 1);
    g_free (host_copy);
    if (!ld) {
        ccnet_warning ("ldap_init failed: %ul.\n", LdapGetLastError());
        return NULL;
    }
#endif

    /* set the LDAP version to be 3 */
    res = ldap_set_option (ld, LDAP_OPT_PROTOCOL_VERSION, &desired_version);
    if (res != LDAP_OPT_SUCCESS) {
        ccnet_warning ("ldap_set_option failed: %s.\n", ldap_err2string(res));
        return NULL;
    }

    if (user_dn) {
#ifndef WIN32
        res = ldap_bind_s (ld, user_dn, password, LDAP_AUTH_SIMPLE);
#else
        char *dn_copy = g_strdup(user_dn);
        char *password_copy = g_strdup(password);
        res = ldap_bind_s (ld, dn_copy, password_copy, LDAP_AUTH_SIMPLE);
        g_free (dn_copy);
        g_free (password_copy);
#endif
        if (res != LDAP_SUCCESS ) {
            ccnet_warning ("ldap_bind failed: %s.\n", ldap_err2string(res));
            ldap_unbind_s (ld);
            return NULL;
        }
    }

    return ld;
}