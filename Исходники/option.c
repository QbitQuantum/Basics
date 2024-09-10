/***********************************************************************
 *      ldap_get_optionA     (WLDAP32.@)
 *
 * See ldap_get_optionW.
 */
ULONG CDECL ldap_get_optionA( WLDAP32_LDAP *ld, int option, void *value )
{
    ULONG ret = WLDAP32_LDAP_NOT_SUPPORTED;
#ifdef HAVE_LDAP

    TRACE( "(%p, 0x%08x, %p)\n", ld, option, value );

    if (!ld || !value) return WLDAP32_LDAP_PARAM_ERROR;

    switch (option)
    {
    case WLDAP32_LDAP_OPT_API_FEATURE_INFO:
    {
        LDAPAPIFeatureInfoW featureW;
        LDAPAPIFeatureInfoA *featureA = value;

        if (!featureA->ldapaif_name) return WLDAP32_LDAP_PARAM_ERROR;

        featureW.ldapaif_info_version = featureA->ldapaif_info_version;
        featureW.ldapaif_name = strAtoW( featureA->ldapaif_name );
        featureW.ldapaif_version = 0;

        if (!featureW.ldapaif_name) return WLDAP32_LDAP_NO_MEMORY;

        ret = ldap_get_optionW( ld, option, &featureW );

        featureA->ldapaif_version = featureW.ldapaif_version;
        strfreeW( featureW.ldapaif_name );
        return ret;
    }
    case WLDAP32_LDAP_OPT_API_INFO:
    {
        LDAPAPIInfoW infoW;
        LDAPAPIInfoA *infoA = value;

        memset( &infoW, 0, sizeof(LDAPAPIInfoW) );
        infoW.ldapai_info_version = infoA->ldapai_info_version;

        ret = ldap_get_optionW( ld, option, &infoW );

        infoA->ldapai_api_version = infoW.ldapai_api_version;
        infoA->ldapai_protocol_version = infoW.ldapai_protocol_version;

        if (infoW.ldapai_extensions)
        {
            infoA->ldapai_extensions = strarrayWtoA( infoW.ldapai_extensions );
            if (!infoA->ldapai_extensions) return WLDAP32_LDAP_NO_MEMORY;
        }
        if (infoW.ldapai_vendor_name)
        {
            infoA->ldapai_vendor_name = strWtoA( infoW.ldapai_vendor_name );
            if (!infoA->ldapai_vendor_name)
            {
                ldap_value_freeW( infoW.ldapai_extensions );
                return WLDAP32_LDAP_NO_MEMORY;
            }
        }
        infoA->ldapai_vendor_version = infoW.ldapai_vendor_version;

        ldap_value_freeW( infoW.ldapai_extensions );
        ldap_memfreeW( infoW.ldapai_vendor_name );
        return ret;
    }

    case WLDAP32_LDAP_OPT_DEREF:
    case WLDAP32_LDAP_OPT_DESC:
    case WLDAP32_LDAP_OPT_ERROR_NUMBER:
    case WLDAP32_LDAP_OPT_PROTOCOL_VERSION:
    case WLDAP32_LDAP_OPT_REFERRALS:
    case WLDAP32_LDAP_OPT_SIZELIMIT:
    case WLDAP32_LDAP_OPT_TIMELIMIT:
        return ldap_get_optionW( ld, option, value );

    case WLDAP32_LDAP_OPT_CACHE_ENABLE:
    case WLDAP32_LDAP_OPT_CACHE_FN_PTRS:
    case WLDAP32_LDAP_OPT_CACHE_STRATEGY:
    case WLDAP32_LDAP_OPT_IO_FN_PTRS:
    case WLDAP32_LDAP_OPT_REBIND_ARG:
    case WLDAP32_LDAP_OPT_REBIND_FN:
    case WLDAP32_LDAP_OPT_RESTART:
    case WLDAP32_LDAP_OPT_THREAD_FN_PTRS:
        return LDAP_LOCAL_ERROR;

    case WLDAP32_LDAP_OPT_AREC_EXCLUSIVE:
    case WLDAP32_LDAP_OPT_AUTO_RECONNECT:
    case WLDAP32_LDAP_OPT_CLIENT_CERTIFICATE:
    case WLDAP32_LDAP_OPT_DNSDOMAIN_NAME:
    case WLDAP32_LDAP_OPT_ENCRYPT:
    case WLDAP32_LDAP_OPT_ERROR_STRING:
    case WLDAP32_LDAP_OPT_FAST_CONCURRENT_BIND:
    case WLDAP32_LDAP_OPT_GETDSNAME_FLAGS:
    case WLDAP32_LDAP_OPT_HOST_NAME:
    case WLDAP32_LDAP_OPT_HOST_REACHABLE:
    case WLDAP32_LDAP_OPT_PING_KEEP_ALIVE:
    case WLDAP32_LDAP_OPT_PING_LIMIT:
    case WLDAP32_LDAP_OPT_PING_WAIT_TIME:
    case WLDAP32_LDAP_OPT_PROMPT_CREDENTIALS:
    case WLDAP32_LDAP_OPT_REF_DEREF_CONN_PER_MSG:
    case WLDAP32_LDAP_OPT_REFERRAL_CALLBACK:
    case WLDAP32_LDAP_OPT_REFERRAL_HOP_LIMIT:
    case WLDAP32_LDAP_OPT_ROOTDSE_CACHE:
    case WLDAP32_LDAP_OPT_SASL_METHOD:
    case WLDAP32_LDAP_OPT_SECURITY_CONTEXT:
    case WLDAP32_LDAP_OPT_SEND_TIMEOUT:
    case WLDAP32_LDAP_OPT_SERVER_CERTIFICATE:
    case WLDAP32_LDAP_OPT_SERVER_CONTROLS:
    case WLDAP32_LDAP_OPT_SERVER_ERROR:
    case WLDAP32_LDAP_OPT_SERVER_EXT_ERROR:
    case WLDAP32_LDAP_OPT_SIGN:
    case WLDAP32_LDAP_OPT_SSL:
    case WLDAP32_LDAP_OPT_SSL_INFO:
    case WLDAP32_LDAP_OPT_SSPI_FLAGS:
    case WLDAP32_LDAP_OPT_TCP_KEEPALIVE:
        FIXME( "Unsupported option: 0x%02x\n", option );
        return WLDAP32_LDAP_NOT_SUPPORTED;

    default:
        FIXME( "Unknown option: 0x%02x\n", option );
        return WLDAP32_LDAP_LOCAL_ERROR;
    }

#endif
    return ret;
}