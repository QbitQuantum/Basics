NET_API_STATUS NET_API_FUNCTION
NetapipBufferAllocate (
    IN DWORD ByteCount,
    OUT LPVOID * Buffer
    )

/*++

Routine Description:

    NetapipBufferAllocate is an old internal function that allocates buffers
    which the APIs will return to the application.  All calls to this routine
    should eventually be replaced by calls to NetApiBufferAllocate.

Arguments:

    (Same as NetApiBufferAllocate.)

Return Value:

    (Same as NetApiBufferAllocate.)

--*/

{
    return (NetApiBufferAllocate( ByteCount, Buffer ));

} // NetapipBufferAllocate