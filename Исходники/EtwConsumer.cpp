ULONG
GetFormattedEventMessage(
    __in PTRACE_EVENT_INFO EventInfo,
    __in PWSTR* RenderItems,
    __out PWSTR* FormattedMessage
)

/*++

Routine Description:

    This routine formats the original event message with the string
    values obtained in the dumping process.

Arguments:

    EventInfo - Supplies the structure containing the original event message.

    RenderItems - Supplies an array of strings for the formatted toplevel properties.

    FormattedMessage - Receives the formatted string.

Return Value:

    ERROR_SUCCES - The formatting was successful or there was no data to format.

    Win32 error code - FormatMessageW() failed.

--*/

{
    ULONG Status = ERROR_SUCCESS;

    //
    // Get the original message (not the formatted event message), which may have
    // references to the payload values of some of the top-level properties.
    //

    PWSTR EventMessage = TEI_EVENT_MESSAGE(EventInfo);

    if (EventMessage != NULL && RenderItems != NULL) {
        ULONG Count = 0;
        Count = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                               FORMAT_MESSAGE_FROM_STRING |
                               FORMAT_MESSAGE_ARGUMENT_ARRAY,
                               (LPCVOID)EventMessage,
                               (ULONG)-1,
                               0,
                               (LPWSTR)FormattedMessage,
                               0,
                               (va_list*)RenderItems);

        if (Count == 0) {
            Status = GetLastError();
        }
    }
    return Status;
}