VOID FreeLargeString(PLARGE_UNICODE_STRING LargeString)
{
    union
    {
        ANSI_STRING     Ansi;
        UNICODE_STRING  Unicode;
    };

    if (LargeString->Buffer == NULL)
        return;

    if (LargeString->Ansi)
    {
        Ansi.Length         = LargeString->Length;
        Ansi.MaximumLength  = LargeString->MaximumLength;
        Ansi.Buffer         = LargeString->AnsiBuffer;

        RtlFreeAnsiString(&Ansi);
    }
    else
    {
        Unicode.Length          = LargeString->Length;
        Unicode.MaximumLength   = LargeString->MaximumLength;
        Unicode.Buffer          = LargeString->UnicodeBuffer;

        RtlFreeUnicodeString(&Unicode);
    }
}