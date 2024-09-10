/*
 * @implemented
 */
NTSTATUS
NTAPI
CheckForNoDriveLetterEntry(IN PWSTR ValueName,
                           IN ULONG ValueType,
                           IN PVOID ValueData,
                           IN ULONG ValueLength,
                           IN PVOID Context,
                           IN PVOID EntryContext)
{
    PBOOLEAN EntryPresent = EntryContext;
    PMOUNTDEV_UNIQUE_ID UniqueId = Context;

    /* Check if matches no drive letter entry */
    if (ValueName[0] != L'#' || ValueType != REG_BINARY ||
        UniqueId->UniqueIdLength != ValueLength)
    {
        return STATUS_SUCCESS;
    }

    /* Compare unique ID */
    if (RtlCompareMemory(UniqueId->UniqueId, ValueData, ValueLength) == ValueLength)
    {
        *EntryPresent = TRUE;
    }

    return STATUS_SUCCESS;
}