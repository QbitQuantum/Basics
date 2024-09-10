DWORD
LwLdapDirectoryOnePagedSearch(
    HANDLE         hDirectory,
    PCSTR          pszObjectDN,
    PCSTR          pszQuery,
    PSTR*          ppszAttributeList,
    DWORD          dwPageSize,
    PLW_SEARCH_COOKIE pCookie,
    int            scope,
    LDAPMessage**  ppMessage
    )
{
    DWORD dwError = LW_ERROR_SUCCESS;
    PLW_LDAP_DIRECTORY_CONTEXT pDirectory = NULL;
    ber_int_t pageCount = 0;
    CHAR pagingCriticality = 'T';
    LDAPControl *pPageControl = NULL;
    LDAPControl *ppInputControls[2] = { NULL, NULL };
    LDAPControl **ppReturnedControls = NULL;
    int errorcodep = 0;
    LDAPMessage* pMessage = NULL;
    BOOLEAN bSearchFinished = FALSE;
    struct berval * pBerCookie = (struct berval *)pCookie->pvData;

    LW_ASSERT(pCookie->pfnFree == NULL || pCookie->pfnFree == LwLdapFreeCookie);
    pDirectory = (PLW_LDAP_DIRECTORY_CONTEXT)hDirectory;

   // dwError = ADEnablePageControlOption(hDirectory);
   // BAIL_ON_LW_ERROR(dwError);

    dwError = ldap_create_page_control(pDirectory->ld,
                                       dwPageSize,
                                       pBerCookie,
                                       pagingCriticality,
                                       &pPageControl);
    BAIL_ON_LDAP_ERROR(dwError);

    ppInputControls[0] = pPageControl;

    dwError = LwLdapDirectorySearchEx(
               hDirectory,
               pszObjectDN,
               scope,
               pszQuery,
               ppszAttributeList,
               ppInputControls,
               0,
               &pMessage);
    BAIL_ON_LW_ERROR(dwError);

    dwError = ldap_parse_result(pDirectory->ld,
                                pMessage,
                                &errorcodep,
                                NULL,
                                NULL,
                                NULL,
                                &ppReturnedControls,
                                0);
    BAIL_ON_LDAP_ERROR(dwError);

    if (pBerCookie != NULL)
    {
        ber_bvfree(pBerCookie);
        pBerCookie = NULL;
    }

    dwError = ldap_parse_page_control(pDirectory->ld,
                                      ppReturnedControls,
                                      &pageCount,
                                      &pBerCookie);
    BAIL_ON_LDAP_ERROR(dwError);

    if (pBerCookie == NULL || pBerCookie->bv_len < 1)
    {
        bSearchFinished = TRUE;
    }

    if (ppReturnedControls)
    {
       ldap_controls_free(ppReturnedControls);
       ppReturnedControls = NULL;
    }

    ppInputControls[0] = NULL;
    ldap_control_free(pPageControl);
    pPageControl = NULL;

    pCookie->bSearchFinished = bSearchFinished;
    *ppMessage = pMessage;
    pCookie->pvData = pBerCookie;
    pCookie->pfnFree = LwLdapFreeCookie;

cleanup:
  /*  dwError_disable = ADDisablePageControlOption(hDirectory);
    if (dwError_disable)
        LW_RTL_LOG_ERROR("Error: LDAP Disable PageControl Info: failed");*/

    if (ppReturnedControls) {
        ldap_controls_free(ppReturnedControls);
    }

    ppInputControls[0] = NULL;

    if (pPageControl) {
        ldap_control_free(pPageControl);
    }

    return (dwError);

error:

    *ppMessage = NULL;
    pCookie->pvData = NULL;
    pCookie->pfnFree = NULL;
    pCookie->bSearchFinished = TRUE;

    if (pBerCookie != NULL)
    {
        ber_bvfree(pBerCookie);
        pBerCookie = NULL;
    }

    goto cleanup;
}