NTSTATUS
LsapInstallationPause( VOID )


/*++

Routine Description:

    This function checks to see if the system is in an
    installation state.  If so, it suspends further initialization
    until the installation state is complete.

    Installation state is signified by the existance of a well known
    event.


Arguments:

    None.

Return Value:


        STATUS_SUCCESS - Proceed with initialization.

        Other status values are unexpected.

--*/

{


    NTSTATUS NtStatus, TmpStatus;
    HANDLE InstallationEvent;
    OBJECT_ATTRIBUTES EventAttributes;
    UNICODE_STRING EventName;


    //
    // If the following event exists, it is an indication that
    // installation is in progress and that further security
    // initialization should be delayed until the event is
    // signalled.  This is expected to be a NOTIFICATION event.
    //

    RtlInitUnicodeString( &EventName, L"\\INSTALLATION_SECURITY_HOLD");
    InitializeObjectAttributes( &EventAttributes, &EventName, 0, 0, NULL );

    NtStatus = NtOpenEvent(
                   &InstallationEvent,
                   SYNCHRONIZE,
                   &EventAttributes
                   );

    if ( NT_SUCCESS(NtStatus)) {

        //
        // The event exists - installation created it and will signal it
        // when it is ok to proceed with security initialization.
        //

        LsapSetupWasRun = TRUE;

        //
        // Installation code is responsible for deleting the event after
        // signalling it.
        //

        NtStatus = NtWaitForSingleObject( InstallationEvent, TRUE, 0 );
        TmpStatus = NtClose( InstallationEvent );
        ASSERT(NT_SUCCESS(TmpStatus));
    } else {
        NtStatus = STATUS_SUCCESS; // Indicate everything is as expected
    }

    return(NtStatus);

}