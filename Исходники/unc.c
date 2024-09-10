NTSTATUS
FsRtlpRegisterProviderWithMUP(IN HANDLE MupHandle,
                              IN PCUNICODE_STRING RedirectorDeviceName,
                              IN BOOLEAN MailslotsSupported)
{
    NTSTATUS Status;
    ULONG BufferSize;
    IO_STATUS_BLOCK IoStatusBlock;
    PMUP_PROVIDER_REGISTRATION_INFO RegistrationInfo;

    PAGED_CODE();

    DPRINT1("FsRtlpRegisterProviderWithMUP(%p, %wZ, %u)\n", (PVOID)MupHandle, RedirectorDeviceName, MailslotsSupported);

    /* We have to be able to store the name and the registration information */
    BufferSize = RedirectorDeviceName->Length + sizeof(MUP_PROVIDER_REGISTRATION_INFO);
    RegistrationInfo = ExAllocatePoolWithTag(NonPagedPool, BufferSize, TAG_UNC);
    if (RegistrationInfo == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Set the information about the provider (including its name) */
    RegistrationInfo->RedirectorDeviceNameOffset = sizeof(MUP_PROVIDER_REGISTRATION_INFO);
    RegistrationInfo->RedirectorDeviceNameLength = RedirectorDeviceName->Length;
    RegistrationInfo->MailslotsSupported = MailslotsSupported;
    RtlCopyMemory((PWSTR)((ULONG_PTR)RegistrationInfo + RegistrationInfo->RedirectorDeviceNameOffset),
                  RedirectorDeviceName->Buffer, RedirectorDeviceName->Length);

    /* Call MUP with the registration FSCTL */
    Status = NtFsControlFile(MupHandle, NULL, NULL, NULL,
                             &IoStatusBlock, FSCTL_MUP_REGISTER_PROVIDER,
                             RegistrationInfo, BufferSize, NULL, 0);
    if (Status == STATUS_PENDING)
    {
        Status = NtWaitForSingleObject(MupHandle, TRUE, NULL);
    }

    if (NT_SUCCESS(Status))
    {
        Status = IoStatusBlock.Status;
    }

    /* And we're done! */
    ASSERT(NT_SUCCESS(Status));
    ExFreePoolWithTag(RegistrationInfo, TAG_UNC);

    return Status;
}