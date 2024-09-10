//------------------------------------
// LdapUtils implementation
//------------------------------------
LDAP* LdapUtils::LdapInit(const char* protocol, const char* host, int port, int secure_port)
{
    LDAP* ld = NULL;
    if(stricmp(protocol, "ldaps") == 0)
    {
#ifdef _WIN32
        ld = ldap_sslinit((char*)host, secure_port, 1);
        if (ld == NULL )
            throw MakeStringException(-1, "ldap_sslinit error" );

        int rc = 0;
        unsigned long version = LDAP_VERSION3;
        long lv = 0;

        rc = ldap_set_option(ld,
            LDAP_OPT_PROTOCOL_VERSION,
            (void*)&version);
        if (rc != LDAP_SUCCESS)
            throw MakeStringException(-1, "ldap_set_option error - %s", ldap_err2string(rc));

        rc = ldap_get_option(ld,LDAP_OPT_SSL,(void*)&lv);
        if (rc != LDAP_SUCCESS)
            throw MakeStringException(-1, "ldap_get_option error - %s", ldap_err2string(rc));

        // If SSL is not enabled, enable it.
        if ((void*)lv != LDAP_OPT_ON)
        {
            rc = ldap_set_option(ld, LDAP_OPT_SSL, LDAP_OPT_ON);
            if (rc != LDAP_SUCCESS)
                throw MakeStringException(-1, "ldap_set_option error - %s", ldap_err2string(rc));
        }

        ldap_set_option(ld, LDAP_OPT_SERVER_CERTIFICATE, verifyServerCert);
#else
        // Initialize an LDAP session for TLS/SSL
#ifndef HAVE_TLS
        //throw MakeStringException(-1, "openldap client library libldap not compiled with TLS support");
#endif
        StringBuffer uri("ldaps://");
        uri.appendf("%s:%d", host, secure_port);
        DBGLOG("connecting to %s", uri.str());
        int rc = LDAP_INIT(&ld, uri.str());
        if(rc != LDAP_SUCCESS)
        {
            throw MakeStringException(-1, "ldap_initialize error %s", ldap_err2string(rc));
        }
        int reqcert = LDAP_OPT_X_TLS_NEVER;
        ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &reqcert);
#endif
    }
    else
    {
        // Initialize an LDAP session
        DBGLOG("connecting to ldap://%s:%d", host, port);
#ifdef _WIN32
        ld = LDAP_INIT(host, port);
        if(NULL == ld)
        {
            throw MakeStringException(-1, "ldap_init(%s,%d) error %s", host, port, ldap_err2string(LdapGetLastError()));
        }
#else
        StringBuffer uri("ldap://");
        uri.appendf("%s:%d", host, port);
        int rc = LDAP_INIT(&ld, uri.str());
        if(rc != LDAP_SUCCESS)
        {
            throw MakeStringException(-1, "ldap_initialize(%s,%d) error %s", host, port, ldap_err2string(rc));
        }
#endif
    }
    return ld;
}