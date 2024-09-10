static
DWORD
ProcessAddRemoveAccountRights(
    IN PRPC_PARAMETERS pRpcParams,
    IN BOOLEAN Add,
    IN PSTR AccountRights,
    IN BOOLEAN RemoveAll,
    IN PSTR AccountName
    )
{
    DWORD err = ERROR_SUCCESS;
    NTSTATUS ntStatus = STATUS_SUCCESS;
    LSA_BINDING hLsa = NULL;
    LW_PIO_CREDS pCreds = NULL;
    WCHAR wszSysName[] = {'\\', '\\', '\0'};
    DWORD policyAccessMask = LSA_ACCESS_LOOKUP_NAMES_SIDS |
                             LSA_ACCESS_CREATE_SPECIAL_ACCOUNTS;
    POLICY_HANDLE hPolicy = NULL;
    PSID pAccountSid = NULL;
    PSTR *ppszAccountRightNames = NULL;
    DWORD numAccountRightNames = 0;
    PWSTR *ppwszAccountRightNames = NULL;
    DWORD i = 0;
    
    err = CreateRpcCredentials(pRpcParams,
                               &pCreds);
    BAIL_ON_LSA_ERROR(err);

    err = CreateLsaRpcBinding(pRpcParams,
                              pCreds,
                              &hLsa);
    BAIL_ON_LSA_ERROR(err);

    ntStatus = LsaOpenPolicy2(hLsa,
                              wszSysName,
                              NULL,
                              policyAccessMask,
                              &hPolicy);
    BAIL_ON_NT_STATUS(ntStatus);

    err = ResolveAccountNameToSid(
                          hLsa,
                          AccountName,
                          &pAccountSid);
    BAIL_ON_LSA_ERROR(err);

    if (AccountRights)
    {
        err = GetStringListFromString(
                              AccountRights,
                              SEPARATOR_CHAR,
                              &ppszAccountRightNames,
                              &numAccountRightNames);
        BAIL_ON_LSA_ERROR(err);

        err = LwAllocateMemory(
                       sizeof(ppwszAccountRightNames[0]) * numAccountRightNames,
                       OUT_PPVOID(&ppwszAccountRightNames));
        BAIL_ON_LSA_ERROR(err);

        for (i = 0; i < numAccountRightNames; i++)
        {
            err = LwMbsToWc16s(ppszAccountRightNames[i],
                               &ppwszAccountRightNames[i]);
            BAIL_ON_LSA_ERROR(err);
        }
    }

    if (Add)
    {
        ntStatus = LsaAddAccountRights(
                              hLsa,
                              hPolicy,
                              pAccountSid,
                              ppwszAccountRightNames,
                              numAccountRightNames);
        BAIL_ON_NT_STATUS(ntStatus);

        fprintf(stdout, "Successfully added account rights to %s\n", AccountName);
    }
    else
    {
        ntStatus = LsaRemoveAccountRights(
                              hLsa,
                              hPolicy,
                              pAccountSid,
                              RemoveAll,
                              ppwszAccountRightNames,
                              numAccountRightNames);
        BAIL_ON_NT_STATUS(ntStatus);

        fprintf(stdout, "Successfully removed account rights from %s\n", AccountName);
    }

error:
    if (ntStatus || err)
    {
        PCSTR errName = LwNtStatusToName(ntStatus);
        PCSTR errDescription = LwNtStatusToDescription(ntStatus);

        if (ntStatus)
        {
            errName = LwNtStatusToName(ntStatus);
            errDescription = LwNtStatusToDescription(ntStatus);
        }
        else
        {
            errName = LwWin32ErrorToName(err);
            errDescription = LwWin32ErrorToDescription(err);
        }

        fprintf(stderr, "Error: %s (%s)\n",
                LSA_SAFE_LOG_STRING(errName),
                LSA_SAFE_LOG_STRING(errDescription));
    }

    if (hPolicy)
    {
        LsaClose(hLsa, hPolicy);
    }

    if (hLsa)
    {
        LsaFreeBinding(&hLsa);
    }

    if (pCreds)
    {
        LwIoDeleteCreds(pCreds);
    }

    for (i = 0; i < numAccountRightNames; i++)
    {
        LW_SAFE_FREE_MEMORY(ppwszAccountRightNames[i]);
        LW_SAFE_FREE_MEMORY(ppszAccountRightNames[i]);
    }
    LW_SAFE_FREE_MEMORY(ppwszAccountRightNames);
    LW_SAFE_FREE_MEMORY(ppszAccountRightNames);

    if (err == ERROR_SUCCESS &&
        ntStatus != STATUS_SUCCESS)
    {
        err = LwNtStatusToWin32Error(ntStatus);
    }

    return err;
}