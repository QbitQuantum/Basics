static
DWORD
_GetSchemaEntryFromPartner(
        LDAP *pLd,
        LDAPMessage **ppResult,
        LDAPMessage **ppEntry
        )
{
    DWORD dwError = 0;
    PCSTR pcszFilter = "(objectclass=*)";
    LDAPMessage *pResult = NULL;
    LDAPMessage *pEntry = NULL;

    dwError = ldap_search_ext_s(
            pLd,
            SUB_SCHEMA_SUB_ENTRY_DN,
            LDAP_SCOPE_BASE,
            pcszFilter,
            ppszSchemaEntryAttrs,
            FALSE, /* get values      */
            NULL,  /* server controls */
            NULL,  /* client controls */
            NULL,  /* timeout         */
            0,     /* size limit      */
            &pResult);
    BAIL_ON_VMDIR_ERROR(dwError);

    // Note: searching by name should yield just one
    if (ldap_count_entries(pLd, pResult) != 1)
    {
        dwError = VMDIR_ERROR_DATA_CONSTRAINT_VIOLATION;
        BAIL_ON_VMDIR_ERROR(dwError);
    }
    pEntry = ldap_first_entry(pLd, pResult);
    *ppEntry = pEntry;
    *ppResult = pResult;

cleanup:
    return dwError;

error:
    VMDIR_LOG_ERROR( VMDIR_LOG_MASK_ALL,
            "%s,%d failed, error(%d)", __FUNCTION__, __LINE__, dwError );

    if (pResult)
    {
        ldap_msgfree(pResult);
    }
    goto cleanup;
}