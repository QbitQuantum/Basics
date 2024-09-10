NTSTATUS
CsrOneTimeInitialize( VOID )
{
    NTSTATUS Status;

    //
    // Save away system information in a global variable
    //

    Status = NtQuerySystemInformation( SystemBasicInformation,
                                       &CsrNtSysInfo,
                                       sizeof( CsrNtSysInfo ),
                                       NULL
                                     );
    if (!NT_SUCCESS( Status )) {
        return( Status );
        }

    //
    // Use the process heap for memory allocation.
    //

    CsrHeap = RtlProcessHeap();

    CsrInitOnceDone = TRUE;

    return( STATUS_SUCCESS );
}