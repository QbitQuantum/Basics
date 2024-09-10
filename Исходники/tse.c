void
DumpWCharString(
    PWSTR String
    )
{
    UNICODE_STRING Unicode;
    ANSI_STRING AnsiString;

    RtlInitUnicodeString( &Unicode, String );
//    DbgPrint("*%Z*\n",&Unicode);
//    DbgPrint("  Length: %d\n", Unicode.Length);
//    DbgPrint("  Max: %d\n", Unicode.MaximumLength);
    RtlUnicodeStringToAnsiString( &AnsiString, &Unicode, TRUE );
    AnsiString.Buffer[AnsiString.Length]=0; // null terminate it
    printf("%s", AnsiString.Buffer );
    RtlFreeAnsiString( &AnsiString );
    return;
}