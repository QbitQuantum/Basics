NTSTATUS PhSvcApiPortInitialization(
    _In_ PUNICODE_STRING PortName
    )
{
    static SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    NTSTATUS status;
    OBJECT_ATTRIBUTES objectAttributes;
    PSECURITY_DESCRIPTOR securityDescriptor;
    ULONG sdAllocationLength;
    UCHAR administratorsSidBuffer[FIELD_OFFSET(SID, SubAuthority) + sizeof(ULONG) * 2];
    PSID administratorsSid;
    PACL dacl;
    ULONG i;
    HANDLE threadHandle;

    // Create the API port.

    administratorsSid = (PSID)administratorsSidBuffer;
    RtlInitializeSid(administratorsSid, &ntAuthority, 2);
    *RtlSubAuthoritySid(administratorsSid, 0) = SECURITY_BUILTIN_DOMAIN_RID;
    *RtlSubAuthoritySid(administratorsSid, 1) = DOMAIN_ALIAS_RID_ADMINS;

    sdAllocationLength = SECURITY_DESCRIPTOR_MIN_LENGTH +
        (ULONG)sizeof(ACL) +
        (ULONG)sizeof(ACCESS_ALLOWED_ACE) +
        RtlLengthSid(administratorsSid) +
        (ULONG)sizeof(ACCESS_ALLOWED_ACE) +
        RtlLengthSid(&PhSeEveryoneSid);

    securityDescriptor = PhAllocate(sdAllocationLength);
    dacl = (PACL)((PCHAR)securityDescriptor + SECURITY_DESCRIPTOR_MIN_LENGTH);

    RtlCreateSecurityDescriptor(securityDescriptor, SECURITY_DESCRIPTOR_REVISION);
    RtlCreateAcl(dacl, sdAllocationLength - SECURITY_DESCRIPTOR_MIN_LENGTH, ACL_REVISION);
    RtlAddAccessAllowedAce(dacl, ACL_REVISION, PORT_ALL_ACCESS, administratorsSid);
    RtlAddAccessAllowedAce(dacl, ACL_REVISION, PORT_CONNECT, &PhSeEveryoneSid);
    RtlSetDaclSecurityDescriptor(securityDescriptor, TRUE, dacl, FALSE);

    InitializeObjectAttributes(
        &objectAttributes,
        PortName,
        OBJ_CASE_INSENSITIVE,
        NULL,
        securityDescriptor
        );

    status = NtCreatePort(
        &PhSvcApiPortHandle,
        &objectAttributes,
        sizeof(PHSVC_API_CONNECTINFO),
        PhIsExecutingInWow64() ? sizeof(PHSVC_API_MSG64) : sizeof(PHSVC_API_MSG),
        0
        );
    PhFree(securityDescriptor);

    if (!NT_SUCCESS(status))
        return status;

    // Start the API threads.

    PhSvcApiThreadContextTlsIndex = TlsAlloc();

    for (i = 0; i < 2; i++)
    {
        threadHandle = PhCreateThread(0, PhSvcApiRequestThreadStart, NULL);

        if (threadHandle)
            NtClose(threadHandle);
    }

    return status;
}