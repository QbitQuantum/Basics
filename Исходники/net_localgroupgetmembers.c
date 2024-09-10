NET_API_STATUS
NetLocalGroupGetMembers(
    IN  PCWSTR  pwszHostname,
    IN  PCWSTR  pwszAliasname,
    IN  DWORD   dwLevel,
    OUT PVOID  *ppBuffer,
    IN  DWORD   dwMaxBufferSize,
    OUT PDWORD  pdwNumEntries,
    OUT PDWORD  pdwTotalEntries,
    OUT PDWORD  pdwResume
    )
{
    const DWORD dwLsaAccessFlags = LSA_ACCESS_LOOKUP_NAMES_SIDS;
    const DWORD dwAliasAccessFlags = ALIAS_ACCESS_GET_MEMBERS;
    const WORD wLookupLevel = 1;

    NTSTATUS status = STATUS_SUCCESS;
    WINERROR err = ERROR_SUCCESS;
    PNET_CONN pConn = NULL;
    SAMR_BINDING hSamrBinding = NULL;
    LSA_BINDING hLsaBinding = NULL;
    ACCOUNT_HANDLE hAlias = NULL;
    PSID *ppSids = NULL;
    DWORD dwInfoLevelSize = 0;
    DWORD dwTotalNumEntries = 0;
    DWORD dwResume = 0;
    DWORD dwAliasRid = 0;
    DWORD i = 0;
    DWORD dwNumSids = 0;
    DWORD dwCount = 0;
    POLICY_HANDLE hLsaPolicy = NULL;
    SID_ARRAY Sids = {0};
    RefDomainList *pDomains = NULL;
    TranslatedName *pNames = NULL;
    PNET_RESOLVED_NAME pResolvedNames = NULL;
    PVOID pSourceBuffer = NULL;
    PVOID pBuffer = NULL;
    PVOID pBufferCursor = NULL;
    DWORD dwSize = 0;
    DWORD dwTotalSize = 0;
    DWORD dwNumEntries = 0;
    DWORD dwSpaceAvailable = 0;
    PIO_CREDS pCreds = NULL;
    NET_VALIDATION_LEVEL eValidation = NET_VALIDATION_NONE;

    BAIL_ON_INVALID_PTR(pwszAliasname, err);
    BAIL_ON_INVALID_PTR(ppBuffer, err);
    BAIL_ON_INVALID_PTR(pdwNumEntries, err);
    BAIL_ON_INVALID_PTR(pdwTotalEntries, err);
    BAIL_ON_INVALID_PTR(pdwResume, err);

    switch (dwLevel)
    {
    case 0:
        dwInfoLevelSize = sizeof(LOCALGROUP_MEMBERS_INFO_0);
        break;

    case 3:
        dwInfoLevelSize = sizeof(LOCALGROUP_MEMBERS_INFO_3);
        break;

    case 1:
    case 2:
    default:
        err = ERROR_INVALID_LEVEL;
        BAIL_ON_WIN_ERROR(err);
    }

    dwResume = *pdwResume;

    status = LwIoGetActiveCreds(NULL, &pCreds);
    BAIL_ON_NT_STATUS(status);

    status = NetConnectSamr(&pConn,
                            pwszHostname,
                            0,
                            0,
                            pCreds);
    BAIL_ON_NT_STATUS(status);

    hSamrBinding = pConn->Rpc.Samr.hBinding;

    status = NetOpenAlias(pConn,
                          pwszAliasname,
                          dwAliasAccessFlags,
                          &hAlias,
                          &dwAliasRid);
    if (status == STATUS_NONE_MAPPED)
    {
        /* No such alias in host's domain.
           Try to look in builtin domain. */
        status = NetOpenAlias(pConn,
                              pwszAliasname,
                              dwAliasAccessFlags,
                              &hAlias,
                              &dwAliasRid);
        BAIL_ON_NT_STATUS(status);

    }
    else if (status != STATUS_SUCCESS)
    {
        BAIL_ON_NT_STATUS(status);
    }

    status = SamrGetMembersInAlias(hSamrBinding,
                                   hAlias,
                                   &ppSids,
                                   &dwNumSids);
    BAIL_ON_NT_STATUS(status);

    status = SamrClose(hSamrBinding, hAlias);
    BAIL_ON_NT_STATUS(status);

    dwTotalNumEntries = dwNumSids;

    if (dwLevel == 0)
    {
        for (i = 0; i + dwResume < dwNumSids; i++)
        {
            pSourceBuffer = ppSids[i + dwResume];

            err = NetAllocateLocalGroupMembersInfo(NULL,
                                                   NULL,
                                                   dwLevel,
                                                   pSourceBuffer,
                                                   &dwSize,
                                                   eValidation);
            BAIL_ON_WIN_ERROR(err);

            dwTotalSize += dwSize;
            dwNumEntries++;

            if (dwTotalSize > dwMaxBufferSize)
            {
                dwTotalSize -= dwSize;
                dwNumEntries--;
                break;
            }
        }
    }
    else
    {
        status = NetConnectLsa(&pConn,
                               pwszHostname,
                               dwLsaAccessFlags,
                               pCreds);
        BAIL_ON_NT_STATUS(status);

        hLsaBinding  = pConn->Rpc.Lsa.hBinding;
        hLsaPolicy   = pConn->Rpc.Lsa.hPolicy;

        Sids.dwNumSids = dwNumSids;
        status = NetAllocateMemory(OUT_PPVOID(&Sids.pSids),
                                   sizeof(Sids.pSids[0]) * Sids.dwNumSids);
        BAIL_ON_NT_STATUS(status);
    
        for (i = 0; i < Sids.dwNumSids; i++)
        {
            Sids.pSids[i].pSid = ppSids[i];
        }

        status = LsaLookupSids(hLsaBinding,
                               hLsaPolicy,
                               &Sids,
                               &pDomains,
                               &pNames,
                               wLookupLevel,
                               &dwCount);
        if (status != STATUS_SUCCESS &&
            status != LW_STATUS_SOME_NOT_MAPPED)
        {
            BAIL_ON_NT_STATUS(status);
        }

        status = NetAllocateMemory(OUT_PPVOID(&pResolvedNames),
                                   sizeof(*pResolvedNames) * dwCount);
        BAIL_ON_NT_STATUS(status);

        for (i = 0; i + dwResume < dwCount; i++)
        {
            DWORD iDomain = pNames[i + dwResume].sid_index;

            pResolvedNames[i].AccountName = pNames[i + dwResume].name;
            pResolvedNames[i].usType      = pNames[i + dwResume].type;
            pResolvedNames[i].DomainName  = pDomains->domains[iDomain].name;

            pSourceBuffer = pResolvedNames;

            err = NetAllocateLocalGroupMembersInfo(NULL,
                                                   NULL,
                                                   dwLevel,
                                                   pSourceBuffer,
                                                   &dwSize,
                                                   eValidation);
            BAIL_ON_WIN_ERROR(err);

            dwTotalSize += dwSize;
            dwNumEntries++;

            if (dwTotalSize > dwMaxBufferSize)
            {
                dwTotalSize -= dwSize;
                dwNumEntries--;
                break;
            }
        }
    }

    if (dwTotalNumEntries > 0 && dwNumEntries == 0)
    {
        err = ERROR_INSUFFICIENT_BUFFER;
        BAIL_ON_WIN_ERROR(err);
    }

    if (dwTotalSize)
    {
        status = NetAllocateMemory(OUT_PPVOID(&pBuffer),
                                   dwTotalSize);
        BAIL_ON_NT_STATUS(status);
    }

    dwSize           = 0;
    pBufferCursor    = pBuffer;
    dwSpaceAvailable = dwTotalSize;

    for (i = 0; i < dwNumEntries; i++)
    {
        if (dwLevel == 0)
        {
            pSourceBuffer = ppSids[i + dwResume];
        }
        else
        {
            pSourceBuffer = &(pResolvedNames[i]);
        }

        pBufferCursor = pBuffer + (i * dwInfoLevelSize);

        err = NetAllocateLocalGroupMembersInfo(pBufferCursor,
                                               &dwSpaceAvailable,
                                               dwLevel,
                                               pSourceBuffer,
                                               &dwSize,
                                               eValidation);
        BAIL_ON_WIN_ERROR(err);
    }

    if (dwResume + dwNumEntries < dwTotalNumEntries)
    {
        err = ERROR_MORE_DATA;
    }

    *ppBuffer        = pBuffer;
    *pdwResume       = dwResume + dwNumEntries;
    *pdwNumEntries   = dwNumEntries;
    *pdwTotalEntries = dwTotalNumEntries;

cleanup:
    NetDisconnectSamr(&pConn);

    if (Sids.pSids)
    {
        NetFreeMemory(Sids.pSids);
    }

    if (ppSids)
    {
        SamrFreeMemory(ppSids);
    }

    if (pNames)
    {
        SamrFreeMemory(pNames);
    }

    if (pDomains)
    {
        SamrFreeMemory(pDomains);
    }

    if (pCreds)
    {
        LwIoDeleteCreds(pCreds);
    }

    if (err == ERROR_SUCCESS &&
        status != STATUS_SUCCESS)
    {
        err = LwNtStatusToWin32Error(status);
    }

    return err;

error:
    if (pBuffer)
    {
        NetFreeMemory(pBuffer);
    }

    *ppBuffer = NULL;

    goto cleanup;
}