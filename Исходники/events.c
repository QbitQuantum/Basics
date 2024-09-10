ULONG
EnumerateChannels (
    VOID
)

/*++

Routine Description:

    This function enumerates all the EventLog channels and prints their names
    to the standard output.

Arguments:

    None.

Return Value:

    Win32 error code indicating if enumeration was successful.

--*/

{
    PWSTR Buffer;
    ULONG BufferLength;
    ULONG BufferLengthNeeded;
    EVT_HANDLE ChannelEnum;
    ULONG Status;

    //
    // Create the channel enumeration handle.
    //

    ChannelEnum = EvtOpenChannelEnum(NULL, 0);
    if (ChannelEnum == NULL) {
        return GetLastError();
    }

    Buffer = NULL;
    BufferLength = 0;
    BufferLengthNeeded = 0;

    do {

        //
        // Expand the buffer size if needed.
        //

        if (BufferLengthNeeded > BufferLength) {
            free(Buffer);
            BufferLength = BufferLengthNeeded;
            Buffer = malloc(BufferLength * sizeof(WCHAR));
            if (Buffer == NULL) {
                Status = ERROR_OUTOFMEMORY;
                break;
            }
        }

        //
        // Try to get the next channel name.
        //

        if (EvtNextChannelPath(ChannelEnum,
                               BufferLength,
                               Buffer,
                               &BufferLengthNeeded) == FALSE) {
            Status = GetLastError();
        } else {
            Status = ERROR_SUCCESS;
            wprintf(L"%s\n", Buffer);
        }

    } while ((Status == ERROR_SUCCESS) ||
             (Status == ERROR_INSUFFICIENT_BUFFER));

    //
    // Free all resources associated with channel enumeration.
    //

    free(Buffer);

    EvtClose(ChannelEnum);

    //
    // When EvtNextChannelPath returns ERROR_NO_MORE_ITEMS, we have actually
    // iterated through all the channels and thus succeeded.
    //

    if (Status == ERROR_NO_MORE_ITEMS) {
        Status = ERROR_SUCCESS;
    }

    return Status;
}