/*NOTE: API IS A HACK */
VOID
WINAPI
BasepAnsiStringToHeapUnicodeString(IN LPCSTR AnsiString,
                                   OUT LPWSTR* UnicodeString)
{
    ANSI_STRING AnsiTemp;
    UNICODE_STRING UnicodeTemp;

    DPRINT("BasepAnsiStringToHeapUnicodeString\n");

    /* First create the ANSI_STRING */
    RtlInitAnsiString(&AnsiTemp, AnsiString);

    if (NT_SUCCESS(RtlAnsiStringToUnicodeString(&UnicodeTemp,
                   &AnsiTemp,
                   TRUE)))
    {
        *UnicodeString = UnicodeTemp.Buffer;
    }
    else
    {
        *UnicodeString = NULL;
    }
}