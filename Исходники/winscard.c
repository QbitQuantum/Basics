LONG WINAPI SCardAddReaderToGroupA(SCARDCONTEXT context, LPCSTR reader, LPCSTR group)
{
    LONG retval;
    UNICODE_STRING readerW, groupW;

    if(reader) RtlCreateUnicodeStringFromAsciiz(&readerW,reader);
    else readerW.Buffer = NULL;
    if(group) RtlCreateUnicodeStringFromAsciiz(&groupW,group);
    else groupW.Buffer = NULL;

    retval = SCardAddReaderToGroupW(context, readerW.Buffer, groupW.Buffer);

    RtlFreeUnicodeString(&readerW);
    RtlFreeUnicodeString(&groupW);

    return retval;
}