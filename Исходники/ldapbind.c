DWORD
VmDirSASLGSSAPIBind(
     LDAP**     ppLd,
     PCSTR      pszURI
     )
{
    DWORD       dwError = 0;
    int         retVal = 0;
    LDAP*       pLd = NULL;
    const int   ldapVer = LDAP_VERSION3;

    if ( ppLd == NULL || pszURI == NULL )
    {
        dwError = VMDIR_ERROR_INVALID_PARAMETER;
        BAIL_ON_VMDIR_ERROR(dwError);
    }

    retVal = ldap_initialize( &pLd, pszURI);
    BAIL_ON_SIMPLE_LDAP_ERROR(retVal);

    retVal = ldap_set_option(pLd, LDAP_OPT_PROTOCOL_VERSION, &ldapVer);
    BAIL_ON_SIMPLE_LDAP_ERROR(retVal);

    retVal = ldap_sasl_interactive_bind_s( pLd,
                                            NULL,
                                            "GSSAPI",
                                            NULL,
                                            NULL,
                                            LDAP_SASL_QUIET,
                                            _VmDirSASLGSSAPIInteraction,
                                            NULL);
    BAIL_ON_SIMPLE_LDAP_ERROR(retVal);

    *ppLd = pLd;

cleanup:

    return dwError;

ldaperror:

    VMDIR_LOG_VERBOSE( VMDIR_LOG_MASK_ALL, "_VmDirSASLGSSBind failed. (%d)(%s)",
                                           retVal, ldap_err2string(retVal) );
    dwError = VmDirMapLdapError(retVal);

error:
    if (retVal == 0)
    {
        VMDIR_LOG_VERBOSE( VMDIR_LOG_MASK_ALL, "_VmDirSASLGSSBind failed. (%u)", dwError);
    }

    if ( pLd )
    {
        ldap_unbind_ext_s( pLd, NULL, NULL);
    }
    goto cleanup;
}