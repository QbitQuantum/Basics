BOOL
GrantUserRight(
    PSID    psidAccountSid,
    LPWSTR  pszUserRight,
    BOOL    bEnable
    )
{
    LSA_HANDLE  PolicyHandle = NULL;
    NTSTATUS    Status;

    //
    // Open the policy on the local host.
    //
    Status = OpenPolicy(
                _T(""),
                POLICY_CREATE_ACCOUNT | POLICY_LOOKUP_NAMES,
                &PolicyHandle
                );


    if(Status != STATUS_SUCCESS) {
        return FALSE;
    }


    //
    // Grant the requested user right represented by psidAccountSid.
    //
    Status = SetPrivilegeOnAccount(
                PolicyHandle,                   // policy handle
                psidAccountSid,                 // SID to grant privilege
                pszUserRight,                   // Unicode privilege
                bEnable                         // enable the privilege
                );

    if(Status != STATUS_SUCCESS)
    {
        LsaClose(PolicyHandle);
        return FALSE;
    }

    //
    // Cleanup any handles and memory allocated during the custom action
    //
    LsaClose(PolicyHandle);
    return TRUE;
}