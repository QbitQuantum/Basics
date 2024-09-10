static
DWORD
KtLdapQuery(
    LDAP  *pLd,
    PCSTR  pszBaseDn,
    DWORD  dwScope,
    PCSTR  pszFilter,
    PCSTR  pszAttrName,
    PSTR  *ppszAttrVal
    )
{
    DWORD dwError = ERROR_SUCCESS;
    int lderr = LDAP_SUCCESS;
    char *attrs[2] = {
        NULL, // This gets filled in later
        NULL  // This null terminates the list of attributes
    };
    LDAPMessage *res = NULL;
    LDAPMessage *entry = NULL;
    char *attr = NULL;
    struct berval **ppBv = NULL;
    BerElement *ptr = NULL;
    struct timeval timeout = { .tv_sec  = 10,
                               .tv_usec = 0 };
    PSTR pszAttrVal = NULL;

    dwError = LwAllocateString(pszAttrName,
                               &attrs[0]);
    BAIL_ON_LSA_ERROR(dwError);

    lderr = ldap_search_ext_s(pLd,
                              pszBaseDn,
                              dwScope,
                              pszFilter,
                              attrs,
                              0,
                              NULL,
                              NULL,
                              &timeout,
                              0,
                              &res);
    BAIL_ON_LDAP_ERROR(lderr);

    if (ldap_count_entries(pLd, res))
    {
        entry = ldap_first_entry(pLd, res);
        if (entry == NULL)
        {
            dwError = ERROR_DS_GENERIC_ERROR;
            BAIL_ON_LSA_ERROR(dwError);
        }

        attr = ldap_first_attribute(pLd, entry, &ptr);
        if (attr)
        {
            ppBv = ldap_get_values_len(pLd, entry, attr);
            if (ldap_count_values_len(ppBv))
            {
                dwError = LwAllocateMemory(ppBv[0]->bv_len + 1,
                                           OUT_PPVOID(&pszAttrVal));
                BAIL_ON_LSA_ERROR(dwError);

                memcpy(pszAttrVal, ppBv[0]->bv_val, ppBv[0]->bv_len);
            }

            ldap_memfree(attr);
        }

        ldap_msgfree(res);
    }

    *ppszAttrVal = pszAttrVal;

cleanup:
    if (ppBv)
    {
        ldap_value_free_len(ppBv);
    }

    if (ptr != NULL)
    {
        ber_free( ptr, 0 );
    }

    LW_SAFE_FREE_STRING(attrs[0]);

    if (dwError == ERROR_SUCCESS &&
        lderr != LDAP_SUCCESS)
    {
        dwError = LwMapLdapErrorToLwError(lderr);
    }

    return dwError;

error:
    *ppszAttrVal = NULL;

    goto cleanup;
}

static
DWORD
KtLdapUnbind(
    LDAP *pLd
    )
{
    DWORD dwError = ERROR_SUCCESS;
    int lderr = LDAP_SUCCESS;

    lderr = ldap_unbind_ext_s(pLd, NULL, NULL);
    BAIL_ON_LDAP_ERROR(lderr);

cleanup:
    if (lderr)
    {
        dwError = LwMapLdapErrorToLwError(lderr);
    }

    return dwError;

error:
    goto cleanup;
}