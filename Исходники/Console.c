BOOL
WINAPI
WriteConsoleOutputCharacterW(
    HANDLE hConsoleOutput,
    IN LPCWSTR lpCharacter,
    IN DWORD nLength,
    IN COORD dwWriteCoord,
    OUT LPDWORD lpNumberOfCharsWritten)
{
    IO_STATUS_BLOCK IoStatusBlock;
    PCHAR Buffer;
    COORD *pCoord;
    PCHAR pText;
    NTSTATUS Status;
//    ULONG i;

    UNICODE_STRING UnicodeString;
    OEM_STRING OemString;
    ULONG OemLength;

    UnicodeString.Length = nLength * sizeof(WCHAR);
    UnicodeString.MaximumLength = nLength * sizeof(WCHAR);
    UnicodeString.Buffer = (LPWSTR)lpCharacter;

    OemLength = RtlUnicodeStringToOemSize(&UnicodeString);


    Buffer = (CHAR*)RtlAllocateHeap(ProcessHeap,
                                    0,
                                    OemLength + sizeof(COORD));
//                                    nLength + sizeof(COORD));
    if (Buffer== NULL)
        return FALSE;

    pCoord = (COORD *)Buffer;
    pText = (PCHAR)(pCoord + 1);

    *pCoord = dwWriteCoord;

    OemString.Length = 0;
    OemString.MaximumLength = OemLength;
    OemString.Buffer = pText;

    Status = RtlUnicodeStringToOemString(&OemString,
                                         &UnicodeString,
                                         FALSE);
    if (!NT_SUCCESS(Status))
        goto done;

    /* FIXME: use real unicode->oem conversion */
//    for (i = 0; i < nLength; i++)
//        pText[i] = (CHAR)lpCharacter[i];

    Status = NtDeviceIoControlFile(hConsoleOutput,
                                   NULL,
                                   NULL,
                                   NULL,
                                   &IoStatusBlock,
                                   IOCTL_CONSOLE_WRITE_OUTPUT_CHARACTER,
                                   NULL,
                                   0,
                                   Buffer,
                                   nLength + sizeof(COORD));

done:
    RtlFreeHeap(ProcessHeap, 0, Buffer);
    if (!NT_SUCCESS(Status))
        return FALSE;

    *lpNumberOfCharsWritten = IoStatusBlock.Information;
    return TRUE;
}