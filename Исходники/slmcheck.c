VOID
SrvReportCorruptSlmStatus (
    IN PUNICODE_STRING StatusFile,
    IN NTSTATUS Status,
    IN ULONG Offset,
    IN ULONG Operation,
    IN PSESSION Session
    )
{
    NTSTATUS status;
    ANSI_STRING ansiStatusFile;
    TIME time;
    TIME_FIELDS timeFields;

    status = RtlUnicodeStringToAnsiString( &ansiStatusFile, StatusFile, TRUE );
    ASSERT( NT_SUCCESS(status) );

    KeQuerySystemTime( &time );
    RtlTimeToTimeFields( &time, &timeFields );

    //
    // Send a broadcast message.
    //

    SrvSendSecondClassMailslot(
        ansiStatusFile.Buffer,
        StatusFile->Length + 1,
        "NTSLMCORRUPT",
        "SlmCheck"
        );

    SrvPrint4( "\n*** CORRUPT STATUS FILE DETECTED ***\n"
                "      File: %Z\n"
                "      Status: 0x%lx, Offset: 0x%lx, detected on %s\n",
                &ansiStatusFile, Status, Offset,
                Operation == SLMDBG_CLOSE ? "close" : "rename" );
    SrvPrint3( "      Workstation: %wZ, User: %wZ, OS: %wZ\n",
                &Session->Connection->ClientMachineNameString,
                &Session->UserName,
                &SrvClientTypes[Session->Connection->SmbDialect] );
    SrvPrint3( "      Current time: %d-%d-%d ",
                timeFields.Month, timeFields.Day, timeFields.Year );
    SrvPrint3( "%d:%d:%d\n",
                timeFields.Hour, timeFields.Minute, timeFields.Second );

    RtlFreeAnsiString( &ansiStatusFile );

    return;

} // SrvReportCorruptSlmStatus