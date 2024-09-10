VOID
NTAPI
SmpMakeSystemManagedPagingFileDescriptor(IN PSMP_PAGEFILE_DESCRIPTOR Descriptor)
{
    NTSTATUS Status;
    LONGLONG MinimumSize, MaximumSize, Ram;
    SYSTEM_BASIC_INFORMATION BasicInfo;

    /* Query the page size of the system, and the amount of RAM */
    Status = NtQuerySystemInformation(SystemBasicInformation,
                                      &BasicInfo,
                                      sizeof(BasicInfo),
                                      NULL);
    if (!NT_SUCCESS(Status))
    {
        /* If we failed, use defaults since we have no idea otherwise */
        DPRINT1("SMSS:PFILE: NtQuerySystemInformation failed with %x \n", Status);
        SmpMakeDefaultPagingFileDescriptor(Descriptor);
        return;
    }

    /* Chekc how much RAM we have and set three times this amount as maximum */
    Ram = BasicInfo.NumberOfPhysicalPages * BasicInfo.PageSize;
    MaximumSize = 3 * Ram;

    /* If we have more than 1GB, use that as minimum, otherwise, use 1.5X RAM */
    MinimumSize = (Ram >= 1024 * MEGABYTE) ? Ram : MaximumSize / 2;

    /* Write the new sizes in the descriptor and mark it as system managed */
    Descriptor->MinSize.QuadPart = MinimumSize;
    Descriptor->MaxSize.QuadPart = MaximumSize;
    Descriptor->Flags |= SMP_PAGEFILE_SYSTEM_MANAGED;
}