INT
APIENTRY
EnumProtocolsA (
    IN     LPINT           lpiProtocols,
    IN OUT LPVOID          lpProtocolBuffer,
    IN OUT LPDWORD         lpdwBufferLength
    )

/*++

Routine Description:

Arguments:

Return Value:

--*/

{
    INT count;
    INT i;
    PPROTOCOL_INFO protocolInfo;
    UNICODE_STRING unicodeString;
    ANSI_STRING ansiString;

    //
    // Get the protocol information in Unicode format.
    //

    count = EnumProtocolsW( lpiProtocols, lpProtocolBuffer, lpdwBufferLength );
    if ( count <= 0 ) {
        return count;
    }

    //
    // Convert each of the Unicode protocol names to Ansi.
    //

    protocolInfo = lpProtocolBuffer;

    for ( i = 0; i < count; i++ ) {

        RtlInitUnicodeString( &unicodeString, protocolInfo[i].lpProtocol );
        ansiString.MaximumLength = unicodeString.MaximumLength;
        ansiString.Buffer = (PCHAR)unicodeString.Buffer;
        RtlUnicodeStringToAnsiString( &ansiString, &unicodeString, FALSE );
    }

    return count;

} // EnumProtocolsA