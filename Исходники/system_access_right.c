static
DWORD
ProcessGetAccountSystemAccessRights(
    IN PRPC_PARAMETERS pRpcParams,
    IN PSTR pszAccountName
    )
{
    DWORD err = ERROR_SUCCESS;
    NTSTATUS ntStatus = STATUS_SUCCESS;
    LSA_BINDING hLsa = NULL;
    LW_PIO_CREDS pCreds = NULL;
    PSID pAccountSid = NULL;
    WCHAR wszSysName[] = {'\\', '\\', '\0'};
    DWORD policyAccessMask = LSA_ACCESS_LOOKUP_NAMES_SIDS |
                             LSA_ACCESS_CREATE_PRIVILEGE |
                             LSA_ACCESS_CREATE_SPECIAL_ACCOUNTS;
    POLICY_HANDLE hPolicy = NULL;
    DWORD accountAccessMask = LSA_ACCOUNT_VIEW;
    LSAR_ACCOUNT_HANDLE hAccount = NULL;
    DWORD systemAccess = 0;

    err = CreateRpcCredentials(pRpcParams,
                               &pCreds);
    BAIL_ON_LSA_ERROR(err);

    err = CreateLsaRpcBinding(pRpcParams,
                              pCreds,
                              &hLsa);
    BAIL_ON_LSA_ERROR(err);

    err = ResolveAccountNameToSid(
                          hLsa,
                          pszAccountName,
                          &pAccountSid);
    BAIL_ON_LSA_ERROR(err);

    ntStatus = LsaOpenPolicy2(hLsa,
                              wszSysName,
                              NULL,
                              policyAccessMask,
                              &hPolicy);
    BAIL_ON_NT_STATUS(ntStatus);

    ntStatus = LsaOpenAccount(hLsa,
                              hPolicy,
                              pAccountSid,
                              accountAccessMask,
                              &hAccount);
    BAIL_ON_NT_STATUS(ntStatus);

    ntStatus = LsaGetSystemAccessAccount(
                              hLsa,
                              hAccount,
                              &systemAccess);
    BAIL_ON_NT_STATUS(ntStatus);

    fprintf(stdout,
            "Account: %s:\n"
            "=================================================================="
            "==============\n", pszAccountName);
    fprintf(stdout, "System Access Rights 0x%08x\n", systemAccess);

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

    if (hAccount)
    {
        LsaClose(hLsa, hAccount);
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

    RTL_FREE(&pAccountSid);

    if (err == ERROR_SUCCESS &&
        ntStatus != STATUS_SUCCESS)
    {
        err = LwNtStatusToWin32Error(ntStatus);
    }

    return err;
}