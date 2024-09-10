NTSTATUS
NTAPI
CmpInitializeMachineDependentConfiguration(IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    UNICODE_STRING KeyName, ValueName, Data, SectionName;
    OBJECT_ATTRIBUTES ObjectAttributes;
    ULONG HavePae, Length, TotalLength = 0, i, Disposition;
    SIZE_T ViewSize;
    NTSTATUS Status;
    HANDLE KeyHandle, BiosHandle, SystemHandle, FpuHandle, SectionHandle;
    CONFIGURATION_COMPONENT_DATA ConfigData;
    CHAR Buffer[128];
    CPU_INFO CpuInfo;
    ULONG VendorId, ExtendedId;
    PKPRCB Prcb;
    USHORT IndexTable[MaximumType + 1] = {0};
    ANSI_STRING TempString;
    PCHAR PartialString = NULL, BiosVersion;
    CHAR CpuString[48];
    PVOID BaseAddress = NULL;
    LARGE_INTEGER ViewBase = {{0, 0}};
    ULONG_PTR VideoRomBase;
    PCHAR CurrentVersion;
    extern UNICODE_STRING KeRosProcessorName, KeRosBiosDate, KeRosBiosVersion;
    extern UNICODE_STRING KeRosVideoBiosDate, KeRosVideoBiosVersion;

    /* Open the SMSS Memory Management key */
    RtlInitUnicodeString(&KeyName,
                         L"\\Registry\\Machine\\SYSTEM\\CurrentControlSet\\"
                         L"Control\\Session Manager\\Memory Management");
    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    Status = NtOpenKey(&KeyHandle, KEY_READ | KEY_WRITE, &ObjectAttributes);
    if (NT_SUCCESS(Status))
    {
        /* Detect if PAE is enabled */
        HavePae = SharedUserData->ProcessorFeatures[PF_PAE_ENABLED];

        /* Set the value */
        RtlInitUnicodeString(&ValueName, L"PhysicalAddressExtension");
        NtSetValueKey(KeyHandle,
                      &ValueName,
                      0,
                      REG_DWORD,
                      &HavePae,
                      sizeof(HavePae));

        /* Close the key */
        NtClose(KeyHandle);
    }

    /* Open the hardware description key */
    RtlInitUnicodeString(&KeyName,
                         L"\\Registry\\Machine\\Hardware\\Description\\System");
    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    Status = NtOpenKey(&SystemHandle, KEY_READ | KEY_WRITE, &ObjectAttributes);
    if (!NT_SUCCESS(Status)) return Status;

    /* Create the BIOS Information key */
    RtlInitUnicodeString(&KeyName,
                         L"\\Registry\\Machine\\SYSTEM\\CurrentControlSet\\"
                         L"Control\\BIOSINFO");
    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    Status = NtCreateKey(&BiosHandle,
                         KEY_ALL_ACCESS,
                         &ObjectAttributes,
                         0,
                         NULL,
                         REG_OPTION_NON_VOLATILE,
                         &Disposition);
    if (ExpInTextModeSetup)
    {
        if (!NT_SUCCESS(Status))
            BiosHandle = NULL;
    }
    else if (!NT_SUCCESS(Status))
        return Status;

    /* Create the CPU Key, and check if it already existed */
    RtlInitUnicodeString(&KeyName, L"CentralProcessor");
    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_CASE_INSENSITIVE,
                               SystemHandle,
                               NULL);
    Status = NtCreateKey(&KeyHandle,
                         KEY_READ | KEY_WRITE,
                         &ObjectAttributes,
                         0,
                         NULL,
                         0,
                         &Disposition);
    NtClose(KeyHandle);

    /* The key shouldn't already exist */
    if (Disposition == REG_CREATED_NEW_KEY)
    {
        /* Allocate the configuration data for cmconfig.c */
        CmpConfigurationData = ExAllocatePoolWithTag(PagedPool,
                                                     CmpConfigurationAreaSize,
                                                     TAG_CM);
        if (!CmpConfigurationData) return STATUS_INSUFFICIENT_RESOURCES;

        /* Loop all CPUs */
        for (i = 0; i < KeNumberProcessors; i++)
        {
            /* Get the PRCB */
            Prcb = KiProcessorBlock[i];

            /* Setup the Configuration Entry for the Processor */
            RtlZeroMemory(&ConfigData, sizeof (ConfigData));
            ConfigData.ComponentEntry.Class = ProcessorClass;
            ConfigData.ComponentEntry.Type = CentralProcessor;
            ConfigData.ComponentEntry.Key = i;
            ConfigData.ComponentEntry.AffinityMask = AFFINITY_MASK(i);
            ConfigData.ComponentEntry.Identifier = Buffer;

            /* Check if the CPU doesn't support CPUID */
            if (!Prcb->CpuID)
            {
                /* Build ID1-style string for older CPUs */
                sprintf(Buffer,
                        CmpID1,
                        Prcb->CpuType,
                        (Prcb->CpuStep >> 8) + 'A',
                        Prcb->CpuStep & 0xff);
            }
            else
            {