static
void
_VmDirClientTestSimpleBind(
    PCSTR   pszLDAPURI
    )
{
    DWORD   dwError = 0;
    int	    ldap_version_3 = LDAP_VERSION3;
    LDAP *  pLD = NULL;
    BerValue    ldapBindPwd = {0};

    printf("_VmDirClientTestSimpleBind ldap simple bind initialize %s\n", pszLDAPURI);
    dwError = ldap_initialize( &pLD, pszLDAPURI );
    /* Set LDAP V3 protocol version */
    ldap_set_option( pLD, LDAP_OPT_PROTOCOL_VERSION, &ldap_version_3 );

    printf("_VmDirClientTestSimpleBind ldap simple ANONYMOUS bind started.\n");
    dwError = ldap_sasl_bind_s(
                                   pLD,
                                   "",
                                   LDAP_SASL_SIMPLE,
                                   &ldapBindPwd,  // no credentials
                                   NULL,
                                   NULL,
                                   NULL);
    BAIL_ON_VMDIR_ERROR(dwError);

    printf("_VmDirClientTestSimpleBind ldap simple ANONYMOUS bind succeeded.\n");

cleanup:
    if (pLD)
    {
        dwError = ldap_unbind_ext_s(    pLD,
                                        NULL,
                                        NULL);
        BAIL_ON_VMDIR_ERROR(dwError);

        printf("_VmDirClientTestSimpleBind ldap unbind succeeded.\n\n\n");
    }

    return;

error:

	printf("_VmDirClientTestSimpleBind failed. (%d)(%s)\n\n", dwError, ldap_err2string(dwError));

	goto cleanup;
}