BOOL
APIENTRY
EngQuerySystemAttribute(
   _In_ ENG_SYSTEM_ATTRIBUTE CapNum,
   _Out_ PDWORD pCapability)
{
    SYSTEM_BASIC_INFORMATION sbi;
    SYSTEM_PROCESSOR_INFORMATION spi;
    NTSTATUS status;

    switch (CapNum)
    {
        case EngNumberOfProcessors:
            status = NtQuerySystemInformation(SystemBasicInformation,
                                              &sbi,
                                              sizeof(SYSTEM_BASIC_INFORMATION),
                                              NULL);
            if (!NT_SUCCESS(status))
            {
                DPRINT1("Failed to query basic information: 0x%lx\n", status);
                return FALSE;
            }

            *pCapability = sbi.NumberOfProcessors;
            return TRUE;

        case EngProcessorFeature:
            status = NtQuerySystemInformation(SystemProcessorInformation,
                                              &spi,
                                              sizeof(SYSTEM_PROCESSOR_INFORMATION),
                                              NULL);
            if (!NT_SUCCESS(status))
            {
                DPRINT1("Failed to query processor information: 0x%lx\n", status);
                return FALSE;
            }
            *pCapability = spi.ProcessorFeatureBits;
            return TRUE;

        default:
            break;
    }

    return FALSE;
}