NTSTATUS
NtDisplayString(
    IN PUNICODE_STRING String
    )

/*++

Routine Description:

    This service calls the HAL to display a string on the console.

    The caller must have SeTcbPrivilege to display a message.

Arguments:

    String - A pointer to the string that is to be displayed.

Return Value:

    !NT_SUCCESS - The operation failed or the caller did not have appropriate
        priviledges.

--*/

{
    KPROCESSOR_MODE PreviousMode;
    UNICODE_STRING CapturedString;
    PUCHAR StringBuffer = NULL;
    PUCHAR AnsiStringBuffer = NULL;
    STRING AnsiString;

    //
    // Check to determine if the caller has the privilege to make this
    // call.
    //

    PreviousMode = KeGetPreviousMode();
    if (!SeSinglePrivilegeCheck(SeTcbPrivilege, PreviousMode)) {
        return STATUS_PRIVILEGE_NOT_HELD;
    }

    try {

        //
        // If the previous mode was user, then check the input parameters.
        //

        if (PreviousMode != KernelMode) {

            //
            // Probe and capture the input unicode string descriptor.
            //

            CapturedString = ProbeAndReadUnicodeString(String);

            //
            // If the captured string descriptor has a length of zero, then
            // return success.
            //

            if ((CapturedString.Buffer == 0) ||
                (CapturedString.MaximumLength == 0)) {
                return STATUS_SUCCESS;
            }

            //
            // Probe and capture the input string.
            //
            // N.B. Note the length is in bytes.
            //

            ProbeForRead(
                CapturedString.Buffer,
                CapturedString.MaximumLength,
                sizeof(UCHAR)
                );

            //
            // Allocate a non-paged string buffer because the buffer passed to
            // HalDisplay string must be non-paged.
            //

            StringBuffer = ExAllocatePoolWithTag(NonPagedPool,
                                                  CapturedString.MaximumLength,
                                                  'grtS');

            if ( !StringBuffer ) {
                return STATUS_NO_MEMORY;
            }

            RtlMoveMemory(StringBuffer,
                          CapturedString.Buffer,
                          CapturedString.MaximumLength);

            CapturedString.Buffer = (PWSTR)StringBuffer;

            //
            // Allocate a string buffer for the ansi string.
            //

            AnsiStringBuffer = ExAllocatePoolWithTag(NonPagedPool,
                                                 CapturedString.MaximumLength,
                                                 'grtS');


            if (AnsiStringBuffer == NULL) {
                ExFreePool(StringBuffer);
                return STATUS_NO_MEMORY;
            }

            AnsiString.MaximumLength = CapturedString.MaximumLength;
            AnsiString.Length = 0;
            AnsiString.Buffer = AnsiStringBuffer;

            //
            // Transform the string to ANSI until the HAL handles unicode.
            //

            RtlUnicodeStringToOemString(
                &AnsiString,
                &CapturedString,
                FALSE
                );

        } else {

            //
            // Allocate a string buffer for the ansi string.
            //

            AnsiStringBuffer = ExAllocatePoolWithTag(NonPagedPool,
                                                     String->MaximumLength,
                                                     'grtS');


            if (AnsiStringBuffer == NULL) {
                return STATUS_NO_MEMORY;
            }

            AnsiString.MaximumLength = String->MaximumLength;
            AnsiString.Length = 0;
            AnsiString.Buffer = AnsiStringBuffer;

            //
            // We were in kernel mode; just transform the original string.
            //

            RtlUnicodeStringToOemString(
                &AnsiString,
                String,
                FALSE
                );
        }

        HalDisplayString( AnsiString.Buffer );

        //
        // Free up the memory we used to store the strings.
        //

        if (PreviousMode != KernelMode) {
            ExFreePool(StringBuffer);
        }

        ExFreePool(AnsiStringBuffer);

    } except(EXCEPTION_EXECUTE_HANDLER) {
        if (StringBuffer != NULL) {
            ExFreePool(StringBuffer);
        }

        return GetExceptionCode();
    }

    return STATUS_SUCCESS;
}