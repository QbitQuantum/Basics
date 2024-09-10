/*
 * @unimplemented
 */
NTSTATUS
NTAPI
LsaApLogonUser(IN PLSA_CLIENT_REQUEST ClientRequest,
               IN SECURITY_LOGON_TYPE LogonType,
               IN PVOID AuthenticationInformation,
               IN PVOID ClientAuthenticationBase,
               IN ULONG AuthenticationInformationLength,
               OUT PVOID *ProfileBuffer,
               OUT PULONG ProfileBufferLength,
               OUT PLUID LogonId,
               OUT PNTSTATUS SubStatus,
               OUT PLSA_TOKEN_INFORMATION_TYPE TokenInformationType,
               OUT PVOID *TokenInformation,
               OUT PLSA_UNICODE_STRING *AccountName,
               OUT PLSA_UNICODE_STRING *AuthenticatingAuthority)
{
    PMSV1_0_INTERACTIVE_LOGON LogonInfo;

    SAMPR_HANDLE ServerHandle = NULL;
    SAMPR_HANDLE DomainHandle = NULL;
    SAMPR_HANDLE UserHandle = NULL;
    PRPC_SID AccountDomainSid = NULL;
    RPC_UNICODE_STRING Names[1];
    SAMPR_ULONG_ARRAY RelativeIds = {0, NULL};
    SAMPR_ULONG_ARRAY Use = {0, NULL};
    PSAMPR_USER_INFO_BUFFER UserInfo = NULL;
    UNICODE_STRING LogonServer;
    BOOLEAN SessionCreated = FALSE;
    LARGE_INTEGER LogonTime;
//    LARGE_INTEGER AccountExpires;
    LARGE_INTEGER PasswordMustChange;
    LARGE_INTEGER PasswordLastSet;
    BOOL SpecialAccount = FALSE;
    NTSTATUS Status;

    TRACE("LsaApLogonUser()\n");

    TRACE("LogonType: %lu\n", LogonType);
    TRACE("AuthenticationInformation: %p\n", AuthenticationInformation);
    TRACE("AuthenticationInformationLength: %lu\n", AuthenticationInformationLength);

    *ProfileBuffer = NULL;
    *ProfileBufferLength = 0;
    *SubStatus = STATUS_SUCCESS;

    if (LogonType == Interactive ||
        LogonType == Batch ||
        LogonType == Service)
    {
        ULONG_PTR PtrOffset;

        LogonInfo = (PMSV1_0_INTERACTIVE_LOGON)AuthenticationInformation;

        /* Fix-up pointers in the authentication info */
        PtrOffset = (ULONG_PTR)AuthenticationInformation - (ULONG_PTR)ClientAuthenticationBase;

        LogonInfo->LogonDomainName.Buffer = FIXUP_POINTER(LogonInfo->LogonDomainName.Buffer, PtrOffset);
        LogonInfo->UserName.Buffer = FIXUP_POINTER(LogonInfo->UserName.Buffer, PtrOffset);
        LogonInfo->Password.Buffer = FIXUP_POINTER(LogonInfo->Password.Buffer, PtrOffset);

        TRACE("Domain: %S\n", LogonInfo->LogonDomainName.Buffer);
        TRACE("User: %S\n", LogonInfo->UserName.Buffer);
        TRACE("Password: %S\n", LogonInfo->Password.Buffer);

        RtlInitUnicodeString(&LogonServer, L"Testserver");
    }
    else
    {
        FIXME("LogonType %lu is not supported yet!\n", LogonType);
        return STATUS_NOT_IMPLEMENTED;
    }

    /* Get the logon time */
    NtQuerySystemTime(&LogonTime);

    /* Check for special accounts */
    if (_wcsicmp(LogonInfo->LogonDomainName.Buffer, L"NT AUTHORITY") == 0)
    {
        SpecialAccount = TRUE;

        /* Get the authority domain SID */
        Status = GetNtAuthorityDomainSid(&AccountDomainSid);
        if (!NT_SUCCESS(Status))
        {
            ERR("GetNtAuthorityDomainSid() failed (Status 0x%08lx)\n", Status);
            return Status;
        }

        if (_wcsicmp(LogonInfo->UserName.Buffer, L"LocalService") == 0)
        {
            TRACE("SpecialAccount: LocalService\n");

            if (LogonType != Service)
                return STATUS_LOGON_FAILURE;

            UserInfo = RtlAllocateHeap(RtlGetProcessHeap(),
                                       HEAP_ZERO_MEMORY,
                                       sizeof(SAMPR_USER_ALL_INFORMATION));
            if (UserInfo == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto done;
            }

            UserInfo->All.UserId = SECURITY_LOCAL_SERVICE_RID;
            UserInfo->All.PrimaryGroupId = SECURITY_LOCAL_SERVICE_RID;
        }
        else if (_wcsicmp(LogonInfo->UserName.Buffer, L"NetworkService") == 0)
        {
            TRACE("SpecialAccount: NetworkService\n");

            if (LogonType != Service)
                return STATUS_LOGON_FAILURE;

            UserInfo = RtlAllocateHeap(RtlGetProcessHeap(),
                                       HEAP_ZERO_MEMORY,
                                       sizeof(SAMPR_USER_ALL_INFORMATION));
            if (UserInfo == NULL)
            {
                Status = STATUS_INSUFFICIENT_RESOURCES;
                goto done;
            }

            UserInfo->All.UserId = SECURITY_NETWORK_SERVICE_RID;
            UserInfo->All.PrimaryGroupId = SECURITY_NETWORK_SERVICE_RID;
        }
        else
        {
            Status = STATUS_NO_SUCH_USER;
            goto done;
        }
    }
    else
    {
        TRACE("NormalAccount\n");

        /* Get the account domain SID */
        Status = GetAccountDomainSid(&AccountDomainSid);
        if (!NT_SUCCESS(Status))
        {
            ERR("GetAccountDomainSid() failed (Status 0x%08lx)\n", Status);
            return Status;
        }

        /* Connect to the SAM server */
        Status = SamIConnect(NULL,
                             &ServerHandle,
                             SAM_SERVER_CONNECT | SAM_SERVER_LOOKUP_DOMAIN,
                             TRUE);
        if (!NT_SUCCESS(Status))
        {
            TRACE("SamIConnect() failed (Status 0x%08lx)\n", Status);
            goto done;
        }

        /* Open the account domain */
        Status = SamrOpenDomain(ServerHandle,
                                DOMAIN_LOOKUP,
                                AccountDomainSid,
                                &DomainHandle);
        if (!NT_SUCCESS(Status))
        {
            ERR("SamrOpenDomain failed (Status %08lx)\n", Status);
            goto done;
        }

        Names[0].Length = LogonInfo->UserName.Length;
        Names[0].MaximumLength = LogonInfo->UserName.MaximumLength;
        Names[0].Buffer = LogonInfo->UserName.Buffer;

        /* Try to get the RID for the user name */
        Status = SamrLookupNamesInDomain(DomainHandle,
                                         1,
                                         Names,
                                         &RelativeIds,
                                         &Use);
        if (!NT_SUCCESS(Status))
        {
            ERR("SamrLookupNamesInDomain failed (Status %08lx)\n", Status);
            Status = STATUS_NO_SUCH_USER;
            goto done;
        }

        /* Fail, if it is not a user account */
        if (Use.Element[0] != SidTypeUser)
        {
            ERR("Account is not a user account!\n");
            Status = STATUS_NO_SUCH_USER;
            goto done;
        }

        /* Open the user object */
        Status = SamrOpenUser(DomainHandle,
                              USER_READ_GENERAL | USER_READ_LOGON |
                              USER_READ_ACCOUNT | USER_READ_PREFERENCES, /* FIXME */
                              RelativeIds.Element[0],
                              &UserHandle);
        if (!NT_SUCCESS(Status))
        {
            ERR("SamrOpenUser failed (Status %08lx)\n", Status);
            goto done;
        }

        Status = SamrQueryInformationUser(UserHandle,
                                          UserAllInformation,
                                          &UserInfo);
        if (!NT_SUCCESS(Status))
        {
            ERR("SamrQueryInformationUser failed (Status %08lx)\n", Status);
            goto done;
        }

        TRACE("UserName: %S\n", UserInfo->All.UserName.Buffer);

        /* Check the password */
        if ((UserInfo->All.UserAccountControl & USER_PASSWORD_NOT_REQUIRED) == 0)
        {
            Status = MsvpCheckPassword(&(LogonInfo->Password),
                                       UserInfo);
            if (!NT_SUCCESS(Status))
            {
                ERR("MsvpCheckPassword failed (Status %08lx)\n", Status);
                goto done;
            }
        }

        /* Check account restrictions for non-administrator accounts */
        if (RelativeIds.Element[0] != DOMAIN_USER_RID_ADMIN)
        {
            /* Check if the account has been disabled */
            if (UserInfo->All.UserAccountControl & USER_ACCOUNT_DISABLED)
            {
                ERR("Account disabled!\n");
                *SubStatus = STATUS_ACCOUNT_DISABLED;
                Status = STATUS_ACCOUNT_RESTRICTION;
                goto done;
            }

            /* Check if the account has been locked */
            if (UserInfo->All.UserAccountControl & USER_ACCOUNT_AUTO_LOCKED)
            {
                ERR("Account locked!\n");
                *SubStatus = STATUS_ACCOUNT_LOCKED_OUT;
                Status = STATUS_ACCOUNT_RESTRICTION;
                goto done;
            }

#if 0
            /* Check if the account expired */
            AccountExpires.LowPart = UserInfo->All.AccountExpires.LowPart;
            AccountExpires.HighPart = UserInfo->All.AccountExpires.HighPart;

            if (AccountExpires.QuadPart != 0 &&
                LogonTime.QuadPart >= AccountExpires.QuadPart)
            {
                ERR("Account expired!\n");
                *SubStatus = STATUS_ACCOUNT_EXPIRED;
                Status = STATUS_ACCOUNT_RESTRICTION;
                goto done;
            }
#endif

            /* Check if the password expired */
            PasswordMustChange.LowPart = UserInfo->All.PasswordMustChange.LowPart;
            PasswordMustChange.HighPart = UserInfo->All.PasswordMustChange.HighPart;
            PasswordLastSet.LowPart = UserInfo->All.PasswordLastSet.LowPart;
            PasswordLastSet.HighPart = UserInfo->All.PasswordLastSet.HighPart;

            if (LogonTime.QuadPart >= PasswordMustChange.QuadPart)
            {
                ERR("Password expired!\n");
                if (PasswordLastSet.QuadPart == 0)
                    *SubStatus = STATUS_PASSWORD_MUST_CHANGE;
                else
                    *SubStatus = STATUS_PASSWORD_EXPIRED;

                Status = STATUS_ACCOUNT_RESTRICTION;
                goto done;
            }

            /* FIXME: more checks */
            // STATUS_INVALID_LOGON_HOURS;
            // STATUS_INVALID_WORKSTATION;
        }
    }

    /* Return logon information */

    /* Create and return a new logon id */
    Status = NtAllocateLocallyUniqueId(LogonId);
    if (!NT_SUCCESS(Status))
    {
        TRACE("NtAllocateLocallyUniqueId failed (Status %08lx)\n", Status);
        goto done;
    }

    /* Create the logon session */
    Status = DispatchTable.CreateLogonSession(LogonId);
    if (!NT_SUCCESS(Status))
    {
        TRACE("CreateLogonSession failed (Status %08lx)\n", Status);
        goto done;
    }

    SessionCreated = TRUE;

    /* Build and fill the interactive profile buffer */
    Status = BuildInteractiveProfileBuffer(ClientRequest,
                                           UserInfo,
                                           &LogonServer,
                                           (PMSV1_0_INTERACTIVE_PROFILE*)ProfileBuffer,
                                           ProfileBufferLength);
    if (!NT_SUCCESS(Status))
    {
        TRACE("BuildInteractiveProfileBuffer failed (Status %08lx)\n", Status);
        goto done;
    }

    /* Return the token information type */
    *TokenInformationType = LsaTokenInformationV1;

    /* Build and fill the token information buffer */
    Status = BuildTokenInformationBuffer((PLSA_TOKEN_INFORMATION_V1*)TokenInformation,
                                         AccountDomainSid,
                                         UserInfo,
                                         SpecialAccount);
    if (!NT_SUCCESS(Status))
    {
        TRACE("BuildTokenInformationBuffer failed (Status %08lx)\n", Status);
        goto done;
    }

done:
    /* Return the account name */
    *AccountName = DispatchTable.AllocateLsaHeap(sizeof(UNICODE_STRING));
    if (*AccountName != NULL)
    {
        (*AccountName)->Buffer = DispatchTable.AllocateLsaHeap(LogonInfo->UserName.Length +
                                                               sizeof(UNICODE_NULL));
        if ((*AccountName)->Buffer != NULL)
        {
            (*AccountName)->MaximumLength = LogonInfo->UserName.Length +
                                            sizeof(UNICODE_NULL);
            RtlCopyUnicodeString(*AccountName, &LogonInfo->UserName);
        }
    }

    if (!NT_SUCCESS(Status))
    {
        if (SessionCreated != FALSE)
            DispatchTable.DeleteLogonSession(LogonId);

        if (*ProfileBuffer != NULL)
        {
            DispatchTable.FreeClientBuffer(ClientRequest,
                                           *ProfileBuffer);
            *ProfileBuffer = NULL;
        }
    }

    if (UserHandle != NULL)
        SamrCloseHandle(&UserHandle);

    SamIFree_SAMPR_USER_INFO_BUFFER(UserInfo,
                                    UserAllInformation);
    SamIFree_SAMPR_ULONG_ARRAY(&RelativeIds);
    SamIFree_SAMPR_ULONG_ARRAY(&Use);

    if (DomainHandle != NULL)
        SamrCloseHandle(&DomainHandle);

    if (ServerHandle != NULL)
        SamrCloseHandle(&ServerHandle);

    if (AccountDomainSid != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, AccountDomainSid);

    if (Status == STATUS_NO_SUCH_USER ||
        Status == STATUS_WRONG_PASSWORD)
    {
        *SubStatus = Status;
        Status = STATUS_LOGON_FAILURE;
    }

    TRACE("LsaApLogonUser done (Status 0x%08lx  SubStatus 0x%08lx)\n", Status, *SubStatus);

    return Status;
}