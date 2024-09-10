NTSTATUS PhSetSeObjectSecurity(
    _In_ HANDLE Handle,
    _In_ ULONG ObjectType,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
)
{
    ULONG win32Result;
    SECURITY_INFORMATION securityInformation = 0;
    BOOLEAN present;
    BOOLEAN defaulted;
    PSID owner = NULL;
    PSID group = NULL;
    PACL dacl = NULL;
    PACL sacl = NULL;

    if (SecurityInformation & OWNER_SECURITY_INFORMATION)
    {
        if (NT_SUCCESS(RtlGetOwnerSecurityDescriptor(SecurityDescriptor, &owner, &defaulted)))
            securityInformation |= OWNER_SECURITY_INFORMATION;
    }

    if (SecurityInformation & GROUP_SECURITY_INFORMATION)
    {
        if (NT_SUCCESS(RtlGetGroupSecurityDescriptor(SecurityDescriptor, &group, &defaulted)))
            securityInformation |= GROUP_SECURITY_INFORMATION;
    }

    if (SecurityInformation & DACL_SECURITY_INFORMATION)
    {
        if (NT_SUCCESS(RtlGetDaclSecurityDescriptor(SecurityDescriptor, &present, &dacl, &defaulted)) && present)
            securityInformation |= DACL_SECURITY_INFORMATION;
    }

    if (SecurityInformation & SACL_SECURITY_INFORMATION)
    {
        if (NT_SUCCESS(RtlGetSaclSecurityDescriptor(SecurityDescriptor, &present, &sacl, &defaulted)) && present)
            securityInformation |= SACL_SECURITY_INFORMATION;
    }

    win32Result = SetSecurityInfo(
                      Handle,
                      ObjectType,
                      SecurityInformation,
                      owner,
                      group,
                      dacl,
                      sacl
                  );

    if (win32Result != ERROR_SUCCESS)
        return NTSTATUS_FROM_WIN32(win32Result);

    return STATUS_SUCCESS;
}