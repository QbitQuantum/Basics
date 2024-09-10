static void set_buffer(LPWSTR *buffer, LPCWSTR string)
{
    static const WCHAR empty_string[] = {0};
    IMalloc *malloc;
    ULONG cb;

    if (string == NULL)
        string = empty_string;
    CoGetMalloc(1, &malloc);

    cb = (strlenW(string) + 1)*sizeof(WCHAR);
    if (*buffer == NULL || cb > IMalloc_GetSize(malloc, *buffer))
        *buffer = IMalloc_Realloc(malloc, *buffer, cb);
    memcpy(*buffer, string, cb);
}