BOOLEAN
RtlCreateUnicodeStringFromAsciiz(
    OUT PUNICODE_STRING DestinationString,
    IN PCSZ SourceString
    )
{
    ANSI_STRING AnsiString;
    NTSTATUS Status;

    RtlInitAnsiString( &AnsiString, SourceString );
    Status = RtlAnsiStringToUnicodeString( DestinationString, &AnsiString, TRUE );
    if (NT_SUCCESS( Status )) {
        return( TRUE );
        }
    else {
        return( FALSE );
        }
}