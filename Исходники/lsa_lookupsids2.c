static
NTSTATUS
LsaSrvLookupDomainSids(
    PPOLICY_CONTEXT        pPolCtx,
    PACCOUNT_SIDS          pAccountSids,
    DWORD                  dwLevel,
    RefDomainList         *pDomains,
    TranslatedNameArray2  *pNamesArray
    )
{
    NTSTATUS ntStatus = STATUS_SUCCESS;
    DWORD dwError = ERROR_SUCCESS;
    PDOMAIN_ENTRY pDomEntry = NULL;
    handle_t hLsaBinding = NULL;
    POLICY_HANDLE hDcPolicy = NULL;
    DWORD dwDomIndex = 0;
    SID_ARRAY Sids = {0};
    RefDomainList *pDomain = NULL;
    TranslatedName *pDomainNames = NULL;
    DWORD dwDomainNamesCount = 0;
    DWORD iDomain = 0;
    DWORD iSid = 0;
    DWORD i = 0;

    ntStatus = LsaSrvGetDomainBySid(pPolCtx,
                                    pPolCtx->pDomainSid,
                                    &pDomEntry);
    if (ntStatus == STATUS_NO_SUCH_DOMAIN)
    {
        ntStatus = LsaSrvConnectDomainBySid(pPolCtx,
                                           pPolCtx->pDomainSid,
                                           &pDomEntry);
        BAIL_ON_NTSTATUS_ERROR(ntStatus);

        hLsaBinding = pDomEntry->hLsaBinding;
        hDcPolicy   = pDomEntry->hPolicy;
    }
    else if (ntStatus == STATUS_SUCCESS)
    {
        hLsaBinding = pDomEntry->hLsaBinding;
        hDcPolicy   = pDomEntry->hPolicy;
    }
    else
    {
        BAIL_ON_NTSTATUS_ERROR(ntStatus);
    }

    Sids.dwNumSids = pAccountSids->dwCount;

    dwError = LwAllocateMemory(sizeof(Sids.pSids[0]) * Sids.dwNumSids,
                               OUT_PPVOID(&Sids.pSids));
    BAIL_ON_LSA_ERROR(dwError);

    for (i = 0; i < Sids.dwNumSids; i++)
    {
        Sids.pSids[i].pSid = pAccountSids->ppSids[i];
    }

    ntStatus = LsaLookupSids(hLsaBinding,
                             hDcPolicy,
                             &Sids,
                             &pDomain,
                             &pDomainNames,
                             dwLevel,
                             &dwDomainNamesCount);
    if (ntStatus == STATUS_SUCCESS ||
        ntStatus == STATUS_SOME_NOT_MAPPED)
    {
        for (iDomain = 0; iDomain < pDomain->count; iDomain++)
        {
            LsaDomainInfo *pSrcDomInfo = NULL;
            LsaDomainInfo *pDstDomInfo = NULL;

            dwDomIndex  = pDomains->count;
            pSrcDomInfo = &(pDomain->domains[iDomain]);
            pDstDomInfo = &(pDomains->domains[dwDomIndex]);

            ntStatus = LsaSrvDuplicateUnicodeStringEx(&pDstDomInfo->name,
                                                      &pSrcDomInfo->name);
            BAIL_ON_NTSTATUS_ERROR(ntStatus);

            ntStatus = LsaSrvDuplicateSid(&pDstDomInfo->sid,
                                          pSrcDomInfo->sid);
            BAIL_ON_NTSTATUS_ERROR(ntStatus);

            for (iSid = 0; iSid < dwDomainNamesCount; iSid++)
            {
                DWORD iTransName = pAccountSids->pdwIndices[iSid];
                TranslatedName *pSrcName = &(pDomainNames[iSid]);
                TranslatedName2 *pDstName = &(pNamesArray->names[iTransName]);

                if (iDomain != pSrcName->sid_index)
                {
                    continue;
                }

                ntStatus = LsaSrvDuplicateUnicodeString(&pDstName->name,
                                                        &pSrcName->name);
                BAIL_ON_NTSTATUS_ERROR(ntStatus);

                pDstName->type      = pSrcName->type;
                pDstName->sid_index = dwDomIndex;
                pDstName->unknown1  = 0;
            }

            pDomains->count  = (++dwDomIndex);
        }

        pNamesArray->count += dwDomainNamesCount;
    }
    else if (ntStatus == STATUS_NONE_MAPPED)
    {
        for (i = 0; i < pAccountSids->dwCount; i++)
        {
            DWORD iTransName = pAccountSids->pdwIndices[i];
            TranslatedName2 *pDstName = &(pNamesArray->names[iTransName]);

            pDstName->type      = SID_TYPE_UNKNOWN;
            pDstName->sid_index = 0;
            pDstName->unknown1  = 0;
        }

        pNamesArray->count += pAccountSids->dwCount;
    }
    else
    {
        BAIL_ON_NTSTATUS_ERROR(ntStatus);
    }

    /*
     * Lookup status is checked later by the caller
     * so avoid bailing accidentally because other lookups
     * may be successful
     */
    if (ntStatus == STATUS_SOME_NOT_MAPPED ||
        ntStatus == STATUS_NONE_MAPPED)
    {
        ntStatus = STATUS_SUCCESS;
    }

cleanup:
    LW_SAFE_FREE_MEMORY(Sids.pSids);

    if (pDomEntry)
    {
        LsaSrvDomainEntryFree(&pDomEntry);
    }

    if (pDomain)
    {
        LsaRpcFreeMemory(pDomain);
    }

    if (pDomainNames)
    {
        LsaRpcFreeMemory(pDomainNames);
    }

    if (ntStatus == STATUS_SUCCESS &&
        dwError != ERROR_SUCCESS)
    {
        ntStatus = LwWin32ErrorToNtStatus(dwError);
    }

    return ntStatus;

error:
    goto cleanup;
}