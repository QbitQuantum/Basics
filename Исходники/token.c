/*
 * @implemented
 */
BOOL WINAPI
CheckTokenMembership(IN HANDLE ExistingTokenHandle,
                     IN PSID SidToCheck,
                     OUT PBOOL IsMember)
{
    PISECURITY_DESCRIPTOR SecurityDescriptor = NULL;
    ACCESS_MASK GrantedAccess;
    struct
    {
        PRIVILEGE_SET PrivilegeSet;
        LUID_AND_ATTRIBUTES Privileges[4];
    } PrivBuffer;
    ULONG PrivBufferSize = sizeof(PrivBuffer);
    GENERIC_MAPPING GenericMapping =
    {
        STANDARD_RIGHTS_READ,
        STANDARD_RIGHTS_WRITE,
        STANDARD_RIGHTS_EXECUTE,
        STANDARD_RIGHTS_ALL
    };
    PACL Dacl;
    ULONG SidLen;
    HANDLE hToken = NULL;
    NTSTATUS Status, AccessStatus;

    /* doesn't return gracefully if IsMember is NULL! */
    *IsMember = FALSE;

    SidLen = RtlLengthSid(SidToCheck);

    if (ExistingTokenHandle == NULL)
    {
        Status = NtOpenThreadToken(NtCurrentThread(),
                                   TOKEN_QUERY,
                                   FALSE,
                                   &hToken);

        if (Status == STATUS_NO_TOKEN)
        {
            /* we're not impersonating, open the primary token */
            Status = NtOpenProcessToken(NtCurrentProcess(),
                                        TOKEN_QUERY | TOKEN_DUPLICATE,
                                        &hToken);
            if (NT_SUCCESS(Status))
            {
                HANDLE hNewToken = FALSE;
                BOOL DupRet;

                /* duplicate the primary token to create an impersonation token */
                DupRet = DuplicateTokenEx(hToken,
                                          TOKEN_QUERY | TOKEN_IMPERSONATE,
                                          NULL,
                                          SecurityImpersonation,
                                          TokenImpersonation,
                                          &hNewToken);

                NtClose(hToken);

                if (!DupRet)
                {
                    WARN("Failed to duplicate the primary token!\n");
                    return FALSE;
                }

                hToken = hNewToken;
            }
        }

        if (!NT_SUCCESS(Status))
        {
            goto Cleanup;
        }
    }
    else
    {
        hToken = ExistingTokenHandle;
    }

    /* create a security descriptor */
    SecurityDescriptor = RtlAllocateHeap(RtlGetProcessHeap(),
                                         0,
                                         sizeof(SECURITY_DESCRIPTOR) +
                                             sizeof(ACL) + SidLen +
                                             sizeof(ACCESS_ALLOWED_ACE));
    if (SecurityDescriptor == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto Cleanup;
    }

    Status = RtlCreateSecurityDescriptor(SecurityDescriptor,
                                         SECURITY_DESCRIPTOR_REVISION);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* set the owner and group */
    Status = RtlSetOwnerSecurityDescriptor(SecurityDescriptor,
                                           SidToCheck,
                                           FALSE);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    Status = RtlSetGroupSecurityDescriptor(SecurityDescriptor,
                                           SidToCheck,
                                           FALSE);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* create the DACL */
    Dacl = (PACL)(SecurityDescriptor + 1);
    Status = RtlCreateAcl(Dacl,
                          sizeof(ACL) + SidLen + sizeof(ACCESS_ALLOWED_ACE),
                          ACL_REVISION);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    Status = RtlAddAccessAllowedAce(Dacl,
                                    ACL_REVISION,
                                    0x1,
                                    SidToCheck);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* assign the DACL to the security descriptor */
    Status = RtlSetDaclSecurityDescriptor(SecurityDescriptor,
                                          TRUE,
                                          Dacl,
                                          FALSE);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* it's time to perform the access check. Just use _some_ desired access right
       (same as for the ACE) and see if we're getting it granted. This indicates
       our SID is a member of the token. We however can't use a generic access
       right as those aren't mapped and return an error (STATUS_GENERIC_NOT_MAPPED). */
    Status = NtAccessCheck(SecurityDescriptor,
                           hToken,
                           0x1,
                           &GenericMapping,
                           &PrivBuffer.PrivilegeSet,
                           &PrivBufferSize,
                           &GrantedAccess,
                           &AccessStatus);
    if (NT_SUCCESS(Status) && NT_SUCCESS(AccessStatus) && (GrantedAccess == 0x1))
    {
        *IsMember = TRUE;
    }

Cleanup:
    if (hToken != NULL && hToken != ExistingTokenHandle)
    {
        NtClose(hToken);
    }

    if (SecurityDescriptor != NULL)
    {
        RtlFreeHeap(RtlGetProcessHeap(),
                    0,
                    SecurityDescriptor);
    }

    if (!NT_SUCCESS(Status))
    {
        SetLastError(RtlNtStatusToDosError(Status));
        return FALSE;
    }

    return TRUE;
}