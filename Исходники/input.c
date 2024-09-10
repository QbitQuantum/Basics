/*++
 * @name RtlClipWaitForInput
 *
 * The RtlClipWaitForInput routine waits for input from an input device.
 *
 * @param hDriver
 *        Handle of the driver/device to get input from.
 *
 * @param Buffer
 *        Input buffer.
 *
 * @param BufferSize
 *        Size of the input buffer.
 *
 * @return STATUS_SUCCESS or error code from the read operation.
 *
 * @remarks This routine waits for input to be available.
 *
 *--*/
NTSTATUS
RtlClipWaitForInput(IN HANDLE hDriver,
                    IN PVOID Buffer,
                    IN OUT PULONG BufferSize)
{
    IO_STATUS_BLOCK Iosb;
    LARGE_INTEGER ByteOffset;
    NTSTATUS Status;

    //
    // Clean up the I/O Status block and read from byte 0
    //
    RtlZeroMemory(&Iosb, sizeof(Iosb));
    RtlZeroMemory(&ByteOffset, sizeof(ByteOffset));

    //
    // Try to read the data
    //
    Status = NtReadFile(hDriver,
                        hEvent,
                        NULL,
                        NULL,
                        &Iosb,
                        Buffer,
                        *BufferSize,
                        &ByteOffset,
                        NULL);

    //
    // Check if data is pending
    //
    if (Status == STATUS_PENDING)
    {
        //
        // Wait on the data to be read
        //
        Status = NtWaitForSingleObject(hEvent, TRUE, NULL);
    }

    //
    // Return status and how much data was read
    //
    *BufferSize = (ULONG)Iosb.Information;
    return Status;
}