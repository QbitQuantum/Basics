NTSTATUS
NTAPI
NtDisplayString(IN PUNICODE_STRING DisplayString)
{
    OEM_STRING OemString;

    /* Convert the string to OEM and display it */
    RtlUnicodeStringToOemString(&OemString, DisplayString, TRUE);
    InbvDisplayString(OemString.Buffer);
    RtlFreeOemString(&OemString);

    /* Return success */
    return STATUS_SUCCESS;
}