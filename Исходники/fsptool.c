static NTSTATUS perm_path(PWSTR Path)
{
    PSECURITY_DESCRIPTOR SecurityDescriptor = 0;
    int ErrorCode;

    ErrorCode = GetNamedSecurityInfoW(Path, SE_FILE_OBJECT,
        OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
        0, 0, 0, 0, &SecurityDescriptor);
    if (0 != ErrorCode)
        return FspNtStatusFromWin32(ErrorCode);

    perm_print_sd(SecurityDescriptor);

    LocalFree(SecurityDescriptor);

    return STATUS_SUCCESS;
}