void WINAPI
redirect_RtlFreeOemString(OEM_STRING *string)
{
    if (is_dynamo_address((app_pc)string->Buffer)) {
        PEB *peb = get_peb(NT_CURRENT_PROCESS);
        redirect_RtlFreeHeap(peb->ProcessHeap, 0, (byte *)string->Buffer);
        memset(string, 0, sizeof(*string));
    } else
        RtlFreeOemString(string);
}