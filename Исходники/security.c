/******************************************************************************
 * ConvertSidToStringSidW [ADVAPI32.@]
 */
BOOL WINAPI ConvertSidToStringSidW(PSID sid, LPWSTR* stringSid)
{
    NTSTATUS ret;
    UNICODE_STRING str = { 0, 0, NULL };
    ret = RtlConvertSidToUnicodeString(&str, sid, TRUE);

    if (ret == STATUS_NO_MEMORY)
    {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FALSE;
    }

    /* FIXME: error codes for other ret values,
     * which don't exist in NTDLL yet */

    *stringSid = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, (str.Length+1)*sizeof(WCHAR));
    lstrcpynW(*stringSid, str.Buffer, str.Length + 1);
    RtlFreeUnicodeString(&str);

    return TRUE;
}