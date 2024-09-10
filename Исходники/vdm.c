BOOL
WINAPI
BaseGetVdmConfigInfo(IN LPCWSTR Reserved,
                     IN ULONG DosSeqId,
                     IN ULONG BinaryType,
                     IN PUNICODE_STRING CmdLineString,
                     OUT PULONG VdmSize)
{
    WCHAR Buffer[MAX_PATH];
    WCHAR CommandLine[MAX_PATH * 2];
    ULONG Length;

    /* Clear the buffer in case we fail */
    CmdLineString->Buffer = 0;

    /* Always return the same size */
    *VdmSize = 0x1000000;

    /* Get the system directory */
    Length = GetSystemDirectoryW(Buffer, MAX_PATH);
    if (!(Length) || (Length >= MAX_PATH))
    {
        /* Eliminate no path or path too big */
        SetLastError(ERROR_INVALID_NAME);
        return FALSE;
    }

    /* Check if this is VDM with a DOS Sequence ID */
    if (DosSeqId)
    {
        /* Build the VDM string for it */
        _snwprintf(CommandLine,
                   sizeof(CommandLine),
                   L"\"%s\\ntvdm.exe\" -i%lx %s%c",
                   Buffer,
                   DosSeqId,
                   (BinaryType == 0x10) ? L" " : L"-w",
                   (BinaryType == 0x40) ? 's' : ' ');
    }
    else
    {
        /* Non-DOS, build the string for it without the task ID */
        _snwprintf(CommandLine,
                   sizeof(CommandLine),
                   L"\"%s\\ntvdm.exe\"  %s%c",
                   Buffer,
                   (BinaryType == 0x10) ? L" " : L"-w",
                   (BinaryType == 0x40) ? 's' : ' ');
    }

    /* Create the actual string */
    return RtlCreateUnicodeString(CmdLineString, CommandLine);
}