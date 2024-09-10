/* Function 15 */
NTSTATUS ElfrRegisterEventSourceA(
    EVENTLOG_HANDLE_A UNCServerName,
    PRPC_STRING ModuleName,
    PRPC_STRING RegModuleName,
    DWORD MajorVersion,
    DWORD MinorVersion,
    IELF_HANDLE *LogHandle)
{
    UNICODE_STRING ModuleNameW    = { 0, 0, NULL };

    if (ModuleName &&
        !RtlAnsiStringToUnicodeString(&ModuleNameW, (PANSI_STRING)ModuleName, TRUE))
    {
        return STATUS_NO_MEMORY;
    }

    /* RegModuleName must be an empty string */
    if (RegModuleName->Length > 0)
    {
        RtlFreeUnicodeString(&ModuleNameW);
        return STATUS_INVALID_PARAMETER;
    }

    if ((MajorVersion != 1) || (MinorVersion != 1))
    {
        RtlFreeUnicodeString(&ModuleNameW);
        return STATUS_INVALID_PARAMETER;
    }

    /* FIXME: Must verify that caller has write access */

    *LogHandle = ElfCreateEventLogHandle(ModuleNameW.Buffer,
                                         TRUE);

    RtlFreeUnicodeString(&ModuleNameW);

    return STATUS_SUCCESS;
}