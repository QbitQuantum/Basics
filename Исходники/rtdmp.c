void
print(
    PUNICODE_STRING  String
    )
{
    static  ANSI_STRING temp;
    static  char        tempbuffer[WORK_SIZE];

    temp.MaximumLength = WORK_SIZE;
    temp.Length = 0L;
    temp.Buffer = tempbuffer;

    RtlUnicodeStringToAnsiString(&temp, String, FALSE);
    printf("%s", temp.Buffer);
    return;
}